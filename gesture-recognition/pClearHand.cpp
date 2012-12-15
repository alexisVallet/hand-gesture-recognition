/* 
 * This operator si in charge of hand cleaning.
 * After execution, scattered pixels are deleted
 * And depending on the precision, we can delelete some imperfections.
 * The operator is executed LOOP times.
 */
#ifndef PCLEARHAND_CPP
#define	PCLEARHAND_CPP
#include "pClearHand.h"

using namespace cv;

inline void testBLACK(Mat & ims, cv::Point2d& cursor, int & counter)
{
    if(ims.data[(int)(cursor.y*ims.cols+cursor.x)] == _BLACK)
        counter++;
}

// This function deletes scatters pixels. It cleans and erodes an hand.
void clearHand(Mat& imd)
{
    cv::Point2d p;
    for(int i=0; i< LOOP ; i++)
    {
        for (p.y = 0 ; p.y < imd.cols ; p.y++)
        {
            for(p.x = 0 ; p.x <imd.rows ; p.x++)
            {
                // Deletes white scatters pixels
                if( imd.data[(int)(p.y*imd.cols+p.x)] == _WHITE)
                {
                    
                    Point2d cursor (p);
                    int black_connex = 0;

                    // bottom left pixel
                    cursor.x--;
                    cursor.y--;
                    testBLACK(imd,cursor,black_connex);
                    // bottom center pixel
                    cursor.x++;
                    testBLACK(imd,cursor,black_connex);
                    // bottom right pixel
                    cursor.x++;
                    testBLACK(imd,cursor,black_connex);
                    // right center pixel
                    cursor.y++;
                    testBLACK(imd,cursor,black_connex);
                    // top right pixel
                    cursor.y++;
                    testBLACK(imd,cursor,black_connex);
                    // top centerpixel
                    cursor.x--;
                    testBLACK(imd,cursor,black_connex);
                    // top left pixel
                    cursor.x--;
                    testBLACK(imd,cursor,black_connex);
                    // left center pixel
                    cursor.y--;
                    testBLACK(imd,cursor,black_connex);
                    
                    imd.data[(int)(p.y*imd.cols+p.x)] = (black_connex >= PRECISION) ? _BLACK : _WHITE;
                }
                else
                    imd.data[(int)(p.y*imd.cols+p.x)] = _BLACK;
 
             }
        }      
    }
//    imshow("cleaned image", imd );
}

// Test color of a given pixel
inline void testWHITE(Mat & ims, cv::Point2d& cursor, int & counter) {
    if(ims.data[(int)(cursor.y*ims.cols+cursor.x)] == _WHITE)
        counter++;
}

// This function deletes scatters pixels on a 256 Grey Levels Pixels.
// This function should correct segmentation failing on few images of Third Group of images.
void clearHandBeforeBinarization(Mat& imd) {
    cv::Point2d p;
    for(int i=0; i< LOOP ; i++)
    {
        for (p.y = 0 ; p.y < imd.cols ; p.y++)
        {
            for(p.x = 0 ; p.x <imd.rows ; p.x++)
            {
                // Deletes white scatters pixels
                if( imd.data[(int)(p.y*imd.cols+p.x)] != _WHITE)
                {
                    
                    Point2d cursor (p);
                    int white_connex = 0;

                    // bottom left pixel
                    cursor.x--;
                    cursor.y--;
                    testWHITE(imd,cursor,white_connex);
                    // bottom center pixel
                    cursor.x++;
                    testWHITE(imd,cursor,white_connex);
                    // bottom right pixel
                    cursor.x++;
                    testWHITE(imd,cursor,white_connex);
                    // right center pixel
                    cursor.y++;
                    testWHITE(imd,cursor,white_connex);
                    // top right pixel
                    cursor.y++;
                    testWHITE(imd,cursor,white_connex);
                    // top centerpixel
                    cursor.x--;
                    testWHITE(imd,cursor,white_connex);
                    // top left pixel
                    cursor.x--;
                    testWHITE(imd,cursor,white_connex);
                    // left center pixel
                    cursor.y--;
                    testWHITE(imd,cursor,white_connex);
                    
                    imd.data[(int)(p.y*imd.cols+p.x)] = (white_connex >= PRECISION) ? _WHITE : _BLACK;
                }
                else
                    imd.data[(int)(p.y*imd.cols+p.x)] = _WHITE;
 
             }
        }      
    }

}

#endif
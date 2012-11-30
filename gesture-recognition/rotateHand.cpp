
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include "HandDirection.h"
#include "utilsFunctions.h"

#include "rotateHand.h"

using namespace cv;
using namespace std;


/*int main()
 {
        Mat hand = extractHandFromBMPFile("F:/iut/utbm/S5/projetIN52-54/ClassImages/2/0b1.bmp");
 *      // le 255 correspond à la valeur des pixels constitutifs de la main dans l'image source
        Mat rotatedHand = redressHandFromBinarySegmentedImage(hand, 255);
 }**/



/**
 * translate image
 * @param x = cols    
 * @param y = rows
 * @param src
 * @param dest
 */
void translate(int x, int y, const Mat &src, Mat &dest)
{
    int chanel =1;
    int w = src.cols;
    int h = src.rows;
    
    /*cout << "x=" << x << " y="<< y << endl;
    cout << "dest.cols=" << dest.cols << " dest.rows="<< dest.rows << endl;
    cout << "idMax = " << dest.cols*dest.rows << endl;*/
    
    //initialize dest with black
    uchar * ptr = dest.datastart;
    while(ptr!= dest.datalimit)
    {
        *(ptr++) = 0;
    }
    
    for(int ligne=0; ligne<src.rows; ligne++)
    {
        for(int col=0; col<src.cols; col++)
        {
            dest.data[(ligne+y)*dest.cols*chanel + (col+x)*chanel] = src.data[ligne*w*chanel+col*chanel];
        }
    }    
    /*namedWindow("translated");
    imshow("translated", dest);*/
}



//effectue une rotation de l'image
/**
 * 
 * @param segmentedHand l'image à rotater
 * @param rotatedHand   l'image rotatée
 * @param angle         l'angle en radian
 */
void rotateHand(const Mat &segmentedHand, Mat &rotatedHand, double angle) 
{
    int diag = ceil(sqrt(segmentedHand.rows*segmentedHand.rows + segmentedHand.cols*segmentedHand.cols));
    Mat intermediaire = Mat_<unsigned char>(diag+1, diag+1);
    translate( (diag-segmentedHand.cols)/2, (diag-segmentedHand.rows)/2, segmentedHand, intermediaire);
    

    Mat rotation = getRotationMatrix2D(Point(diag/2, diag/2), angle*180.0/M_PI, 1);
    warpAffine(intermediaire, rotatedHand, rotation, Size(diag,diag));
}


//prends en entrée la main segmentée, avec les px de la main valant handPxValue
Mat redressHandFromBinarySegmentedImage(Mat hand, int handPxValue)
{
    //get angle from source image
     pair<Mat,Mat> directions = handDirectionWithPixelValue(hand, handPxValue);
    cout<< directions.first.at<float>(0,0) << " " << directions.first.at<float>(0,1) <<endl;
    
    float cos = directions.first.at<float>(0,0);
    float sin = directions.first.at<float>(0,1);
    
    float angle = acos(cos)* 180.0 / M_PI;
    
    if(sin<0) 
        angle *= -1;

    cout << "angle = " << angle << endl;
    
    namedWindow("handaredresser", CV_WINDOW_AUTOSIZE );
    imshow("handaredresser", hand );
    
    //rotate hand
    Mat rotated;
    rotateHand(hand, rotated, -angle/180*M_PI);
    
    namedWindow("rotated", CV_WINDOW_AUTOSIZE );
    imshow("rotated", rotated );
    
    Mat reboundedHand = extractHandFromBinarizedMat(rotated);
    
    namedWindow("final", CV_WINDOW_AUTOSIZE );
    imshow("final", reboundedHand );
    
    return rotated;
}

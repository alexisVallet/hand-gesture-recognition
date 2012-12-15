/* 
 * File:   Segmentation.cp
 * Author: Quentin
 *
 * Created on 1 décembre 2012, 15:20
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include "pClearHand.h"
#include "convert.h"
#include "Pfisher.h"
#include "Segmentation.h"
#include "utilsFunctions.h"

#define THRESH_BINARIZATION 0
#define NB_CLASS_FISHER 5
#define SHOW_IMAGES 1
#define SAVE_IMAGES 0

using namespace cv;
using namespace pandore;

/* 
 * Fisher Thresholding and
 * Segment an image from source and save it on destination
 */
void Segment(const Mat& source, Mat& destination) {

    
    imwrite( "./runFolder/imgresult/source.jpg", source );
    
    Img2duc imgpan = _MatToPan(source);
    Img2duc fished = Img2duc(imgpan.Size());
    
    PFisher_(imgpan, fished, Uchar(0), long(NB_CLASS_FISHER));
    fished.SaveFile("./runFolder/imgresult/fished.pan");
        
    Mat MatFished = _PanToMat(fished);
    if(SHOW_IMAGES) imshow("Fished", MatFished);
    if(SAVE_IMAGES)imwrite( "./runFolder/imgresult/fished.jpg", MatFished );
    
    Mat MatEqualized;
    equalizeHist(MatFished, MatEqualized);
    normalize(MatEqualized);
    if(SHOW_IMAGES) imshow("Equalized", MatEqualized);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/equalized.jpg", MatEqualized );
    
    Mat segmented;
    threshold( MatEqualized, segmented, THRESH_BINARIZATION, 255, THRESH_BINARY);
    if(SHOW_IMAGES) imshow("Segmented", segmented);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/segmented.jpg", segmented );    
    
    inverse(segmented);
    if(SHOW_IMAGES) imshow("Inversed Segmented", segmented);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/inversed.jpg", segmented );    
    
    clearHand(segmented);
    if(SHOW_IMAGES) imshow("Cleaned", segmented);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/cleaned.jpg", segmented );    
    
    destination = segmented;
}


/* This function is similar to Segment function. 
 * It clean a hand before Fisher Algorithm application and binarization.
 */
void specialSegmentation(const Mat& source, Mat& destination) 
{
    Mat cleanedHandBeforeBinarization(source);
    clearHandBeforeBinarization(cleanedHandBeforeBinarization);
        
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/source.jpg", source );
    
    Img2duc imgpan = _MatToPan(cleanedHandBeforeBinarization);
    Img2duc fished = Img2duc(imgpan.Size());
    
    PFisher_(imgpan, fished, Uchar(0), long(NB_CLASS_FISHER));
    if(SAVE_IMAGES) fished.SaveFile("./runFolder/imgresult/fished.pan");
        
    Mat MatFished = _PanToMat(fished);
    if(SHOW_IMAGES) imshow("Fished", MatFished);
    if(SAVE_IMAGES)imwrite( "./runFolder/imgresult/fished.jpg", MatFished );
    
    Mat MatEqualized;
    equalizeHist(MatFished, MatEqualized);
    normalize(MatEqualized);
    if(SHOW_IMAGES) imshow("Equalized", MatEqualized);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/equalized.jpg", MatEqualized );
    
    Mat segmented;
    threshold( MatEqualized, segmented, THRESH_BINARIZATION, 255, THRESH_BINARY);
    if(SHOW_IMAGES) imshow("Segmented", segmented);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/segmented.jpg", segmented );    
    
    inverse(segmented);
    if(SHOW_IMAGES) imshow("Inversed Segmented", segmented);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/inversed.jpg", segmented );    
    
    clearHand(segmented);
    if(SHOW_IMAGES) imshow("Cleaned", segmented);
    if(SAVE_IMAGES) imwrite( "./runFolder/imgresult/cleaned.jpg", segmented );    
    
    destination = segmented;
}

void inverse(Mat& matrix) {
    for(int i=0; i<matrix.cols*matrix.rows; i++)
        matrix.data[i] = (matrix.data[i] == 0) ? 255 : 0;
}

void normalize(Mat& ims)
{    
    unsigned int min (0-1), max(0), diff;
    
    // Min Max Extraction
    for(int i=0; i<ims.cols*ims.rows ; i++) {
        if(ims.data[i] < min)
            min = ims.data[i];
        if(ims.data[i] > max)
            max = ims.data[i];
    }
    
    diff = max - min;
    
    // Normalization
    for(int i=0; i<ims.cols*ims.rows ; i++) {
        if(ims.data[i] == min)
            ims.data[i] = 0;
        else {
            int delta = ims.data[i] - min;
            ims.data[i] = delta * 255 / diff;
        }
    }
}

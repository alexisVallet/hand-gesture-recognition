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

#define SEUIL 30

using namespace cv;
using namespace pandore;

/* 
 * Fisher Thresholding and
 * Segment an image from source and save it on destination
 */
void Segment(const Mat& source, Mat& destination, bool show) {
    Img2duc imgpan = _MatToPan(source);
    Img2duc fished = Img2duc(imgpan.Size());
    
    PFisher_(imgpan, fished, Uchar(0), long(5));
//    fished.SaveFile(panfile.c_str());
        
    Mat MatFished = _PanToMat(fished);
    if(show) imshow("Fished", MatFished);
        
    Mat MatEqualized;
    equalizeHist(MatFished, MatEqualized);
    if(show) imshow("Equalized", MatEqualized);
    
    Mat segmented;
    threshold( MatEqualized, segmented, SEUIL, 255, THRESH_BINARY );
    if(show) imshow("Segmented", segmented);

    inverse(segmented);
//    
//    Mat cleaned(segmented);
//    if(show) imshow("Inversed", segmented);
//    
    clearHand(segmented);
    if(show) imshow("Cleaned", segmented);
    
    destination = segmented;
}

void inverse(Mat& matrix) {
    for(int i=0; i<matrix.cols*matrix.rows; i++)
        matrix.data[i] = (matrix.data[i] == 0) ? 255 : 0;
}
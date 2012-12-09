/* 
 * File:   SegmentationTest.cpp
 * Author: Quentin
 *
 * Created on 01 nov. 2012, 15:27:29
 */

#include <stdlib.h>
#include "pandore.h"
#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include "convert.h"
#include "utilsFunctions.h"
#include "Pfisher.h"
#include "Segmentation.h"

using namespace cv;
using namespace pandore;
using namespace std;

void loadAndSegment(const char * filename) {
    
    Mat img = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
    Mat des; 

    // Segmentation
    Segment(img, des);

    imshow("Equalized", des);
    
    waitKey();
}

int main(int argc, char** argv) {
   
    loadAndSegment("./runFolder/img/1.bmp");
    loadAndSegment("./runFolder/img/2.bmp");
    loadAndSegment("./runFolder/img/3.bmp");
    loadAndSegment("./runFolder/img/4.bmp");
    loadAndSegment("./runFolder/img/5.bmp");
    loadAndSegment("./runFolder/img/6.bmp");
    loadAndSegment("./runFolder/img/7.bmp");
    loadAndSegment("./runFolder/img/8.bmp");
    loadAndSegment("./runFolder/img/9.bmp");
    loadAndSegment("./runFolder/img/10.bmp");
    loadAndSegment("./runFolder/img/11.bmp");
    loadAndSegment("./runFolder/img/12.bmp");
    loadAndSegment("./runFolder/img/13.bmp");
    loadAndSegment("./runFolder/img/14.bmp");
    loadAndSegment("./runFolder/img/15.bmp");
    loadAndSegment("./runFolder/img/16.bmp");
    
    return (EXIT_SUCCESS);
}
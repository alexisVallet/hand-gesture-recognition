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

void loadAndSegment(const char * filename, bool cleanBefore) {
    
    Mat img = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
    Mat des; 

    // Segmentation
    if(cleanBefore)
        specialSegmentation(img, des);
    else
        Segment(img, des);

    imshow("Equalized", des);
    
    waitKey();
}

int main(int argc, char** argv) {
   
    loadAndSegment("./runFolder/img/groupe3/1.bmp", false);    
    loadAndSegment("./runFolder/img/groupe3/2.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/3.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/4.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/5.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/6.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/7.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/8.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/9.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/10.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/11.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/12.bmp", false);
    
//    loadAndSegment("./runFolder/img/groupe3/13.bmp", false);
//    loadAndSegment("./runFolder/img/groupe3/13.bmp", true);
//    loadAndSegment("./runFolder/img/groupe3/14.bmp", false);
//    loadAndSegment("./runFolder/img/groupe3/14.bmp", true);
//    loadAndSegment("./runFolder/img/groupe3/15.bmp", false);
//    loadAndSegment("./runFolder/img/groupe3/15.bmp", true);
//    loadAndSegment("./runFolder/img/groupe3/16.bmp", false);
//    loadAndSegment("./runFolder/img/groupe3/16.bmp", true);

    loadAndSegment("./runFolder/img/groupe3/17.bmp", false);
    loadAndSegment("./runFolder/img/groupe3/18.bmp", false);
    
    return (EXIT_SUCCESS);
}
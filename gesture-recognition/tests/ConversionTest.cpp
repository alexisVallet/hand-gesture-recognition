/* 
 * File:   ConversionTest.cpp
 * Author: Quentin
 *
 * Created on 26 nov. 2012, 19:11:29
 */

#include <stdlib.h>
#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include "convert.hpp"
#include "utilsFunctions.h"
#include "Pfisher.h"
#include "PHistogramEqualization.h"

using namespace cv;
using namespace pandore;
using namespace std;

int main(int argc, char** argv) {

    string ymlfile = "./runFolder/img/1.yml";
    string panfile = "./runFolder/imgresult/1.pan";
     
    IplImage * imgyml = loadYml(ymlfile.c_str());
    Mat img = IplToMat(*imgyml);
    Img2duc imgpan = _MatToPan(img, panfile);
    Img2duc fished = Img2duc(imgpan.Size());
    
    PFisher_(imgpan, fished, Uchar(0), long(5));
//    fished.SaveFile(panfile.c_str());
        
    Mat MatFished = _PanToMat(fished);
    imshow("Fished", MatFished);
        
    Mat MatEqualized;
    equalizeHist(MatFished, MatEqualized);
    imshow("Equalized", MatEqualized);
    
    Mat segmented;
    threshold( MatEqualized, segmented, 10, 255, THRESH_BINARY );
    imshow("Segmented", segmented);
      
    waitKey(0);
    
    return (EXIT_SUCCESS);
}
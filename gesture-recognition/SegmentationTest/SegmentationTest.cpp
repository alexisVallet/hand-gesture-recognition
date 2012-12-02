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

int main(int argc, char** argv) {

    string ymlfile = "./runFolder/img/1.yml";
    string panfile = "./runFolder/imgresult/1.pan";
     
    IplImage * imgyml = loadYml(ymlfile.c_str());
    Mat img = IplToMat(*imgyml);
    Mat des;

    // Segmentation
    Segment(img, des, true);
    
    waitKey(0);
    
    return (EXIT_SUCCESS);
}
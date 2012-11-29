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
#include "LoadYML.h"

using namespace cv;
using namespace pandore;
using namespace std;

int main(int argc, char** argv) {

    string ymlfile = "C:/Users/Alexis/Documents/Dev/IN5x/in5x-gesture-recognition/gesture-recognition/runFolder/img/1.yml";
    string panfile = "C:/Users/Alexis/Documents/Dev/IN5x/in5x-gesture-recognition/gesture-recognition/runFolder/imgresult/1.pan";
     
    IplImage * imgyml = loadYml(ymlfile.c_str());
    Mat img = IplToMat(*imgyml);
    cvNamedWindow("test",1);
    imshow("test", img);
    Img2duc imgpan = _MatToPan(img, panfile);
//    imgpan.SaveFile(panfile.c_str());
    
//    system("C:/Program Files (x86)/pandore/bin/pvisu.exe "+"panfile");
    
    waitKey(0);
    
    return (EXIT_SUCCESS);
}
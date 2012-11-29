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

    string ymlfile = "./runFolder/img/1.yml";
    string panfile = "./runFolder/imgresult/1.pan";
     
    IplImage * imgyml = loadYml(ymlfile.c_str());
    Mat img = IplToMat(*imgyml);
//    cvNamedWindow("test",1);
//    imshow("test", img);
    cout << "image loaded" << endl;
    Img2duc imgpan = _MatToPan(img, panfile);
    imgpan.SaveFile(panfile.c_str());
    cout << "Avant creation nouvelle matrice" << endl;
    Mat new_mat = _PanToMat(imgpan);
    cout << "Apres creation nouvelle matrice" << endl << "Affichage : ";
    imshow("test", img);
    
//    system("pvisu "+panfile);
    
    waitKey(0);
    
    return (EXIT_SUCCESS);
}
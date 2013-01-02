/* 
 * File:   ConvexityClassifier_TEST.cpp
 * Author: ALEXANDRE-BARFF
 *
 * Created on 30 nov. 2012, 23:21:48
 */

#include <stdlib.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ConvexityClassifier.h"
#include "utilsFunctions.h"
#include "Segmentation.h"

using namespace cv;
using namespace std;

/*
 * Simple C++ Test Suite
 */
//extrait la main à partir du nom de fichier BMP passé en paramètre
//chargement de l'image, segmentation quentin, détection des bounds de la main, extraction de la main
Mat AextractHandFromBMPFile(string filename)
{
    Mat img = imread( filename, CV_LOAD_IMAGE_GRAYSCALE );
    //img = greyscale(img);
    
    
    //SEUIL A SETTER
    //binarize(img, 90, revertBinarize);
    Mat hand; 
    // Segmentation
    Segment(img, hand);
    hand.dims=0;//tres important, trop de pb à cause de ces conneries de channel
    
    string windowName = "BINARIZED" ;
    windowName+=filename;
//    namedWindow(windowName.c_str(), CV_WINDOW_AUTOSIZE );
//    imshow(windowName.c_str(), hand );
//waitKey(0);

    int xMin, xMax, yMin, yMax;   
    calculBounds(hand, xMin, xMax, yMin, yMax);
    xMax+=2;
    yMax+=2;
    xMin-=2;
    yMin-=2;
    int sx = xMax - xMin;
    int sy = yMax - yMin;
    //extraction of the hand
    Mat hand2 = Mat_<unsigned char>(sy, sx);
    hand2.dims=0;//tres important, trop de pb à cause de ces conneries de channel

    extractSubimageFromBounds(hand, hand2, xMin, xMax, yMin, yMax);
    return hand;
}

int main(int argc, char** argv) {
    
    ConvexityClassifier classifier;
    Mat image = AextractHandFromBMPFile("./runFolder/7.bmp");
    
    //imshow("TEST",image);
    //classifier.resizeCol(image,0,(double)0);
    
    classifier.numberOfFingers(image);
    
    waitKey(0);
    
    return (EXIT_SUCCESS);
}

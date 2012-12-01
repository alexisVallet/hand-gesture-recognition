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

using namespace cv;
using namespace std;

/*
 * Simple C++ Test Suite
 */


void ShowConvexityPoints(string filepath) {
    
    Mat out;//,contours_points,polygon;
    vector<Point> polygon;
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours_points;
    Mat segmentedHandRGB = imread(filepath);
    imshow(filepath, segmentedHandRGB);
    
    /*CONVERSION FORMAT: Grayscale */
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    
    /*Computing Convexity Classifier*/
    medianBlur(segmentedHandGray,out,15);
    
    /*Looking for Contours Points*/
    findContours( out, contours_points, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    
    /*Approximation of Hands Contours by Polygon*/
    approxPolyDP(contours_points,polygon,5,true);
    
    /*Affichage*/
    namedWindow(filepath);
    imshow(filepath,out);
    
}

int main(int argc, char** argv) {
    
    ShowConvexityPoints("./runFolder/test-segmented-2.bmp");
    waitKey(0);
    
    return (EXIT_SUCCESS);
}


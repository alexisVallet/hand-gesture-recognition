/* 
 * File:   rotateHandTest.cpp
 * Author: Alexis
 *
 * Created on 30 nov. 2012, 08:30:16
 */
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "rotatehand.h"
#include "crop.h"
#include "utilsFunctions.h"

/*
 * Simple C++ Test Suite
 */

int main(int argc, char** argv) {
    Mat segmentedHandRGB = imread("./runFolder/test-segmented-5-2-wristless.bmp");
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat segmentedHandBin = segmentedHandGray / 255;
    Mat rotatedHand;
    Mat croppedRotatedHand;
    
    rotateHand(segmentedHandBin, rotatedHand, M_PI/3);
    crop(rotatedHand, croppedRotatedHand);
    
    namedWindow("Original");
    imshow("Original", segmentedHandBin * 255);
    namedWindow("Rotated");
    imshow("Rotated", croppedRotatedHand * 255);
    waitKey(0);

    return (EXIT_SUCCESS);
}


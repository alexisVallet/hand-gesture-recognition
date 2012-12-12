/* 
 * File:   HandSideDetectionTest.cpp
 * Author: Alexis
 *
 * Created on 12 déc. 2012, 19:24:04
 */

#include <stdlib.h>
#include <iostream>

#include "HandSideDetection.h"
#include "rotateHand.h"
#include "Symmetry.h"

void showHandSide(Mat &segmentedHandRGB) {
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat segmentedHandBin = segmentedHandGray / 255;
    Mat direction = handDirection(segmentedHandBin).second;
    float angle = atan(direction.at<float>(0,1)/direction.at<float>(0,0));
    Mat rotatedHand;
    rotateHand(segmentedHandBin, rotatedHand, angle);
    
    cout<<"this image has side "<<detectHandSide(rotatedHand, 1)<<endl;
}

int main(int argc, char** argv) {
    Mat five = imread("./runFolder/test-segmented-5-2-wristless.bmp");
    Mat flippedFive;
    verticalSymmetry(five, flippedFive);
    showHandSide(five);
    showHandSide(flippedFive);
    
    return (EXIT_SUCCESS);
}


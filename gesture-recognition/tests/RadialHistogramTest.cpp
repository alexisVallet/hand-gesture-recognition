/* 
 * File:   RadialHistogramTest.cpp
 * Author: Alexis
 *
 * Created on 26 nov. 2012, 09:30:33
 */

#include <stdlib.h>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "RadialHistogram.h"
#include "HandSideDetection.h"
#include "Symmetry.h"
#include "utilsFunctions.h"

/*
 * Simple C++ Test Suite
 */

using namespace cv;
using namespace std;

void showHandAndRadialHistogram(Mat &segmentedHandBin) {
    static int j = 0;
    MatND histogram;
    MatND histogramPalm;
    Point2f massCenter = computeMassCenter(segmentedHandBin);
    Point2f palmCenter = estimatePalmCenter(segmentedHandBin, 15);
    circle(segmentedHandBin, Point(massCenter.y, massCenter.x), 2, CV_RGB(255,0,0), 2);
    circle(segmentedHandBin, Point(palmCenter.y, palmCenter.x), 2, CV_RGB(0,255,0), 2);
    cout<<"points computed and drawn"<<endl;
    // computes radial histogram around mass center
    radialHistogram(segmentedHandBin, histogram, 150);
    cout<<"radial histogram around mass center computed"<<endl;
    // compute radial histogram around palm center
    radialHistogramWithCenter(segmentedHandBin, histogramPalm, 150, palmCenter);
    cout<<"radial histogram arount palm center computed"<<endl;
    Mat histogramImage = imHist(histogram * 100.0);
    Mat histogramPalmImage = imHist(histogramPalm * 100.0);
    cout<<"Histogram image computed"<<endl;
    namedWindow("Segmented hand " + j);
    imshow("Segmented hand " + j, segmentedHandBin);
    namedWindow("Radial histogram " + j);
    imshow("Radial histogram " + j, histogramImage);
    namedWindow("Radial histogram with palm center " + j);
    imshow("Radial histogram with palm center " + j, histogramPalmImage);
    j++;
}

int main(int argc, char** argv) {
    Mat four = extractHandFromBMPFile("./runFolder/test-segmented-4.bmp");
    Mat flippedFour, rotatedFour;
    Mat five = extractHandFromBMPFile("./runFolder/test-segmented-5-2-wristless.bmp");
    Mat flippedFive, rotatedFive;
    horizontalSymmetry(four, flippedFour);
    verticalSymmetry(flippedFour, rotatedFour);
    horizontalSymmetry(five, flippedFive);
    verticalSymmetry(flippedFive, rotatedFive);
    showHandAndRadialHistogram(four);
    showHandAndRadialHistogram(rotatedFour);
/*    showHandAndRadialHistogram(five);
    showHandAndRadialHistogram(flippedFive);*/
    waitKey(0);
    
    return (EXIT_SUCCESS);
}

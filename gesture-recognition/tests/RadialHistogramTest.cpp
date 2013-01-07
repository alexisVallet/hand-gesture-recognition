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
    static int i = 0;
    string is;
    stringstream iss;
    iss << i;
    is = iss.str();
    MatND histogram;
    MatND histogramPalm;
    cout<<"computing mass center"<<endl;
    Point2f massCenter = computeMassCenter(segmentedHandBin);
    cout<<"computing palm center"<<endl;
    Point2f palmCenter = estimatePalmCenter(segmentedHandBin, 15);
    cout<<"circling: mass center = "<<massCenter<<", palm center = "<<palmCenter<<endl;
    Mat segmentedHandCircles;
    cvtColor(segmentedHandBin, segmentedHandCircles, CV_GRAY2RGB);
    circle(segmentedHandCircles, Point(massCenter.y, massCenter.x), 2, CV_RGB(255,0,0), 2);
    circle(segmentedHandCircles, Point(palmCenter.y, palmCenter.x), 2, CV_RGB(0,255,0), 2);
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
    namedWindow("Segmented hand " + is);
    imshow("Segmented hand " + is, segmentedHandCircles);
    namedWindow("Radial histogram " + is);
    imshow("Radial histogram " + is, histogramImage);
    namedWindow("Radial histogram with palm center " + is);
    imshow("Radial histogram with palm center " + is, histogramPalmImage);
    i++;
}

int main(int argc, char** argv) {
    Mat four = extractHandFromBMPFile("./runFolder/ClassImages2/4/0.bmp");
    Mat flippedFour, rotatedFour;
    Mat five = extractHandFromBMPFile("./runFolder/ClassImages2/5/0.bmp");
    Mat flippedFive, rotatedFive;
    namedWindow("test");
    imshow("test", four);
    waitKey(0);
    namedWindow("test");
    imshow("test", five);
    waitKey(0);
    horizontalSymmetry(four, flippedFour);
    verticalSymmetry(flippedFour, rotatedFour);
    horizontalSymmetry(five, flippedFive);
    verticalSymmetry(flippedFive, rotatedFive);
    cout<<"showing four"<<endl;
    showHandAndRadialHistogram(four);
    cout<<"showing rotated four"<<endl;
    showHandAndRadialHistogram(rotatedFour);
/*    showHandAndRadialHistogram(five);
    showHandAndRadialHistogram(flippedFive);*/
    waitKey(0);
    
    return (EXIT_SUCCESS);
}

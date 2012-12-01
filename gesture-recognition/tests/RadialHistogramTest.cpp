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

/*
 * Simple C++ Test Suite
 */

using namespace cv;
using namespace std;

void horizontalSymmetry(Mat &inputImage, Mat &outputImage) {
    Mat symmetryMatrix = Mat::zeros(2,3,CV_32F);
    symmetryMatrix.at<float>(0,0) = -1;
    symmetryMatrix.at<float>(1,1) = 1;
    symmetryMatrix.at<float>(0,2) = inputImage.cols;
    symmetryMatrix.at<float>(1,2) = 0;
    warpAffine(inputImage, outputImage, symmetryMatrix, Size(inputImage.cols, inputImage.rows));
}

void verticalSymmetry(Mat &inputImage, Mat &outputImage) {
    Mat symmetryMatrix = Mat::zeros(2,3,CV_32F);
    symmetryMatrix.at<float>(0,0) = 1;
    symmetryMatrix.at<float>(1,1) = -1;
    symmetryMatrix.at<float>(0,2) = 0;
    symmetryMatrix.at<float>(1,2) = inputImage.rows;
    warpAffine(inputImage, outputImage, symmetryMatrix, Size(inputImage.cols, inputImage.rows));
}

Mat imHist(Mat hist, float scaleX=1, float scaleY=1){
  double maxVal=0;
  minMaxLoc(hist, 0, &maxVal, 0, 0);
  int rows = 64; //default height size
  int cols = hist.rows; //get the width size from the histogram
  Mat histImg = Mat::zeros(rows*scaleX, cols*scaleY, CV_8UC3);
  //for each bin
  for(int i=0;i<cols-1;i++) {
    float histValue = hist.at<float>(i,0);
    float nextValue = hist.at<float>(i+1,0);
    Point pt1 = Point(i*scaleX, rows*scaleY);
    Point pt2 = Point(i*scaleX+scaleX, rows*scaleY);
    Point pt3 = Point(i*scaleX+scaleX, (rows-nextValue*rows/maxVal)*scaleY);
    Point pt4 = Point(i*scaleX, (rows-nextValue*rows/maxVal)*scaleY);

    int numPts = 5;
    Point pts[] = {pt1, pt2, pt3, pt4, pt1};

    fillConvexPoly(histImg, pts, numPts, Scalar(255,255,255));
  }
  return histImg;
}

void showHandAndRadialHistogram(Mat &segmentedHandRGB) {
    static int j = 0;
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat segmentedHandBin = segmentedHandGray / 255;
    MatND histogram;
    MatND histogramPalm;
    Point2f massCenter = computeMassCenter(segmentedHandBin);
    Point2f palmCenter = estimatePalmCenter(segmentedHandBin, 15);
    circle(segmentedHandRGB, Point(massCenter.y, massCenter.x), 2, CV_RGB(255,0,0), 2);
    circle(segmentedHandRGB, Point(palmCenter.y, palmCenter.x), 2, CV_RGB(0,255,0), 2);
    // computes radial histogram around mass center
    radialHistogram(segmentedHandBin, histogram, 150);
    // compute radial histogram around palm center
    radialHistogramWithCenter(segmentedHandBin, histogramPalm, 150, palmCenter);
    Mat histogramImage = imHist(histogram * 100.0);
    Mat histogramPalmImage = imHist(histogramPalm * 100.0);
    namedWindow("Segmented hand " + j);
    imshow("Segmented hand " + j, segmentedHandRGB);
    namedWindow("Radial histogram " + j);
    imshow("Radial histogram " + j, histogramImage);
    namedWindow("Radial histogram with palm center " + j);
    imshow("Radial histogram with palm center " + j, histogramPalmImage);
    j++;
}

int main(int argc, char** argv) {
    Mat four = imread("./runFolder/test-segmented-4.bmp").t();
    Mat flippedFour, rotatedFour;
    Mat five = imread("./runFolder/test-segmented-5-2-wristless.bmp").t();
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

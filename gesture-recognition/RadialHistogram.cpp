/* 
 * File:   RadialHistogram.cpp
 * Author: Alexis
 * 
 * Created on 25 novembre 2012, 17:26
 */

#include "RadialHistogram.h"

using namespace cv;
using namespace std;

static void radialHistogramWithCenterAndPixels(
        const Mat &segmentedHand, 
        MatND &histogram, 
        int numberOfBins, 
        Point center, 
        Mat &handPixelsMatrix) {
    Mat angleOffsets = Mat::zeros(segmentedHand.rows, segmentedHand.cols, CV_32F);
    
    for (int i = 0; i < handPixelsMatrix.cols; i++) {
        Mat handPixelMat = handPixelsMatrix.col(i);
        Point handPixel(handPixelMat.at<int>(0,0), handPixelMat.at<int>(1,0));
        angleOffsets.at<float>(handPixel.x, handPixel.y) =
                atan(((float)(handPixel.x - center.x))/
                     ((float)(handPixel.y - center.y)));
    }
    Mat segmentedHandMask = Mat_<unsigned char>(segmentedHand);
    int hsize[] = {numberOfBins};
    float range[] = {-M_PI/2.0, M_PI/2.0};
    const float *ranges[] = {range};
    int channels[] = {0};
    calcHist(&angleOffsets, 1, channels, segmentedHandMask, histogram, 1, hsize, ranges);
//    double max;
//    minMaxIdx(histogram, NULL, &max);
    histogram = Mat_<float>(histogram);
}

void radialHistogram(const Mat &segmentedHand, MatND &histogram, int numberOfBins) {
    Mat handPixelsMatrix = handPixels(Mat_<int>(segmentedHand));
    PCA handPCA(Mat_<float>(handPixelsMatrix), Mat(), CV_PCA_DATA_AS_COL);
    Mat massCenterMat = handPCA.mean;
    Point2f massCenter(massCenterMat.at<float>(0,0), massCenterMat.at<float>(0,1));
    radialHistogramWithCenterAndPixels(segmentedHand, histogram, numberOfBins, massCenter, handPixelsMatrix);
}

void radialHistogramWithCenter(const Mat &segmentedHand, MatND &histogram, int numberOfBins, Point2f center) {
    Mat handPixelsMatrix = handPixels(Mat_<int>(segmentedHand));
    radialHistogramWithCenterAndPixels(segmentedHand, histogram, numberOfBins, center, handPixelsMatrix);
}

Mat imHist(Mat hist, float scaleX, float scaleY){
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
/* 
 * File:   RadialHistogram.cpp
 * Author: Alexis
 * 
 * Created on 25 novembre 2012, 17:26
 */

#include "RadialHistogram.h"

using namespace cv;
using namespace std;

static void radialHistogramWithCenterAndPixels(const Mat &segmentedHand, MatND &histogram, int numberOfBins, Point center, Mat &handPixelsMatrix) {
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
    double max;
    minMaxIdx(histogram, NULL, &max);
    histogram = Mat_<float>(histogram) / max;
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

Point2f estimatePalmCenter(const Mat &segmentedHand, int maxFingerWidth) {
    Mat structuringElement = getStructuringElement(
            MORPH_ELLIPSE, 
            Size(maxFingerWidth-1,maxFingerWidth-1));
    Mat palm;
    erode(segmentedHand, palm, structuringElement);

    return computeMassCenter(palm);
}

Point2f computeMassCenter(const Mat &segmentedHand) {
    Mat handPixelsMatrix = handPixels(Mat_<int>(segmentedHand));
    PCA handPCA(Mat_<float>(handPixelsMatrix), Mat(), CV_PCA_DATA_AS_COL);
    Mat massCenterMat = handPCA.mean;
    Point2f massCenter(massCenterMat.at<float>(0,0), massCenterMat.at<float>(0,1));
    
    return massCenter;
}
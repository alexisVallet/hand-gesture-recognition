/* 
 * File:   RadialHistogram.cpp
 * Author: Alexis
 * 
 * Created on 25 novembre 2012, 17:26
 */

#include "RadialHistogram.h"

using namespace cv;

void radialHistogram(const Mat &segmentedHand, OutputArray histogram, int numberOfBins) {
    Mat handPixelsMatrix = handPixels(Mat_<int>(segmentedHand));
    PCA handPCA(Mat_<float>(handPixelsMatrix), Mat(), CV_PCA_DATA_AS_COL);
    Mat massCenterMat = handPCA.mean;
    Point2f massCenter(massCenterMat.at<float>(0,0), massCenterMat.at<float>(0,1));
    Mat angleOffsets(Mat::zeros(segmentedHand.rows, segmentedHand.cols, CV_32F));
    
    for (int i = 0; i < handPixelsMatrix.cols; i++) {
        Mat handPixelMat = handPixelsMatrix.col(i).t();
        Point handPixel(handPixelMat.at<int>(0,0), handPixelMat.at<int>(1,0));
        angleOffsets.at<float>(handPixel.x, handPixel.y) = 
                atan(((float)(handPixel.x - massCenter.x))/
                     ((float)(handPixel.y - massCenter.y)));
    }
    Mat segmentedHandMask = Mat_<char>(segmentedHand);
    int channels[] = {0};
    int histSize[] = {numberOfBins};
    float offsetRange[1][2] = {{-M_PI/2, M_PI/2}};
    calcHist(&angleOffsets, 1, channels, segmentedHandMask, histogram, 1,
             histSize, (const float**)offsetRange, true, false);
}

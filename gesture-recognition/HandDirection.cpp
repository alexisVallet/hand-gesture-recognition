/* 
 * File:   HandDirection.cpp
 * Author: Alexis
 * 
 * Created on 24 novembre 2012, 08:45
 */

#include "HandDirection.h"

using namespace cv;

Mat handPixelsWithPixelValue(const Mat &segmentedHand, int handPixelValue) {
    int numberOfHandPixels = countNonZero(segmentedHand);
    Mat handPixelsMatrix(2, numberOfHandPixels, CV_32S);
    int currentHandPixel = 0;
    
    for (int i = 0; i < segmentedHand.rows; i++) {
        for (int j = 0; j < segmentedHand.cols; j++) {
            int pixelValue = segmentedHand.at<int>(i,j);
            
            if (pixelValue == handPixelValue) {
                handPixelsMatrix.at<int>(0, currentHandPixel) = i;
                handPixelsMatrix.at<int>(1, currentHandPixel) = j;
                currentHandPixel++;
            }
        }
    }

    handPixelsMatrix = handPixelsMatrix.colRange(0, currentHandPixel);
    
    return handPixelsMatrix;
}

Mat handPixels(const Mat &segmentedHand) {
    return handPixelsWithPixelValue(segmentedHand, HAND_PIXEL_VALUE);
}

std::pair < cv::Mat,cv::Mat > handDirectionWithPixelValue(
        const cv::Mat &segmentedHand, int handPixelValue) {
    Mat handPixelsMatrix = Mat_<float>(handPixelsWithPixelValue(Mat_<int>(segmentedHand),handPixelValue));
    PCA handPCA;
    handPCA(handPixelsMatrix, Mat(), CV_PCA_DATA_AS_COL);
    Mat eigenVectors = handPCA.eigenvectors.clone();
    std::pair < Mat, Mat > separatedEigenVectors(eigenVectors.row(0), eigenVectors.row(1));
    
    return separatedEigenVectors;
}

std::pair < Mat,Mat > handDirection(const Mat &segmentedHand) {
    return handDirectionWithPixelValue(segmentedHand, HAND_PIXEL_VALUE);
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
    // Fails when there are no hand pixels.
    if (handPixelsMatrix.cols == 0) {
        return Point2f(-1,-1);
    }
    PCA handPCA(Mat_<float>(handPixelsMatrix), Mat(), CV_PCA_DATA_AS_COL);
    Mat massCenterMat = handPCA.mean;
    Point2f massCenter(massCenterMat.at<float>(0,0), massCenterMat.at<float>(0,1));
    
    return massCenter;
}
/* 
 * File:   HandDirection.cpp
 * Author: Alexis
 * 
 * Created on 24 novembre 2012, 08:45
 */

#include "HandDirection.h"

using namespace cv;

Mat handPixels(const Mat &segmentedHand) {
    int numberOfHandPixels = countNonZero(segmentedHand);
    Mat handPixelsMatrix(2, numberOfHandPixels, CV_32S);
    int currentHandPixel = 0;
    
    for (int i = 0; i < segmentedHand.rows; i++) {
        for (int j = 0; j < segmentedHand.cols; j++) {
            int pixelValue = segmentedHand.at<int>(i,j);
            
            if (pixelValue == HAND_PIXEL_VALUE) {
                handPixelsMatrix.at<int>(0, currentHandPixel) = i;
                handPixelsMatrix.at<int>(1, currentHandPixel) = j;
                currentHandPixel++;
            }
        }
    }
    
    return handPixelsMatrix;
}

static std::pair < Mat,Mat > handDirectionPCA(const Mat &segmentedHand, Mat &handPixelsMatrix) {
    PCA handPCA;
    handPCA(handPixelsMatrix, Mat(), CV_PCA_DATA_AS_COL);
    std::cout<<"PCA computed"<<std::endl;
    Mat eigenVectors = handPCA.eigenvectors.clone();
    std::pair < Mat, Mat > separatedEigenVectors(eigenVectors.row(0), eigenVectors.row(1));
    
    return separatedEigenVectors;
}

std::pair < Mat,Mat > handDirection(const Mat &segmentedHand) {
    Mat handPixelsMatrix = Mat_<float>(handPixels(Mat_<int>(segmentedHand)));
    
    return handDirectionPCA(segmentedHand, handPixelsMatrix);
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
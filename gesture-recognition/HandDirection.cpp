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

std::pair < Mat,Mat > handDirection(const Mat &segmentedHand) {
    Mat handPixelsMatrix = Mat_<float>(handPixels(Mat_<int>(segmentedHand)));
    PCA handPCA;
    handPCA(handPixelsMatrix, Mat(), CV_PCA_DATA_AS_COL);
    std::cout<<"PCA computed"<<std::endl;
    Mat eigenVectors = handPCA.eigenvectors.clone();
    std::pair < Mat, Mat > separatedEigenVectors(eigenVectors.row(0), eigenVectors.row(1));
    
    return separatedEigenVectors;
}

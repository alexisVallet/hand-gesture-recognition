/* 
 * File:   HandDirection.cpp
 * Author: Alexis
 * 
 * Created on 24 novembre 2012, 08:45
 */

#include "HandDirection.h"

using namespace cv;

/**
 * Returns the position of the pixels belonging to the hand as a 2xn matrix,
 * where columns are pixel coordinates. Assumes that the hand image is integer
 * valued, with HAND_PIXEL_VALUE (defined in HandDirection.h at the moment) 
 * for the hand pixels.
 * 
 * @param segmentedHand the segmented, cropped and binarized hand image.
 * @return a 2 lines matrix where columns are hand pixels coordinates.
 */
static Mat handPixels(const Mat &segmentedHand) {
    int numberOfHandPixels = countNonZero(segmentedHand);
    Mat handPixelsMatrix(2, numberOfHandPixels, CV_32S);
    Size segmentedHandSize = segmentedHand.size();
    int currentHandPixel = 0;
    
    for (int i = 0; i < segmentedHandSize.height; i++) {
        for (int j = 0; j < segmentedHandSize.width; j++) {
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
    Mat handPixelsMatrix = handPixels(segmentedHand);
    PCA handPCA(handPixelsMatrix, noArray(), CV_PCA_DATA_AS_COL);
    Mat eigenVectors = handPCA.eigenvectors.clone();
    std::pair < Mat, Mat > separatedEigenVectors(eigenVectors.col(0), eigenVectors.col(1));
    
    return separatedEigenVectors;
}

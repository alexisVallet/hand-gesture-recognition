/* 
 * File:   Symmetry.cpp
 * Author: Alexis
 * 
 * Created on 12 décembre 2012, 19:33
 */

#include "Symmetry.h"

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

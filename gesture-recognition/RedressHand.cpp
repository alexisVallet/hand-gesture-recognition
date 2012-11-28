/* 
 * File:   RedressHand.cpp
 * Author: Alexis
 * 
 * Created on 28 novembre 2012, 10:38
 */

#include "RedressHand.h"

void rotateHand(const Mat &segmentedHand, Mat &rotatedHand, double angle) {
    Mat translation = Mat::eye(3,3,CV_32FC1);
    int diag = ceil(sqrt(segmentedHand.rows*segmentedHand.rows + segmentedHand.cols*segmentedHand.cols));
    translation.at<float>(0,2) = diag - segmentedHand.cols/2;
    translation.at<float>(1,2) = diag - segmentedHand.rows/2;
    translation.at<float>(2,2) = 0;
    Mat rotation = getRotationMatrix2D(Point(segmentedHand.cols/2,segmentedHand.rows/2), angle*180.0/M_PI, 1);
    rotation.reshape(0, 3);
    warpAffine(Mat_<float>(segmentedHand), Mat_<float>(rotatedHand), Mat_<float>(translation * rotation), Size(diag,diag));
}
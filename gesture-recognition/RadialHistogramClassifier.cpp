/* 
 * File:   RadialHistogramClassifier.cpp
 * Author: Alexis
 * 
 * Created on 29 novembre 2012, 10:01
 */

#include "RadialHistogramClassifier.h"

RadialHistogramClassifier::RadialHistogramClassifier() :
numberOfBins(DEFAULT_RADIAL_BINS_NUMBER), maxFingerWidth(DEFAULT_MAX_FINGER_WIDTH)
{
}

RadialHistogramClassifier::RadialHistogramClassifier(
        int numberOfBins = DEFAULT_RADIAL_BINS_NUMBER,
        int maxFingerWidth = DEFAULT_MAX_FINGER_WIDTH) {
    this->numberOfBins = numberOfBins;
    this->maxFingerWidth = maxFingerWidth;
}

Mat RadialHistogramClassifier::caracteristicVector(Mat &segmentedHand) {
    Mat direction = handDirection(segmentedHand).second;
    float angle = atan(direction.at<float>(0,1)/direction.at<float>(0,0));
    Mat rotatedHand;
    rotateHand(segmentedHand, rotatedHand, angle);
    MatND handRadialHistogram;
    Point2f palmCenter = estimatePalmCenter(rotatedHand, this->maxFingerWidth);
    radialHistogramWithCenter(
            rotatedHand, 
            handRadialHistogram, 
            this->numberOfBins, 
            palmCenter);
    return handRadialHistogram;
}

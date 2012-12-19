#include "RadialHistogramClassifier.h"

RadialHistogramClassifier::RadialHistogramClassifier() {
}

RadialHistogramClassifier::RadialHistogramClassifier(
        TrainableStatModel *internalStatisticalModel,
        int numberOfBins,
        int maxFingerWidth) 
        : StatisticalClassifier(internalStatisticalModel)
{
    this->numberOfBins = numberOfBins;
    this->maxFingerWidth = maxFingerWidth;
}

Mat RadialHistogramClassifier::caracteristicVector(const Mat &segmentedHand) {
    Mat direction = handDirection(segmentedHand).second;
    float angle = atan(direction.at<float>(0,1)/direction.at<float>(0,0));
    Mat rotatedHand;
    rotateHand(segmentedHand, rotatedHand, angle);
    Mat flippedHand = rotatedHand;
    if (detectHandSide(rotatedHand, 1) == LEFT_HAND) {
        horizontalSymmetry(rotatedHand, flippedHand);
    }
    MatND handRadialHistogram;
    Point2f palmCenter = estimatePalmCenter(
           flippedHand, 
           this->maxFingerWidth);
    radialHistogramWithCenter(
        flippedHand, 
        handRadialHistogram, 
        this->numberOfBins, 
        palmCenter);
    return handRadialHistogram.t();
}

int RadialHistogramClassifier::caracteristicVectorLength() {
   return this->numberOfBins;
}
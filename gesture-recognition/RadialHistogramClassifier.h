/* 
 * File:   RadialHistogramClassifier.h
 * Author: Alexis
 *
 * Created on 29 novembre 2012, 10:01
 */

#ifndef RADIALHISTOGRAMCLASSIFIER_H
#define	RADIALHISTOGRAMCLASSIFIER_H

#include "ClassifierParameters.h"
#include "StatisticalClassifier.h"
#include "RadialHistogram.h"
#include "HandDirection.h"
#include "rotateHand.h"
#include "HandSideDetection.h"
#include "Symmetry.h"

#define DEFAULT_RADIAL_BINS_NUMBER 80
#define DEFAULT_MAX_FINGER_WIDTH 15

/**
 * Classifies a segmented hand using its radial histogram.
 * First rotates the hand according to its direction (up
 * to a rotation of angle pi, for which the radial
 * histogram is invariant), computes its radial
 * histogram.
 */
class RadialHistogramClassifier : public StatisticalClassifier {
public:
    RadialHistogramClassifier() {
    }
    RadialHistogramClassifier(
        TrainableStatModel *internalStatisticalModel,
        int numberOfBins = DEFAULT_RADIAL_BINS_NUMBER,
        int maxFingerWidth = DEFAULT_MAX_FINGER_WIDTH) 
        : StatisticalClassifier(internalStatisticalModel)
    {
        this->numberOfBins = numberOfBins;
        this->maxFingerWidth = maxFingerWidth;
    }

    Mat caracteristicVector(const Mat &segmentedHand) {
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

    int caracteristicVectorLength() {
        return this->numberOfBins;
    }

private:
    int numberOfBins;
    int maxFingerWidth;
};

#endif	/* RADIALHISTOGRAMCLASSIFIER_H */

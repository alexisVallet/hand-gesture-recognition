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
#include "AutoSubClassingClassifier.h"

#define DEFAULT_RADIAL_BINS_NUMBER 80
#define DEFAULT_MAX_FINGER_WIDTH 15

/**
 * Classifies a segmented hand using its radial histogram.
 * First rotates the hand according to its direction (up
 * to a rotation of angle pi, for which the radial
 * histogram is invariant), computes its radial
 * histogram.
 */
class RadialHistogramClassifier : public AutoSubClassingClassifier {
public:
    RadialHistogramClassifier();
    RadialHistogramClassifier(
        TrainableStatModel *internalStatisticalModel,
        int numberOfBins = DEFAULT_RADIAL_BINS_NUMBER,
        int maxFingerWidth = DEFAULT_MAX_FINGER_WIDTH,
        vector<int> numberOfSubClasses = vector<int>(6, 1));
    Mat caracteristicVector(const Mat &segmentedHand);
    int caracteristicVectorLength();

private:
    int numberOfBins;
    int maxFingerWidth;
};

#endif	/* RADIALHISTOGRAMCLASSIFIER_H */

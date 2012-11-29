/* 
 * File:   RadialHistogramClassifier.h
 * Author: Alexis
 *
 * Created on 29 novembre 2012, 10:01
 */

#ifndef RADIALHISTOGRAMCLASSIFIER_H
#define	RADIALHISTOGRAMCLASSIFIER_H

#include "StatisticalClassifier.h"
#include "RadialHistogram.h"
#include "HandDirection.h"
#include "RedressHand.h"

/**
 * Classifies a segmented hand using its radial histogram.
 * First rotates the hand according to its direction (up
 * to a rotation of angle pi, for which the radial
 * histogram is invariant), computes its radial
 * histogram.
 */
class RadialHistogramClassifier : StatisticalClassifier {
public:
    RadialHistogramClassifier();
    Mat caracteristicVector(Mat &segmentedHand);
};

#endif	/* RADIALHISTOGRAMCLASSIFIER_H */

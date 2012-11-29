/* 
 * File:   RadialHistogramClassifier.cpp
 * Author: Alexis
 * 
 * Created on 29 novembre 2012, 10:01
 */

#include "RadialHistogramClassifier.h"

RadialHistogramClassifier::RadialHistogramClassifier() {
}

Mat RadialHistogramClassifier::caracteristicVector(Mat &segmentedHand) {
    Mat handDirectionVector = handDirection(segmentedHand).second;
}
/* 
 * File:   Classifier.cpp
 * Author: Alexis
 * 
 * Created on 23 novembre 2012, 18:02
 */

#include "Classifier.h"

/**
 * Default implementation, simply returns a vector containing 1 for the class
 * returned by numberOfFingers.
 */
vector<float> Classifier::classProbabilities(Mat& segmentedHand) {
    vector<float> defaultResults(6, 0);
    defaultResults[this->numberOfFingers(segmentedHand)] = 1;
    
    return defaultResults;
}
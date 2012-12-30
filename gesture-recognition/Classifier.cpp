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

float Classifier::recognitionRate(vector<Mat> handsToRecognize, vector<int> expectedNumberOfFingers) {
    int numberOfSuccesses = 0;
    assert(handsToRecognize.size() == expectedNumberOfFingers.size());
    
    for (int i = 0; i < handsToRecognize.size(); i++) {
        int actual = this->numberOfFingers(handsToRecognize[i]);
        if (actual == expectedNumberOfFingers[i]) {
            numberOfSuccesses++;
        }
    }
    
    return ((float)numberOfSuccesses)/((float)handsToRecognize.size());
}

vector<float> Classifier::recognitionRatePerClass(vector<Mat> handsToRecognize, vector<int> expectedNumberOfFingers) {
    assert(handsToRecognize.size() == expectedNumberOfFingers.size());
    vector<int> numberOfSuccesses(6, 0);
    vector<int> totalNumberOfSamples(6, 0);
    
    for (int i = 0; i < handsToRecognize.size(); i++) {
        int actual = this->numberOfFingers(handsToRecognize[i]);
        int expected = expectedNumberOfFingers[i];
        if (actual == expected) {
            numberOfSuccesses[expected]++;
        }
        totalNumberOfSamples[expected]++;
    }
    
    vector<float> recognitionRates(6,0);
    
    for (int i = 0; i < 6; i++) {
        recognitionRates[i] = ((float)numberOfSuccesses[i])/((float)totalNumberOfSamples[i]);
    }
    
    return recognitionRates;
}

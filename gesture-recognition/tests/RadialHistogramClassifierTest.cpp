/* 
 * File:   RadialHistogramClassifierTest.cpp
 * Author: Alexis
 *
 * Created on 30 nov. 2012, 17:27:26
 */

#include <stdlib.h>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "RadialHistogram.h"
#include "RadialHistogramClassifier.h"

Mat readAndNormalize(string filepath) {
    Mat segmentedHandRGB = imread(filepath);
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat segmentedHandBin = segmentedHandGray / 255;
    
    return segmentedHandBin;
}

void loadTrainingData(vector<Mat> &segmentedHands, vector<int> &numberOfFingers) {
    segmentedHands.clear();
    numberOfFingers.clear();
    
    for (int i = 0; i < 6; i++) {
        
        Mat segmentedHand = readAndNormalize(completePath);
        segmentedHands.insert(segmentedHands.end(),segmentedHand);
        numberOfFingers.insert(numberOfFingers.end(),i);
    }
}

int main(int argc, char** argv) {
    CvNormalBayesClassifier bayesClassifier;
    RadialHistogramClassifier<CvNormalBayesClassifier> classifier(bayesClassifier);
    vector<Mat> segmentedHands;
    vector<int> numberOfFingers;
    loadTrainingData(segmentedHands, numberOfFingers);
    classifier.train(segmentedHands, numberOfFingers);
    
    return (EXIT_SUCCESS);
}

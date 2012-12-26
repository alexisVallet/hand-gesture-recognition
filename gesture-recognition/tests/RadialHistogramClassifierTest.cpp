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
#include "Segmentation.h"
#include "utilsFunctions.h"

void loadTrainingData(string basePath, vector<Mat> &segmentedHands, vector<int> &classes) {
    vector < vector < string > > pathsByClasses;
    
    readPath(pathsByClasses, basePath, "bmp");

    for (int i = 0; i < pathsByClasses.size(); i++) {
        for (int j = 0; j < pathsByClasses[i].size(); j++) {
            cout<<pathsByClasses[i][j]<<" is in "<<i<<endl;
            Mat image = extractHandFromBMPFile(pathsByClasses[i][j]);
            segmentedHands.push_back(image);
            classes.push_back(i);
        }
    }
}

vector<float> recognitionRateByNumberOfBins(
        TrainableStatModel *internalModel, 
        int minNbBins, 
        int maxNbBins, 
        vector<Mat> baseInputs, 
        vector<int> baseOutputs) {
    vector<float> recognitionRates(maxNbBins - minNbBins+ 1);
    for (int nbBins = minNbBins; nbBins <= maxNbBins; nbBins++) {
        cout<<nbBins<<" bins"<<endl;
        RadialHistogramClassifier classifier(internalModel, nbBins, 15, vector<int>(6, 3));
        recognitionRates[nbBins-minNbBins] = classifier.leaveOneOutRecognitionRate(baseInputs, baseOutputs);
        cout<<"Recognition rate for "<<nbBins<<" bins: "<<recognitionRates[nbBins-minNbBins]<<endl;
    }
    
    return recognitionRates;
}

int main(int argc, char** argv) {
    CvNormalBayesClassifier internalClassifier;
    BayesModel internalModel(&internalClassifier);
    vector<Mat> segmentedHands;
    vector<int> classes;
    loadTrainingData("./runFolder/ClassImages2/", segmentedHands, classes);
    recognitionRateByNumberOfBins(&internalModel, 80, 80, segmentedHands, classes);
    return (EXIT_SUCCESS);
}

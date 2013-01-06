/* 
 * File:   RadialHistogramClassifierTest.cpp
 * Author: Alexis
 *
 * Created on 30 nov. 2012, 17:27:26
 */

#include <stdlib.h>
#include <iostream>
#include <algorithm>
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

Mat recognitionRateByNumberOfBins(
        TrainableStatModel &internalModel,          
        int minNbBins, 
        int maxNbBins, 
        vector<Mat> baseInputs, 
        vector<int> baseOutputs,
        Mat &perClasses) {
    Mat recognitionRates(1, maxNbBins - minNbBins+ 1, CV_32F);
    perClasses = Mat::zeros(6, maxNbBins - minNbBins + 1, CV_32F);
    for (int nbBins = minNbBins; nbBins <= maxNbBins; nbBins++) {
        RadialHistogramClassifier classifier(&internalModel, nbBins, 15, vector<int>(6, 2));
        cout<<"radial histogram classifier initialized"<<endl;
        recognitionRates.at<float>(0,nbBins-minNbBins) = classifier.leaveOneOutRecognitionRate(baseInputs, baseOutputs);
        Mat perClass = classifier.leaveOneOutRecognitionRatePerClass(baseInputs, baseOutputs).t();
        perClass.copyTo(perClasses.colRange(nbBins-minNbBins, nbBins-minNbBins+1));
    }
    
    return recognitionRates;
}

int main(int argc, char** argv) {
    vector<Mat> segmentedHands;
    vector<int> classes;
    loadTrainingData("./runFolder/ClassImages2/", segmentedHands, classes);
    KNearestModel internalModel(1);
    Mat perClasses;
    Mat rates = recognitionRateByNumberOfBins(internalModel, 106, 106, segmentedHands, classes, perClasses);
    double bestRate;
    Point bestRateIdx;
    minMaxLoc(rates, NULL, &bestRate, NULL, &bestRateIdx);
    cout<<"best rate: "<<bestRate<<" at "<<bestRateIdx<<endl;
    cout<<"per class: "<<perClasses.colRange(bestRateIdx.y, bestRateIdx.y+1)<<endl;
    waitKey(0);
    return (EXIT_SUCCESS);
}

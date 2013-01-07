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
        Mat &perClasses,
        int step) {
    Mat recognitionRates(1, (maxNbBins - minNbBins)/step + 1, CV_32F);
    perClasses = Mat::zeros(6, (maxNbBins - minNbBins)/step + 1, CV_32F);
    int i = 0;
    for (int nbBins = minNbBins; nbBins <= maxNbBins; nbBins += step) {
        RadialHistogramClassifier classifier(&internalModel, nbBins, 15, vector<int>(6, 1));
        cout<<"radial histogram classifier initialized"<<endl;
        recognitionRates.at<float>(0,i) = classifier.leaveOneOutRecognitionRate(baseInputs, baseOutputs);
        Mat perClass = classifier.leaveOneOutRecognitionRatePerClass(baseInputs, baseOutputs).t();
        perClass.copyTo(perClasses.colRange(i, i + 1));
        i++;
    }
    
    return recognitionRates;
}

int main(int argc, char** argv) {
    vector<Mat> segmentedHands;
    vector<int> classes;
    loadTrainingData("./runFolder/ClassImages2/", segmentedHands, classes);
    BayesModel internalModel;
    Mat perClasses;
    Mat rates = recognitionRateByNumberOfBins(internalModel, 10, 150, segmentedHands, classes, perClasses, 10);
    double bestRate;
    Point bestRateIdx;
    minMaxLoc(rates, NULL, &bestRate, NULL, &bestRateIdx);
    cout<<"rates: "<<rates<<endl;
    cout<<"best rate: "<<bestRate<<" at "<<bestRateIdx<<endl;
    cout<<"per class: "<<perClasses.colRange(bestRateIdx.y, bestRateIdx.y+1)<<endl;
    waitKey(0);
    return (EXIT_SUCCESS);
}

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

Mat recognitionRateByHiddenLayerSize( 
        int minNbBins, 
        int maxNbBins, 
        vector<Mat> baseInputs, 
        vector<int> baseOutputs) {
    Mat recognitionRates(1, maxNbBins - minNbBins+ 1, CV_32F);
    for (int nbBins = minNbBins; nbBins <= maxNbBins; nbBins++) {
        Mat layerSizes(1,3,CV_32S);
        layerSizes.at<int>(0,0) = 80;
        layerSizes.at<int>(0,1) = nbBins;
        layerSizes.at<int>(0,2) = 12;
        cout<<"calling constructor"<<endl;
        ANNModel internalModel(layerSizes, CvANN_MLP::SIGMOID_SYM, 1, 0.5);
        cout<<"initializing radial histogram classifier"<<endl;
        RadialHistogramClassifier classifier(&internalModel, 80, 15, vector<int>(6, 2));
        cout<<"radial histogram classifier initialized"<<endl;
        recognitionRates.at<float>(0,nbBins-minNbBins) = classifier.leaveOneOutRecognitionRate(baseInputs, baseOutputs);
    }
    
    return recognitionRates;
}

int main(int argc, char** argv) {
    vector<Mat> segmentedHands;
    vector<int> classes;
    loadTrainingData("./runFolder/ClassImages2/", segmentedHands, classes);
    Mat rates = recognitionRateByHiddenLayerSize(200, 600, segmentedHands, classes);
    cout<<"rates computed"<<endl;
    double bestRate;
    Point2i bestRateIdx;
    minMaxLoc(rates, NULL, &bestRate, NULL, &bestRateIdx);
    cout<<"Best rate: "<<bestRate<<" at "<<bestRateIdx<<endl;
    Mat plot =imHist(rates.t() *100, 1, 1);
    cout<<"image computed"<<endl;
    namedWindow("recognitionRateByBins");
    imshow("recognitionRateByBins", plot);
    waitKey(0);
    return (EXIT_SUCCESS);
}

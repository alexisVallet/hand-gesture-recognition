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

void loadTrainingData(vector<Mat> &segmentedHands, vector<int> &classes) {
    vector < vector < string > > pathsByClasses;
    
    readPath(pathsByClasses, "./runFolder/ClassImagesEtendue2/", "bmp");

    for (int i = 0; i < pathsByClasses.size(); i++) {
        for (int j = 0; j < pathsByClasses[i].size(); j++) {
            cout<<pathsByClasses[i][j]<<" is in "<<i<<endl;
            Mat image = extractHandFromBMPFile(pathsByClasses[i][j]);
            segmentedHands.push_back(image);
            classes.push_back(i);
        }
    }
}

int class1ToNbFingers(int classNumber) {
    int assocs[] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 3, 2, 2, 3, 2, 3, 3, 4,
        2, 3, 3, 4, 3, 4, 4, 5
    };
    
    return assocs[classNumber];
}

void showImageAndExpectedClass(StatisticalClassifier &classifier, string filepath) {
    Mat image = extractHandFromBMPFile(filepath);
    cout<<"image loaded"<<endl;
    namedWindow(filepath);
    imshow(filepath, image);
    waitKey(0);
    cout<<"Image "<<filepath<<" has "<<class1ToNbFingers(classifier.predict(image))<<" fingers"<<endl;
}

vector<Mat> loadTestData(string basePath, int numberOfImages) {
    vector<Mat> testData(numberOfImages);
    cout<<"called"<<endl;
    
    for (int i = 1; i <= numberOfImages; i++) {
        cout<<"image "<<i<<endl;
        stringstream ss;
        ss<<i;
        Mat image = extractHandFromBMPFile(basePath + ss.str() +".bmp");
        testData[i-1] = image;
    }
    
    return testData;
}

float measureSuccessRate(StatisticalClassifier &classifier, vector<Mat> inputs, int *expectedClasses) {
    int numberOfSuccesses = 0;
    
    for (int i = 0; i < inputs.size(); i++) {
        int actual = class1ToNbFingers(classifier.predict(inputs[i]));
        if (actual == expectedClasses[i]) {
            numberOfSuccesses++;
        }
        namedWindow("image" + i);
        imshow("image" + i, inputs[i]);
        cout<<"Image "<<i<<" actual: "<<actual<<", expected: "<<expectedClasses[i]<<endl;
        waitKey(0);
    }
    
    return ((float)numberOfSuccesses)/((float)inputs.size());
}

vector<float> recognitionRateByNumberOfBins(
        TrainableStatModel *internalModel, 
        int minNbBins, 
        int maxNbBins, 
        vector<Mat> baseInputs, 
        vector<int> baseOutputs) {
    vector<float> recognitionRates(maxNbBins - minNbBins+ 1);
    for (int nbBins = minNbBins; nbBins <= maxNbBins; nbBins++) {
        RadialHistogramClassifier classifier(internalModel, nbBins);
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
    loadTrainingData(segmentedHands, classes);
    vector<Mat> group1 = loadTestData("./runFolder/groupe1/", 16);
    vector<Mat> group2 = loadTestData("./runFolder/groupe3/", 18);
    group1.insert(group1.end(), group2.begin(), group2.end());
    int actualNumberOfFingers[] = {
        5, 3, -1, 0, 4, 2, 3, 4, 5, 4, 3, 2, 0,
        5, 4, 3, 1, 2, 3, 4, 5, 5, 0, 5, 4, 3,
        2, 1, 5, 4, 3, 2, 1, 0
    };
    vector<int> numberOfFingers;
    numberOfFingers.insert(numberOfFingers.begin(), actualNumberOfFingers, actualNumberOfFingers + 34);
    recognitionRateByNumberOfBins(&internalModel, 80, 85, group1, numberOfFingers);
    return (EXIT_SUCCESS);
}

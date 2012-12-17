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

int classToNbFingers(int classNumber) {
    if (classNumber == 0) {
        return 0;
    } else if (classNumber >= 1 && classNumber <= 2) {
        return 1;
    } else if (classNumber >= 3 && classNumber <= 5) {
        return 2;
    } else if (classNumber >= 6 && classNumber <= 8) {
        return 3;
    } else if (classNumber >= 9 && classNumber <= 10) {
        return 4;
    } else if (classNumber >= 11) {
        return 5;
    }
}

void showImageAndExpectedClass(StatisticalClassifier &classifier, string filepath) {
    Mat image = extractHandFromBMPFile(filepath);
    cout<<"image loaded"<<endl;
    namedWindow(filepath);
    imshow(filepath, image);
    waitKey(0);
    cout<<"Image "<<filepath<<" has "<<classToNbFingers(classifier.predict(image))<<" fingers"<<endl;
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
        int actual = classToNbFingers(classifier.predict(inputs[i]));
        if (actual == expectedClasses[i]) {
            numberOfSuccesses++;
        }
    }
    
    return ((float)numberOfSuccesses)/((float)inputs.size());
}

int main(int argc, char** argv) {
    CvKNearest internalClassifier;
    KNearestModel internalModel(&internalClassifier, 1);
    RadialHistogramClassifier classifier(&internalModel);
    cout<<"classifier initialized"<<endl;
    vector<Mat> segmentedHands;
    vector<int> classes;
    loadTrainingData(segmentedHands, classes);
    cout<<"training data loaded: segmentedHands"<<segmentedHands.size()<<", numberOfFingers:"<<classes.size()<<endl;
    classifier.train(segmentedHands, classes);
    cout<<"classifier trained"<<endl;
    vector<Mat> group1 = loadTestData("./runFolder/groupe1/", 16);
    cout<<"group 1 loaded"<<endl;
    vector<Mat> group2 = loadTestData("./runFolder/groupe3/", 18);
    cout<<"group 3 loaded"<<endl;
    group1.insert(group1.end(), group2.begin(), group2.end());
    int actualNumberOfFingers[] = {
        5, 3, -1, 0, 4, 2, 3, 4, 5, 4, 3, 2, 0,
        5, 4, 3, 1, 2, 3, 4, 5, 5, 0, 5, 4, 3,
        2, 1, 5, 4, 3, 2, 1, 0
    };
    float successRate = measureSuccessRate(classifier, group1, actualNumberOfFingers);
    cout<<"Success rate: "<<successRate<<endl;
    return (EXIT_SUCCESS);
}

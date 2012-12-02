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
        stringstream ss;
        ss<<i;
        Mat segmentedHand = readAndNormalize("./runFolder/ClassImagesSeg/" + ss.str() + "/0.bmp");
        segmentedHands.insert(segmentedHands.end(),segmentedHand);
        numberOfFingers.insert(numberOfFingers.end(),i);
    }
}

void showImageAndExpectedClass(RadialHistogramClassifier<CvNormalBayesClassifier> classifier, string filepath) {
    Mat image = readAndNormalize("./runFolder/test-segmented-1-wristless.bmp");
    namedWindow(filepath);
    imshow(filepath, image*255);
    cout<<"Expected class for "<<filepath<<" is "<<classifier.predict(image)<<endl;
}

int main(int argc, char** argv) {
    CvNormalBayesClassifier bayesClassifier;
    RadialHistogramClassifier<CvNormalBayesClassifier> classifier(bayesClassifier);
    cout<<"classifier initialized"<<endl;
    vector<Mat> segmentedHands;
    vector<int> numberOfFingers;
    loadTrainingData(segmentedHands, numberOfFingers);
    cout<<"training data loaded: segmentedHands"<<segmentedHands.size()<<", numberOfFingers:"<<numberOfFingers.size()<<endl;
    classifier.train(segmentedHands, numberOfFingers);
    cout<<"classifier trained"<<endl;
    showImageAndExpectedClass(classifier, "./runFolder/test-segmented-1-wristless.bmp");
/*    showImageAndExpectedClass(classifier, "./runFolder/test-segmented-2.bmp");
    showImageAndExpectedClass(classifier, "./runFolder/test-segmented-4.bmp");
    showImageAndExpectedClass(classifier, "./runFolder/test-segmented-5-2-wristless.bmp");*/
    waitKey(0);
    
    return (EXIT_SUCCESS);
}

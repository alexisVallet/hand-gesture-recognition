/* 
 * File:   ClassifiersComparison.cpp
 * Author: Alexis
 *
 * Created on 30 déc. 2012, 08:06:14
 */

#include <stdlib.h>
#include <iostream>
#include "RadialHistogramClassifier.h"
#include "ConvexityClassifier.h"
#include "utilsFunctions.h"

using namespace cv;
using namespace std;

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


int main(int argc, char** argv) {
    vector<Mat> segmentedHands;
    vector<int> classes;
    loadTrainingData("./runFolder/ClassImages2/", segmentedHands, classes);
    ConvexityClassifier convexityClassifier;
    float convexityTotalRate = convexityClassifier.recognitionRate(segmentedHands, classes);
    vector<float> convexityRatePerClass = convexityClassifier.recognitionRatePerClass(segmentedHands, classes);
    
    cout<<"Convexity classifier total recognition rate: "<<convexityTotalRate<<endl;

    for (int i = 0; i < 6; i++) {
        cout<<"Convexity classifier for class "<<i<<" has rate: "<<convexityRatePerClass[i]<<endl;
    }

    return (EXIT_SUCCESS);
}

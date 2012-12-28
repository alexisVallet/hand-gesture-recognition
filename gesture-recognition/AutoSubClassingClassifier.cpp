/* 
 * File:   AutoSubClassingClassifier.cpp
 * Author: Alexis
 * 
 * Created on 20 décembre 2012, 08:09
 */

#include "AutoSubClassingClassifier.h"

AutoSubClassingClassifier::AutoSubClassingClassifier() {
}

AutoSubClassingClassifier::AutoSubClassingClassifier(
        vector<int> numberOfSubclassesPerClass, 
        TrainableStatModel* statisticalModel) 
        : StatisticalClassifier(statisticalModel),
        numberOfSubclasses(numberOfSubclassesPerClass)
{
}

void AutoSubClassingClassifier::train(
        const vector<Mat>& segmentedHands, 
        const vector<int>& expectedClass) {
    assert(segmentedHands.size() == expectedClass.size());
    this->subclassesOfTrainingBase.clear();
    int numberOfClasses = *max_element(expectedClass.begin(), expectedClass.end()) + 1;
    vector<Mat> samplesPerClass(numberOfClasses);
    
    for (int i = 0; i < segmentedHands.size(); i++) {
        Mat currentCaracteristicVector = this->caracteristicVector(segmentedHands[i]);
        
        if (samplesPerClass[expectedClass[i]].empty()) {
            samplesPerClass[expectedClass[i]] = currentCaracteristicVector;
        } else {
            vconcat(samplesPerClass[expectedClass[i]], currentCaracteristicVector, samplesPerClass[expectedClass[i]]);
        }
    }
    int accumulatedNumberOfClasses = 0;
    for (int i = 0; i < samplesPerClass.size(); i++) {
        Mat labels;
        int clusterCount = this->numberOfSubclasses[i];
        kmeans(samplesPerClass[i], clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 0.0001, 10000), 5, KMEANS_RANDOM_CENTERS);
        this->subclassesOfTrainingBase.push_back(labels + (Mat::ones(samplesPerClass[i].rows, 1, CV_32S) * accumulatedNumberOfClasses));
        accumulatedNumberOfClasses += this->numberOfSubclasses[i];
    }
    
    Mat trainingInputs(segmentedHands.size(), this->caracteristicVectorLength(), CV_32F);
    Mat trainingOutputs(segmentedHands.size(), 1, CV_32F);
    int firstIndex = 0;
    for (int i = 0; i < samplesPerClass.size(); i++) {
        int lastIndex = firstIndex + samplesPerClass[i].rows;
        Mat samples = samplesPerClass[i];
        Mat range = trainingInputs.rowRange(firstIndex, lastIndex);
        samples.copyTo(range);
        Mat outputs = this->subclassesOfTrainingBase[i];
        outputs.copyTo(trainingOutputs.rowRange(firstIndex, lastIndex));
        firstIndex = lastIndex;
    }
    this->statisticalModel->train(trainingInputs, trainingOutputs);
}

int AutoSubClassingClassifier::numberOfFingersFromClassifierResult(float classifierResult) {
    int result = round(classifierResult);
        
    for (int i = 0; i < this->subclassesOfTrainingBase.size(); i++) {
        for (int j = 0; j < this->subclassesOfTrainingBase[i].rows; j++) {
            if (this->subclassesOfTrainingBase[i].at<int>(j,0) == result) {
                return i;
            }
        }
    }
    throw "Invalid classifier result.";
}
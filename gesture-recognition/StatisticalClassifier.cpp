/* 
 * File:   StatisticalClassifier.cpp
 * Author: Alexis
 * 
 * Created on 23 novembre 2012, 18:10
 */

#include "StatisticalClassifier.h"

StatisticalClassifier::StatisticalClassifier() {
}

StatisticalClassifier::StatisticalClassifier(const CvStatModel &statisticalModel, PredictionFunction predict) 
: statisticalModel(statisticalModel), predict(predict)
{
}

const CvStatModel &StatisticalClassifier::getStatisticalModel() {
    return this->statisticalModel;
}

int StatisticalClassifier::numberOfFingers(Mat &segmentedHand) {
    Mat handCaracteristicVector = this->caracteristicVector(segmentedHand);
    float classifierResult = 
        this->predict(this->statisticalModel, handCaracteristicVector);
    return this->numberOfFingersFromClassifierResult(classifierResult);
}

int StatisticalClassifier::numberOfFingersFromClassifierResult(float classifierResult) {
    return round(classifierResult);
}
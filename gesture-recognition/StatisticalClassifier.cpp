#include "StatisticalClassifier.h"

StatisticalClassifier::StatisticalClassifier(TrainableStatModel *statisticalModel)
        : statisticalModel(statisticalModel)
{
}

TrainableStatModel *StatisticalClassifier::getStatisticalModel() const{
    return this->statisticalModel;
}

float StatisticalClassifier::predict(Mat &caracteristicVector) {
    return this->statisticalModel->predict(caracteristicVector);
}

int StatisticalClassifier::numberOfFingersFromClassifierResult(float classifierResult) {
    return round(classifierResult);
}

int StatisticalClassifier::numberOfFingers(Mat &segmentedHand) {
    Mat handCaracteristicVector = this->caracteristicVector(segmentedHand);
    float classifierResult = 
          this->predict(handCaracteristicVector);
    return this->numberOfFingersFromClassifierResult(classifierResult);
}

void StatisticalClassifier::train(
        const vector<Mat> &segmentedHands,
        const vector<int> &expectedClass) {
    assert(segmentedHands.size() == expectedClass.size());
    Mat trainData(segmentedHands.size(), this->caracteristicVectorLength(), CV_32F);
    Mat expectedResponses(1, segmentedHands.size(), CV_32F);

    for (int i = 0; i < segmentedHands.size(); i++) {
        Mat currentCaracteristicVector = this->caracteristicVector(segmentedHands[i]);
        currentCaracteristicVector.copyTo(trainData.row(i));
        expectedResponses.at<float>(0, i) = expectedClass[i];
    }
    this->statisticalModel->train(trainData, expectedResponses);
}

void StatisticalClassifier::load(const char *filepath) {
    this->statisticalModel->getStatModel()->load(filepath);
}

void StatisticalClassifier::save(const char *filepath) {
    this->statisticalModel->getStatModel()->save(filepath);
}

float StatisticalClassifier::leaveOneOutRecognitionRate(vector<Mat> baseInputs, vector<int> baseOutputs) {
    int numberOfSuccesses = 0;
    assert(baseInputs.size() == baseOutputs.size());
    
    for (int i = 0; i < baseInputs.size(); i++) {
        Mat testInput = baseInputs[i];
        int testOutput = baseOutputs[i];
        baseInputs.erase(baseInputs.begin()+i);
        baseOutputs.erase(baseOutputs.begin()+i);
        this->getStatisticalModel()->clear();
        this->train(baseInputs, baseOutputs);
        int actualOutput = this->numberOfFingers(testInput);
        if (actualOutput == testOutput) {
            numberOfSuccesses++;
        }
        baseInputs.insert(baseInputs.begin()+i, testInput);
        baseOutputs.insert(baseOutputs.begin()+i, testOutput);
    }
    
    return ((float)numberOfSuccesses)/((float)baseInputs.size());
}

Mat StatisticalClassifier::leaveOneOutRecognitionRatePerClass(vector<Mat> baseInputs, vector<int> baseOutputs) {
    Mat rates = Mat::zeros(1,6, CV_32F);
    Mat totals = Mat::zeros(1,6,CV_32F);
    assert(baseInputs.size() == baseOutputs.size());
    
    for (int i = 0; i < baseInputs.size(); i++) {
        Mat testInput = baseInputs[i];
        int testOutput = baseOutputs[i];
        baseInputs.erase(baseInputs.begin()+i);
        baseOutputs.erase(baseOutputs.begin()+i);
        this->getStatisticalModel()->clear();
        this->train(baseInputs, baseOutputs);
        int actualOutput = this->numberOfFingers(testInput);
        if (actualOutput == testOutput) {
            rates.at<float>(0, testOutput)++;
        }
        baseInputs.insert(baseInputs.begin()+i, testInput);
        baseOutputs.insert(baseOutputs.begin()+i, testOutput);
        totals.at<float>(0,testOutput)++;
    }
    
    for (int i = 0; i < 6; i++) {
        rates.at<float>(0,i) /= totals.at<float>(0,i);
    }
    
    return rates;
}

vector<float> StatisticalClassifier::classProbabilities(Mat &segmentedHand) {
    Mat handCaracteristicVector = this->caracteristicVector(segmentedHand);
    return this->statisticalModel->probabilitiesVector(handCaracteristicVector);
}
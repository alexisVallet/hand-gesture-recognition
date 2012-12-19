#include "TrainableStatModel.h"

BayesModel::BayesModel() {
    this->internalStatModel = NULL;
}
    
BayesModel::BayesModel(CvNormalBayesClassifier *internalStatModel) {
    this->internalStatModel = internalStatModel;
}
    
CvStatModel *BayesModel::getStatModel() {
    return this->internalStatModel;
}

void BayesModel::train(Mat &trainData, Mat &expectedResponses) {
    this->internalStatModel->train(trainData, expectedResponses);
}

float BayesModel::predict(Mat &samples) {
    return this->internalStatModel->predict(samples);
}

KNearestModel::KNearestModel() : k(DEFAULT_K) {
}
    
KNearestModel::KNearestModel(CvKNearest *internalStatModel, int kValue) : k(kValue) {
    this->internalStatModel = internalStatModel;
}
    
CvStatModel *KNearestModel::getStatModel() {
    return this->internalStatModel;
}
    
void KNearestModel::train(Mat &trainData, Mat &expectedResponses) {
    this->internalStatModel->train(trainData, expectedResponses);
}
    
float KNearestModel::predict(Mat &samples) {
    return this->internalStatModel->find_nearest(samples, this->k);
}
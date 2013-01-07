#include "TrainableStatModel.h"

vector<float> TrainableStatModel::probabilitiesVector(Mat& segmentedHand) {
    vector<float> defaultResults(6, 0);
    defaultResults[(int)this->predict(segmentedHand)] = 1;
    
    return defaultResults;
}

BayesModel::BayesModel() {
}
    
CvStatModel *BayesModel::getStatModel() {
    return (CvStatModel*)&(this->internalStatModel);
}

void BayesModel::train(Mat &trainData, Mat &expectedResponses) {
    this->internalStatModel.train(trainData, expectedResponses);
}

float BayesModel::predict(Mat &samples) {
    return this->internalStatModel.predict(samples);
}

void BayesModel::clear() {
    this->internalStatModel.clear();
}

KNearestModel::KNearestModel() : k(DEFAULT_K) {
}
    
KNearestModel::KNearestModel(int kValue) : k(kValue) {
}
    
CvStatModel *KNearestModel::getStatModel() {
    return (CvStatModel*)&(this->internalStatModel);
}
    
void KNearestModel::train(Mat &trainData, Mat &expectedResponses) {
    this->internalStatModel.train(trainData, expectedResponses);
}
    
float KNearestModel::predict(Mat &samples) {
    return this->internalStatModel.find_nearest(samples, this->k);
}

void KNearestModel::clear() {
    this->internalStatModel.clear();
}

vector<float> KNearestModel::probabilitiesVector(Mat& sample) {
    vector<float> res(6,0);
    Mat neighborResponses;
    Mat results;
    Mat dists;
    this->internalStatModel.find_nearest(sample, this->k, results, neighborResponses, dists);
    
    for (int i = 0; i < this->k; i++) {
        res[round(neighborResponses.at<float>(0,i))] += 1.0/(float)k;
    }
    
    return res;
}

ANNModel::ANNModel() {
}

ANNModel::ANNModel(Mat layerSizes, int activateFunc, double fparam1, double fparam2)
: internalStatModel(layerSizes, activateFunc, fparam1, fparam2), fparam2(fparam2)
{
}

CvStatModel *ANNModel::getStatModel() {
    return (CvStatModel*)&(this->internalStatModel);
}

void ANNModel::train(Mat& trainData, Mat& expectedResponses) {
    Mat layerSizes = this->internalStatModel.get_layer_sizes();
    int lastLayerSize = layerSizes.at<int>(0, layerSizes.cols-1);
    Mat responsesVectors = Mat::zeros(expectedResponses.rows, lastLayerSize, CV_32F);
    for (int i = 0; i < expectedResponses.rows; i++) {
        responsesVectors.at<float>(i, expectedResponses.at<float>(i,0)) = 1;
    }
        
    this->internalStatModel.train(trainData, responsesVectors, Mat());
}

/**
 * Takes the value with highest probability.
 * 
 * @param samples
 * @return 
 */
float ANNModel::predict(Mat& samples) {
    Mat networkOutput;
    this->internalStatModel.predict(samples, networkOutput);
    Point2i maxIndex;
    minMaxLoc(networkOutput, NULL, NULL, NULL, &maxIndex);
    return (float)maxIndex.x;
}

/**
 * Doesn't do anything, as calling the train method
 * clears the previous synaptic weights. 
 */
void ANNModel::clear() {
    
}

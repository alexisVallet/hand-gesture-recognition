#include "TrainableStatModel.h"

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
    cout<<"computing last layer size"<<endl;
    Mat layerSizes = this->internalStatModel.get_layer_sizes();
    int lastLayerSize = layerSizes.at<int>(0, layerSizes.cols-1);
    Mat responsesVectors = Mat::zeros(expectedResponses.rows, lastLayerSize, CV_32F);
    cout<<"computing response vectors for neural network training"<<endl;
    for (int i = 0; i < expectedResponses.rows; i++) {
        responsesVectors.at<float>(i, expectedResponses.at<float>(i,0)) = 1;
    }
    
    cout<<"inputs: ("<<trainData.rows<<","<<trainData.cols<<"), outputs: ("<<responsesVectors.rows<<","<<responsesVectors.cols<<")"<<endl;
    
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
    cout<<"output: "<<networkOutput<<endl;
    minMaxLoc(networkOutput, NULL, NULL, NULL, &maxIndex);
    cout<<"max: "<<maxIndex<<endl;
    return (float)maxIndex.x;
}

/**
 * Doesn't do anything, as calling the train method
 * clears the previous synaptic weights. 
 */
void ANNModel::clear() {
    
}

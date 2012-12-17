/* 
 * File:   TrainableStatModel.h
 * Author: Alexis
 *
 * Created on 1 décembre 2012, 11:15
 */

#ifndef TRAINABLESTATMODEL_H
#define	TRAINABLESTATMODEL_H

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

/**
 * Wrapper around CvStatModels which implement a train and predict (-like)
 * method.
 */
class TrainableStatModel {
public:
    virtual CvStatModel *getStatModel() = 0;
    virtual void train(Mat &trainData, Mat &expectedResponses) = 0;
    virtual float predict(Mat &samples) = 0;
};

class BayesModel : public TrainableStatModel {
private:
    CvNormalBayesClassifier *internalStatModel;

public:    
    BayesModel() {
        this->internalStatModel = NULL;
    }
    
    BayesModel(CvNormalBayesClassifier *internalStatModel) {
        this->internalStatModel = internalStatModel;
    }
    
    CvStatModel *getStatModel() {
        return this->internalStatModel;
    }

    void train(Mat &trainData, Mat &expectedResponses) {
        this->internalStatModel->train(trainData, expectedResponses);
    }

    float predict(const Mat &samples) {
        return this->internalStatModel->predict(samples);
    }
};

#define DEFAULT_K 1

class KNearestModel : public TrainableStatModel {
private:
    int k;
    CvKNearest *internalStatModel;
    
public:
    KNearestModel() : k(DEFAULT_K) {
    }
    
    KNearestModel(CvKNearest *internalStatModel, int kValue = DEFAULT_K) : k(kValue) {
        this->internalStatModel = internalStatModel;
    }
    
    CvStatModel *getStatModel() {
        return this->internalStatModel;
    }
    
    void train(Mat &trainData, Mat &expectedResponses) {
        this->internalStatModel->train(trainData, expectedResponses);
    }
    
    float predict(Mat &samples) {
        return this->internalStatModel->find_nearest(samples, this->k);
    }
};

#endif	/* TRAINABLESTATMODEL_H */

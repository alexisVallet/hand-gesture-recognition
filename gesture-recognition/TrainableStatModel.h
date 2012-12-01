/* 
 * File:   TrainableStatModel.h
 * Author: Alexis
 *
 * Created on 1 décembre 2012, 11:15
 */

#ifndef TRAINABLESTATMODEL_H
#define	TRAINABLESTATMODEL_H

#include "opencv2/opencv.hpp"

using namespace cv;

/**
 * Wrapper around CvStatModels which implement a train and predict (-like)
 * method.
 */
template <typename T> 
class TrainableStatModel {
public:
    TrainableStatModel() {
        throw "TrainableStatModel: constructor is not implemented for this type.";
    }
    
    TrainableStatModel(T &internalStatModel) {
        throw "TrainableStatModel: constructor is not implemented for this type.";
    }
    
    CvStatModel &getStatModel() const {
        throw "TrainableStatModel: getStatModel is not implemented for this type.";
    }
    void train(Mat &trainData, Mat &expectedResponses) {
        throw "TrainableStatModel: train is not implemented for this type";
    }
    float predict(Mat &samples) {
        throw "TrainableStatModel: predict is not implemented for this type";
    }
};

template <>
class TrainableStatModel <CvNormalBayesClassifier> {
private:
    CvNormalBayesClassifier internalStatModel;
    
public:    
    TrainableStatModel() {
        
    }
    
    TrainableStatModel(CvNormalBayesClassifier &internalStatModel) {
        this->internalStatModel = internalStatModel;
    }
    
    CvStatModel &getStatModel() const {
        return (CvStatModel&)(this->internalStatModel);
    }
    void train(Mat &trainData, Mat &expectedResponses) {
        this->internalStatModel.train(trainData, expectedResponses);
    }
    float predict(const Mat &samples) {
        return this->internalStatModel.predict(samples);
    }
};

#endif	/* TRAINABLESTATMODEL_H */

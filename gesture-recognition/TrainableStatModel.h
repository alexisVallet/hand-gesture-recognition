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
    /**
     * Returns the opencv statistical model which this statistical model
     * is based on.
     * 
     * @return the opencv statistical model which this statistical model
     * is based on.
     */
    virtual CvStatModel *getStatModel() = 0;
    /**
     * Trains the classifier using a specific training base.
     * 
     * @param trainData the input training data.
     * @param expectedResponses the expected response to the training data.
     */
    virtual void train(Mat &trainData, Mat &expectedResponses) = 0;
    /**
     * Predicts the class of a sample.
     * 
     * @param samples one or many samples to compute the class for.
     * @return the predicted class of the sample.
     */
    virtual float predict(Mat &samples) = 0;
};

/**
 * Wrapper class for Bayes's classifier.
 */
class BayesModel : public TrainableStatModel {
private:
    CvNormalBayesClassifier *internalStatModel;

public:    
    BayesModel();
    
    BayesModel(CvNormalBayesClassifier *internalStatModel);
    
    CvStatModel *getStatModel();

    void train(Mat &trainData, Mat &expectedResponses);

    float predict(Mat &samples);
};

#define DEFAULT_K 1

/**
 * Wrapper class around the K nearest neighbors classifier.
 */
class KNearestModel : public TrainableStatModel {
private:
    int k;
    CvKNearest *internalStatModel;
    
public:
    KNearestModel();
    
    KNearestModel(CvKNearest *internalStatModel, int kValue = DEFAULT_K);
    
    CvStatModel *getStatModel();
    
    void train(Mat &trainData, Mat &expectedResponses);
    
    float predict(Mat &samples);
};

#endif	/* TRAINABLESTATMODEL_H */

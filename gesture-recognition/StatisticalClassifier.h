/* 
 * File:   StatisticalClassifier.h
 * Author: Alexis
 *
 * Created on 23 novembre 2012, 18:10
 */

#ifndef STATISTICALCLASSIFIER_H
#define	STATISTICALCLASSIFIER_H

#include "opencv2/ml/ml.hpp"
#include "Classifier.h"
#include "TrainableClassifier.h"
#include "TrainableStatModel.h"
#include "math.h"

/**
 * A statistical classifier is a classifier which classifies the segmented
 * hand in 2 (possibly 3) steps:
 * 
 * 1. Computing a caracteristic vector of the hand.
 * 
 * 2. Classifies the caracteristic vector into classes using a statistical
 * model (ie Bayes classifier, 
 * 
 * 3. (Optional) Computes the number of fingers from the classifier result.
 * This may be useful for aggregating classes into one. By default, rounds
 * the result of the classifier.
 */
class StatisticalClassifier : public TrainableClassifier {
public:
    StatisticalClassifier() {
    }
    /**
     * Initializes the statistical classifier from a given statistical model.
     *
     * @param statisticalModel the statistical model used to classify the
     * caracteristic vector.
     */
    StatisticalClassifier(TrainableStatModel *statisticalModel);
    /**
     * Returns the opencv statistical model this classifier uses.
     */
    TrainableStatModel *getStatisticalModel();
    /**
     * Returns a caracteristic vector for a segmented hand. This caracteristic
     * vector will be used to classify the hand.
     * 
     * @param segmentedHand the hand to classify
     * @return the hand's caracteristic vector for classification
     */
    virtual Mat caracteristicVector(const Mat &segmentedHand) = 0;
    /**
     * Predicts the class a specific caracteristic vector belongs to using
     * previous training data. If numberOfFingersFromClassifierResult is not
     * overridden, this result is simply the number of fingers.
     * 
     * @param caracteristicVector caracteristic vector of the hand to classify.
     * @return the predicted class of the caracteristic vector.
     */
    float predict(Mat &caracteristicVector);
    /**
     * Returns the number from the result returnes by the opencv statistical
     * model. By default just rounds the result of the classifier.
     * 
     * @param classifierResult result of the classifier.
     * @return the computed number of fingers.
     */
    virtual int numberOfFingersFromClassifierResult(float classifierResult);
    /**
     * Returns the length of the caracteristic vectors computed by this
     * classifier.
     * @return the length of the caracteristic vectors computed by this
     * classifier.
     */
    virtual int caracteristicVectorLength(void) = 0;
    /**
     * Computes the recognition rate of the classifier using the leave one out
     * method. This method consists in classifying by using the sample we want to
     * classify as the test base and the rest as the training base. As a result,
     * the training base changes for each sample, but this allows us to compute
     * a recognition rate even with a small amount of data.
     * 
     * @param baseInputs the entire sample data inputs
     * @param baseOutputs the entire sample data outputs
     * @return a recognition rate between 0 and 1
     */
    float leaveOneOutRecognitionRate(vector<Mat> baseInputs, vector<int> baseOutputs);
    /**
     * Compute the recognition rate of the classifier for each number of
     * fingers using the leave one out method.
     * 
     * @param baseInputs the entire sample data inputs
     * @param baseOutputs the entire sample data outputs
     * @return a line vector with recognition rate for each number of fingers.
     */
    Mat leaveOneOutRecognitionRatePerClass(vector<Mat> baseInputs, vector<int> baseOutputs);
    
    int numberOfFingers(Mat &segmentedHand);
    virtual void train(
        const vector<Mat> &segmentedHands,
        const vector<int> &expectedClass);

    void load(const char *filepath);

    void save(const char *filepath);

    vector<float> classProbabilities(Mat &segmentedHand);
    
protected:
    TrainableStatModel *statisticalModel;
};

#endif	/* STATISTICALCLASSIFIER_H */

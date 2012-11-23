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
#include "math.h"

typedef float (*PredictionFunction)(CvStatModel, Mat&);

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
class StatisticalClassifier : Classifier {
public:
    StatisticalClassifier();
    /**
     * Initializes the statistical classifier from a given statistical model
     * and a given prediction function. The prediction function returns the
     * result of the classifier given as parameter. This is useful to 
     * encapsulate additional parameters, for instance K nearest neighbors 
     * requires an additional parameter (K). In most cases, it simply means
     * calling the predict method on the CvStatModel.
     *
     * @param statisticalModel the statistical model used to classify the
     * caracteristic vector.
     * @param predict the prediction function to classify samples with.
     */
    StatisticalClassifier(const CvStatModel &statisticalModel, PredictionFunction predict);
    const CvStatModel &getStatisticalModel();
    virtual Mat caracteristicVector(Mat &segmentedHand) = 0;
    virtual int numberOfFingersFromClassifierResult(float classifierResult);
    int numberOfFingers(Mat &segmentedHand);
    
private:
    PredictionFunction predict;
    CvStatModel statisticalModel;
};

#endif	/* STATISTICALCLASSIFIER_H */


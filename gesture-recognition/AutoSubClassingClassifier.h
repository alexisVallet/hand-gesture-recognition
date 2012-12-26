/* 
 * File:   AutoSubClassingClassifier.h
 * Author: Alexis
 *
 * Created on 20 décembre 2012, 08:09
 */

#ifndef AUTOSUBCLASSINGCLASSIFIER_H
#define	AUTOSUBCLASSINGCLASSIFIER_H

#include "StatisticalClassifier.h"

#include "opencv2/opencv.hpp"
#include <algorithm>

using namespace cv;
using namespace std;

/**
 * This class implements a statistical classifier in which subclasses of number
 * of fingers are automatically computed by clustering using the K means
 * algorithm.
 */
class AutoSubClassingClassifier : public StatisticalClassifier {
public:
    AutoSubClassingClassifier();
    /**
     * Initializes the classifier by specifying the number of subclasses each
     * class should have.
     * 
     * @param numberOfSubclassesPerClass array associating to a class number its
     * number of subclasses.
     * @param statisticalModel internal statistical model to be used.
     */
    AutoSubClassingClassifier(vector<int> numberOfSubclassesPerClass, TrainableStatModel *statisticalModel);
    /**
     * Trains the model, first refining the expected classes into subclasses
     * using the K means algorithm.
     * 
     * @param segmentedHands segmented hand to use as a training set.
     * @param expectedClass number of fingers for each hand in segmentedHands.
     */
    void train(
        const vector<Mat> &segmentedHands,
        const vector<int> &expectedClass);
    /**
     * Returns the number of finger by associating each subclass to its
     * containing class (ie number of fingers).
     * 
     * @param classifierResult result from the internal statistical model.
     * @return the number of fingers corresponding to the subclass.
     */
    int numberOfFingersFromClassifierResult(float classifierResult);
    
private:
    vector<int> numberOfSubclasses;
    vector<Mat> subclassesOfTrainingBase;
};

#endif	/* AUTOSUBCLASSINGCLASSIFIER_H */


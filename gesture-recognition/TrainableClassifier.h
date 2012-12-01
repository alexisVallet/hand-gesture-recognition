/* 
 * File:   TrainableClassifier.h
 * Author: Alexis
 *
 * Created on 1 décembre 2012, 07:29
 */

#ifndef TRAINABLECLASSIFIER_H
#define	TRAINABLECLASSIFIER_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "Classifier.h"

using namespace std;
using namespace cv;

/**
 * Abstract classifier that can be trained with an input set and a desired output
 * set. The result of the training should be saveable and loadable to and
 * from a file.
 */
class TrainableClassifier : Classifier {
public:
    /**
     * Trains the classifier using an input vector of segmented hands, and
     * their respective expected class. Both vectors should have
     * size n. Let 0 <= i < n, then segmentedHands[i] is in class 
     * expectedClass[i].
     * 
     * @param segmentedHands segmented hands constituting the training base
     * input for the classifier.
     * @param expectedClass class
     */
    virtual void train(
        const vector<Mat> &segmentedHands, 
        const vector<int> &expectedClass) = 0;
    /**
     * Saves the result of the training to a file.
     * 
     * @param filepath file to write training results to.
     */
    virtual void save(const char *filepath) = 0;
    /**
     * Loads the training results from a file.
     * 
     * @param filepath file to load training results from.
     */
    virtual void load(const char *filepath) = 0;
};

#endif	/* TRAINABLECLASSIFIER_H */

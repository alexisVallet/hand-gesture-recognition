/* 
 * File:   Classifier.h
 * Author: Alexis
 *
 * Created on 23 novembre 2012, 18:02
 */

#ifndef CLASSIFIER_H
#define	CLASSIFIER_H

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

/**
 * A classifier for hand gesture recognition. Takes a segmented and binarized
 * hand image as a parameter, and returns its number of fingers.
 */
class Classifier {
public:
    /**
     * Computes the number of fingers of the hand image. The
     * image is expected to be segmented and cropped (ie only the hand in its
     * bounding box is left in) and binarized (pixels of the hand
     * have value 1, pixels of the background have value 0).
     * 
     * @param segmentedHand the segmented, binarized and cropped hand image
     * @return the number of lifted fingers of the hand.
     */
    virtual int numberOfFingers(Mat &segmentedHand) = 0;
    /**
     * Computes the probability of the segmented hand to belong to each class
     * (ie number of fingers).
     * 
     * @param segmentedHand the segmented, binarized and cropped hand image
     * @return the probability vector for the hand
     */
    virtual vector<float> classProbabilities(Mat &segmentedHand);
    /**
     * Computes the recognition rate of the classifier using a specific test
     * set.
     * 
     * @param handsToRecognize segmented hands to recognize.
     * @param expectedNumberOfFingers number of finger of each hand in the input.
     * @return the recognition rate of the classifier for this test set.
     */
    float recognitionRate(vector<Mat> handsToRecognize, vector<int> expectedNumberOfFingers);
    /**
     * Computes the recognition rate of the classifier for each number of fingers
     * using a specific test set.
     * 
     * @param handsToRecognize segmented hands to recognize.
     * @param expectedNumberOfFingers number of finger of each hand in the input.
     * @return the recognition rate of the classifier for this test set.
     */
    vector<float> recognitionRatePerClass(vector<Mat> handsToRecognize, vector<int> expectedNumberOfFingers);
};

#endif	/* CLASSIFIER_H */


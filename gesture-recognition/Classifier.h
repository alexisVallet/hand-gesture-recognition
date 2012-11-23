/* 
 * File:   Classifier.h
 * Author: Alexis
 *
 * Created on 23 novembre 2012, 18:02
 */

#ifndef CLASSIFIER_H
#define	CLASSIFIER_H

#include "opencv2/opencv.hpp"

using namespace cv;

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
};

#endif	/* CLASSIFIER_H */


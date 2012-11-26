/* 
 * File:   HandDirection.h
 * Author: Alexis
 *
 * Created on 24 novembre 2012, 08:45
 */

#ifndef HANDDIRECTION_H
#define	HANDDIRECTION_H

#include <utility>
#include <iostream>
#include "opencv2/opencv.hpp"

#include "ClassifierParameters.h"

/**
 * Returns the position of the pixels belonging to the hand as a 2xn matrix,
 * where columns are pixel coordinates. Assumes that the hand image is integer
 * valued, with HAND_PIXEL_VALUE (defined in ClassifierParameters.h at the moment) 
 * for the hand pixels.
 * 
 * @param segmentedHand the segmented, cropped and binarized hand image.
 * @return a 2 lines matrix where columns are hand pixels coordinates.
 */
cv::Mat handPixels(const cv::Mat &segmentedHand);

/**
 * Computes the direction of the hand using principal component
 * analysis. Returns the 2 eigenvectors of the covariance matrix
 * of the hand pixels. Should be more reliable if the segmentation
 * includes the wrist.
 * 
 * @param segmentedHand the segmented, cropped and binarized hand
 * @return direction vectors of the hand.
 */
std::pair < cv::Mat,cv::Mat > handDirection(const cv::Mat& segmentedHand);

#endif	/* HANDDIRECTION_H */

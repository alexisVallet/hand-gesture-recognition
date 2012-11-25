/* 
 * File:   HandDirection.h
 * Author: Alexis
 *
 * Created on 24 novembre 2012, 08:45
 */

#ifndef HANDDIRECTION_H
#define	HANDDIRECTION_H

#define HAND_PIXEL_VALUE 1
#define BACKGROUND_PIXEL_VALUE 0

#include <utility>
#include <iostream>
#include "opencv2/opencv.hpp"

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

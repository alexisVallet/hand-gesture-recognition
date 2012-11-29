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

using namespace cv;

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
 * of the hand pixels. Does not guarantee the direction of the fingers,
 * the returned vector can point the other way, but it should be colinear
 * Takes hand pixels as an additional parameter.
 * 
 * @param segmentedHand the segmented, cropped and binarized hand
 * @return direction vectors of the hand.
 */
std::pair < Mat,Mat > handDirectionPCA(const Mat &segmentedHand, Mat &handPixelsMatrix);

/**
 * Computes the direction of the hand using principal component
 * analysis. Returns the 2 eigenvectors of the covariance matrix
 * of the hand pixels. Does not guarantee the direction of the fingers,
 * the returned vector can point the other way, but it should be colinear
 * 
 * 
 * @param segmentedHand the segmented, cropped and binarized hand
 * @return direction vectors of the hand.
 */
std::pair < cv::Mat,cv::Mat > handDirection(const cv::Mat &segmentedHand);

/**
 * Estimates the center of the palm by first eroding the hand with a kernel
 * large enough to remove fingers, then computing the center of mass of what
 * remains (hopefully the palm). If the erosion leaves no white pixels on the
 * image, this function returns (-1,-1).
 * 
 * @param segmentedHand the hand for which we want to estimate the palm center.
 * @param maxFingerWidth maximum width of a finger
 * @return an estimation of the center of mass of the palm.
 */
Point2f estimatePalmCenter(const Mat &segmentedHand, int maxFingerWidth);

/**
 * Computes the mass center of the hand by computing the mean of the hand
 * pixel positions. When passed an empty image (with no white pixels), this
 * function returns (-1,-1).
 * 
 * @param segmentedHand hand to compute the mass center for.
 * @return the mass center of the hand.
 */
Point2f computeMassCenter(const Mat &segmentedHand);

#endif	/* HANDDIRECTION_H */

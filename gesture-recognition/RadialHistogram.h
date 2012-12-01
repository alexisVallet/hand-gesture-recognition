/* 
 * File:   RadialHistogram.h
 * Author: Alexis
 *
 * Created on 25 novembre 2012, 17:26
 */

#ifndef RADIALHISTOGRAM_H
#define	RADIALHISTOGRAM_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

#include "HandDirection.h"

using namespace cv;

/**
 * Computes the radial histogram of a segmented, binarized and cropped
 * hand image around the center of mass of the hand.
 * 
 * @param segmentedHand the image for which to compute the radial histogram
 * @param histogram output radial histogram. Normalized and float valued.
 * @param numberOfBins the number of bins to sample the histogram with
 */
void radialHistogram(const Mat &segmentedHand, MatND &histogram, int numberOfBins);

/**
 * Computes the radial histogram of a segmented, binarized and cropped
 * hand image around a user-supplied center point.
 * 
 * @param segmentedHand the image for which to compute the radial histogram
 * @param histogram output radial histogram. Normalized and float valued.
 * @param numberOfBins the number of bins to sample the histogram with
 * @param center center point to compute the histogram around.
 */
void radialHistogramWithCenter(const Mat &segmentedHand, MatND &histogram, int numberOfBins, Point2f center);

#endif	/* RADIALHISTOGRAM_H */

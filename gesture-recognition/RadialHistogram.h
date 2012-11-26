/* 
 * File:   RadialHistogram.h
 * Author: Alexis
 *
 * Created on 25 novembre 2012, 17:26
 */

#ifndef RADIALHISTOGRAM_H
#define	RADIALHISTOGRAM_H

#include "opencv2/opencv.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

#include "HandDirection.h"

using namespace cv;

/**
 * Computes the radial histogram of a segmented, binarized and cropped
 * hand image.
 * 
 * @param segmentedHand the image for which to compute the radial histogram
 * @param histogram output radial histogram.
 */
void radialHistogram(const Mat &segmentedHand, OutputArray histogram);

#endif	/* RADIALHISTOGRAM_H */


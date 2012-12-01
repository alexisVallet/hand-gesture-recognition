/* 
 * File:   Crop.h
 * Author: Alexis
 *
 * Created on 30 novembre 2012, 08:58
 */

#ifndef CROP_H
#define	CROP_H

#include "opencv2/opencv.hpp";

using namespace cv;

/**
 * Crops a segmented hand image so it only includes its
 * bounding box.
 * 
 * @param segmentedHand segmented, binarized hand
 * @param croppedHand output cropped hand
 */
void crop(Mat &segmentedHand, Mat &croppedHand);

#endif	/* CROP_H */


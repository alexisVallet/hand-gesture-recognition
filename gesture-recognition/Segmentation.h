/* 
 * File:   Segmentation.h
 * Author: Quentin
 *
 * Created on 1 décembre 2012, 15:19
 */

#ifndef SEGMENTATION_H
#define	SEGMENTATION_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

using namespace cv;

/* 
 * Fisher Thresholding and
 * Segment an image from source and save it on destination
 */
void Segment(const Mat& source, Mat& destination);

/* Same function as Segment, but, it clean the image before
 * Fisher and segmentation. (Scatters pixels which are harmful for histogram 
 * equalizarion are deleted).
 */
void specialSegmentation(const Mat& source, Mat& destination);

int segmentHand(const Mat& source);

/* 
 * Inverse a binary image
 */
void inverse(Mat& matrix);

/*
 * Normalize an gray scaled image
 */
void normalize(Mat& ims);

#endif	/* SEGMENTATION_H */
/* 
 * File:   HandSideDetection.h
 * Author: Alexis
 *
 * Created on 12 décembre 2012, 17:53
 */

#ifndef HANDSIDEDETECTION_H
#define	HANDSIDEDETECTION_H

#include "opencv2/opencv.hpp"

#include "HandDirection.h"

using namespace cv;

typedef enum {LEFT_HAND, RIGHT_HAND, UNDEFINED_SIDE} HandSide;

/**
 * This function tries to detect the side of the hand, eg. if it is a
 * left hand or a right hand. It does so by comparing the horizontal
 * position of the center of the palm compared to the center of the entire hand.
 * It the difference is greater than an epsilon on one side, we assume the
 * thumb is on this side. If the difference is too small, this function returns
 * UNDEFINED_SIDE.
 * 
 * @param rotatedHand the binarized, cropped hand rotated so the hand is
 * oriented vertically.
 * @param epsilon a positive number defining the difference threshold 
 * @return a prediction of the hand side.
 */
HandSide detectHandSide(Mat &rotatedHand, float epsilon);

#endif	/* HANDSIDEDETECTION_H */

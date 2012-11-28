/* 
 * File:   RedressHand.h
 * Author: Alexis
 *
 * Created on 28 novembre 2012, 10:38
 */

#ifndef REDRESSHAND_H
#define	REDRESSHAND_H

#include "opencv2/opencv.hpp"

using namespace cv;

/**
 * Rotates the hand by a given angle, then crops it.
 * 
 * @param segmentedHand
 * @param rotatedHand
 * @param angle in radians.
 */
void rotateHand(const Mat &segmentedHand, Mat &rotatedHand, double angle);

#endif	/* REDRESSHAND_H */


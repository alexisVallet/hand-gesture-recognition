/* 
 * File:   Symmetry.h
 * Author: Alexis
 *
 * Created on 12 décembre 2012, 19:33
 */

#ifndef SYMMETRY_H
#define	SYMMETRY_H

#include "opencv2/opencv.hpp"

using namespace cv;

/**
 * Computes the symmetry of an image from the vertical axis at the center
 * of the image.
 * 
 * @param inputImage input image to compute the symmetry from.
 * @param outputImage transformed image.
 */
void horizontalSymmetry(Mat &inputImage, Mat &outputImage);

/**
 * Computes the symmetry of an image from the horizontal axis at the center of
 * the image.
 * 
 * @param inputImage input image to compute the symmetry from.
 * @param outputImage transformed image.
 */
void verticalSymmetry(Mat &inputImage, Mat &outputImage);

#endif	/* SYMMETRY_H */


/* 
 * File:   pClearHand.hpp
 * Author: Alexis
 *
 * Created on 21 novembre 2012, 14:00
 */

#ifndef PCLEARHAND_HPP
#define	PCLEARHAND_HPP

#include <stdio.h>
#include <pandore.h>
#include <vector>
#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#define _WHITE 255
#define _BLACK 0


#define PRECISION 5
#define LOOP 3

using namespace cv;

// Test color of a given pixel
inline void testBLACK(Mat & ims, cv::Point2d& cursor, int & counter);

// This function deletes scatters pixels. It cleans and erodes an hand.
void clearHand(Mat& imd);


// Test color of a given pixel
inline void testWHITE(Mat & ims, cv::Point2d& cursor, int & counter);

// This function deletes scatters pixels on a 256 Grey Levels Pixels.
// This function should correct segmentation failing on few images of Third Group of images.
void clearHandBeforeBinarization(Mat& imd);



#endif	/* PCLEARHAND_HPP */

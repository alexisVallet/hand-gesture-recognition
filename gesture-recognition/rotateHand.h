/* 
 * File:   rotateHand.h
 * Author: VIRTUAL_BUG
 *
 * Created on 29 novembre 2012, 11:51
 */

#ifndef ROTATEHAND_H
#define	ROTATEHAND_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

using namespace cv;
using namespace std;


void rotateHand(const Mat &segmentedHand, Mat &rotatedHand, double angle) ;
Mat redressHandFromBinarySegmentedImage(Mat hand, int handPxValue);
void translate(int x, int y, const Mat &src, Mat &dest);


#endif	/* ROTATEHAND_H */


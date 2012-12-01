/* 
 * File:   convert.hpp
 * Author: Quentin Dorléat
 *
 * Created on 25 novembre 2012, 16:50
 */

#ifndef CONVERT_HPP
#define	CONVERT_HPP

#include <stdio.h>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include "utilsFunctions.h"
#include "pandore.h"

using namespace cv;
using namespace pandore;

/*
 * These functions are operators convertors betwenn pandore Img2duc format 
 * and OpenCV Mat format
 */

Mat _PanToMat(const Img2duc &ims);
Img2duc _MatToPan(const Mat &matrix);

/*
 * This function allows to switch between Mat and IplImage OpenCV formats.
 */

Mat IplToMat(IplImage &src);

#endif	/* CONVERT_HPP */




/* 
 * File:   utilsFunctions.h
 * Author: VIRTUAL_BUG
 *
 * Created on 24 novembre 2012, 14:31
 */
#ifndef UTILSFUNCTIONS_H
#define	UTILSFUNCTIONS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include <iostream>
#include <dirent.h>

using namespace cv;
using namespace std;




IplImage * loadYml(const char * filename);
void calcHist(IplImage * img);
void calculBounds(Mat img, int &xMin, int &xMax, int &yMin, int &yMax);
void extractSubimageFromBounds(Mat img, Mat &dest, int xMin, int xMax, int yMin, int yMax);
void revertBinarize(Mat &img, int seuil);
Mat IplToMat(IplImage &src);
float * horizontalProfiling(Mat img);
void convertAllYMLImageFromPath();
Mat extractHandFromBMPFile(string filename);
Mat extractHandFromBinarizedMat(Mat &img);



#endif	/* UTILSFUNCTIONS_H */


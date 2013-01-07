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





void calcHist(IplImage * img);
void calculBounds(Mat img, int &xMin, int &xMax, int &yMin, int &yMax);
void extractSubimageFromBounds(Mat img, Mat &dest, int xMin, int xMax, int yMin, int yMax);
void binarize(Mat &img, int seuil, bool invert);
Mat IplToMat(IplImage &src);
float * horizontalProfiling(Mat img);
void convertAllYMLImageFromPath();
Mat extractHandFromBMPFile(string filename);
Mat extractHandFromBinarizedMat(Mat &img);

Mat greyscale(Mat &img);

void readPath(vector< vector<string> > &base, string dir, string fileExtension);
IplImage * MatToIpl(Mat &src);
void binarizeFile(string path, int seuil);

void readPath2(vector< vector<string> > &base, vector< int >&classCorrespondances, string dir, string fileExtension);

int getMaxIndexFromTab(float * tab, int size);

//distance euclidienne entre deux vecteurs de taille égale    
float distanceBetweenVectors(float * vec1, float * vec2, int size);

void ymlToBmp(string src, string dest);


#endif	/* UTILSFUNCTIONS_H */


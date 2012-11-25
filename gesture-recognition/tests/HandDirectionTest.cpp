/* 
 * File:   HandDirectionTest.cpp
 * Author: Alexis
 *
 * Created on 24 nov. 2012, 10:27:26
 */

#include <stdlib.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "HandDirection.h"

using namespace cv;
using namespace std;

void drawVector(Mat &image, Mat vector, const Scalar &color) {
    Point center(image.cols/2, image.rows/2);
    Point vectorEnd(center.x + vector.at<float>(0,0), center.y + vector.at<float>(0,1));
    line(image, center, vectorEnd, color);
}

void showHandAndDirection(string filepath) {
    Mat segmentedHandRGB = imread(filepath);
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat segmentedHandBin = segmentedHandGray / 255;
    pair<Mat,Mat> directions = handDirection(segmentedHandBin);
    cout<<directions.first<<";"<<directions.second<<endl;
    Mat handAndVectors = segmentedHandRGB;
    drawVector(handAndVectors, directions.first * 20, CV_RGB(255,0,0));
    drawVector(handAndVectors, directions.second * 20, CV_RGB(0,255,0));
    namedWindow(filepath);
    imshow(filepath, handAndVectors);
}

int main(int argc, char** argv) {
    showHandAndDirection(".\\test-segmented-5-2.bmp");
    showHandAndDirection(".\\test-segmented-5-2-wristless.bmp");
    showHandAndDirection(".\\test-segmented-1.bmp");
    showHandAndDirection(".\\test-segmented-1-wristless.bmp");
    showHandAndDirection(".\\test-segmented-5.bmp");
    showHandAndDirection(".\\test-segmented-5-wristless.bmp");
    waitKey(0);
    
    return (EXIT_SUCCESS);
}

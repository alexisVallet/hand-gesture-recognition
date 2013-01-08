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
#include "utilsFunctions.h"

using namespace cv;
using namespace std;

void drawVector(Mat &image, Mat vector, const Scalar &color) {
    Point center(image.cols/2, image.rows/2);
    Point vectorEnd(center.x + vector.at<float>(0,0), center.y + vector.at<float>(0,1));
    line(image, center, vectorEnd, color);
}

void showHandAndDirection(string filepath) {
    Mat segmentedHandBin = extractHandFromBMPFile("./runFolder/ClassImages2/2/0.bmp");
    cout<<"computing directions"<<endl;
    pair<Mat,Mat> directions = handDirection(segmentedHandBin);
    cout<<directions.first<<";"<<directions.second<<endl;
    Mat handAndVectors;
    cvtColor(segmentedHandBin, handAndVectors, CV_GRAY2RGB);
    drawVector(handAndVectors, directions.first * 20, CV_RGB(255,0,0));
    drawVector(handAndVectors, directions.second * 20, CV_RGB(0,255,0));
    namedWindow(filepath);
    imshow(filepath, handAndVectors);
}

int main(int argc, char** argv) {
    showHandAndDirection("./runFolder/test-segmented-5-2.bmp");
    showHandAndDirection("./runFolder/test-segmented-5-2-wristless.bmp");
    showHandAndDirection("./runFolder/test-segmented-1.bmp");
    showHandAndDirection("./runFolder/test-segmented-1-wristless.bmp");
    showHandAndDirection("./runFolder/test-segmented-5.bmp");
    showHandAndDirection("./runFolder/test-segmented-5-wristless.bmp");
    waitKey(0);
    
    return (EXIT_SUCCESS);
}

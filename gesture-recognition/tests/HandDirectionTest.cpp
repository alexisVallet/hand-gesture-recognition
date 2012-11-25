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

int main(int argc, char** argv) {
    Mat segmentedHandRGB = imread("C:\\Users\\Alexis\\Documents\\Dev\\IN5x\\in5x-gesture-recognition\\gesture-recognition\\runFolder\\test-segmented-2.bmp");
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat segmentedHandBin = segmentedHandGray / 255;
    cout<<"Binhand="<<segmentedHandBin<<endl;
    pair<Mat,Mat> directions = handDirection(segmentedHandBin);
    cout<<directions.first<<";"<<directions.second<<endl;
    imshow("Out", segmentedHandGray);
    waitKey(0);
    
    return (EXIT_SUCCESS);
}

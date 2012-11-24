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
    Mat segmentedHandGray = imread("test-segmented-2.bmp");
    cout<<"Image loaded"<<endl;
    namedWindow("Out", CV_WINDOW_AUTOSIZE);
    cout<<"Window opened"<<endl;
    imshow("Out", segmentedHandGray);
    cout<<"Image shown"<<endl;
    waitKey(0);
    
    return (EXIT_SUCCESS);
}


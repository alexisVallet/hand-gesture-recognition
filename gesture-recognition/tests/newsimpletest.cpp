/* 
 * File:   newsimpletest.cpp
 * Author: Alexis
 *
 * Created on 28 nov. 2012, 10:50:07
 */

#include <stdlib.h>
#include <iostream>

#include "RedressHand.h"

using namespace cv;
using namespace std;

/*
 * Simple C++ Test Suite
 */

int main(int argc, char** argv) {
    Mat hand = imread("C:/Users/Alexis/Documents/Dev/IN5x/in5x-gesture-recognition/gesture-recognition/runFolder/7.bmp");
    Mat rotated;
    
    rotateHand(hand, rotated, M_PI/3);
    
    namedWindow("pouet");
    imshow("pouet", rotated);
    waitKey(0);
    
    return (EXIT_SUCCESS);
}


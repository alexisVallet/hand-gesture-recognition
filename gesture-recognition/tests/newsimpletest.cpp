/* 
 * File:   newsimpletest.cpp
 * Author: Alexis
 *
 * Created on 28 nov. 2012, 10:50:07
 */

#include <stdlib.h>
#include <iostream>

#include "rotateHand.h"
#include "utilsFunctions.h"

using namespace cv;
using namespace std;

/*
 * Simple C++ Test Suite
 */

int main(int argc, char** argv) {
    Mat handGray = extractHandFromBMPFile("./runFolder/13.bmp");
    Mat redressed = redressHandFromBinarySegmentedImage(handGray, 255);
    
    namedWindow("pouet");
    imshow("pouet", redressed);
    waitKey(0);
    
    return (EXIT_SUCCESS);
}


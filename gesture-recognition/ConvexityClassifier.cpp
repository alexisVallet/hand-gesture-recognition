/* 
 * File:   ConvexityClassifier.cpp
 * Author: ALEXANDRE-BARFF
 * 
 * Created on 26 novembre 2012, 08:49
 */

#include "ConvexityClassifier.h"

ConvexityClassifier::ConvexityClassifier() {
}

ConvexityClassifier::ConvexityClassifier(const ConvexityClassifier& orig) {
}

ConvexityClassifier::~ConvexityClassifier() {
}

int ConvexityClassifier::numberOfFingers(Mat &segmentedHand) {
    
    Mat tmp, out;
    tmp = segmentedHand;
    
    /*Compute Median Blur*/
    medianBlur( tmp , out, 15 );
    
    /**/
    
}

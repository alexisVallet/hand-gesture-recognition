/* 
 * File:   ConvexityClassifier.h
 * Author: ALEXANDRE-BARFF
 *
 * Created on 26 novembre 2012, 08:49
 */

#ifndef CONVEXITYCLASSIFIER_H
#define	CONVEXITYCLASSIFIER_H

#include "opencv2/ml/ml.hpp"
#include "Classifier.h"
#include "math.h"

/**
 * A convexity classifier which classifies the segmented hand in 5 (possibly 6)
 * steps:
 * 
 * #1: Median filter
 * #2: Contour Plot of Hand
 * #3: Hand Contour Approximation by Polygon
 * #4: Convexities points Detection
 * #5: Convexities points Filtering
 * #6: Find out the Result of Hand Signing
 * 
 */
class ConvexityClassifier : Classifier {
public:
    ConvexityClassifier();
    ConvexityClassifier(const ConvexityClassifier& orig);
    virtual ~ConvexityClassifier();    
    /**
     * Return the Number of Fingers identify by the Classifier
     * 
     * @param segmentedHand the binarise image of the hand
     */
    int numberOfFingers(Mat &segmentedHand);
private:

};

#endif	/* CONVEXITYCLASSIFIER_H */


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
class ConvexityClassifier : public Classifier {
public:
    ConvexityClassifier();
    ConvexityClassifier(const ConvexityClassifier& orig);
    virtual ~ConvexityClassifier();
    float Compute_Distance( Point a , Point b );
    void findConvexityDefects(vector<Point>& contour, vector<int>& hull, vector<Point>& convexDefects);    
    vector<Point> BiggestContour( vector<vector<Point> > contours_points );
    vector<Point> Filtering_Concave_Point( vector<Point> convexDefects , RotatedRect Palm );
    vector<int> Filtering_Convex_Point( vector<int> hull , vector<Point> contour , RotatedRect Palm );
    vector<int> Isolating_Convex_Point( vector<int> Convex_points , vector<Point> contour );
    vector<int> Isolating_Convex_Point_byAverage( vector<Point> contour , vector<Point> Concave_points , float min_distance , vector<int> tmp );
    int Compute_Result( vector<Point> contour , vector<Point> Concave_points , vector<int> result , float min_distance );
    int Convexity_Computing(Mat &segmentedHand);
    /**
     * Return the Number of Fingers identify by the Classifier
     * 
     * @param segmentedHand the binarise image of the hand
     */
    int numberOfFingers(Mat &segmentedHand);
private:

};

#endif	/* CONVEXITYCLASSIFIER_H */


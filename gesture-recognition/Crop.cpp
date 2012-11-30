/* 
 * File:   Crop.cpp
 * Author: Alexis
 * 
 * Created on 30 novembre 2012, 08:58
 */

#include "Crop.h"

void crop(Mat &segmentedHand, Mat &croppedHand) {
    // code taken from 
    // http://stackoverflow.com/questions/3669611/bounding-box-using-opencv
    vector<vector<Point> > v;
    // Finds contours
    findContours(segmentedHand,v,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

    // Finds the contour with the largest area
    int area = 0;
    int idx;
    for(int i=0; i<v.size();i++) {
        if(area < v[i].size())
            idx = i; 
    }

    // Calculates the bounding rect of the largest area contour
    Rect rect = boundingRect(v[idx]);
    getRectSubPix(
        segmentedHand,
        rect.size(),
        Point2f(rect.x + rect.width/2.0, rect.y + rect.height/2.0),
        croppedHand);
}

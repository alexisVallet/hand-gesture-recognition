/* 
 * File:   ConvexityClassifier_TEST.cpp
 * Author: ALEXANDRE-BARFF
 *
 * Created on 30 nov. 2012, 23:21:48
 */

#include <stdlib.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

/*
 * Simple C++ Test Suite
 */


void ShowConvexityPoints(string filepath) {
    
    Mat out;//,contours_points,polygon;
    vector<Point> contours,polygon;
    vector<int> hull;
    vector<Vec4i> hierarchy,convexityDefects;
    vector<vector<Point> > contours_points;
    Mat segmentedHandRGB = imread(filepath);
    imshow(filepath, segmentedHandRGB);
    
    /*CONVERSION FORMAT: Grayscale */
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    
    /*Computing Convexity Classifier*/
    medianBlur(segmentedHandGray,out,15);
    
    /*Looking for Contours Points*/
    findContours( out, contours_points, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE );
    
    /*Convert vector<vector<Point>> to vector<Point>*/
    for(int i = 0; i < contours_points.size() ; i++){
        for(int j = 0; j < contours_points[i].size() ; j++){
            contours.push_back(contours_points[i][j]);
        }
    }
    
    /*Drawing Contours*/
    Scalar color(rand()&255, rand()&255, rand()&255);
    //drawContours(out, contours_points, 0, color, 1, 8, hierarchy);
    
    /*Approximation of Hands Contours by Polygon*/
    approxPolyDP(contours,polygon,5,true);
    
    /*Drawing Identify Polygons*/
    //fillConvexPoly( out, polygon , color );
    
    /**
     * vector<Point> contours,polygon;
     * vector<int> hull;
     * vector<Vec4i> hierarchy,convexityDefects;
     * vector<vector<Point> > contours_points;
     */
    /*Convexity points Detection*/
    vector<vector<Point> > hull_points(contours_points.size());
    for(int i = 0 ; i< contours_points.size();i++)
        convexHull(Mat(contours_points[i]),hull_points[i],false); //Find the Convex of the polygon
    
    /*Drawing Convex of polygon*/
    for(int i = 0; i < contours_points.size() ; i++)
        drawContours( out, hull_points, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
    //convexityDefects(polygon,hull,convexityDefects);
    
    /*Affichage*/
    namedWindow(filepath);
    imshow(filepath,out);
    
}

int main(int argc, char** argv) {
    
    ShowConvexityPoints("./runFolder/test-segmented-2.bmp");
    waitKey(0);
    
    return (EXIT_SUCCESS);
}


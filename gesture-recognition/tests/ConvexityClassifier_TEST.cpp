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

void findConvexityDefects(vector<Point>& contour, vector<int>& hull, vector<Point>& convexDefects){
    if(hull.size() > 0 && contour.size() > 0){
    CvSeq* contourPoints;
    CvSeq* defects;
    CvMemStorage* storage;
    CvMemStorage* strDefects;
    CvMemStorage* contourStr;
    CvConvexityDefect *defectArray = 0;

    strDefects = cvCreateMemStorage();
    defects = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvSeq),sizeof(CvPoint), strDefects );

    //We transform our vector<Point> into a CvSeq* object of CvPoint.
    contourStr = cvCreateMemStorage();
    contourPoints = cvCreateSeq(CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvSeq), sizeof(CvPoint), contourStr);
    for(int i=0; i<(int)contour.size(); i++) {
        CvPoint cp = {contour[i].x,  contour[i].y};
        cvSeqPush(contourPoints, &cp);
    }

    //Now, we do the same thing with the hull index
    int count = (int)hull.size();
    //int hullK[count];
    int* hullK = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++){hullK[i] = hull.at(i);}
    CvMat hullMat = cvMat(1, count, CV_32SC1, hullK);

    //We calculate convexity defects
    storage = cvCreateMemStorage(0);
    defects = cvConvexityDefects(contourPoints, &hullMat, storage);
    defectArray = (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect)*defects->total);
    cvCvtSeqToArray(defects, defectArray, CV_WHOLE_SEQ);
    //printf("DefectArray %i %i\n",defectArray->end->x, defectArray->end->y);

    //We store defects points in the convexDefects parameter.
    for(int i = 0; i<defects->total; i++){
        CvPoint ptf;
        ptf.x = defectArray[i].depth_point->x;
        ptf.y = defectArray[i].depth_point->y;
        convexDefects.push_back(ptf);
    }

    //We release memory
    cvReleaseMemStorage(&contourStr);
    cvReleaseMemStorage(&strDefects);
    cvReleaseMemStorage(&storage);
    }
}

float Compute_Distance( Point a , Point b ){
    
    float d;
    
    return d = sqrt( pow( a.x - b.x , 2 ) + pow( a.y - b.y , 2 ) );
    
}

void ShowConvexityPoints(string filepath) {
    
    Mat out;//,contours_points,polygon;
    vector<Point> contours,polygon;
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours_points;
    Mat segmentedHandRGB = imread(filepath);
    imshow(filepath, segmentedHandRGB);
    
    /*CONVERSION FORMAT: Grayscale */
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    
    /*Computing median filter*/
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
    
    /*Finding the center of palm*/
    RotatedRect Palm = minAreaRect(contours);
    float Palm_Radius;
    if( Palm.size.height <= Palm.size.width )
        Palm_Radius = Palm.size.height / 2;
    else
        Palm_Radius = Palm.size.width / 2;
    
    /*Convexity points Detection*/
    vector<vector<Point> > hull_points(contours_points.size());
    vector<int> index_hull_points(contours_points.size());
    vector<Point> convexityDefects(contours_points.size());
    vector<Point> Concave_points;
    vector<int> Convex_points;
    for(int i = 0 ; i< contours_points.size();i++)
    {
        convexHull(contours_points[i],hull_points[i],false,true); //Find the Convex of the hand
            
    }
    
    convexHull(contours,index_hull_points,false,false); //Find the index of Convex points
       
    vector<Point>& contour = contours;
    vector<Point>& convexDefects = convexityDefects;
    vector<int>& hull = index_hull_points;
    findConvexityDefects(contour,hull,convexDefects);
    
    /*Filtering Concave points*/
    for(int i =0; i < convexDefects.size(); i++){
        /*Compare to the y-coordinate of the center of the palm*/
        if( Palm.center.y > convexDefects[i].y )
            Concave_points.push_back(convexDefects[i]);
    }
       
    /*Filtering Convex points*/
    for(int i =0; i < hull.size(); i++){
        /*Compare to tje y-coordiante of the center of the palm*/
        if( Palm.center.y > contour[hull[i]].y )
            Convex_points.push_back(hull[i]);
    }
       
    vector<int> tmp;
    /*Isolating the interesting convex points*/
    switch(Convex_points.size()){
        
        /*No fingers is detected*/
        case 0 : {}
        /*Only one fingers is detected*/
        case 1 :{
            tmp = Convex_points;
            break;
        }
        
        others : {
            
            /*case: between the last point and the first point*/
            float d = Compute_Distance( contour[Convex_points[Convex_points.size()-1]] , contour[Convex_points[0]] );
            
            /*Minimum distance*/
            if( d > 20 )
                tmp.push_back(Convex_points[Convex_points.size()-1]);
            
            /*Generic cases*/
            for(int i=0; i < Convex_points.size() - 1; i++){
                
                /*Compute distance between each neighboors Convex_points*/
                d = Compute_Distance( contour[Convex_points[i]] , contour[Convex_points[i+1]] );
                
                /*Minimum distance*/
                if( d > 20 )
                    tmp.push_back(Convex_points[i]);
                   
            }
            
        }
    }
    
    /*Isolating convex_points by the Average Radius of the palm**/
    vector<int> result;
    float min_distance = Palm.center.y - Palm_Radius;
    /*Compute the result*/
    if( (tmp.size() > 2) && (Concave_points.size() > 1) ) //Generic cases
        result = tmp;
    else{ // Cases: 0 or 1
        for(int i =0; i < tmp.size(); i++){
            if(min_distance > contour[tmp[i]].y)
                result.push_back(tmp[i]);
        }
    }
    
    /*Controling Result*/
    cout << "Unfiltered defects: " << convexDefects.size() << endl;
    cout << "Unfiltered hull size: " << hull.size() << endl;
    cout << "FilteredHull size: " << tmp.size() << endl;
    cout << "FilteredDefect size: " << Concave_points.size() << endl;
    
    /*Compute result*/
    if(Concave_points.size() > 0){ //Genric Cases
        cout << "Number of Digit = " << result.size() << endl; 
    }
    else{ //Cases: 0 or One
        int i = 0;
        while(i < tmp.size() || contour[tmp[i]].y > min_distance){
            i++;
        }
        
        if(i >= tmp.size())
            cout << "Number of Digit = 0" << endl;
        else
            cout << "Number of Digit = 1" << endl;
    }
    
    /*Drawing Convex of polygon*/
    for(int i = 0; i < contours_points.size() ; i++)
    {
        drawContours( out, contours_points, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        drawContours( out, hull_points, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
    }
    
    /*Affichage*/
    namedWindow(filepath);
    imshow(filepath,out);
    
}

int main(int argc, char** argv) {
    
    ShowConvexityPoints("./runFolder/test-segmented-2.bmp");
    waitKey(0);
    
    return (EXIT_SUCCESS);
}


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
    
    return d = sqrt( (float)pow((float) a.x - b.x , 2 ) + pow((float) a.y - b.y , 2 ) );
    
}

void ShowConvexityPoints(string filepath) {
    
    Mat out;//,contours_points,polygon;
    vector<Point> contours,polygon;
    vector<Vec4i> hierarchy;
    vector<vector<Point> > contours_points;
    Mat segmentedHandRGB = imread(filepath);
    
    /*CONVERSION FORMAT: Grayscale */
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    
    /*Computing median filter*/
    medianBlur(segmentedHandGray,out,15);
    
    /*Looking for Contours Points*/
    findContours( out, contours_points, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE );
    
    double Contour_tmp1, Contour_tmp2;
    Contour_tmp1 = 0;
    Contour_tmp2 = 0;
    /*Convert vector<vector<Point>> to vector<Point> and find the biggest contours*/
    vector<vector<Point> >::iterator it;
    it = contours_points.begin();
    while( it != contours_points.end() ){
        
        Contour_tmp1 = contourArea( *it , false );
        
        if( Contour_tmp1 > Contour_tmp2 ){
            
            Contour_tmp2 = Contour_tmp1;
            contours = *it;
            
        }
        
        it++;
        
    }
    
    /* OLD VERSION
    for(int i = 0; i < contours_points.size() ; i++){
        for(int j = 0; j < contours_points[i].size() ; j++){
            contours.push_back(contours_points[i][j]);
        }
    }
    /**/
    
    /*Drawing Contours*/
    Scalar color(rand()&255, rand()&255, rand()&255);
    drawContours(out, contours_points, 0, color, 1, 8, hierarchy);
    
    /*Approximation of Hands Contours by Polygon*/
    approxPolyDP(contours,polygon,15,true);
    contours = polygon;
    
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
    for(int i = 0 ; i< contours_points.size();i++)
    {
        convexHull(contours_points[i],hull_points[i],false,true); //Find the Convex of the hand
            
    }
    
    
    vector<int> index_hull_points(contours_points.size());
    vector<Point> convexityDefects(contours_points.size());
    vector<Point> Concave_points;
    vector<int> Convex_points;
    convexHull(contours,index_hull_points,false,false); //Find the index of Convex points
    
    /*Convexity Adapt from OpenCV [C versions]*/
    vector<Point>& contour = contours;
    vector<Point>& convexDefects = convexityDefects;
    vector<int>& hull = index_hull_points;
    findConvexityDefects(contour,hull,convexDefects);
    
    /*Controling Result*/
    cout << "ALL Concave points: " << convexDefects.size() << endl;
    for (int i=0; i < convexDefects.size(); i++){
        //circle(segmentedHandGray, convexDefects[i],5, color, 2, 8, 0);
    }
    cout << "ALL Convex points: " << hull.size() << endl;
    for (int i=0; i<hull.size(); i++) {
        //circle(segmentedHandGray, contour[hull[i]], 5, color, 1, 8, 0);
    }
    
    /*Filtering Concave points*/
    for(int i =0; i < convexDefects.size(); i++){
        /*Compare to the y-coordinate of the center of the palm*/
        if( Palm.center.y + 10 > convexDefects[i].y )
            Concave_points.push_back(convexDefects[i]);
    }
       
    /*Filtering Convex points*/
    for(int i =0; i < hull.size(); i++){
        /*Compare to the y-coordiante of the center of the palm*/
        if( Palm.center.y + 10 > contour[hull[i]].y )
            Convex_points.push_back(hull[i]);
    }
    
    cout << "First Filter Convex points: " << Convex_points.size() << endl;
    for (int i=0; i<Convex_points.size(); i++) {
        //circle(segmentedHandGray, contour[Convex_points[i]], 5, color, 1, 8, 0);
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
        
        default : {
            
            float d;
            
            /*Generic cases*/
            for(int i=0; i < Convex_points.size() - 1; i++){
                
                /*Compute distance between each neighboors Convex_points*/
                d = Compute_Distance( contour[Convex_points[i]] , contour[Convex_points[i+1]] );
                cout << "Generics Distance " << d << endl;
                
                /*Minimum distance*/
                if( d > 20 )
                    tmp.push_back(Convex_points[i]);
                   
            }
            
            /*case: between the last point and the first point*/
            d = Compute_Distance( contour[Convex_points[0]] , contour[Convex_points[Convex_points.size()-1]] );
            cout << "Last Distance " << d << endl;
            
            /*Minimum distance*/
            if( d > 20 )
                tmp.push_back(Convex_points[Convex_points.size()-1]);
            else if(Convex_points.size() == 2)
                tmp.push_back(Convex_points[0]);
            
        }
    }
    
    cout << "Second Filter Convex points: " << tmp.size() << endl;
    for (int i=0; i<tmp.size(); i++) {
        //circle(segmentedHandGray, contour[tmp[i]], 5, color, 1, 8, 0);
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
    
    cout << "Convex points: " << result.size() << endl;
    for (int i=0; i<result.size(); i++) {
        //circle(segmentedHandGray, contour[result[i]], 5, color, 1, 8, 0);
    }
    
    cout << "Concave points: " << Concave_points.size() << endl;
    for (int i=0; i < Concave_points.size(); i++){
        //circle(segmentedHandGray, Concave_points[i],5, color, 2, 8, 0);
    }
    
    /*Compute result*/
    float min_distance2 = Palm.center.y - (Palm_Radius * 2);
    if(Concave_points.size() > 0){ //Genric Cases
        cout << "Number of Digit = " << result.size() << endl; 
    }
    else{ //Cases: 0 or One
        int i = 0;
        while(i < result.size() || contour[result[i]].y > min_distance2){
            i++;
        }
        
        if(i >= result.size())
            cout << "Number of Digit = 0" << endl;
        else
            cout << "Number of Digit = 1" << endl;
    }
    
    /*Drawing Convex of polygon*/
    for(int i = 0; i < contours_points.size() ; i++)
    {
        //drawContours( segmentedHandGray, contours_points, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        //drawContours( segmentedHandGray, hull_points, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
    }
    
    /*Affichage*/
    namedWindow(filepath);
    imshow(filepath,segmentedHandGray);
    
}

int main(int argc, char** argv) {
    
    ShowConvexityPoints("./runFolder/imgresult/cleaned.jpg");
    waitKey(0);
    
    return (EXIT_SUCCESS);
}


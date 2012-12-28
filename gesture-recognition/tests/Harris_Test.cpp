/* 
 * File:   HarrisTest.cpp
 * Author: Quentin
 *
 * Created on 9 déc. 2012, 16:05:13
 */


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Segmentation.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define DISTANCE_MIN 5

/// Global variables
Mat src, src_gray, seg;
int thresh = 125;
int max_thresh = 255;

char* source_window = "image source";
char* corners_window = "Harris detection";

/// Function header
void loadAndSegment(const char *, bool);
void printMat(const Mat&);
vector<Point> Harris();
void matching(vector<Point>, vector<Point>);
double euclidean(Point A, Point B);


/** @function main */
int main( int argc, char** argv )
{
    loadAndSegment("./runFolder/groupe2/1.bmp", false);
    imshow("Segmented", seg);
    vector<Point> P1= Harris();

    loadAndSegment("./runFolder/groupe2/2.bmp", false);
    imshow("Segmented2", seg);
    vector<Point> P2= Harris();
    
    for(int i=0 ; i<P1.size() ; i++)
        cout << P1.at(i);
    cout << endl << P1.size() << endl;
    
    for(int i=0 ; i<P2.size() ; i++)
        cout << P2.at(i);
    cout << endl << P2.size();
    cout << endl;
    
    matching(P1,P2);
    
    waitKey(0);
    return(0);
}

/** @function Harris */
vector<Point> Harris() 
{   
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros( src.size(), CV_32FC1 );

    /// Detector parameters
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    /// Detecting corners
    cornerHarris( seg, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

    /// Normalizing
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );

//    printMat(dst_norm_scaled);
    
    vector<Point> HarrisPoints;
    
    for( int j = 0; j < dst_norm.rows ; j++ )
        for( int i = 0; i < dst_norm.cols; i++ )
            if( (int) dst_norm.at<float>(j,i) > thresh ) {
               circle( dst_norm_scaled, Point( i, j ), 2,  Scalar(255), 2, 8, 0 );
               HarrisPoints.push_back(Point( i, j ));
            }
    
    /// Showing the result
    namedWindow( corners_window, CV_WINDOW_AUTOSIZE );
    imshow( corners_window, dst_norm_scaled );   
    
    return HarrisPoints;
}

void matching(vector<Point> P1, vector<Point> P2)
{
    // Distances
    double distances[P1.size()][P2.size()];
    // Matchs between Harris points of first & second image
    bool match[P1.size()][P2.size()];
    
    // Computes distances and matchs
    for(int i=0 ; i< P1.size() ; i++) {
        int min = 10000;
        int nearestpoint = 0;
        for(int j=0 ; j< P2.size() ; j++)
        {
            match[i][j] = false;
            distances[i][j] = euclidean(P1[i], P2[j]);
            if(distances[i][j] < min) {
                min = distances[i][j];
                nearestpoint = j;
            }
            cout << euclidean(P1[i], P2[j]) << "  ";
        }
        if(distances[i][nearestpoint] < DISTANCE_MIN)
        match[i][nearestpoint] = true;
        cout << endl;
    }
    
    for(int i=0 ; i< P1.size() ; i++) {
        for(int j=0 ; j< P2.size() ; j++)
        {
             cout << match[i][j] << "  ";       
        }
        cout << endl;
    }
}

double euclidean(Point A, Point B) {
    return (sqrt( pow(A.x-B.x,2)+pow(A.y-B.y,2) ));
}


void loadAndSegment(const char * filename, bool cleanBefore) {
    
    Mat img = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

    // Segmentation
    if(cleanBefore)
        specialSegmentation(img, seg);
    else
        Segment(img, seg);

//    imshow("segmented", seg);
}

void printMat(const Mat& mat) {
    
    for(int i=0 ; i< mat.rows ; i++) {
        for(int j=0; j<mat.cols ; j++)
            cout << mat.data[i*mat.cols+j] << "   " ;
        cout << endl << endl;
    }
}
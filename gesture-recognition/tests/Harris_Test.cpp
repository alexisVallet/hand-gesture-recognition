/* 
 * File:   HarrisTest.cpp
 * Author: Quentin
 *
 * Created on 9 déc. 2012, 16:05:13
 */


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Segmentation.h"
#include "utilsFunctions.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define DISTANCE_MIN 800
#define WINDOW_SIZE_CORRELATION 4

/// Global variables
Mat src1, src2, seg;
int thresh = 200;
int max_thresh = 255;

// Current movement of hand between two images.
double currentmovX, currentmovY = 0;

/// Function headers
void loadAndSegment(const char * , bool, Mat & src);
void segmentAccordingToBox(const char *, Mat&, pair<Point,Point>);
void printMat(const Mat&);
vector<Point> Harris(string);
void matching(vector<Point>, vector<Point>);
double euclidean(Point A, Point B);
pair<Point,Point> box(const Mat& mat);
int SAD(const Mat& mat1, Point P1, const Mat& mat2, Point P2);

/** @function main */
int main( int argc, char** argv )
{
    vector< vector<string> > base;
    readPath(base, "./runFolder/groupe2/", "bmp");
    
//    for(int i=0 ; i< base[0].size()-1 ; i++) {

        // Segment two first images
        src1 = cvLoadImage(base[0][0].c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        loadAndSegment(base[0][0].c_str(), false, src1);
        vector<Point> P1= Harris(base[0][0]);
        pair<Point,Point> rect = box(seg);
        rectangle(seg, rect.first, rect.second, Scalar(255), 1, 8, 0);
        imshow("Segmented1", seg);
        
        src2 = cvLoadImage(base[0][1].c_str(), CV_LOAD_IMAGE_GRAYSCALE);
        loadAndSegment(base[0][1].c_str(), false, src2);
        vector<Point> P2= Harris(base[0][1]);

        matching(P1,P2);
        Point p1adapt ((int)rect.first.x + currentmovX, (int)rect.first.y + currentmovY);
        Point p2adapt ((int)rect.second.x + currentmovX, (int)rect.second.y + currentmovY);
        rectangle(seg, p1adapt, p2adapt, Scalar(255), 1, 8, 0);
        pair<Point,Point> box = make_pair(p1adapt,p2adapt);
        imshow("Segmented2", seg);

        // Hand Tracking
        for(int i=2 ; i< base[0].size()-3 ; i++) {

            // Segment two first images
            src1 = cvLoadImage(base[0][i].c_str(), CV_LOAD_IMAGE_GRAYSCALE);
            segmentAccordingToBox(base[0][i].c_str(), src1, box);
//            loadAndSegment(base[0][i].c_str(), false, src1);
//            vector<Point> P1= Harris(base[0][i]);
//            pair<Point,Point> rect = box(seg);
//            rectangle(seg, rect.first, rect.second, Scalar(255), 1, 8, 0);
//            imshow("Segmented1", seg);
//
//            src2 = cvLoadImage(base[0][i].c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//            loadAndSegment(base[0][i].c_str(), false, src2);
//            vector<Point> P2= Harris(base[0][i]);
//
//            matching(P1,P2);
//            Point p1adapt ((int)rect.first.x + currentmovX, (int)rect.first.y + currentmovY);
//            Point p2adapt ((int)rect.second.x + currentmovX, (int)rect.second.y + currentmovY);
//            rectangle(seg, p1adapt, p2adapt, Scalar(255), 1, 8, 0);
//            imshow("Segmented2", seg);
//
//
//            cout << "Movement X: " << currentmovX << "  Y:" << currentmovY << endl;

            waitKey(0);
        }        
        
        cout << "Movement X: " << currentmovX << "  Y:" << currentmovY << endl;
        
        waitKey(0);
//    }
    

    return(0);
}

/** @function Harris */
vector<Point> Harris(string filename) 
{   
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros( seg.size(), CV_32FC1 );

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
    namedWindow( filename, CV_WINDOW_AUTOSIZE );
    imshow( filename, dst_norm_scaled );   
    
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
        for(int j=0 ; j< P2.size() ; j++) {
            match[i][j] = false;
            
            // Similarity Measure : Sum of Absolute Differences
            //distances[i][j] = euclidean(P1[i], P2[j]);
            distances[i][j] = SAD(src1, P1[i], src2,P2[j]);
cout << distances[i][j] << "  ";
        }
cout << endl;
    }
cout << endl;
    int nbpoints_match = min(P1.size(), P2.size());
    // For each point we have to match
    for(int p=0 ; p< nbpoints_match ; p++) {
        int min = 100000;
        int p_fromP1 = -1;
        int p_fromP2 = -1;
        
        // search min SAD distance
        for(int i =0 ; i<P1.size() ; i++)
            for(int j=0 ; j<P2.size() ; j++)
                // if distance is min & (i & j) are not matched 
                if(distances[i][j] < min && !match[i][j]) {
                    bool matched = false;
                    // check if i and j are not matched
                    for(int imatch =0 ; imatch<P1.size() ; imatch++)
                        if(match[imatch][j])
                            matched = true;
                    for(int jmatch=0 ; jmatch<P2.size() ; jmatch++)
                        if(match[i][jmatch])
                            matched = true;
                    if(!matched && distances[i][j] < DISTANCE_MIN) {
                        min = distances[i][j];
                        p_fromP1 = i;
                        p_fromP2 = j;
                    }
                }
        match[p_fromP1][p_fromP2] = true;
    }
    
    for(int i =0 ; i<P1.size() ; i++) {
        for(int j=0 ; j<P2.size() ; j++)
            cout << match[i][j] << "  ";
        cout << endl;
    }
    
    double movX = 0,movY = 0;
    int n = 0;
    for(int i=0 ; i< P1.size() ; i++)
        for(int j=0 ; j< P2.size() ; j++)
            if(match[i][j]) {
                movX += P2[j].x - P1[i].x;
                movY += P2[j].y - P1[i].y;
                n++;
            }
    currentmovX += (movX / n);
    currentmovY += (movY / n);
}

double euclidean(Point A, Point B) {
    return (sqrt( pow(A.x-B.x,2)+pow(A.y-B.y,2)));
}


void loadAndSegment(const char * filename, bool cleanBefore, Mat& src) {
    
    src = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

    // Segmentation
    if(cleanBefore)
        specialSegmentation(src, seg);
    else
        Segment(src, seg);

//    imshow("segmented", seg);
}

void segmentAccordingToBox(const char * filename, Mat& src, pair<Point,Point> box) {
    
    src = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
    
    int sx = abs(box.second.x - box.first.x);
    int sy = abs(box.second.y - box.first.y);
    
    Mat hand = Mat_<unsigned char>(sy,sx);
    hand.dims=0;//tres important, trop de pb à cause de ces conneries de channel
    
    // extract hand to segment
    int xMin = box.first.x;
    int xMax = box.second.x;
    int yMin = box.second.y;
    int yMax = box.first.y;
    
    cout <<  "xMin : " << xMin << endl;
    cout <<  "xMax : " << xMax << endl;
    cout <<  "yMin : " << yMin << endl;
    cout <<  "yMax : " << yMax << endl;
    
    imshow("Source2", src);
    
    extractSubimageFromBounds(src, hand, xMin, xMax, yMin, yMax);
    
    imshow("Hand", hand);
}

void printMat(const Mat& mat) {
    
    for(int i=0 ; i< mat.rows ; i++) {
        for(int j=0; j<mat.cols ; j++)
            cout << mat.data[i*mat.cols+j] << "   " ;
        cout << endl << endl;
    }
}

pair<Point,Point> box (const Mat& mat) {
    
    int xMin (mat.cols), xMax(0), yMin(mat.cols), yMax(0);
    
    for(int i=0 ; i< mat.cols ; i++)
        for(int j = 0 ; j<mat.rows ; j++)
            if(mat.data[j*mat.cols+i] > 0) {
                if(i < xMin)
                    xMin = i;
                if(i > xMax)
                    xMax = i;
                if(j < yMin)
                    yMin = j;
                if(j > yMax)
                    yMax = j;                
            }
    
    Point p1(xMin, yMax);
    Point p2(xMax, yMin);

    return make_pair(p1,p2);
}

int SAD(const Mat& mat1, Point P1, const Mat& mat2, Point P2){
    
    double sum = 0;
    // Computes window sum of absolute distances
    for(int i= -WINDOW_SIZE_CORRELATION ; i<WINDOW_SIZE_CORRELATION ; i++ )
        for(int j= -WINDOW_SIZE_CORRELATION ; j<WINDOW_SIZE_CORRELATION ; j++ )
            sum += abs((int)(mat1.data[(P1.y+j)*mat1.cols+(P1.x+i)]) - (int)(mat2.data[(P2.y+j)*mat1.cols+(P2.x+i)]));
    return sum;
}
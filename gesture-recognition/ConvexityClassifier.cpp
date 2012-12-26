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

float ConvexityClassifier::Compute_Distance( Point a , Point b ){
    
    float d;
    
    return d = sqrt( (float)pow((float) a.x - b.x , 2 ) + pow((float) a.y - b.y , 2 ) );
    
}
/*
void ConvexityClassifier::findConvexityDefects(vector<Point>& contour, vector<int>& hull, vector<Point>& convexDefects){
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
 */

int ConvexityClassifier::numberOfFingers(Mat &segmentedHand) {
    
    Mat tmp, out;
    tmp = segmentedHand;
    
    /*Compute Median Blur*/
    medianBlur( tmp , out, 15 );
    
    /**/
    
}

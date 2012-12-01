#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"


#include <iostream>
#include <dirent.h>
//#include "utilsFunctions.cpp"
#include "ClassifieurDistEuclidienne.cpp"
#include "ClassifieurDistHistogramm.cpp"
#include "HandDirection.h"

using namespace cv;
using namespace std;


void drawVector(Mat &image, Mat vector, const Scalar &color) {
    Point center(image.cols/2, image.rows/2);
    Point vectorEnd(center.x + vector.at<float>(0,0), center.y + vector.at<float>(0,1));
    line(image, center, vectorEnd, color);
}

void showHandAndDirection(string filepath) {
    Mat segmentedHandRGB = imread(filepath);
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat segmentedHandBin = segmentedHandGray / 255;
    pair<Mat,Mat> directions = handDirection(segmentedHandBin);
    cout<<directions.first<<";"<<directions.second<<endl;
    Mat handAndVectors = segmentedHandRGB;
    drawVector(handAndVectors, directions.first * 20, CV_RGB(255,0,0));
    drawVector(handAndVectors, directions.second * 20, CV_RGB(0,255,0));
    namedWindow(filepath);
    imshow(filepath, handAndVectors);
}



void redressHand()
{
    string fn = "F:/iut/utbm/S5/projetIN52-54/ClassImages/2/0b1.bmp";
    
        
    Mat segmentedHandRGB = imread(fn);
    vector<Mat> rgbPlanes;
    split(segmentedHandRGB, rgbPlanes);
    Mat segmentedHandGray = rgbPlanes[0];
    Mat hand = segmentedHandGray / 255;
    pair<Mat,Mat> directions = handDirection(hand);
    cout<< directions.first.at<float>(0,0) << " " << directions.first.at<float>(0,1) <<endl;
    
    
    
    //Mat hand = extractHandFromBMPFile(fn);

    std::pair < Mat, Mat > orientation = handDirection( hand );
    cout << "x = " << (double)orientation.second.data[0] << "  y = " << (float)orientation.second.data[1] << endl;
    
    
    float x = directions.first.at<float>(0,0);
    float y = directions.first.at<float>(0,1);
    
    float norme = sqrt( pow(x, 2) + pow(y, 2) );
    cout << "norme = " << norme << endl;
    
    float xnormalized = x/norme;
    float ynormalized = y/norme;
    
    cout << "xn = " << xnormalized << "yn = " << ynormalized << endl;
    
    float angle = acos(xnormalized)* 180.0 / M_PI;
    cout << "angle = " << angle << endl;
    
    
    
showHandAndDirection( fn );
    
    namedWindow("subImage", CV_WINDOW_AUTOSIZE );
    imshow("subImage", hand );
}



int main( int argc, char** argv )
{
    /*//chargement de l'image yml "originale"
    IplImage * imgyml = loadYml("d:/1.yml");   
    cvNamedWindow("LoadedImage", 1);
    cvShowImage("LoadedImage", imgyml);


    //histo de l'image originale
    calcHist(imgyml);


    //conversion en Mat 
    //Mat img = imread( "d:/4segmentee.bmp", 1 );
    Mat img = IplToMat(*imgyml);
    IplImage aaa = IplImage(img);
    cvSaveImage("d:/aaaaaa.bmp", &aaa);
    
    
    cvNamedWindow("imgMat", 1);
    imshow("imgMat", img);

    //on binarise (seuil arbitraire pour le moment)
    revertBinarize(img, 90);
    cvNamedWindow("imgBinarised", 1);
    imshow("imgBinarised", img);
    
    //detection of bounds of the hand
    int xMin, xMax, yMin, yMax;    
    calculBounds(img, xMin, xMax, yMin, yMax);    
    xMax++;
    yMax++;
            
    int sx = xMax - xMin;
    int sy = yMax - yMin;
    cout << "handSX = " << sx << "handSY = " << sy << endl;
    //extraction of the hand
    Mat hand = Mat_<unsigned char>(sy, sx);
    extractSubimageFromBounds(img, hand, xMin, xMax, yMin, yMax);
    
    namedWindow("subImage", CV_WINDOW_AUTOSIZE );
    imshow("subImage", hand );
    
    
    
    //sauvegarde, inutile pour le moment mais à terme ça pourait servir
    IplImage iplimg = IplImage(hand);
    cvSaveImage("d:/hand.bmp", &iplimg);*/
    
    //convertAllYMLImageFromPath();
    
    /*ClassifieurDistEuclidienne classifieur;
    classifieur.initBase();
    classifieur.testImage("./7.bmp");
    
    ClassifieurDistHistogramm cl2;
    cl2.initBase();
    cl2.testImage("./7.bmp");*/
    //classifieur.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImages/1/0.bmp");
    redressHand();

    waitKey(0);
    return 0;
}

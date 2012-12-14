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

#include "rotateHand.h"

using namespace cv;
using namespace std;









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
    
    
    
    //test classifieur1
    ClassifieurDistEuclidienne classifieur;
    classifieur.initBase();
    //classifieur.testImage("F:/iut/utbm/S5/projetIN52-54/dropbox/Dropbox/Projet IN5x/Images/groupe1/7.bmp");
    classifieur.testImage("./runFolder/ClassImages/test.bmp");
    //classifieur.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImagesSeg/test1.bmp");
    
    //test classifieur2
    ClassifieurDistHistogramm cl2;
    cl2.initBase();
    cl2.testImage("./runFolder/groupe1/7.bmp");
    //cl2.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImagesSeg/test1.bmp");
    //cl2.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImages/test.bmp");
    //cl2.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImages/1/0.bmp");
    
    //Mat hand = extractHandFromBMPFile("F:/iut/utbm/S5/projetIN52-54/ClassImages/2/0b1.bmp", true);
    //Mat rotatedHand = redressHandFromBinarySegmentedImage(hand, 255);
    
    
   
    //binarizeFile("F:/iut/utbm/S5/projetIN52-54/ClassImagesSeg/5/1.bmp", 100);
    

    waitKey(0);
    return 0;
}





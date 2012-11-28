#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include <iostream>
#include <dirent.h>
#include "utilsFunctions.h"

using namespace cv;
using namespace std;

#ifndef __UTILS_FUNCTIONS_
#define __UTILS_FUNCTIONS_


//converti une image au format IplImage en une image au format Mat
Mat IplToMat(IplImage &src)
{
    Mat * dest = new Mat_<unsigned char>(src.width, src.height);
    dest->dims = 0;
    int sz = src.height*src.width;
    
    for(int i=0; i<sz; i++)
        dest->data[i] = src.imageData[i];
    
    return *dest;
}


//extrait la main à partir du nom de fichier BMP passé en paramètre
//chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main
//c'est (pour le moment) dans cette fonction qu'il faut setter le seuil, pour le moment arbitraire, l'idée étant par ex de remplacer le 90 actuelle par l'appelle d'une fonction qui va trouver automatiquement le seuil adapté, je crois que c'est ce sur quoi quentin a bossé
//+ effectuer une passe de l'operateur supprimant les px orphelins
Mat extractHandFromBMPFile(string filename)
{
    Mat img = imread( filename );
    
    //SEUIL A SETTER
    revertBinarize(img, 90); 
    
    int xMin, xMax, yMin, yMax;   
    calculBounds(img, xMin, xMax, yMin, yMax);
    xMax++;
    yMax++;
    int sx = xMax - xMin;
    int sy = yMax - yMin;
    //extraction of the hand
    Mat hand = Mat_<unsigned char>(sy, sx);
    hand.dims=0;//tres important, trop de pb à cause de ces conneries de channel
    extractSubimageFromBounds(img, hand, xMin, xMax, yMin, yMax);
    return hand;
}



//binarisation on ne peut plus élémentaire, à la différence que si <seuil -> 255 et si >seuil ->0
void revertBinarize(Mat &img, int seuil)
{
    for(int i=0; i<img.cols*img.rows*(img.dims+1); i++)
        if(img.data[i]>seuil)img.data[i] =0;
        else img.data[i] =255;
}



IplImage * loadYml(const char * filename)
{
    CvMat* my_matrix;
    my_matrix = (CvMat*)cvLoad(filename);

    float min = my_matrix->data.fl[0], max = my_matrix->data.fl[0];
    float moy = 0;

    for(int i=0; i<my_matrix->rows; i++)
        for(int j=0; j<my_matrix->cols; j++)
        {
            if(my_matrix->data.fl[i*200+j]<min) min = my_matrix->data.fl[i*200+j];
            else if(my_matrix->data.fl[i*200+j]>max) max = my_matrix->data.fl[i*200+j];

            moy+=my_matrix->data.fl[i*200+j];
        }

    moy/= my_matrix->rows * my_matrix->cols;

    IplImage* img = cvCreateImage(cvSize(my_matrix->cols, my_matrix->rows),IPL_DEPTH_8U,1);
    
    float mintmp = 0, maxtmp = 0;
    for(int i=0; i<my_matrix->rows; i++)
        for(int j=0; j<my_matrix->cols; j++)
        {
            //float val = (unsigned char) 255* ((my_matrix->data.fl[i*200+j]-min)/(max-min));
            //float val = (unsigned char) ((my_matrix->data.fl[i*200+j]/moy)*255);
            float val = my_matrix->data.fl[i*200+j]*16;
            val*=val;


            if(mintmp > val) mintmp = val;
            if(maxtmp < val) maxtmp = val;

            if(val<0) val = 0;
            if(val>255) val=255;

            img->imageData[i*200+j] = val;
        }
    return img;
}



void calcHist(IplImage * img)
{
    int histSize = 256;

    int histo[histSize];
    for(int i=0; i<256; i++)
        histo[i]=0;
    
    for(int i=0; i<img->height; i++)
      for(int j=0; j<img->width; j++)
          histo[ (unsigned char)img->imageData[i*img->width+j] ]++;

    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );



    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(histo[i-1]) ) ,
                        Point( bin_w*(i), hist_h - cvRound(histo[i]) ),
                        Scalar( 255, 0, 0), 2, 8, 0  );
    }


    namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
    imshow("calcHist Demo", histImage );
}



void calculBounds(Mat img, int &xMin, int &xMax, int &yMin, int &yMax)
{
    int canal = img.dims+1;
    //cout << "canal = " << canal << endl;

    bool xMinFinded = false, xMaxFinded = false;
    //1 - détection des min/max en x
    for(int j=0; j<img.cols ; j++)
    {
        for(int i=0; i<img.rows; i++)
        {
            if(!xMinFinded && img.data[i*img.cols*canal+j*canal]==255) 
            {
                xMin = j;
                xMinFinded = true;
            }
            if(!xMaxFinded && img.data[(img.rows-i-1)*img.cols*canal + (img.cols-j)*canal]==255) 
            {
                xMax = img.rows-j;
                xMaxFinded = true;
            }
        }
    }
    
    
    //2 - detection des min/max en Y
    bool yMinFinded = false, yMaxFinded = false;
    for(int i=0; i<img.rows; i++)
        for(int j=0; j<img.cols; j++)
        {
            if(!yMinFinded && img.data[i*img.cols*canal+j*canal]==255) 
            {
                yMin = i;
                yMinFinded = true;
            }
            if(!yMaxFinded && img.data[(img.rows-i-1)*img.cols*canal + (img.cols-j)*canal]==255) 
            {
                yMax = img.rows-i;
                yMaxFinded = true;
            }
        }
    //cout << "xmin = " << xMin << "  xMax = " << xMax << "  yMin = " << yMin << "  yMax = " << yMax << endl;
}



void extractSubimageFromBounds(Mat img, Mat &dest, int xMin, int xMax, int yMin, int yMax)
{
    int sx = xMax - xMin;
    int sy = yMax - yMin;
    int chanel = img.dims+1;
    
    for(int j=yMin; j<yMax; j++)
        for(int i=xMin; i<xMax; i++)
        {
            dest.data[(j-yMin)*sx+i-xMin] = img.data[j*chanel*img.cols+i*chanel];
        }
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//juste pour convertir toutes les images yml du dossier pathSrc vers bmp
void ymlToBmp(string src, string dest);
//oui je sais, c'est pas optimal, c'est dégueulasse (et je vous emmerde !), mais c'est purement utilitaire !
string pathSrc = "d:/img/";
void convertAllYMLImageFromPath()
{
    DIR *dp;
    struct dirent *ep;
    vector<string> filenames;

    dp = opendir (pathSrc.c_str());
    if (dp != NULL)
    {
        while (ep = readdir (dp))
        {
                if (*(ep->d_name) != '.' && *(ep->d_name)!='..')
                {
                    if(   ep->d_name[strlen(ep->d_name)-1]=='l' && ep->d_name[strlen(ep->d_name)-2]=='m' && ep->d_name[strlen(ep->d_name)-3]=='y'  )
                    {        
                        string filename = ep->d_name;
                        ymlToBmp(pathSrc+ep->d_name, pathSrc+filename.substr(0, filename.size()-4));
                    }
                }
        }
        (void) closedir (dp);
    }
}


void ymlToBmp(string src, string dest)
{
    cout << "src = " << src << "  dest = " << dest << endl;
    IplImage * imgyml = loadYml(src.c_str()); 
    
    /*Mat img = IplToMat(*imgyml);
    IplImage iplimg = IplImage(img);*/
    
    cvSaveImage( (dest+".bmp").c_str(), imgyml);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
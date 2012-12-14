#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include <iostream>
#include <dirent.h>
#include "utilsFunctions.h"
#include "Segmentation.h"
#include "LoadYML.h"

using namespace cv;
using namespace std;

#ifndef __UTILS_FUNCTIONS_
#define __UTILS_FUNCTIONS_


//converti une image GRAYSCALE au format IplImage en une image au format Mat
Mat IplToMat(IplImage &src)
{
    Mat * dest = new Mat_<unsigned char>(src.width, src.height);
    dest->dims = 0;
    int sz = src.height*src.width;
    
    for(int i=0; i<sz; i++)
        dest->data[i] = src.imageData[i];
    
    return *dest;
}


//converti une image Mat vers image au format IPL
IplImage * MatToIpl(Mat &src)
{
    IplImage* img = cvCreateImage(cvSize(src.cols, src.rows),IPL_DEPTH_8U,1);

    int sz = src.cols*src.rows;
    
    for(int i=0; i<sz; i++)
        img->imageData[i] = src.data[i];
    
    return img;
}



//premiere chose a faire apres utilisation de imread, si l'image chargée est RGB, on en fait une image en niveau de gris, trop de problèmes à cause de ça, au moins après cette conversion on sait sur quoi on travaille
Mat greyscale(Mat &img)
{
    int datasz = img.dataend - img.datastart;
    int res = img.cols*img.rows;
    int dim = datasz/res;
    cout << "datasz/res = " << datasz/res << endl;
    Mat grey = Mat_<unsigned char>(img.rows, img.cols);
    grey.dims = 0;
    
    for(int line=0; line<img.rows; line++)
        for(int col=0; col<img.cols; col++)
        {
            int val = img.data[line*img.cols*dim + col*dim] + img.data[line*img.cols*dim + col*dim +1] + img.data[line*img.cols*dim + col*dim +2];
            grey.data[line*img.cols+col] = val/3;
        }
    
    namedWindow("grey", CV_WINDOW_AUTOSIZE );
    imshow("grey", grey );
    return grey;
}

//fonction à l'arrache binarisant automatiquement une image et l'enregistrant dans le mm dossier
//utile pour binariser rapidement des mains pour la base à partir d'images dont on a simplement gommé la gueule du mec s'il est trop pres
void binarizeFile(string path, int seuil)
{
    Mat img = imread(path.c_str());
    binarize(img, seuil, true);
    img = greyscale(img);
    cvSaveImage( (path+"2"+".bmp").c_str(), MatToIpl(img));
}


//extrait la main à partir du nom de fichier BMP passé en paramètre
//chargement de l'image, segmentation quentin, détection des bounds de la main, extraction de la main
Mat extractHandFromBMPFile(string filename)
{
    Mat img = imread( filename, CV_LOAD_IMAGE_GRAYSCALE );
    //img = greyscale(img);
    
    
    //SEUIL A SETTER
    //binarize(img, 90, revertBinarize);
    Mat hand; 
    // Segmentation
    Segment(img, hand);
    hand.dims=0;//tres important, trop de pb à cause de ces conneries de channel
    
    string windowName = "BINARIZED" ;
    windowName+=filename;
    namedWindow(windowName.c_str(), CV_WINDOW_AUTOSIZE );
    imshow(windowName.c_str(), hand );
waitKey(0);

    int xMin, xMax, yMin, yMax;   
    calculBounds(hand, xMin, xMax, yMin, yMax);
    xMax++;
    yMax++;
    int sx = xMax - xMin;
    int sy = yMax - yMin;
    //extraction of the hand
    Mat hand2 = Mat_<unsigned char>(sy, sx);
    hand2.dims=0;//tres important, trop de pb à cause de ces conneries de channel

    extractSubimageFromBounds(hand, hand2, xMin, xMax, yMin, yMax);
    return hand2;
}

//La même qu'au dessus mais à partir d'une image Mat déjà binarisée
Mat extractHandFromBinarizedMat(Mat &img)
{
    img.dims=0;
   
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
void binarize(Mat &img, int seuil, bool invert)
{
    int high, low;
    
    if(invert)
    {
        high = 0;
        low = 255;
    }
    else
    {
        high = 255;
        low = 0;
    }
    
    
    switch(img.dims)
    {
        case 0 :
            for(int i=0; i<img.cols*img.rows*(img.dims+1); i++)
                if(img.data[i]>seuil) 
                    img.data[i] = high;
                else img.data[i] = low;
        break;
        
        case 2 :
            for(int i=0; i<img.cols*img.rows*(img.dims+1); i+=3)
            {
                int avg = img.data[i] + img.data[i+1] + img.data[i+2];
                
                if(avg/3>seuil) 
                {
                    img.data[i] = high;
                    img.data[i+1] = high;
                    img.data[i+2] = high;
                }
                else 
                {
                    img.data[i] = low;
                    img.data[i+1] = low;
                    img.data[i+2] = low;
                }
            }
        break;
    }

  
   
}





/*Mat binarize(Mat &img, int seuil, bool invert)
{
    int high, low;
    
    if(invert)
    {
        high = 0;
        low = 255;
    }
    else
    {
        high = 255;
        low = 0;
    }
    
    Mat binarized = Mat_<unsigned char>(img.cols, img.rows);
    binarized.dims = 0;
    
    
    switch(img.dims)
    {
        case 0 :
            cout << "MONODIM" << endl;
            for(int i=0; i<img.cols*img.rows; i++)
                if(img.data[i]>seuil) 
                    binarized.data[i] = high;
                else binarized.data[i] = low;
        break;
        
        case 2 :
            cout << "TRIDIM" << endl;
            for(int i=0; i<img.cols*img.rows*(img.dims+1); i+=3)
            {
                int avg = img.data[i] + img.data[i+1] + img.data[i+2];
                
                if(avg/3>seuil) 
                {
                    img.data[i] = high;
                    img.data[i+1] = high;
                    img.data[i+2] = high;
                    
                    binarized.data[i/3] = high;
                }
                else 
                {
                    img.data[i] = low;
                    img.data[i+1] = low;
                    img.data[i+2] = low;
                    
                    binarized.data[i/3] = low;
                }
            }
        break;
    }

    return binarized;
   
}*/





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
    
//    cout << "calculBounds, dims = " << img.cols << " " << img.rows << endl;
//    cout << "datasize = " << img.dataend - img.datastart << endl;
//    cout << "image.dims = " << img.dims << endl;
    int max = 0;
    
    
    int canal = img.dims+1;
    //cout << "canal = " << canal << endl;

    bool xMinFinded = false, xMaxFinded = false;
    //1 - détection des min/max en x
    for(int j=0; j<img.cols ; j++)
    {
        for(int i=0; i<img.rows; i++)
        {
//            cout << (int)(img.data[i*img.cols*canal+j*canal])/255;
            if(!xMinFinded && img.data[i*img.cols*canal+j*canal]==255) 
            {
//                if(max<i*img.cols*canal+j*canal) max = i*img.cols*canal+j*canal;
                xMin = j;
                xMinFinded = true;
            }
            if(!xMaxFinded && img.data[(img.rows-i-1)*img.cols*canal + (img.cols-j-1)*canal]==255) 
            {
//                if(max<(img.rows-i-1)*img.cols*canal + (img.cols-j-1)*canal) max = (img.rows-i-1)*img.cols*canal + (img.cols-j-1)*canal;
                xMax = img.cols-j-1;
                xMaxFinded = true;
            }
        }
//        cout << endl;
    }
//    cout << "max = " << max << endl;
    
    
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
            if(!yMaxFinded && img.data[(img.rows-i-1)*img.cols*canal + (img.cols-j-1)*canal]==255) 
            {
                yMax = img.rows-i-1;
                yMaxFinded = true;
            }
        }
    cout << "xmin = " << xMin << "  xMax = " << xMax << "  yMin = " << yMin << "  yMax = " << yMax << endl;
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



/*
 * liste les fichiers de la base, on obtient un vecteur[nbclasses][nbimagesclasse]
 * 
 EX :
vector< vector<string> > base;
readPath(base, "F:/iut/utbm/S5/projetIN52-54/ClassImages/", "bmp")
 * 
 */
void readPath(vector< vector<string> > &base, string dir, string fileExtension)
{
    DIR *dp;
    struct dirent *ep;

    dp = opendir (dir.c_str());
    if (dp != NULL)
    {
        while (ep = readdir (dp))
        {
            
                if (*(ep->d_name) != '.' && *(ep->d_name)!='..')
                {
                    base.push_back( vector<string>() );
                    string newPath = dir + ep->d_name;
                    DIR *dpsubdir = opendir ( newPath.c_str() );
                    struct dirent *epsubdir;

                    while (epsubdir = readdir (dpsubdir))
                    {
                        if(   tolower(epsubdir->d_name[strlen(epsubdir->d_name)-1])==tolower(fileExtension[fileExtension.size()-1]) && tolower(epsubdir->d_name[strlen(epsubdir->d_name)-2])==tolower(fileExtension[fileExtension.size()-2]) && tolower(epsubdir->d_name[strlen(epsubdir->d_name)-3])==tolower(fileExtension[fileExtension.size()-3])  )
                        {        
                            string filename = dir;
                            filename+= *(ep->d_name);
                            filename+="/";
                            filename += epsubdir->d_name;
                            base[base.size()-1].push_back(filename);
                        }
                    }
                    (void) closedir (dpsubdir);
                }
        }
        (void) closedir (dp);
    }
}


#endif
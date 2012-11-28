/* 
 * File:   ClassifieursProfils.cpp
 * Author: VIRTUAL_BUG
 * 
 * Created on 27 novembre 2012, 16:29
 */

#ifndef CLASSIFIEURSPROFILS_H
#define	CLASSIFIEURSPROFILS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include <math.h>

#include "utilsFunctions.h"
#include "paramsClassifieurs.h"

using namespace cv;
using namespace std;

class ClassifieursProfils 
{
    protected:
        
        //contain all profiles of all images constituting base (ohlà, je crois que jvais repasser au français pour les comm !)
        vector< vector<float *> > baseHorizontalProfiles;
        vector< vector<float *> > baseVerticalProfiles;
        //les profils moyens de chaque classe
        vector<float *> baseHorizontalAVGProfiles;
        vector<float *> baseVerticalAVGProfiles;
        
        //facteur à 1 pour le classifieur histogramm, à 2 pour le classifieur profils
        int loopFactor;
        
    public:
        
        virtual float * horizontalProfiling(Mat img) = 0;
        virtual float * verticalProfiling(Mat img) = 0;
        
        void initBase()
        {
            //on set les images de la base de référence
            vector< vector<string> > imagesClass;
            
            for(int i=0; i<NB_CLASSES; i++)
                imagesClass.push_back( vector<string>() );
            
            //pour chaque classe, on ajoute la/les images correspondantes à la base (pour le moment je travaille avec les 7 images initiales de Capelle)
            imagesClass[0].push_back(pathBase+"0/0.bmp");
            imagesClass[1].push_back(pathBase+"1/0.bmp");
            imagesClass[2].push_back(pathBase+"2/0.bmp");
            imagesClass[3].push_back(pathBase+"3/0.bmp");
            imagesClass[4].push_back(pathBase+"4/0.bmp");
            imagesClass[5].push_back(pathBase+"5/0.bmp");
            imagesClass[5].push_back(pathBase+"5/1.bmp");
            
            //on calcule les profils de chaque image de la base
            for(int currentClass = 0; currentClass < NB_CLASSES; currentClass++)
            {
                baseHorizontalProfiles.push_back( vector<float *>() );
                baseVerticalProfiles.push_back( vector<float *>() );
                for(int currentImage = 0; currentImage < imagesClass[currentClass].size(); currentImage++)
                {
                    //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
                    Mat hand = extractHandFromBMPFile( imagesClass[currentClass][currentImage] );
                    
                    /*string windowname = "subImage"+currentImage;
                    namedWindow(windowname.c_str(), CV_WINDOW_AUTOSIZE );
                    imshow(windowname.c_str(), hand );*/

                    baseHorizontalProfiles[currentClass].push_back( horizontalProfiling(hand) );  
                    baseVerticalProfiles[currentClass].push_back( verticalProfiling(hand) );      
                    
                }
            }
            setAVGValue();
        }
        
        
        
        
        
        //calcule la valeur moyenne des profils et les stocke dans baseHorizontalAVGProfiles/baseVerticalAVGProfiles[currentClass][currentProfile]
        void setAVGValue()
        {
            for(int currentClass = 0; currentClass < NB_CLASSES; currentClass++)
            {
                baseHorizontalAVGProfiles.push_back(new float[NB_PROFILES*loopFactor]);
                baseVerticalAVGProfiles.push_back(new float[NB_PROFILES*loopFactor]);
                
                for(int currentProfile=0; currentProfile<NB_PROFILES*loopFactor; currentProfile++)
                {
                    float sumH=0, sumV=0;
                    int nbImagesCurrentClass = baseHorizontalProfiles[currentClass].size();
                    for(int currentImage = 0; currentImage < nbImagesCurrentClass; currentImage++)
                    {
                        sumH+=baseHorizontalProfiles[currentClass][currentImage][currentProfile];
                        sumV+=baseVerticalProfiles[currentClass][currentImage][currentProfile];
                    }
                    sumH/=nbImagesCurrentClass;
                    sumV/=nbImagesCurrentClass;
                    baseHorizontalAVGProfiles[currentClass][currentProfile] = sumH;
                    baseVerticalAVGProfiles[currentClass][currentProfile] = sumV;
                }
            }
            
        }
        
        
        
        
        //distance entre deux vecteurs de taille égale    
        float distanceBetweenVectors(float * vec1, float * vec2, int size)
        {
            float accum=0;
            for(int i=0; i<size; i++)
                accum+= pow(vec2[i]-vec1[i], 2);
            accum = sqrt(accum);
            return accum;
        }
        
        
        
        
        
        //pour le moment se contente d'afficher la proba d'appartenance à chaque classe
        void probaForEachClass(float * horizontalProfilesTestedImage, float * verticalProfilesTestedImage)
        {
            float numeratorsH[NB_CLASSES], numeratorsV[NB_CLASSES];
            float denominatorH=0, denominatorV=0;
            for(int currentClass=0; currentClass<NB_CLASSES; currentClass++)
            {
                numeratorsH[currentClass] = exp( -distanceBetweenVectors(horizontalProfilesTestedImage, baseHorizontalAVGProfiles[currentClass], NB_PROFILES*loopFactor ));
                numeratorsV[currentClass] = exp( -distanceBetweenVectors(verticalProfilesTestedImage, baseVerticalAVGProfiles[currentClass], NB_PROFILES*loopFactor ));
                denominatorH+=numeratorsH[currentClass];
                denominatorV+=numeratorsV[currentClass];
            }
            
            /*float maxH = 0, maxV = 0;
            int maxHClass, maxVClass;*/
            for(int currentClass=0; currentClass<NB_CLASSES; currentClass++)
            {
                float probaH = numeratorsH[currentClass]/denominatorH;
                float probaV = numeratorsV[currentClass]/denominatorV;
                
                //a décommenter quand on sera d'accord sur la prise de décision lorsque les profils H et V ne donnent pas les mêmes résultats
                /*if(maxH<probaH)
                {
                    maxH = probaH;
                    maxHClass = currentClass;
                }
                if(maxV<probaV)
                {
                    maxV = probaV;
                    maxVClass = currentClass;
                }*/
                
                cout << "probaH class" << currentClass << " = " << probaH << endl;
                cout << "probaV class" << currentClass << " = " << probaV << endl;
            }
        }
        
        
        
        //teste une image BMP, à adapter selon besoin
        //on affiche les images intermédiaires pour contrôler ce qu'il se passe
        //le seuil reste arbitraire et à adapter
        void testImage(String filename)
        {
            //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
            Mat img = imread( filename, 1 );
            namedWindow("original", CV_WINDOW_AUTOSIZE );
            imshow("original", img );
            
            revertBinarize(img, 100);
            namedWindow("binarized", CV_WINDOW_AUTOSIZE );
            imshow("binarized", img );
            
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
            
            
            namedWindow("extracted hand", CV_WINDOW_AUTOSIZE );
            imshow("extracted hand", hand );
            
            
            float * horizontalProfilesTestedImage = horizontalProfiling(hand);
            float * verticalProfilesTestedImage = verticalProfiling(hand);
            probaForEachClass(horizontalProfilesTestedImage, verticalProfilesTestedImage);
        }
        
       
};

#endif	/* CLASSIFIEURSPROFILS_H */


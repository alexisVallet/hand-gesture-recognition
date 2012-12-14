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
#include <fstream>
#include <typeinfo>

#include "utilsFunctions.h"
#include "paramsClassifieurs.h"
#include "rotateHand.h"

using namespace cv;
using namespace std;

//booléen indiquant si les mains doivent être redressées ou non avant traitement
static bool redressHand = true;

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
            //imagesClass[5].push_back(pathBase+"5/1.bmp");
            bool revertBinarize = true;
            
            /*imagesClass[0].push_back(pathSegmentedBase+"0/0.bmp");
            imagesClass[1].push_back(pathSegmentedBase+"1/0.bmp");
            imagesClass[2].push_back(pathSegmentedBase+"2/0.bmp");
            imagesClass[2].push_back(pathSegmentedBase+"2/1.bmp");
            imagesClass[3].push_back(pathSegmentedBase+"3/0.bmp");
            imagesClass[3].push_back(pathSegmentedBase+"3/1.bmp");
            imagesClass[4].push_back(pathSegmentedBase+"4/0.bmp");
            imagesClass[4].push_back(pathSegmentedBase+"4/1.bmp");
            imagesClass[5].push_back(pathSegmentedBase+"5/0.bmp");
            imagesClass[5].push_back(pathSegmentedBase+"5/1.bmp");
            bool revertBinarize = false;**/
            
            
             string windowname = "ImageFinaleBase";
            //on calcule les profils de chaque image de la base
            for(int currentClass = 0; currentClass < NB_CLASSES; currentClass++)
            {
                baseHorizontalProfiles.push_back( vector<float *>() );
                baseVerticalProfiles.push_back( vector<float *>() );
                for(int currentImage = 0; currentImage < imagesClass[currentClass].size(); currentImage++)
                {
//                    cout << "imgpath = " << imagesClass[currentClass][currentImage] << endl;
                    //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
                    Mat hand = extractHandFromBMPFile( imagesClass[currentClass][currentImage]);
                    hand.dims = 0;
                   
                    namedWindow("avant redressement", CV_WINDOW_AUTOSIZE );
                    imshow("avant redressement", hand );
  waitKey(0);                   
                    if(redressHand)
                        hand = redressHandFromBinarySegmentedImage(hand, 255);
                    
                    windowname +="a";
                    namedWindow(windowname.c_str(), CV_WINDOW_AUTOSIZE );
                    imshow(windowname.c_str(), hand );
waitKey(0);
                    float * horizontalProfiles = horizontalProfiling(hand);
                    float * verticalProfiles = horizontalProfiling(hand);
                    baseHorizontalProfiles[currentClass].push_back( horizontalProfiles );  
                    baseVerticalProfiles[currentClass].push_back( verticalProfiles ); 
                    
                    //cout << "this.typeid() = " << (string)typeid(*this).name() << endl;
                    writeProfils(imagesClass[currentClass][currentImage], horizontalProfiles, verticalProfiles);
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
            
            float combinedNumerators[NB_CLASSES];
            float combinedDenominator = 0;
            for(int currentClass=0; currentClass<NB_CLASSES; currentClass++)
            {
                numeratorsH[currentClass] = exp( -distanceBetweenVectors(horizontalProfilesTestedImage, baseHorizontalAVGProfiles[currentClass], NB_PROFILES*loopFactor ));
                numeratorsV[currentClass] = exp( -distanceBetweenVectors(verticalProfilesTestedImage, baseVerticalAVGProfiles[currentClass], NB_PROFILES*loopFactor ));
                denominatorH+=numeratorsH[currentClass];
                denominatorV+=numeratorsV[currentClass];
                
                //combinaisons des profils horizontaux et verticaux pour considérer les vecteurs comme un seul
                float * baseCombinedProfiles = new float[NB_PROFILES*loopFactor*2];
                float * imageCombinedProfiles = new float[NB_PROFILES*loopFactor*2];
                for(int i=0; i<NB_PROFILES*loopFactor; i++)
                {
                    baseCombinedProfiles[i] = baseHorizontalAVGProfiles[currentClass][i];
                    baseCombinedProfiles[i + NB_PROFILES*loopFactor] = baseVerticalAVGProfiles[currentClass][i];
                    
                    imageCombinedProfiles[i] = horizontalProfilesTestedImage[i];
                    imageCombinedProfiles[i + NB_PROFILES*loopFactor] = verticalProfilesTestedImage[i];
                }
                combinedNumerators[currentClass] = exp( -distanceBetweenVectors(imageCombinedProfiles, baseCombinedProfiles, NB_PROFILES*loopFactor*2 ));
                combinedDenominator+=combinedNumerators[currentClass];
            }

            
            /*float maxH = 0, maxV = 0;
            int maxHClass, maxVClass;*/
            for(int currentClass=0; currentClass<NB_CLASSES; currentClass++)
            {
                float probaH = numeratorsH[currentClass]/denominatorH;
                float probaV = numeratorsV[currentClass]/denominatorV;
                float probaCombined = combinedNumerators[currentClass]/combinedDenominator;
                
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
                cout << "probaCombined class" << currentClass << " = " << probaCombined << endl << endl;
            }
        }
        
        
        
        //teste une image BMP, à adapter selon besoin
        //on affiche les images intermédiaires pour contrôler ce qu'il se passe
        //le seuil reste arbitraire et à adapter
        void testImage(String filename)
        {
            //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
            Mat hand = extractHandFromBMPFile(filename);
            
            
            namedWindow("extracted hand", CV_WINDOW_AUTOSIZE );
            imshow("extracted hand", hand );
            
 waitKey(0);          
            float * horizontalProfilesTestedImage = horizontalProfiling(hand);
            float * verticalProfilesTestedImage = verticalProfiling(hand);
            probaForEachClass(horizontalProfilesTestedImage, verticalProfilesTestedImage);
        }
        
        
        
        
        //enregistre les profils dans un fichier texte
        void writeProfils(string filepath, float * horizontalProfiles, float * verticalProfiles)
        {
            int posDernierSlash =filepath.rfind("/", filepath.size()-1);
            
            string path = filepath.substr(0, posDernierSlash+1);
            
            //on determine le préfixe du fichier, PROFIL ou HISTO selon type de classifieur
            string prefix;
            if( ((string)typeid(*this).name()).find(classNameProfilesClassifier)!=string::npos )
                prefix = prefixProfilesClassifier;
            else if( ((string)typeid(*this).name()).find(classNameHistoClassifier)!=string::npos )
                prefix = prefixHistoClassifier;
            
            
            //on détermine le nom du fichier export
            string filename = prefix;
            filename += filepath.substr( posDernierSlash+1, filepath.size()-1-posDernierSlash-4 );
            filename += ".txt";
            String fn = path + filename;
            cout << "final = " << fn << endl;
            
            ofstream profil( fn.c_str());
            
            profil << "Hleft:" << endl;
            for(int i=0; i<NB_PROFILES; i++)
            {
                profil << horizontalProfiles[i] << endl;
            }
            profil << "\nHright:" << endl;
            for(int i=0; i<NB_PROFILES; i++)
            {
                profil << horizontalProfiles[i+NB_PROFILES] << endl;
            }
            profil << "\nVup:" << endl;
            for(int i=0; i<NB_PROFILES; i++)
            {
                profil << verticalProfiles[i] << endl;
            }
            profil << "\nVdown:" << endl;
            for(int i=0; i<NB_PROFILES; i++)
            {
                profil << verticalProfiles[i] << endl;
            }
        }
        
       
};

#endif	/* CLASSIFIEURSPROFILS_H */


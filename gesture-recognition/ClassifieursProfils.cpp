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





class ClassifieursProfils
{
    protected:
        
        //contain all profiles of all images constituting base (ohlà, je crois que jvais repasser au français pour les comm !)
        vector< vector<float *> > baseHorizontalProfiles;
        vector< vector<float *> > baseVerticalProfiles;
        //les profils moyens de chaque classe
        vector<float *> baseHorizontalAVGProfiles;
        vector<float *> baseVerticalAVGProfiles;
        
        //inutile, utilisable pour optimisations futures pour pas être obligé de retraiter n fois les images de la base
        vector< vector<Mat> > baseSegmentedImagesClass;
        
        
        
        //facteur à 1 pour le classifieur histogramm, à 2 pour le classifieur profils
        int loopFactor;
        
    public:
        
        //correspondance des classes dans le cas de la base étendue
        vector< int >classCorrespondances;
        
        virtual float * horizontalProfiling(Mat img) = 0;
        virtual float * verticalProfiling(Mat img) = 0;
        

        
        
        /**
         * add image into base
         * @param segmentedImage the segmented extracted binarized hand
         * @param expectedClass the expected class of the hand
         */
        void train(Mat segmentedImage, int expectedClass)
        {
            if(redressHand)
                segmentedImage = redressHandFromBinarySegmentedImage(segmentedImage, 255);


            float * horizontalProfiles = horizontalProfiling(segmentedImage);
            float * verticalProfiles = verticalProfiling(segmentedImage);

            if(baseHorizontalProfiles.size()<=expectedClass)
                while(baseHorizontalProfiles.size()<=expectedClass)
                    baseHorizontalProfiles.push_back(vector<float *>());
            
            if(baseVerticalProfiles.size()<=expectedClass)
                while(baseVerticalProfiles.size()<=expectedClass)
                    baseVerticalProfiles.push_back(vector<float *>());
         
            baseHorizontalProfiles[expectedClass].push_back(horizontalProfiles);
            baseVerticalProfiles[expectedClass].push_back(verticalProfiles);

            setAVGValue(baseHorizontalProfiles.size());
        }
        
        
        
        void initBase()
        {
            //reinitialization of datas
            NB_CLASSES = (baseImagesCappelle==true ? 6:12);
            baseHorizontalProfiles.clear();
            baseVerticalProfiles.clear();
            baseHorizontalAVGProfiles.clear();
            baseVerticalAVGProfiles.clear();        
            baseSegmentedImagesClass.clear();
            classCorrespondances.clear();

            //on set les images de la base de référence
            vector< vector<string> > imagesClass;
            
            if(!baseImagesCappelle)
                readPath2(imagesClass, classCorrespondances, /*"F:/iut/utbm/S5/projetIN52-54/ClassImagesEtendue2/"*/"./runFolder/ClassImagesEtendue2/", "bmp"); // base étendue
            else readPath(imagesClass, pathBase, "bmp"); // base élémentaire
            
            cout << "imagesClass = " << imagesClass.size() << endl;

            //on calcule les profils de chaque image de la base
            for(int currentClass = 0; currentClass < NB_CLASSES; currentClass++)
            {
                
                baseHorizontalProfiles.push_back( vector<float *>() );
                baseVerticalProfiles.push_back( vector<float *>() );
                baseSegmentedImagesClass.push_back(vector<Mat>());
                for(int currentImage = 0; currentImage < imagesClass[currentClass].size(); currentImage++)
                {
                    //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
                    Mat hand = extractHandFromBMPFile( imagesClass[currentClass][currentImage]);
                    hand.dims = 0;             
                    
                    if(redressHand)
                        hand = redressHandFromBinarySegmentedImage(hand, 255);
                    
                    baseSegmentedImagesClass[currentClass].push_back(hand);

                    float * horizontalProfiles = horizontalProfiling(hand);
                    float * verticalProfiles = verticalProfiling(hand);
                    baseHorizontalProfiles[currentClass].push_back( horizontalProfiles );  
                    baseVerticalProfiles[currentClass].push_back( verticalProfiles ); 
                    
                    //writeProfils(imagesClass[currentClass][currentImage], horizontalProfiles, verticalProfiles);
                }
            }
            setAVGValue();
        }
        
        
        
        
        
        //calcule la valeur moyenne des profils et les stocke dans baseHorizontalAVGProfiles/baseVerticalAVGProfiles[currentClass][currentProfile]
        void setAVGValue(int nbClasses = NB_CLASSES)
        {
            for(int currentClass = 0; currentClass < nbClasses; currentClass++)
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
        
        

        
        
        
        /**
         * compute distance from AVG base values and return a vector of probability for each class
         * @param horizontalProfilesTestedImage vector of H profiles of tested image, size = NB_CLASSES
         * @param verticalProfilesTestedImage vector of V profiles of tested image, size = NB_CLASSES
         * @return vector of probability for each class, size = NB_CLASSES
         */
        float* probaForEachClass(float * horizontalProfilesTestedImage, float * verticalProfilesTestedImage)
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
            
            float * result = new float[NB_CLASSES];
            
            for(int currentClass=0; currentClass<NB_CLASSES; currentClass++)
            {
                float probaH = numeratorsH[currentClass]/denominatorH;
                float probaV = numeratorsV[currentClass]/denominatorV;
                float probaCombined = combinedNumerators[currentClass]/combinedDenominator;
                
                result[currentClass] = probaCombined;
                if(DEBUG)
                {
                    cout << "probaH class" << currentClass << " = " << probaH << endl;
                    cout << "probaV class" << currentClass << " = " << probaV << endl;
                    cout << "probaCombined class" << currentClass << " = " << probaCombined << endl << endl;
                }
            }
            return result;
        }
        
        
        
        /**
         * test BMP filename, without KPPV
         * @param filename name of BMP file
         * @return vector of probability for each class, size = NB_CLASSES
         */
        float* testImage(String filename)
        {
            //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
            Mat hand = extractHandFromBMPFile(filename);
            
            if(redressHand)
               hand = redressHandFromBinarySegmentedImage(hand, 255);
            
            if(DEBUG)
            {
                namedWindow("TESTED hand", CV_WINDOW_AUTOSIZE );
                imshow("TESTED hand", hand );
                 waitKey(0);  
            }
     
            float * horizontalProfilesTestedImage = horizontalProfiling(hand);
            float * verticalProfilesTestedImage = verticalProfiling(hand);
            
            return probaForEachClass(horizontalProfilesTestedImage, verticalProfilesTestedImage);
        }
        
        
        
        /**
         * test BMP filename, using KPPV
         * @param filename bmp file to test
         * @param probaForEachClassKPPV empty pointer to return the probability for each class based on result of KPPV, size = NB_CLASSES
         * @return number of finger according to KPPV
         */
        int testImageKPPV(String filename, float * &probaForEachClassKPPV)
        {
            //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
            Mat hand = extractHandFromBMPFile(filename);
            
            if(redressHand)
               hand = redressHandFromBinarySegmentedImage(hand, 255);
            
            if(DEBUG)
            {
                namedWindow("TESTED hand", CV_WINDOW_AUTOSIZE );
                imshow("TESTED hand", hand );
                 waitKey(0);      
            }
                    
            float * horizontalProfilesTestedImage = horizontalProfiling(hand);
            float * verticalProfilesTestedImage = verticalProfiling(hand);
            
            //testKPPV
            int * classesKPPV = KPPV(horizontalProfilesTestedImage, verticalProfilesTestedImage);
            int resKPPV = KPPVResult( classesKPPV );
            
            if(DEBUG) cout << "final resKPPV = " << resKPPV << endl;
            
            //calcul de la proba de chaque classe selon les res KPPV
            probaForEachClassKPPV = new float[NB_CLASSES];
            for(int cl=0; cl<NB_CLASSES; cl++)
                probaForEachClassKPPV[cl] = 0.0;
            
            for(int k=0; k<K; k++)
            {
                probaForEachClassKPPV[ classesKPPV[k] ]+=1.0;
                if(DEBUG)cout << "probaForEachClassKPPV[ classesKPPV[k] ]= " << probaForEachClassKPPV[ classesKPPV[k] ] << endl;
            }
                        
            for(int cl=0; cl<NB_CLASSES; cl++)
            {
                probaForEachClassKPPV[cl]/=K;
            }
            
            return resKPPV;
        }
        
        
        /**
         * test all images of directory having the same structure of base path to compute succes rate
         * @param path
         * @return string containing results
         */
        string testDir(string path)
        {
            stringstream result;
            
            vector< vector<string> > imagesTest;       
            vector< int >classCorrespondancesTest;
            //readPath(imagesTest, path, "bmp");
            
            if(testImagesCappelle)
            {
                for(int i=0; i<NB_CLASSES; i++)
                    imagesTest.push_back( vector<string>() );
                imagesTest[0].push_back(pathBase+"0/0.bmp");
                imagesTest[1].push_back(pathBase+"1/0.bmp");
                imagesTest[2].push_back(pathBase+"2/0.bmp");
                imagesTest[3].push_back(pathBase+"3/0.bmp");
                imagesTest[4].push_back(pathBase+"4/0.bmp");
                imagesTest[5].push_back(pathBase+"5/0.bmp");
                //readPath(imagesTest, pathBase, "bmp");
            }
            else readPath2(imagesTest, classCorrespondancesTest, /*"F:/iut/utbm/S5/projetIN52-54/ClassImagesEtendue2/"*/"./runFolder/ClassImagesEtendue2/", "bmp");
            
            int numberOfTestedImages = 0;
            int resJustes = 0;
            
            //toutes les images tests, imagesTest[i=classe de l'image testée][img = numéro de l'image de la classe i]
            for(int i=0; i<imagesTest.size(); i++)
            {
                for(int img=0; img<imagesTest[i].size(); img++)
                {
                    numberOfTestedImages++;
                    
                    int resultClass;
                    string imgFile = imagesTest[i][img];
                    float * probaForEachClass;
                    float * probaForEachClassKPPV;
                    
                    if(useKPPV)
                    {
                        resultClass = testImageKPPV(imgFile, probaForEachClassKPPV);
                    }
                    else
                    {
                        probaForEachClass = testImage(imgFile);
                        resultClass = getMaxIndexFromTab(probaForEachClass , NB_CLASSES );
                    }

                    if(baseImagesCappelle)
                    {
                        if(testImagesCappelle)
                        {
                            if(resultClass==i)
                                resJustes++;
                        }
                        else
                        {
                            if(resultClass==classCorrespondancesTest[i])
                                resJustes++;
                        }
                        
                        if(DEBUG)cout << "l'image : " << imgFile << "  est détectée comme appartenant à la classe : " << resultClass << endl; 
                        if(DEBUG)result << "l'image : " << imgFile << "  est détectée comme appartenant à la classe : " << resultClass << endl;
                    }
                    //base étendue
                    else
                    {
                        if(testImagesCappelle)
                        {
                            if(classCorrespondances[resultClass]==i)
                                resJustes++;
                        }
                        else
                        {
                            if(classCorrespondances[resultClass]==classCorrespondances[i])
                                resJustes++;
                        }
                        if(DEBUG) cout << "l'image : " << imgFile << "  est détectée comme appartenant à la classe : " << classCorrespondances[resultClass] << endl; 
                        if(DEBUG) result << "l'image : " << imgFile << "  est détectée comme appartenant à la classe : " << classCorrespondances[resultClass] << endl; 
                    }
                 }
            }
            
            string testedImages, baseImages, redress, kppv;
            if(useKPPV)
                 kppv = " avec KPPV :";
            else kppv = " sans KPPV :";
            if(testImagesCappelle)
                testedImages = "images de base testée";
            else testedImages = "images étendues à la con testée";
            if(baseImagesCappelle)
                baseImages = "base élémentaire";
            else baseImages = "base étendue";
            if(redressHand)
                redress = "images redressées";
            else redress = "images non redressées";
            
            cout << baseImages << ", " << testedImages << ", " << redress << kppv << endl;
            result << baseImages << ", " << testedImages << ", " << redress << kppv << endl;
            
            cout << "sur " << numberOfTestedImages <<" images, il en a détecté " << resJustes << " correctement" <<endl;
            cout << "soit un taux de réussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl << endl;
            result << "sur " << numberOfTestedImages <<" images, il en a détecté " << resJustes << " correctement" <<endl;
            result << "soit un taux de réussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl << endl;
            
            return result.str();
        }
        
        
 
        
        
        
        
        //enregistre les profils dans un fichier texte
        /**
         * not used...
         * @param filepath
         * @param horizontalProfiles
         * @param verticalProfiles
         */
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
            if(DEBUG) cout << "final = " << fn << endl;
            
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
        
        
        

        
        
        //retourne un vecteur d'entier contenant les K classes les plus proches
        /**
         * 
         * @param horizontalProfiles H profiles of tested image
         * @param verticalProfiles V profiles of tested image
         * @return int vector containing K nearest class
         */
        int * KPPV(float * horizontalProfiles, float * verticalProfiles)
        {
            float baseCombinedProfiles[NB_PROFILES*loopFactor*2];
            float imageCombinedProfiles[NB_PROFILES*loopFactor*2];
            
            //un conteneur intermédiaire
            float KPPV[K][2];
            //initialisation à une valeur supérieure à la distance max 
            for(int i=0; i<K; i++)
                for(int j=0; j<2; j++)
                    KPPV[i][j] = 99999999;
            
            int * returnedKPPV = new int[K];
            
            //fusion des profils H et V de l'image a tester
            for(int profiles=0; profiles<NB_PROFILES*loopFactor; profiles++)
            {
                imageCombinedProfiles[profiles] = horizontalProfiles[profiles];
                imageCombinedProfiles[profiles + NB_PROFILES*loopFactor] = verticalProfiles[profiles];
            }
            
            for(int cl=0; cl<NB_CLASSES; cl++)
            {
                for(int img=0; img<baseHorizontalProfiles[cl].size(); img++)
                {
                    //fusion des profils H et V de la base
                    for(int profiles=0; profiles<NB_PROFILES*loopFactor; profiles++)
                    {
                        baseCombinedProfiles[profiles] = baseHorizontalProfiles[cl][img][profiles];
                        baseCombinedProfiles[profiles + NB_PROFILES*loopFactor] = baseVerticalProfiles[cl][img][profiles];
                    }
                    
                    float dist = distanceBetweenVectors(baseCombinedProfiles, imageCombinedProfiles, NB_PROFILES*loopFactor*2);
                    if(DEBUG)cout << "dist = " << dist << "  cl= " << cl << endl;
                    
                    float maxK = 0; int indicemaxK = 0;
                    for(int k=0; k<K; k++)
                    {
                        if( maxK < KPPV[k][1] )
                        {
                            maxK = KPPV[k][1];
                            indicemaxK = k;
                        }
                    }
                    if(dist<maxK)
                    {
                        KPPV[indicemaxK][1] = dist;
                        KPPV[indicemaxK][0] = cl;
                    }
                }
            }
            //recopie des valeurs finales
            for(int i=0; i<K; i++)
            {
                returnedKPPV[i] = KPPV[i][0];
                if(DEBUG)cout << "returnedKPPV[ " << i << " ] = " << returnedKPPV[i] << endl;
            }
            
            return returnedKPPV;
        }
        
        //prends en paramètre le vecteur retourné par KPPV() et retourne la classe d'appartenance correspondante
        int KPPVResult(int * KPPV)
        {
            int classesRepresentees[NB_CLASSES];
            for(int cl=0; cl<NB_CLASSES; cl++)
                classesRepresentees[cl] = 0;
            
            for(int k=0; k<K; k++) 
                classesRepresentees[ KPPV[k] ]++;
            
            //on prends la classe la plus représentée
            int classMax = 0;
            int valClassMax = 0;
            for(int cl=0; cl<NB_CLASSES; cl++)
                if(valClassMax < classesRepresentees[cl])
                {
                    valClassMax = classesRepresentees[cl];
                    classMax = cl;
                }

            return classMax;
        }
        
       
       
};

#endif	/* CLASSIFIEURSPROFILS_H */


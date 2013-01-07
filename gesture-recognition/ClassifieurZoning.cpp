/* 
 * File:   ClassifieurZoning.cpp
 * Author: VIRTUAL_BUG
 * 
 * Created on 5 janvier 2013, 12:18
 */
#ifndef CLASSIFIEURZONING
#define	CLASSIFIEURZONING

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include <vector>
#include "utilsFunctions.h"
#include "paramsClassifieurs.h"
#include "rotateHand.h"

using namespace std;


class ClassifieurZoning 
{
    private:
        //baseZoning[nbClasses][nbimagesClasse] = float[m*n]
        vector< vector<float *> > baseZoning;
        vector< float* > baseZoningAVG;
        
    public:
        
        //correspondance des classes dans le cas de la base étendue
        vector< int >classCorrespondances;
        
        
        /**
         * add image into base
         * @param segmentedImage the segmented extracted binarized hand
         * @param expectedClass the expected class of the hand
         */
        void train(Mat segmentedImage, int expectedClass)
        {
            if(redressHand)
                segmentedImage = redressHandFromBinarySegmentedImage(segmentedImage, 255);

            float * zonings = zoning(segmentedImage);

            if(baseZoning.size()<=expectedClass)
                while(baseZoning.size()<=expectedClass)
                    baseZoning.push_back(vector<float *>());
         
            baseZoning[expectedClass].push_back(zonings);

            setAVGValue(baseZoning.size());
        }
        
        ClassifieurZoning()
        {
 //           cout << "constructeur OK" << endl;
        }
        
        
        void initBase()
        {
            //on set les images de la base de référence
            vector< vector<string> > imagesClass;
            
            readPath(imagesClass, pathBase, "bmp"); // base élémentaire
            
            /*for(int i=0; i<NB_CLASSES; i++)
                imagesClass.push_back( vector<string>() );
            //pour chaque classe, on ajoute la/les images correspondantes à la base (pour le moment je travaille avec les 7 images initiales de Capelle)
            imagesClass[0].push_back("D:/0.bmp");
            imagesClass[1].push_back("D:/1.bmp");
            imagesClass[2].push_back("D:/2.bmp");
            imagesClass[3].push_back("D:/3.bmp");
            imagesClass[4].push_back("D:/4.bmp");
            imagesClass[5].push_back("D:/5.bmp");**/
            
            //on calcule les profils de chaque image de la base
            for(int currentClass = 0; currentClass < NB_CLASSES; currentClass++)
            {
                baseZoning.push_back( vector<float *>() );
                
                for(int currentImage = 0; currentImage < imagesClass[currentClass].size(); currentImage++)
                {
//                    cout << "initbase, currentclass = " << currentClass << "  currentImage = " << currentImage << endl;
                    //chargement de l'image, binarisation seuil arbitraire, détection des bounds de la main, extraction de la main, définition des profils
                    Mat hand = extractHandFromBMPFile( imagesClass[currentClass][currentImage]);
                    //Mat hand = imread( imagesClass[currentClass][currentImage], CV_LOAD_IMAGE_GRAYSCALE );
                    hand.dims = 0;             
                    
                    if(redressHand)
                        hand = redressHandFromBinarySegmentedImage(hand, 255);
//                    cout << "avant zoningInitBase" << endl;
                    float * zonings = zoning(hand);
 //                   cout << "apres zoningInitBase" << endl;
                    baseZoning[currentClass].push_back( zonings ); 
                }
            }
            setAVGValue();
        }
        
        
        
        
        
        float* probaForEachClass(float * zoningsTestedImage)
        {
            float numerators[NB_CLASSES];
            float denominator=0;
            
            for(int currentClass=0; currentClass<NB_CLASSES; currentClass++)
            {
                numerators[currentClass] = exp( -distanceBetweenVectors(zoningsTestedImage, baseZoningAVG[currentClass], M*N ));
                denominator+=numerators[currentClass];
            }
            
            float * result = new float[NB_CLASSES];
            for(int currentClass=0; currentClass<NB_CLASSES; currentClass++)
            {
                result[currentClass] = numerators[currentClass]/denominator;
                if(DEBUG)
                {
                    cout << "probaclass" << currentClass << " = " << result[currentClass] << endl << endl;
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
            //Mat hand = imread( filename, CV_LOAD_IMAGE_GRAYSCALE );
            
            if(redressHand)
               hand = redressHandFromBinarySegmentedImage(hand, 255);
            
            if(DEBUG)
            {
                namedWindow("TESTED hand", CV_WINDOW_AUTOSIZE );
                imshow("TESTED hand", hand );
                 waitKey(0);  
            }
     
            float * zoningsTestedImage = zoning(hand);
            
            return probaForEachClass(zoningsTestedImage);
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
                    
            float * zoningsTestedImage = zoning(hand);
            
            //testKPPV
            int * classesKPPV = KPPV(zoningsTestedImage);
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
        
        
        
        
        
        
        
        
        //retourne un vecteur d'entier contenant les K classes les plus proches
        /**
         * 
         * @param horizontalProfiles H profiles of tested image
         * @param verticalProfiles V profiles of tested image
         * @return int vector containing K nearest class
         */
        int * KPPV(float * horizontalProfiles)
        {
            
            //un conteneur intermédiaire
            float KPPV[K][2];
            //initialisation à une valeur supérieure à la distance max = 1*NB_PROFILES*loopFactor*2
            for(int i=0; i<K; i++)
                for(int j=0; j<2; j++)
                    KPPV[i][j] = 99999999;
            
            int * returnedKPPV = new int[K];

            
            for(int cl=0; cl<NB_CLASSES; cl++)
            {
                for(int img=0; img<baseZoning[cl].size(); img++)
                {
                    
                    float dist = distanceBetweenVectors(baseZoning[cl][img], horizontalProfiles, M*N);
                    cout << "dist = " << dist << "  cl= " << cl << endl;
                    
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
                cout << "returnedKPPV[ " << i << " ] = " << returnedKPPV[i] << endl;
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
        
        
        
        
        void setAVGValue(int nbClasses = NB_CLASSES)
        {
            baseZoningAVG.clear();

            for(int currentClass = 0; currentClass < nbClasses; currentClass++)
            {
                baseZoningAVG.push_back(new float[M*N]);
                
                for(int currentProfile=0; currentProfile<M*N; currentProfile++)
                {
                    float sum=0;
                    int nbImagesCurrentClass = baseZoning[currentClass].size();
                    for(int currentImage = 0; currentImage < nbImagesCurrentClass; currentImage++)
                    {
                        sum+=baseZoning[currentClass][currentImage][currentProfile];
                    }
                    sum/=nbImagesCurrentClass;

                    baseZoningAVG[currentClass][currentProfile] = sum;
                }
            }
        }
        
        
        
        
        
        void testVitFait()
        {
            cout << "entree dans testVitFait" << endl;
            //Mat hand = extractHandFromBMPFile( "D:/test.bmp");
            Mat hand = imread( /*"D:/test3.bmp"*/pathBase+"1/0.bmp", CV_LOAD_IMAGE_GRAYSCALE );
            hand.dims = 0;           
            cout << "image chargee" << endl;

            //if(redressHand)
            //    hand = redressHandFromBinarySegmentedImage(hand, 255);
            
            namedWindow("TESTED hand", CV_WINDOW_AUTOSIZE );
            imshow("TESTED hand", hand );
             waitKey(0);  

            float * zonings = zoning(hand);

            
        }
        
        
        
        
        float * zoning(Mat hand)
        {
            float * zones = new float[M*N];
            
            int w = hand.cols;
            int h = hand.rows;
            int canal = hand.dims+1;

            int stepX = (float)w/(float)M;
            int stepY = (float)h/(float)N;
            
            int currentZoning = 0;
            
            if(DEBUG)cout << "stepX = " << stepX << "   stepY = " << stepY << endl;
            
            for(int i=0; i<M; i++)
            {
                for(int j=0; j<N; j++)
                {
                    if(DEBUG)cout << "i = " << i << "   j = " << j << endl;
                    int accumHandPx = 0;
                    int accumTot = 0;
                    for(int x=i*stepX; x<i*stepX+stepX; x++)
                    {
                        for(int y=j*stepY; y<j*stepY+stepY; y++)
                        {
                            if(DEBUG)cout << "indiceMaxData = " << y*w+x << endl;
                            if(hand.data[y*w+x] == 255) accumHandPx++;
                            accumTot++;
                        }
                        
                    }
                    
                    int sx = stepX;
                    int sy = stepY;
                    int x =i*stepX;
                    int y = j*stepY;
                    //extraction of the hand
                    Mat hand2 = Mat_<unsigned char>(sy, sx);
                    hand2.dims=0;//tres important, trop de pb à cause de ces conneries de channel
 //                   cout << "avant extractSubimageFromBounds" << endl;
                    extractSubimageFromBounds(hand, hand2, x, x+stepX, y, y+stepY);
                    
                    if(DEBUG)
                    {
                        namedWindow("SUB hand", CV_WINDOW_AUTOSIZE );
                        imshow("SUB hand", hand2 );
                         waitKey(0);  
                    }
                    
                    
                    if(DEBUG)cout << "hand.data.size = " << hand.cols*hand.rows << endl;
                    if(DEBUG)cout << "accumHandPx = " << accumHandPx << endl;
                    if(DEBUG)cout << "indice zone = " << currentZoning << endl;
                    zones[currentZoning] = (float)accumHandPx/(float)accumTot;
                    currentZoning++;
                }
            }
            if(DEBUG)
            for(int zone=0; zone<M*N; zone++)
            {
                cout << "zone = " << zone << "value = " << zones[zone] << endl;
            }
            
//            cout << "fin zoning " << endl;
            return zones;
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
            else readPath2(imagesTest, classCorrespondancesTest, /*"F:/iut/utbm/S5/projetIN52-54/ClassImagesEtendue2/"*/"D:/partage/projetIN52-54/dropbox/Dropbox/Projet IN5x/Images/ClassImagesEtendue2/", "bmp");
            
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
            
            string testedImages, baseImages, redress;

            if(testImagesCappelle)
                testedImages = "images de base testée";
            else testedImages = "images étendues à la con testée";
            if(baseImagesCappelle)
                baseImages = "base élémentaire";
            else baseImages = "base étendue";
            if(redressHand)
                redress = "images redressées";
            else redress = "images non redressées";
            
            cout << baseImages << ", " << testedImages << ", " << redress  << endl;
            result << baseImages << ", " << testedImages << ", " << redress  << endl;
            
            cout << "sur " << numberOfTestedImages <<" images, il en a détecté " << resJustes << " correctement" <<endl;
            cout << "soit un taux de réussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl << endl;
            result << "sur " << numberOfTestedImages <<" images, il en a détecté " << resJustes << " correctement" <<endl;
            result << "soit un taux de réussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl << endl;
            
            return result.str();
        }

    

};

#endif	/* CLASSIFIEURZONING */
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

#include "HandSideDetection.h"
#include "rotateHand.h"
#include "Symmetry.h"

#include "ClassifieurZoning.cpp"

using namespace cv;
using namespace std;

string testDirWithTwoClassifiers(string path, ClassifieursProfils &cl1, ClassifieursProfils &cl2)
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
    }
    else readPath2(imagesTest, classCorrespondancesTest, /*"F:/iut/utbm/S5/projetIN52-54/ClassImagesEtendue2/"*/"D:/partage/projetIN52-54/dropbox/Dropbox/Projet IN5x/Images/ClassImagesEtendue2/", "bmp");

    int numberOfTestedImages = 0;
    int resJustes = 0;

    //toutes les images tests, imagesTest[i=classe de l'image testÃ©e][img = numÃ©ro de l'image de la classe i]
    for(int i=0; i<imagesTest.size(); i++)
    {
        for(int img=0; img<imagesTest[i].size(); img++)
        {
            numberOfTestedImages++;

            int resultClass;
            string imgFile = imagesTest[i][img];
            
            float * probaForEachClassCL1;
            float * probaForEachClassCL2;
            float * combinedProbaForEachClass = new float[NB_CLASSES];
            
            
            
            //resultClass = cl1.getMaxIndexFromTab( cl1.testImage(imgFile), NB_CLASSES );
            //resultClass = cl1.getMaxIndexFromTab( combinedProbaForEachClass, NB_CLASSES );
            
            
            if(useKPPV)
            {
                 cl1.testImageKPPV(imgFile, probaForEachClassCL1);
                 cl2.testImageKPPV(imgFile, probaForEachClassCL2);
                 
                 if(DEBUG)
                     for(int prob=0; prob<NB_CLASSES; prob++)
                     {
                         cout << "probaForEachClassCL1[prob] = " << probaForEachClassCL1[prob] << endl;
                         cout << "probaForEachClassCL2[prob] = " << probaForEachClassCL2[prob] << endl;
                     }
            }
            else
            {
                probaForEachClassCL1 = cl1.testImage(imgFile);
                probaForEachClassCL2 = cl2.testImage(imgFile);
            }
            
            for(int a=0; a<NB_CLASSES; a++)
                    combinedProbaForEachClass[a] = probaForEachClassCL1[a] * probaForEachClassCL2[a];

            resultClass = getMaxIndexFromTab( combinedProbaForEachClass, NB_CLASSES );
            


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
                if(DEBUG) result << "l'image : " << imgFile << "  est dÃ©tectÃ©e comme appartenant Ã  la classe : " << resultClass << endl;
                if(DEBUG) cout << "l'image : " << imgFile << "  est dÃ©tectÃ©e comme appartenant Ã  la classe : " << resultClass << endl; 
            }
            //base Ã©tendue
            else
            {
                if(testImagesCappelle)
                {
                    if(cl1.classCorrespondances[resultClass]==i)
                        resJustes++;
                }
                else
                {
                    if(cl1.classCorrespondances[resultClass]==cl1.classCorrespondances[i])
                        resJustes++;
                }
                if(DEBUG)result << "resultClass = " << resultClass << "   i = " << i << endl;
                if(DEBUG)result << "l'image : " << imgFile << "  est dÃ©tectÃ©e comme appartenant Ã  la classe : " << cl1.classCorrespondances[resultClass] << endl; 
                if(DEBUG)cout << "resultClass = " << resultClass << "   i = " << i << endl;
                if(DEBUG)cout << "l'image : " << imgFile << "  est dÃ©tectÃ©e comme appartenant Ã  la classe : " << cl1.classCorrespondances[resultClass] << endl; 
            }


        }
    }

    string testedImages, baseImages, redress, kppv;
    if(useKPPV)
         kppv = " avec KPPV :";
    else kppv = " sans KPPV :";
    if(testImagesCappelle)
        testedImages = "images de base testÃ©e";
    else testedImages = "images Ã©tendues Ã  la con testÃ©e";
    if(baseImagesCappelle)
        baseImages = "base Ã©lÃ©mentaire";
    else baseImages = "base Ã©tendue";
    if(redressHand)
        redress = "images redressÃ©es";
    else redress = "images non redressÃ©es";

    cout << baseImages << ", " << testedImages << ", " << redress << kppv << endl;
    result << baseImages << ", " << testedImages << ", " << redress << kppv << endl;

    cout << "sur " << numberOfTestedImages <<" images, il en a dÃ©tectÃ© " << resJustes << " correctement" <<endl;
    cout << "soit un taux de rÃ©ussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl;
    result << "sur " << numberOfTestedImages <<" images, il en a dÃ©tectÃ© " << resJustes << " correctement" <<endl;
    result << "soit un taux de rÃ©ussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl << endl;
            
    return result.str();
}


void testAllConfigurationsMonoClassifier(ClassifieursProfils &classifieur)
{
    string results;
    
    /*redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    useKPPV = false;
    
    classifieur.initBase();
    results = classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");**/
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    /*redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");*/
    
   /* useKPPV = true;
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");*/

    
    cout << endl << results << endl;
}











void testAllConfigurationsTwoClassifier(ClassifieursProfils &cl1, ClassifieursProfils &cl2)
{
    string results;
    
    /*redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    useKPPV = false;
    
    cl1.initBase(); cl2.initBase();
    results = testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); */
    
    useKPPV = true;
    
    /*redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2);
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2);*/
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    /*redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); 
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    cl1.initBase(); cl2.initBase();
    results += testDirWithTwoClassifiers("blabla", cl1, cl2); **/

    
    cout << endl << results << endl;
}













void testAllConfigurationsMonoClassifier(ClassifieurZoning &classifieur)
{
    string results;
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    useKPPV = false;
    
    /*classifieur.initBase();
    results = classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");**/
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    /*redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");*/
    
   /* useKPPV = true;
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = false;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = false;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = false;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");
    
    redressHand = true;
    testImagesCappelle = true;
    baseImagesCappelle = true;
    classifieur.initBase();
    results += classifieur.testDir("blabla");*/

    
    cout << endl << results << endl;
}

int main( int argc, char** argv )
{

    //test classifieur1
//    ClassifieurDistEuclidienne classifieur;
//    ClassifieurDistHistogramm cl2;
    
//    classifieur.initBase();
    //classifieur.testImage("F:/iut/utbm/S5/projetIN52-54/dropbox/Dropbox/Projet IN5x/Images/groupe1/7.bmp");
//    classifieur.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImages/test.bmp");
//    testAllConfigurationsMonoClassifier(cl2);
    

    //classifieur.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImagesSeg/test1.bmp");
    
    //test classifieur2
//    ClassifieurDistHistogramm cl2;
//    testAllConfigurationsTwoClassifier(classifieur, cl2);
//    cl2.initBase();
    //cl2.testImage("F:/iut/utbm/S5/projetIN52-54/dropbox/Dropbox/Projet IN5x/Images/groupe1/7.bmp");
//    cl2.testDir("blabla");
    //cl2.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImagesSeg/test1.bmp");
    //cl2.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImages/test.bmp");
    //cl2.testImage("F:/iut/utbm/S5/projetIN52-54/ClassImages/1/0.bmp");
    
    //Mat hand = extractHandFromBMPFile("F:/iut/utbm/S5/projetIN52-54/ClassImages/2/0b1.bmp", true);
    //Mat rotatedHand = redressHandFromBinarySegmentedImage(hand, 255);
    
//    testDirWithTwoClassifiers("blabla", classifieur, cl2);    
   
    //binarizeFile("F:/iut/utbm/S5/projetIN52-54/ClassImagesSeg/5/1.bmp", 100);
    
    
//ClassifieurZoning zn;
    ClassifieurDistHistogramm cl2;
testAllConfigurationsMonoClassifier(cl2);



/*Mat hand = extractHandFromBMPFile( pathBase+"0/0.bmp");
zn.train(hand, 0);

hand = extractHandFromBMPFile( pathBase+"1/0.bmp");
zn.train(hand, 1);

hand = extractHandFromBMPFile( pathBase+"2/0.bmp");
zn.train(hand, 2);

hand = extractHandFromBMPFile( pathBase+"3/0.bmp");
zn.train(hand, 3);

hand = extractHandFromBMPFile( pathBase+"4/0.bmp");
zn.train(hand, 4);

hand = extractHandFromBMPFile( pathBase+"5/0.bmp");
zn.train(hand, 5);

testImagesCappelle = true;
useKPPV = false;
zn.testDir("aze");*/

//testAllConfigurationsMonoClassifier(zn);
/*zn.initBase();
cout << "apres initbase "<< endl;

float * res = zn.testImage(pathBase+"2/0.bmp");

for(int z=0; z<NB_CLASSES; z++)
    cout << "proba classe " << z << " = " << res[z] << endl;
//zn.testVitFait();**/

    waitKey(0);
    return 0;
}





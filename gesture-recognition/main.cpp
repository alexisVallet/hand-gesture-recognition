#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "paramsClassifieurs.h"
#include "ClassifieurDistEuclidienne.cpp"
#include "ClassifieurDistHistogramm.cpp"
#include "ConvexityClassifier.h"
#include "ClassifieurZoning.cpp"
#include "RadialHistogramClassifier.cpp"

#define TEST_PATH "./testBase/"
#define LEARNING_PATH "./learningBase/"

using namespace cv;
using namespace std;

string testDirWithTwoClassifiers(string path)
{
    ClassifieurDistEuclidienne profils;
    ClassifieurDistHistogramm histoVertHoriz;
    ClassifieurZoning zoning;
    ConvexityClassifier convexity;
    KNearestModel internalModel(3);
    RadialHistogramClassifier radialHistogram(&internalModel, 82);
    
    stringstream result;
    vector< vector < string > > imagesTraining;
    vector< vector<string> > imagesTest;       
    vector< int >classCorrespondancesTest;
    //readPath(imagesTest, path, "bmp");

    readPath(imagesTest, TEST_PATH, "bmp");
    readPath(imagesTraining, LEARNING_PATH, "bmp");
    
    pathBase = LEARNING_PATH;
    profils.initBase();
    histoVertHoriz.initBase();
    zoning.initBase();
    
    vector<Mat> segmentedHands;
    vector<int> classes;
    
    for (int i = 0; i < imagesTraining.size(); i++) {
        for (int j = 0; j < imagesTraining[i].size(); j++) {
            cout<<imagesTraining[i][j]<<" is in "<<i<<endl;
            Mat image = extractHandFromBMPFile(imagesTraining[i][j]);
            segmentedHands.push_back(image);
            classes.push_back(i);
        }
    }
    
    radialHistogram.train(segmentedHands, classes);

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
            
            float * probaForEachClassProfils;
            float * probaForEachClassHisto;
            float * probaForEachClassZoning;
            vector<float> probaForEachClassRadial;
            vector<float> probaForEachClassConvexity;
            float * combinedProbaForEachClass = new float[NB_CLASSES];
            
            
            
            //resultClass = cl1.getMaxIndexFromTab( cl1.testImage(imgFile), NB_CLASSES );
            //resultClass = cl1.getMaxIndexFromTab( combinedProbaForEachClass, NB_CLASSES );
            
            
          
            probaForEachClassProfils = profils.testImage(imgFile);
            probaForEachClassHisto = histoVertHoriz.testImage(imgFile);
            probaForEachClassZoning = zoning.testImage(imgFile);
            Mat segmentedHand = extractHandFromBMPFile(imgFile);
            probaForEachClassRadial = radialHistogram.classProbabilities(segmentedHand);
            probaForEachClassConvexity = convexity.classProbabilities(segmentedHand);
            
            for(int a=0; a<NB_CLASSES; a++) {
                combinedProbaForEachClass[a] = 
                        probaForEachClassProfils[a] +
                        probaForEachClassHisto[a] +
                        probaForEachClassZoning[a] +
                        probaForEachClassRadial[a] +
                        probaForEachClassConvexity[a];
            }

            resultClass = getMaxIndexFromTab( combinedProbaForEachClass, NB_CLASSES);

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


int main(int argc, char** argv) {
    
    //create a gui window:
    namedWindow("Output",1);
    
    //initialize a 120X350 matrix of black pixels:
    Mat output = Mat::zeros( 120, 350, CV_8UC3 );
    
    //write text on the matrix:
    putText(output,
            "Hello World :)",
            cvPoint(15,70),
            FONT_HERSHEY_PLAIN,
            3,
            cvScalar(0,255,0),
            4);
    
    //display the image:
    imshow("Output", output);
    
    //wait for the user to press any key:
    waitKey(0);
    
    return 0;

}
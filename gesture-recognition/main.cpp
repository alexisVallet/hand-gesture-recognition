#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "paramsClassifieurs.h"
#include "ClassifieurDistEuclidienne.cpp"
#include "ClassifieurDistHistogramm.cpp"
#include "ConvexityClassifier.h"
#include "ClassifieurZoning.cpp"
#include "RadialHistogramClassifier.h"

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
    KNearestModel internalModel(7);
    RadialHistogramClassifier radialHistogram(&internalModel, 90);
    
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


                    if(resultClass==i)
                        resJustes++;
                
       //         result << "l'image : " << imgFile << "  est dÃ©tectÃ©e comme appartenant Ã  la classe : " << resultClass << endl;
                cout << "l'image : " << imgFile << "  est detectee comme appartenant a  la classe : " << resultClass << endl;
            
            


        }
    }

    cout << "sur " << numberOfTestedImages <<" images, il en a detecte " << resJustes << " correctement" <<endl;
    cout << "soit un taux de reussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl;
    result << "sur " << numberOfTestedImages <<" images, il en a detecte " << resJustes << " correctement" <<endl;
    result << "soit un taux de reussite de : " << (float)((float)resJustes/(float)numberOfTestedImages)*100 << "%" << endl << endl;
            
    return result.str();
}


int main(int argc, char** argv) {
    testDirWithTwoClassifiers("pouet");
    cout<<"Press any key to quit..."<<endl;
    namedWindow("press any key to quit...");
    waitKey(0);
    return 0;
}
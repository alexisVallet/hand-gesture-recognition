#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include <math.h>

#include "utilsFunctions.h"
#include "paramsClassifieurs.h"
#include "ClassifieursProfils.cpp"


using namespace cv;
using namespace std;




class ClassifieurDistEuclidienne : public ClassifieursProfils
{
    private :
        
       
    
    public :
        
        ClassifieurDistEuclidienne()
        {
            loopFactor = 2;
        }
        
        
       
        

        //attention, fonctionne avec une image binaire, n canaux mais ne travaille que sur un seul, si 3 canaux on les considère identiques
        //défini les profils gauche et droit, basé sur le même systeme que ce qu'on a fait en TP !
        float * horizontalProfiling(Mat img)
        {
            //tableau dans lequel on stocke les profils, dans la première moitier les profils gauches, et dans la seconde les profils droits
            float * profiles = new float[NB_PROFILES*loopFactor];

            int w = img.cols;
            int h = img.rows;
            int canal = img.dims+1;

            bool xLeftFinded = false, xRightFinded = false;
            int xLeft = 0;
            int xRight = 0;

            int step = (float)h/(float)NB_PROFILES;
            
            //1 - détection des min/max en x
            for(int ligne=0, currentProfil=0; currentProfil < NB_PROFILES ; ligne+=step, currentProfil++)
            {
                for(int i=0; i<w; i++)
                {
                    if(!xLeftFinded && img.data[ligne*w*canal+i*canal]==255) 
                    {
                        xLeft = i;
                        xLeftFinded = true;
                    }
                    if(!xRightFinded && img.data[ligne*w*canal+(w-i-1)*canal]==255) 
                    {
                        xRight = w-i;
                        xRightFinded = true;
                    }
                }
                //si ligne vide, on set le profil à w
                if(xLeft==0)
                    profiles[currentProfil] = w;
                else profiles[currentProfil] = xLeft-1;
                if(xRight==0)
                    profiles[NB_PROFILES+currentProfil] = w;
                else profiles[NB_PROFILES+currentProfil] = w-(xRight+1);

                xLeftFinded = false;
                xRightFinded = false;
                xLeft = 0;
                xRight = 0;
            }
                       
            //normalisation
            for(int i=0; i<NB_PROFILES*loopFactor; i++)
            {
                profiles[i]/=w;
            }

            return profiles;
        }
        
        
        
        
        float * verticalProfiling(Mat img)
        {
            //tableau dans lequel on stocke les profils, dans la première moitier les profils up, et dans la seconde les profils down
            float * profiles = new float[NB_PROFILES*loopFactor];

            int w = img.cols;
            int h = img.rows;
            int canal = img.dims+1;

            bool yUpFinded = false, yDownFinded = false;
            int yUp = 0;
            int yDown = 0;

            int step = (float)w/(float)NB_PROFILES;
            
            //détection des min/max en y
            //ici on peut peut être améliorer en initialisant col à step/2
            for(int col=0, currentProfil=0; currentProfil < NB_PROFILES ; col+=step, currentProfil++)
            {
                for(int i=0; i<h; i++)
                {
                    if(!yUpFinded && img.data[i*w*canal+col*canal]==255) 
                    {
                        yUp = i;
                        yUpFinded = true;
                    }                    
                    if(!yDownFinded && img.data[(h-i-1)*w*canal+col*canal]==255) 
                    {
                        yDown = h-i;
                        yDownFinded = true;
                    }
                }
                
                //au cas où la colone testée ne contient rien, on set le profil à h
                if(yUp==0)
                    profiles[currentProfil] = h;
                else profiles[currentProfil] = yUp-1;
                
                if(yDown==0)
                    profiles[NB_PROFILES+currentProfil] = h;
                else profiles[NB_PROFILES+currentProfil] = h-(yDown+1);
                                
                yUpFinded = false;
                yDownFinded = false;
                yUp = 0;
                yDown = 0;
            }
            
            /*namedWindow("hand", CV_WINDOW_AUTOSIZE );
            imshow("hand", img );           
            cout << endl <<"step = "<< step << endl;**/
            //normalisation
            for(int i=0; i<NB_PROFILES*loopFactor; i++)
            {
                //cout << "profilVertical"<< i << " = " << profiles[i] << endl;
                profiles[i]/=h;
            }
            return profiles;
        }
        
        
        
        
};

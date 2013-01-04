
#include "ClassifieursProfils.cpp"

using namespace cv;
using namespace std;





class ClassifieurDistHistogramm : public ClassifieursProfils
{
    private :
        
        
        
    
    public :
        
        ClassifieurDistHistogramm() 
        {
            loopFactor = 1;
        }
        
        
        
        

        //attention, fonctionne avec une image binaire, n canaux mais ne travaille que sur un seul, si 3 canaux on les considère identiques
        //défini les profils gauche et droit, basé sur le même systeme que ce qu'on a fait en TP !
        /**
         * compute caracteristic vector
         * 
         * @param img binarised segmented hand
         * @return normalized H caracteristic vector, size = NB_PROFILES
         */
        float * horizontalProfiling(Mat img)
        {
            //tableau dans lequel on stocke les profils, dans la première moitier les profils gauches, et dans la seconde les profils droits
            float * profiles = new float[NB_PROFILES*loopFactor];

            int w = img.cols;
            int h = img.rows;
            int canal = img.dims+1;

            int count = 0;
            int step = (float)h/(float)NB_PROFILES;
            
            //1 - détection des min/max en x
            for(int ligne=0, currentProfil=0; currentProfil < NB_PROFILES ; ligne+=step, currentProfil++)
            {
                for(int i=0; i<w; i++)
                {
                    if(img.data[ligne*w*canal+i*canal]==255) 
                    {
                        count++;
                    }
                }
                profiles[currentProfil] = count;    
                count = 0;
            }
                       
            //normalisation
            for(int i=0; i<NB_PROFILES*loopFactor; i++)
            {
                profiles[i]/=w;
            }
            
            return profiles;
        }
        
        
        
        /**
         * compute caracteristique vector
         * 
         * @param img binarised segmented hand
         * @return normalized H caracteristic vector, size = NB_PROFILES
         */
        float * verticalProfiling(Mat img)
        {
            //tableau dans lequel on stocke les profils, dans la première moitier les profils up, et dans la seconde les profils down
            float * profiles = new float[NB_PROFILES*loopFactor];

            int w = img.cols;
            int h = img.rows;
            int canal = img.dims+1;

            int count = 0;
            int step = (float)w/(float)NB_PROFILES;
            
            //détection des min/max en y
            //ici on peut peut être améliorer en initialisant col à step/2
            for(int col=0, currentProfil=0; currentProfil < NB_PROFILES ; col+=step, currentProfil++)
            {
                for(int i=0; i<h; i++)
                {
                    if(img.data[i*w*canal+col*canal]==255) 
                    {
                        count++;
                    }                    
                }
                
                profiles[currentProfil] = count;
                count = 0;
            }
            
            //normalisation
            for(int i=0; i<NB_PROFILES*loopFactor; i++)
            {
                profiles[i]/=h;
            }
            return profiles;
        }
        
        
        
        
    
};

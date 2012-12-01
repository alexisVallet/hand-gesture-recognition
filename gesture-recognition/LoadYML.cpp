/* 
 * File:   LoadYML.h
 * Author: Pierre
 *
 * Created on 26 novembre 2012, 19:07
 */

#include "loadYML.h"

using namespace cv;

IplImage * loadYml(const char * filename)
{
    CvMat* my_matrix;
    my_matrix = (CvMat*)cvLoad(filename);

    float min = my_matrix->data.fl[0], max = my_matrix->data.fl[0];
    float moy = 0;

    for(int i=0; i<my_matrix->rows; i++)
        for(int j=0; j<my_matrix->cols; j++)
        {
            if(my_matrix->data.fl[i*200+j]<min) min = my_matrix->data.fl[i*200+j];
            else if(my_matrix->data.fl[i*200+j]>max) max = my_matrix->data.fl[i*200+j];

            moy+=my_matrix->data.fl[i*200+j];
        }

    moy/= my_matrix->rows * my_matrix->cols;

    IplImage* img = cvCreateImage(cvSize(my_matrix->cols, my_matrix->rows),IPL_DEPTH_8U,1);


    float mintmp = 0, maxtmp = 0;
    for(int i=0; i<my_matrix->rows; i++)
        for(int j=0; j<my_matrix->cols; j++)
        {
            //float val = (unsigned char) 255* ((my_matrix->data.fl[i*200+j]-min)/(max-min));
            //float val = (unsigned char) ((my_matrix->data.fl[i*200+j]/moy)*255);
            float val = my_matrix->data.fl[i*200+j]*16;
            val*=val;


            if(mintmp > val) mintmp = val;
            if(maxtmp < val) maxtmp = val;

            if(val<0) val = 0;
            if(val>255) val=255;

            img->imageData[i*200+j] = val;
        }
    return img;
}


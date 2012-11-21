/*
 #  
 #  File        : pviewer.h
 #  
 #  Description : An image visualization class for Pandore
 #
 #  Copyright   : David Tschumperle
 #                ( http://www.greyc.ensicaen.fr/~dtschump/ )
 #   
 #  This software is governed by the CeCILL  license under French law and
 #  abiding by the rules of distribution of free software.  You can  use, 
 #  modify and/ or redistribute the software under the terms of the CeCILL
 #  license as circulated by CEA, CNRS and INRIA at the following URL
 #  "http://www.cecill.info". 
 #  
 #  As a counterpart to the access to the source code and  rights to copy,
 #  modify and redistribute granted by the license, users are provided only
 #  with a limited warranty  and the software's author,  the holder of the
 #  economic rights,  and the successive licensors  have only  limited
 #  liability. 
 #  
 #  In this respect, the user's attention is drawn to the risks associated
 #  with loading,  using,  modifying and/or developing or reproducing the
 #  software by the user in light of its specific status of free software,
 #  that may mean  that it is complicated to manipulate,  and  that  also
 #  therefore means  that it is reserved for developers  and  experienced
 #  professionals having in-depth computer knowledge. Users are therefore
 #  encouraged to load and test the software's suitability as regards their
 #  requirements in conditions enabling the security of their systems and/or 
 #  data to be ensured and,  more generally, to use and operate it in the 
 #  same conditions as regards security. 
 #  
 #  The fact that you are presently reading this means that you have had
 #  knowledge of the CeCILL license and that you accept its terms.
 #  
 */

#ifndef __PVIEWERH__
#define __PVIEWERH__
#include "CImg1-16.h"
using namespace cimg_library1_16;
#include "pandore.h"
using namespace pandore;

/*
 #
 # Definition of the Viewer class
 #
 */
struct Viewer : public cimg_library1_16::CImgDisplay {
  
  Viewer(const unsigned int dimw, const unsigned int dimh, const char *title=0,
	 const unsigned int normalization_type=1, const unsigned int events_type=3,
	 const bool fullscreen_flag=false, const bool closed_flag=false):
    CImgDisplay(dimw, dimh, title, normalization_type, events_type, fullscreen_flag, closed_flag) {};
  
  template<typename T> 
  Viewer(const Imx2d<T>& img, const char *title=0,
	 const unsigned int normalization_type=1, const unsigned int events_type=3,
	 const bool fullscreen_flag=false, const bool closed_flag=false):
    CImgDisplay(CImg<T>(&(img[0][0][0]), img.Width(), img.Height(), 1, img.Bands(), true),title,normalization_type,
		events_type,fullscreen_flag,closed_flag) {}

  template<typename T> 
  Viewer(const Imx3d<T>& img, const char *title=0,
	 const unsigned int normalization_type=1, const unsigned int events_type=3,
	 const bool fullscreen_flag=false, const bool closed_flag=false):
    CImgDisplay(CImg<T>(&(img[0][0][0][0]), img.Width(), img.Height(), 1, img.Bands(), true),title,normalization_type,
		events_type,fullscreen_flag,closed_flag) {}
  
  Viewer(const Viewer& win,char *title="[Copy]"):CImgDisplay(win) {}

  template<typename T> Viewer& display(const Imx2d<T>& img) {
    CImgDisplay::display(CImg<T>(&(img[0][0][0]), img.Width(), img.Height(), 1, img.Bands(), true));
    return *this;
  }

  template<typename T> Viewer& display(const Imx3d<T>& img) {
    CImgDisplay::display(CImg<T>(&(img[0][0][0][0]), img.Width(), img.Height(), img.Depth(), img.Bands(), true));
    return *this;
  }
  
};

#endif

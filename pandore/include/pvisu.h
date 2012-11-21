/* -*- mode: c++; c-basic-offset: 3 -*-
 *
 * PANDORE (PANTHEON Project)
 *
 * GREYC IMAGE
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex France
 *
 * This file is free software. You can use it, distribute it
 * and/or modify it. However, the entire risk to the quality
 * and performance of this program is with you.
 *
 *
 * For more information, refer to:
 * http://www.greyc.ensicaen.fr/EquipeImage/Pandore/
 */

/**
 * @author Régis Clouard - 2009-04-06
 */

/**
 * @file pvisu.h
 * @brief Allows the usage of the Pandore viewer inside an application.
 * usage : Img2duc x; Visu(x);
 *         Graph2d g; Visu(g);
 *         Imc3dsf i; Visu(i);
 */

#undef _DRAWINGMODE
#ifdef MAIN
#undef MAIN
#include "src/viewers/Qt/pvisu.cpp"
#define MAIN
#else
#undef MAIN
#include "src/viewers/Qt/pvisu.cpp"
#endif

template <typename T>
/**
 * Displays the specified Pandore object in a windows.
 * @param object a regular Pandore object. 
 */
void Visu( T &object ) {
  QWidget *visual=NULL;
  static int _index=1;
  // Use the name imagex where x is the instance index.
  nomentree=(char*)malloc(30*sizeof(char));
  sprintf(nomentree,"Pandore image #%02d",_index++);
  _DRAWINGMODE=false;
  
  Long pid;
  if ((pid=fork()) >0 ) return;
  else if (pid == -1) Exit(FAILURE);
  int argcQt=0;
  QApplication app( argcQt, 0 );
  
  visual=Visu(object,0);
  if (visual) {
    app.exec();
    delete visual;
  }
  Exit(pid);
}

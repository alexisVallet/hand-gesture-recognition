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
 * @author Régis Clouard - 1999-10-08
 * @author Francois Angot - 1999-10-08
 * @author Alexandre Duret-Lutz. 1999-10-08
 * @author Régis Clouard - 2001-04-10 (version 3.00)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file main.h
 * @brief The definition of all main utilities.
 */

#ifndef __PMAINH__
#define __PMAINH__

namespace pandore {
   /**
    * Reads and parses the input argument list.
    * Arguments list follows the syntax ::<br>
    * <tt>operator [-hp]</tt><br>
    * in case of documentation usage, where
    * <ul>
    * <li>-h: display the usage of the operator.
    * <li>-p: display the prototype of the operator.
    * </ul>
    * <br>or <tt>operator parameter* [-m mask] images_in* images_out*</tt><br>
    * for a normal execution with input and output files and parameters.<br>
    * The "masking" parameter <tt>-m mask</tt> specifies
    * if the optional mask is used to realize:
    * <ul>
    * <li>masking = 0: neither masking nor unmasking.
    * <li>masking = 1: masking and unmaking
    * <li>masking = 2: only the masking operation
    * <li>masking = 3: only unmasking operation
    * </ul>
    * @param argc	the number of input arguments.
    * @param argv	the list of input arguments.
    * @param parc	the number of parameters.
    * @param finc	the number of input images.
    * @param foutc	the number of output images.
    * @param mask	the mask (a region map) or NULL.
    * @param objin	the pointer to the input Pandore object.
    * @param objs	the pointer to the input masked Pandore object.
    * @param objout	the pointer to the output Pandore object.
    * @param objd	the pointer to the output masked Pandore object.
    * @param parv	the list of parameters.
    * @param usage	the text describing the usage.
    * @param masking	the masking level in [0..3]
    */
   void ReadArgs( int argc, char* argv[], int parc, int finc, int foutc,
		  Pobject** mask, Pobject* objin[], Pobject* objs[],
		  Pobject* objout[], Pobject* objd[],
		  char* parv[], const char* usage, char masking=1 );
   /**
    * Writes the output arguments list.<br>
    * The "masking" parameter <tt>-m mask</tt> specifies
    * if the optional mask is used to realize:
    * <ul>
    * <li>masking = 0: neither masking nor unmasking.
    * <li>masking = 1: masking and unmaking
    * <li>masking = 2: only the masking operation
    * <li>masking = 3: only unmasking operation
    * </ul>
    * @param argc	the number of input arguments.
    * @param argv	the list of input arguments.
    * @param parc	the number of parameters.
    * @param finc	the number of input images.
    * @param foutc	the number of output images.
    * @param mask	the mask (a region map) or NULL.
    * @param objin	the pointer to the input Pandore object.
    * @param objs	the pointer to the input masked Pandore object.
    * @param objout	the pointer to the output Pandore object.
    * @param objd	the pointer to the output masked Pandore object.
    * @param masking	the masking level in [0..3]
    */
   void WriteArgs( int argc, char* argv[], int parc, int finc, int foutc,
		   Pobject** mask, Pobject* objin[], Pobject* objs[],
		   Pobject* objout[], Pobject* objd[], char masking=1 );
   
   /**
    * Prints the error message for bad argument list.
    * Displays a normalized error message for
    * bad input images.
    * @param objin	the array of input images.
    * @param finc	the number of input images.
    */
   void PrintErrorFormat( Pobject* objin[], int finc, char *argv[] = NULL );
   
} //End of pandore:: namespace

#endif  // __PMAINH__

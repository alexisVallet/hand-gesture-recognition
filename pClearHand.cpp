/* -*- c-basic-offset: 3 -*-
 *
 * PANTHEON Project
 *
 * GREYC IMAGE
 * 6 Boulevard MarÃ©chal Juin
 * F-14050 Caen Cedex France
 *
 * This file is free software. You can use it, distribute it
 * and/or modify it. However, the entire risk to the quality
 * and performance of this program is with you.
 *
 * For more information, refer to:
 * http://www.greyc.ensicaen.fr/EquipeImage/Pandore/
 */
#ifndef PCLEARHAND_CPP
#define	PCLEARHAND_CPP
#include "pClearHand.hpp"

#define _WHITE 1
#define _BLACK 0

using namespace pandore;


inline void testBLACK(const Img2duc& ims, Point2d& cursor, int & counter)
{
    if(ims[cursor] == BLACK)
        counter++;
}


/*
 * L'opérateur suivant nettoie une image après binarisation afin de supprimer les pixels residuels
 * issus d'une segmentation non parfaite.
 */

Errc pClearHand( const Img2duc &ims, Img2duc &imd, int loops, int precision) {

	Point2d p;

	// Met imd en noir
	for(p.y=0; p.y<ims.Height(); p.y++)
		for (p.x=0; p.x<ims.Width(); p.x++)
			imd [p] = 0;

    /*
     * Pour chaque pixel, on le change de couleur si ses pixels connexes sont pas tous de la même couleur.
     */

	for(int l=0; l<loops; l++)
	{
		for(p.y=1; p.y<ims.Height()-1; p.y++)
		{
			for (p.x=1; p.x<ims.Width()-1; p.x++)
		    {
		        // Suppression des pixels blancs
		        if(ims[p] == WHITE)
		        {
			        Point2d cursor (p);
		            int black_connex = 0;

		            // Pixel bas gauche
		            cursor.x--;
		            cursor.y--;
		            testBLACK(ims,cursor,black_connex);
		            // Pixel bas centre
		            cursor.x++;
		            testBLACK(ims,cursor,black_connex);
		            // Pixel bas droite
		            cursor.x++;
		            testBLACK(ims,cursor,black_connex);
		            // Pixel droite centre
		            cursor.y++;
		            testBLACK(ims,cursor,black_connex);
		            // Pixel haut droite
		            cursor.y++;
		            testBLACK(ims,cursor,black_connex);
		            // Pixel haut centre
		            cursor.x--;
		            testBLACK(ims,cursor,black_connex);
		            // Pixel haut gauche
		            cursor.x--;
		            testBLACK(ims,cursor,black_connex);
		            // Pixel gauche centre
		            cursor.y--;
		            testBLACK(ims,cursor,black_connex);

		            imd[p] = (black_connex >= precision) ? BLACK: WHITE;
				}
				else
					imd[p] = BLACK;
			}
		}
	}

   return SUCCESS;
}

#endif
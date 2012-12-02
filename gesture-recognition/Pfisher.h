/* 
 * File:   Pfisher.h
 * Author: Admin
 *
 * Created on 1 décembre 2012, 11:33
 */

#ifndef PFISHER_H
#define	PFISHER_H

#include <pandore.h>
using namespace pandore;

void PFisherbis( int histo[], int nbclass, int seuil[] );
Errc PFisher_( const Img2duc &ims, Img2duc &imd, Uchar minval, long nbclass );

#endif	/* PFISHER_H */


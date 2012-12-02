/* -*- c-basic-offset: 3 -*-
 *
 * PANTHEON Project
 *
 * GREYC IMAGE
 * 6 Boulevard Mar�chal Juin
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
 * @author R�gis Clouard - 1997-03-03
 * @author R�gis Clouard - 2002-11-27
 * @author R�gis Clouard - 2006-09-07 (fix bug on histogram inialization)
 */

#include "Pfisher.h"
#include <pandore.h>
using namespace pandore;

/**
 * @file pfisher.cpp
 *
 * Classification des pixels par la methode de fisher niveau 2.
 * Reference: Fisher law.
 */

#define MAXCLASS 25

/**
 * Histogramme a decouper en "nbclass" classes 
 * La methode utilisee est celle de Fisher : 
 * La partition trouvee minimise la somme des variances 
 * a l'interieur de chaque classe. 
 * M est le nombre de colonnes de h au maximum egal a 256 
 * nbclass est le nombre de classes.
 * Au retour les bornes des intervalles sont dans seuil 
 * pour la classe i les bornes sont [seuil[i]+1,seuil[i+1]].
 *
 * @auteur : JM Chassery
 */
void PFisherbis( int histo[], int nbclass, int seuil[] ) {

   int i,l;
   Uchar p[MAXUCHAR+1+1][MAXCLASS];
   long hc[MAXUCHAR+1+1]; // Histogramme cumule: Sum{histo[i]}
   float hp[MAXUCHAR+1+1]; // Histogramme cumule pondere: Sum{histo[i]*i}
   float he[MAXUCHAR+1+1]; // Histogramme cumule pondere par le carre: Sum{histo[i]*i*i }
   long nbe, rbe;
   float  w[MAXUCHAR+1+1], wc;
   int i1, k1, i2;
   float sst, ssq, wm;
   int jm=0, ic, l0;
   float criter;
   
   // Calcul des histogrammes cumules et ponderes.
   hc[1] = histo[1];
   hp[1] = (float)histo[1];
   he[1] = (float)histo[1];
   
   for (i=2; i<= (MAXUCHAR+1); i++) {
      hc[i] = hc[i-1] + histo[i];
      hp[i] = hp[i-1] + (float)i * (float)histo[i] ;
      he[i] = he[i-1] + (float)i * (float)i * (float)histo[i] ;
   }

   // Calcul de w pour une classe.
   // w[i] = Sum(i,MAX){k*K*histo[k]} - ((Sum(i,MAX){(k*histo[k])^2}/ Sum(i,MAX){histo[k]})
   for (i=1; i<= (MAXUCHAR+1); i++) {
      nbe = hc[(MAXUCHAR+1)];
      sst = hp[(MAXUCHAR+1)]; 
      ssq = he[(MAXUCHAR+1)];
      rbe=0;
      if (i > 1) {
	 rbe = nbe - hc[i-1];
	 sst = sst - hp[i-1];
	 ssq = ssq - he[i-1];
      }
      if (rbe != 0) 
	 criter=ssq-sst*(sst/rbe) ;
      else
	 criter=0.;
      w[i]=criter;
   } 

   // Calcul de w pour 2 a k-1 classes
   // et memorisation des indices dans p[][] des intervalles.
   k1 = nbclass-1;
   for (l=2; l<=k1; l++){ 
      i1 = nbclass-l+1;
      i2 = (MAXUCHAR+1)-l+1;
      for (i=i1; i<=i2; i++) {
	 wm=MAXFLOAT;
	 for (int j=i; j<= i2; j++) {
	    rbe = hc[j] - hc[i-1] ;
	    if (rbe != 0.)
	       criter=(he[j] - he[i-1])-((hp[j] - hp[i-1])*(hp[j] - hp[i-1]))/rbe ;
	    else
	       criter=0. ;

	    wc=w[j+1]+criter ;
	    if (wc < wm) {
	       wm=wc;
	       jm=j;
	    }
	 } 
	 w[i]=wm;
	 p[i][l]=jm ;
      }
   }
   
   // Calcul de w pour partitionnement de [1,m] en nbclass classes 
   wm=MAXFLOAT;
   i2 = (MAXUCHAR+1)-nbclass+1;
   int imin=0;
   for (i=1; i<=i2; i++) {
      nbe = hc[i];
      sst = hp[i];
      ssq = he[i] ;
      if (nbe != 0)
	 criter=ssq-sst*sst/nbe ;
      else 
	 criter = 0. ;
      
      wc=w[i+1]+criter ;
      if (wc < wm) {
	 wm=wc;
	 imin=i ;
      }
   }
   
   // Calcul des seuils avec les bornes de la partition optimale .
   seuil[0]=-1;
   seuil[1]=imin;
   seuil[nbclass]=MAXUCHAR ;
   ic=imin;
   for (l=2; l<=nbclass-1; l++) {
      l0=nbclass-l+1;
      i=p[ic+1][l0];
      seuil[l]=i;
      ic=i; 
   }
}

/**
 * Partitionnement de l'image "ims" en "nbclass" classes 
 * par la technique de Fisher op�rant sur histogramme. 
 * Seules valeurs entre "minval" et MAXUCHAR sont prises
 * en compte pour le calcul.
 */
Errc PFisher_( const Img2duc &ims, Img2duc &imd, Uchar minval, long nbclass ) {
   int y,x;
   int i;
   int histo[MAXUCHAR+1+1];
   int seuil[MAXCLASS];

   //  Test de validite du nombre de classes.
   if (nbclass<2)
      nbclass=2;
   if (nbclass>=MAXCLASS)
      nbclass=MAXCLASS-1;

   // Initialisation de l'histogramme.
   for (i=1; i<=MAXUCHAR+1 ; histo[i++]=0) ;
   
   // Calcul histogramme entre minval et MAXUCHAR
   // Attention decalage de 1 pour eviter que l'histogramme pondere = 0 pour le pixel 0.
   for (y=0; y<ims.Height(); y++) { 
      for (x=1; x<ims.Width(); x++) {
	 Uchar pix=ims[y][x];
	 if (pix >= minval) {
	    histo[pix+1]++;
	 }
      }
   }
   
   PFisherbis(histo,nbclass,seuil) ;

   // Calcul de l'image sortie.
   for (y=0; y<ims.Height(); y++){
      for (x=0; x<ims.Width(); x++) {
	 Uchar pix=ims[y][x];
	 if (pix < minval) {
	    imd[y][x]=0;
	 }else{
	    int k=0;
	    while (pix > seuil[k])
	       k=k+1;
 	    imd[y][x]=(Uchar)seuil[k];
	 }
      }
   }
   
   return SUCCESS; 
}

/*
 * Modify only the following constants, and the function call.
 */
/*
#define	USAGE	"usage: %s minval nbclass [-m mask] [im_in|-] [im_out|-]"
#define	PARC	2
#define	FINC	1
#define	FOUTC	1
#define	MASK	1

int main( int argc, char *argv[] ) {
   Errc result;	             // The result code of the execution.
   Pobject* mask;	     // The region mask.
   Pobject* objin[FINC+1];   // The input objects;
   Pobject* objs[FINC+1];    // The source objects masked by the mask.
   Pobject* objout[FOUTC+1]; // The output object.
   Pobject* objd[FOUTC+1];   // The result object of the execution.
   char* parv[PARC+1];	     // The input parameters.

   ReadArgs(argc,argv,PARC,FINC,FOUTC,&mask,objin,objs,objout,objd,parv,USAGE,MASK);

   switch(objs[0]->Type()){
   case Po_Img2duc :{
      Img2duc* const ims=(Img2duc*)objs[0];
      objd[0]=new Img2duc(ims->Size());
      Img2duc* const imd=(Img2duc*)objd[0];

      result=PFisher(*ims,*imd,(Uchar)atoi(parv[0]),atol(parv[1]));
   }break;

   default :
      PrintErrorFormat(objin,FINC);
      result=FAILURE;
   }
   
   if (result)
      WriteArgs(argc,argv,PARC,FINC,FOUTC,&mask,objin,objs,objout,objd,MASK);
   
   Exit(result);
   return 0;
}
*/
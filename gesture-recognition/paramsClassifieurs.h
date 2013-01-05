/* 
 * File:   paramsClassifieurs.h
 * Author: VIRTUAL_BUG
 *
 * Created on 27 novembre 2012, 16:07
 */

#ifndef PARAMSCLASSIFIEURS_H
#define	PARAMSCLASSIFIEURS_H
#include <string>
using namespace std;


//chemin vers le dossier contenant les images de la base^(dossier Images/ClassImages/ sur le dropbox
static string pathBase = "D:/partage/projetIN52-54/ClassImages/";
//static string pathBase = "D:/partage/projetIN52-54/ClassImages2/";

//les préfixes des fichiers profils correspondant aux classifieurs histo ou profils
static string prefixProfilesClassifier = "PROFILES";
static string prefixHistoClassifier = "HISTO";

//le nom des classes des classifieurs histo et profils, utilisé pour le chargement/enregistrement des profils sur le disque
static string classNameProfilesClassifier = "ClassifieurDistEuclidienne";
static string classNameHistoClassifier = "ClassifieurDistHistogramm";


//const static int NB_CLASSES = 12;
const static int NB_PROFILES = 14;
const static int K = 3;

static bool DEBUG = false;







//booléen indiquant si les mains doivent être redressées ou non avant traitement
static bool redressHand = false;

//si true, on teste les images de base de cappelle, sinon on teste les images de la base étendue
static bool testImagesCappelle = true;
//si true, la base est la base élémentaire, sinon la base est étendue
static bool baseImagesCappelle = true;

static bool useKPPV = true;

static int NB_CLASSES = (baseImagesCappelle==true ? 6:12);

static int M = 3;
static int N = 3;


#endif	/* PARAMSCLASSIFIEURS_H */


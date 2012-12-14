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
static string pathBase = "./runFolder/ClassImages/";
static string pathSegmentedBase = "./runFolder/ClassImagesSeg/";

//les préfixes des fichiers profils correspondant aux classifieurs histo ou profils
static string prefixProfilesClassifier = "PROFILES";
static string prefixHistoClassifier = "HISTO";

//le nom des classes des classifieurs histo et profils, utilisé pour le chargement/enregistrement des profils sur le disque
static string classNameProfilesClassifier = "ClassifieurDistEuclidienne";
static string classNameHistoClassifier = "ClassifieurDistHistogramm";


const static int NB_CLASSES = 6;
const static int NB_PROFILES = 5;


#endif	/* PARAMSCLASSIFIEURS_H */


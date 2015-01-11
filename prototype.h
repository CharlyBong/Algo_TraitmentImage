/**
 * \file prototype.h
 * \brief Prototype des fonctions
 *
 * Contient les prototypes des fonctions du projet, les includes
    les définitions des structures et variables.
 *
 * \author Charles Bong.
 * \date 15 octobre 2013
 */

#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "BmpLib.h"
#include "OutilsLib.h"
/*!
  \def EPSILON
  Marge de l'erreur dans la création des arbres quaternaire (entre 0 et 255)
*/
#define EPSILON 5

/*!13
  \def DEBUG
  Commande de débuggage du programme (0 -> pas d'affichage)
*/
#define DEBUG 5
// 0 pour pas de debug

#endif // PROTOTYPE_H_INCLUDED




/*!
  \struct abquat
  Structure d'un nœud de l'arbre quaternaire.<br/>
  valmediane,valmediane1,valmediane2 -> Contient les valeurs médiane du carré.<br/>
  x0,x1,y0,y1 -> délimitation du carrée<br/>
  fils1, 2 , 3 et 4 -> lien vers les fils du nœud<br/>
  epsi -> &epsilon; de la structure<br/>
*/
typedef struct abquat{
    short int valmediane;
    short int valmediane1;
    short int valmediane2;
    int x0;
    int y0;
    int x1;
    int y1;
    struct abquat* fils1;
    struct abquat* fils2;
    struct abquat* fils3;
    struct abquat* fils4;
    int epsi;
}abquat;



//main.c
void choixMenu(char* nom_fichier);

//partie1.c
void cree3matrices(DonneesImageRGB *img,short int **matriceR,short int **matriceG,short int **matriceB);
DonneesImageRGB *creeImage(short int **matriceR,short int **matriceG,short int **matriceB, int haut, int larg);
void negatifImageNG(short int **matrice, int haut, int larg);
void negatifImage(short int **matriceR,short int **matriceG,short int **matriceB, int haut, int larg);
void couleur2NG(short int **matriceR,short int **matriceG,short int **matriceB, int haut, int larg);
DonneesImageRGB *sauveImageNG(short int **matrice, int haut, int larg);
void seuillageNG(short int **matrice, int haut, int larg, int seuil);
int changeimage(DonneesImageRGB *img,char * nouvelleimage);
void sflush();
short int ** allocationMatrice(int haut, int larg);
void triallocationMatrice(short int **matriceR,short int **matriceG,short int **matriceB, int haut, int larg);
void liberationtrimatrice(short int **matriceR,short int **matriceG,short int **matriceB, int haut);
void liberationmatrice(short int **matrice, int haut);

//median.c

short int** medianGrisNxN(short int **matrice, int haut, int larg);
short int medianGriscase(short int **matrice,int haut, int larg);
short int tritableau(short int * table,int taille);
int nimtableau(short int * table,int taille);
void medianCouleurNxN2(short int **matriceR,short int **matriceG,short int **matriceB,short int **matriceR2,short int **matriceG2,short int **matriceB2, int haut, int larg);
void medianCouleurcase2(short int **matriceR,short int **matriceG,short int **matriceB,short int **matriceR2,short int **matriceG2,short int **matriceB2,int x, int y);

//quaternaire.c

short int calculCarre(short int** matrice,int x0, int y0, int x1, int y1);
abquat* creeArbreNB(short int** matrice, int dim);
abquat* creeNoeudArbreNB(short int** matrice, int x0, int y0, int x1, int y1);
abquat* creeationArbreNB(short int** matrice, int x0, int y0, int x1, int y1);
short int** creeMatriceNB(abquat* racine);
void creationMatriceNB(abquat* racine,short int** matrice);
void creationMatriceCase(abquat* racine,short int** matrice);
short int valeurMedianeNG(short int** matrice,int x0, int y0, int x1, int y1);
void couleurMedianeRVB(short int **matriceR,short int **matriceG,short int **matriceB,int x0, int y0, int x1, int y1,short int * result);
short int carreHomogeneNG(short int** matrice,int x0, int y0, int x1, int y1,abquat* racine);
short int carreHomogeneRVB(short int **matriceR,short int **matriceG,short int **matriceB,int x0, int y0, int x1, int y1,abquat* racine);
abquat* creeArbreNG(short int** matrice, int dim);
abquat* creeNoeudArbreNG(short int** matrice, int x0, int y0, int x1, int y1);
abquat* creeationArbreNG(short int** matrice, int x0, int y0, int x1, int y1);
abquat* creeArbreRVB(short int **matriceR,short int **matriceG,short int **matriceB, int dim);
abquat* creeNoeudArbreRVB(short int **matriceR,short int **matriceG,short int **matriceB, int x0, int y0, int x1, int y1);
abquat* creeationArbreRVB(short int **matriceR,short int **matriceG,short int **matriceB, int x0, int y0, int x1, int y1);
short int** creeMatriceNG(abquat* racine,int nn);
void creationMatriceNG(abquat* racine,short int** matrice,int nn);
void creationMatriceCaseNG(abquat* racine,short int** matrice);
void creationMatriceRVB(abquat* racine,short int** matriceR,short int** matriceG,short int** matriceB,int nn);
void creationMatriceCaseRVB(abquat* racine,short int** matriceR,short int** matriceG,short int** matriceB);
int profondeurArbre(abquat* racine);
int convknn(int profondeur, int k);

void zoomCouleur(abquat* arbre,short int** matriceR,short int** matriceG,short int** matriceB,int k);
short int ** zoomNG(abquat* arbre,int k);
void tousLesZoomsCouleur(abquat* arbre,short int** matriceR,short int** matriceG,short int** matriceB,char* nom_fichier);
void tousLesZoomsNG(abquat* arbre,short int** matrice,char* nom_fichier);

//Caldist.c

short int ** calculDistance(short int ** matriceOrgine, int haut, int larg);
short int ** copieMatrice(short int ** matriceOrgine, int haut, int larg);
short int minimun(short int nb1,short int nb2);
short int minimun4(short int nb1,short int nb2,short int nb3,short int nb4);
short int minimun5(short int nb1,short int nb2,short int nb3,short int nb4,short int nb5);
short int ** fctCalculDistance(short int ** matriceOrgine, int haut, int larg);



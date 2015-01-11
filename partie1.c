/**
 * \file partie1.c
 * \brief Fonctions de base pour les matrices
 *
 * Premières fonctions, liées à la création et traitement basique des matrices
 *
 * \author Charles Bong.
 * \date 15 octobre 2013
 */

#include "prototype.h"

/** \brief Créer les 3 matrices d'une image
 *
 *  Permet de remplir 3 matrices (RGB) avec les données d'une image
 *
 * \param img DonneesImageRGB * : Donnée de l'image
 * \param matriceR short int ** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \return void
 *
 * \author Charles Bong.
 */

void cree3matrices(DonneesImageRGB *img,short int **matriceR,short int **matriceG,short int **matriceB){
    int i,j,cas;
    cas=0;
    for(i=0;i < img->hauteurImage;i++){
        for(j=0;j < img->largeurImage;j++){
            matriceB[i][j] = img->donneesRGB[cas];
            matriceG[i][j] = img->donneesRGB[cas+1];
            matriceR[i][j] = img->donneesRGB[cas+2];
            cas += 3;
        }
    }
}

/** \brief Cree une image avec 3 matrices
 *
 *  Créer une image à partir de 3 matrices RGB
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return DonneesImageRGB *
 *
 * \author Charles Bong.
 */

DonneesImageRGB *creeImage(short int **matriceR,short int **matriceG,short int **matriceB, int haut, int larg){
    int i,j,cas;
    cas=0;

    DonneesImageRGB *img = (DonneesImageRGB *) malloc(sizeof(DonneesImageRGB));
    img->hauteurImage = haut;
    img->largeurImage = larg;
    img->donneesRGB = (unsigned char *) malloc(haut*larg*3 *sizeof(unsigned char));

    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            img->donneesRGB[cas] = matriceB[i][j];
            img->donneesRGB[cas+1] = matriceG[i][j];
            img->donneesRGB[cas+2] = matriceR[i][j];
            cas += 3;
        }
    }
    return img;
}

/** \brief Retour le negatif d'une matrice
 *
 * Inverse les couleurs avec 1 matrices (NG)
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return void
 *
 * \author Charles Bong.
 */

void negatifImageNG(short int **matrice, int haut, int larg){
    int i,j;
    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            matrice[i][j] = 255-matrice[i][j];
        }
    }
}

/** \brief Retour le negatif de 3 matrices
 *
 * Inverse les couleurs avec 3 matrices (RVG)
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return void
 *
 * \author Charles Bong.
 */

void negatifImage(short int **matriceR,short int **matriceG,short int **matriceB, int haut, int larg){
    int i,j;

    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            matriceB[i][j] = 255-matriceB[i][j];
            matriceG[i][j] = 255-matriceG[i][j];
            matriceR[i][j] = 255-matriceR[i][j];
        }
    }
}

/** \brief converti 3 matrices couleur en 1 en NG
 *
 * Utilise les 3 matrices RVG pour en faire une en niveau de gris, stocké dans la première matrice passé en paramètre (matriceR)
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return void
 *
 * \author Charles Bong.
 */

void couleur2NG(short int **matriceR,short int **matriceG,short int **matriceB, int haut, int larg){
    int i,j;
    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            matriceR[i][j] = 0.2125*matriceR[i][j] + 0.7154*matriceG[i][j] + 0.0721*matriceB[i][j];
        }
    }
}


/** \brief Sauvegarde une image NG
 *
 * Retourne une image (BMP) à partir d'une matrice (NB)
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return DonneesImageRGB*
 *
 * \author Charles Bong.
 */

DonneesImageRGB *sauveImageNG(short int **matrice, int haut, int larg){
    return creeImage(matrice,matrice,matrice,haut,larg);
}

/** \brief Seuil une matrice
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \param seuil int : Niveau de seuil (entre 0 et 255)
 * \return void
 *
 * \author Charles Bong.
 */

void seuillageNG(short int **matrice, int haut, int larg, int seuil){
    int i,j;
    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            if(matrice[i][j]>seuil) matrice[i][j] = 255;
            else matrice[i][j] = 0;
        }
    }
}

/** \brief Charge une nouvelle image
 *
 * Libère les données d'une image pour en charger une nouvelle (nom passé en paramètre)
 *
 * \param img DonneesImageRGB* : Donnée de l'image
 * \param nouvelleimage char* : Nom de la nouvelle image
 * \return int
 *
 * \author Charles Bong.
 */

int changeimage(DonneesImageRGB *img,char * nouvelleimage){
    if(img != NULL) libereDonneesImageRGB(&img);
    img = lisBMPRGB(nouvelleimage);
    if (img == NULL){
        printf("\tErreur de Chargement : Le fichier demande n'a pas ete trouve: %s\n",nouvelleimage);
        return -1;
    }
    printf("Chargement de %s\n",nouvelleimage);
    return 0;
}

void sflush(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}


/** \brief Retour une matrice de dimension haut * larg
 *
 * S'occupe de l'allocation d'une matrice
 *
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return short int**
 *
 * \author Charles Bong.
 */

short int **allocationMatrice(int haut, int larg){
    int i,j;
    short int **matrice = (short int **) malloc(haut * sizeof(short int*));
    for(i=0;i<haut;i++){
        matrice[i] = (short int *) malloc(larg * sizeof(short int));
    }
    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            matrice[i][j] = 0;
        }
    }
    return matrice;
}


/** \brief Allocation de trois matrices
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return void
 *
 * \author Charles Bong.
 */

void triallocationMatrice(short int** matriceR,short int** matriceG,short int** matriceB, int haut, int larg){
    matriceR = allocationMatrice(haut,larg);
    matriceG = allocationMatrice(haut,larg);
    matriceB = allocationMatrice(haut,larg);
}

/** \brief Libération de trois matrices en même temps
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param haut int : Hauteur
 * \return void
 * \return
 *
 * \author Charles Bong.
 */


void liberationtrimatrice(short int **matriceR,short int **matriceG,short int **matriceB, int haut){
    int i;
    for(i=0;i<haut;i++){
        free(matriceR[i]);
        free(matriceG[i]);
        free(matriceB[i]);
    }
    free(matriceR);
    free(matriceG);
    free(matriceB);
}

/** \brief Libération d'une matrice
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param haut int : Hauteur
 * \return void
 *
 * \author Charles Bong.
 */

void liberationmatrice(short int **matrice, int haut){
    int i;
    for(i=0;i<haut;i++){
        free(matrice[i]);
    }
    free(matrice);
}

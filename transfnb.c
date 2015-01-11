/**
 * \file transfnb.c
 * \brief Fonctions de transformation d'une image en NB (v2)
 *
 * Fonctions de transformation d'une matrice NB
 *
 * \author Charles Bong.
 * \date 07 octobre 2013
 */

#include "prototype.h"

/** \brief Effectue un échantillonnage sur l'image n&b
 *
 * \param matrice short int**
 * \param haut int
 * \param larg int
 * \param niveau int
 * \return short int **
 *
 * \author Charles Bong.
 */

short int ** echantillonnagenb(short int **matrice, int haut, int larg, int niveau){
    int i,j,k,l,result,compt;
    short int **echantil = allocationMatrice(haut,larg);
    for(i=0;i<haut;i=i+niveau){
        for(j=0;j<larg;j=j+niveau){
            result = 0;
            compt = 0;
            for(k=i;k<i+niveau;k++){
                for(l=j;l<j+niveau;l++){
                    if(k<haut && l<larg){
                        result += matrice[k][l];
                        compt++;
                    }
                }
            }
            if (compt != 0) result = result / (compt);
            for(k=i;k<i+niveau;k++){
                for(l=j;l<j+niveau;l++){
                    if(k<haut && l<larg) echantil[k][l] = result;
                }
            }
        }
    }
    return echantil;
}

/** \brief Effectue une quantification sur l'image n&b avec en niveau en paramètre
 *
 * \param matrice short int**
 * \param haut int
 * \param larg int
 * \param niveau int
 * \return short int **
 *
 * \author Charles Bong.
 */

short int ** quantificationnb(short int **matrice, int haut, int larg, int niveau){
    if(niveau > 255) return (short int **) -1;
    if(niveau < 2) return (short int **) -1;
    int palier = (int) 256 / (niveau-1);
    if(DEBUG == 2) printf("palier = %d\n",palier);

    short int **quantification = allocationMatrice(haut,larg);

    int i,j;
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            quantification[i][j] = getColorByNiveau(palier, getNiveauByPalier(palier,matrice[i][j]), matrice[i][j]);
        }
    }
    return(short int **) quantification;
}

/** \brief Calcul et affiche les statistiques d'une image n&b
 *
 * \param matrice short int**
 * \param haut int
 * \param larg int
 * \return void
 *
 * \author Charles Bong.
 */

void statistiquenb(short int **matrice, int haut, int larg){
    int moyenne = 0;
    int variance = 0;
    double ecarttype = 0;
    int i,j;
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            moyenne += matrice[i][j];
        }
    }
    moyenne = moyenne/(haut*larg);
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            variance += ((matrice[i][j]-moyenne)*(matrice[i][j]-moyenne));
        }
    }
    variance = variance/(haut*larg);
    ecarttype = sqrt(variance);

    printf("\n\t moyenne : %d",moyenne);
    printf("\n\t variance : %d",variance);
    printf("\n\t ecarttype : %f\n",ecarttype);
}

/** \brief Génère un Histogramme d'une image n&b
 *
 * \param matrice short int**
 * \param haut int
 * \param larg int
 * \return short int**
 *
 * \author Charles Bong.
 */
short int **histogrammenb(short int **matrice, int haut, int larg){
    int pixelgris[256];
    int niveaugris[256];
    int i,j,tmp,max;
    max = 0;
    for(i=0;i<256;i++){
        pixelgris[i]=0;
        niveaugris[i]=0;
    }
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            tmp = matrice[i][j];
            pixelgris[tmp]++;
        }
    }
    for(i=0;i<256;i++){
        if(pixelgris[i]>max) max = pixelgris[i];
    }
    for(i=0;i<256;i++){
        niveaugris[i] = (pixelgris[i]*256)/max;

        if(DEBUG == 2) printf("niv %d = %d - %d\n",i,pixelgris[i],niveaugris[i]);
    }
    short int **histo = allocationMatrice(256,256);
    for(j=0;j<256;j++){
        for(i=0;i<256;i++){
            if(i<niveaugris[j]) histo[i][j]=0;
            else histo[i][j]=255;
        }
    }
    return histo;
}

/** \brief Donne le niveau du palier sur lequel le pixel se trouve
 *
 * \param palier int
 * \param pixel int
 * \return int
 *
 * \author Charles Bong.
 */
int getNiveauByPalier(int palier,int pixel){
    int niveau = 0;
    while(pixel > 0){
        pixel = pixel - palier;
        niveau++;
    }
    return niveau;
}

/** \brief Donne la nouvelle couleurs du pixel par rapport au niveau du palier.
 *
 * \param palier int
 * \param niveau int
 * \param pixel int
 * \return int
 *
 * \author Charles Bong.
 */
int getColorByNiveau(int palier, int niveau, int pixel){
    int HighColor = palier * niveau;
    int LowColor = palier * (niveau - 1);
    int color = ((HighColor - pixel) < (pixel - LowColor) ? HighColor : LowColor);
    color = (color>255 ? 255 : color);
    if(DEBUG == 2 && color > 255) printf("%d (%d-%d) -> %d\n",pixel,LowColor,HighColor,color);
    return color ;
}

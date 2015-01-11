/**
 * \file caldist.c
 * \brief Partie Calcul distance
 *
 * Fonction liée à la partie personnel
 *
 * \author Charles Bong.
 * \date 29 octobre 2013
 */

#include "prototype.h"

/** \brief Calcul la distance entre des pixel de couleur différente
 *
 * Algorithme donné par notre professeur d'algo, Mme ROBERT-INACIO
 *
 * \param matriceOrgine short int**
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return short int**
 *
 * \author Mme ROBERT-INACIO
 */
short int** calculDistance(short int** matriceOrgine, int haut, int larg){
    short int** mfinal = copieMatrice(matriceOrgine,haut,larg);
    int i,j;
    for(i=0;i<haut-1;i++){
        for(j=0;j<larg-2;j++){
            mfinal[i+1][j+1] = minimun5(mfinal[i+1][j+1],mfinal[i][j+1]+3,mfinal[i+1][j]+3,mfinal[i][j]+4,mfinal[i][j+2]+4);
        }
        mfinal[i+1][larg-1] = minimun4(mfinal[i+1][larg-1],mfinal[i][larg-1]+3,mfinal[i+1][larg-2]+3,mfinal[i][larg-2]+4);
    }
    for(j=larg-2;j>-1;j--){
        mfinal[haut-1][j] = minimun(mfinal[haut-1][j],mfinal[haut-1][j+1]+3);
    }
    for(i=haut-2;i>-1;i--){
        mfinal[i][larg-1] = minimun4(mfinal[i][larg-1],(mfinal[i+1][larg-1])+3,(mfinal[i+1][larg-2])+3,(mfinal[i][larg-2])+4);
        for(j=larg-2;j>0;j--){
            mfinal[i][j] = minimun5(mfinal[i][j],mfinal[i][j+1]+3,mfinal[i+1][j]+3,mfinal[i+1][j+1]+4,mfinal[i+1][j-1]+4);
        }
        mfinal[i][0] = minimun4(mfinal[i][0],mfinal[i][1]+3,mfinal[i+1][1]+4,mfinal[i+1][0]+3);
    }
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            mfinal[i][j] = (short int) mfinal[i][j]/3;
        }
    }
    return mfinal;
}

/** \brief Copie une matrice
 *
 * Création une matrice de dimension (haut * larg) et y copie la matrice passé en paramètre
 *
 * \param matriceOrgine short int**
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return short int**
 *
 * \author Charles Bong.
 */
short int** copieMatrice(short int** matriceOrgine, int haut, int larg){
    short int **matricefinal = allocationMatrice(haut,larg);
    int i,j;
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            matricefinal[i][j] = matriceOrgine[i][j];
        }
    }
    return matricefinal;
}

/** \brief Calcul le minimum entre deux nombres
 *
 * \param nb1 short int
 * \param nb2 short int
 * \return short int
 *
 * \author Charles Bong.
 */
short int minimun(short int nb1,short int nb2){
    if(nb1 < nb2) return nb1;
    else return nb2;
}

/** \brief Calcul le maximum entre deux nombres
 *
 * \param nb1 short int
 * \param nb2 short int
 * \return short int
 *
 * \author Charles Bong.
 */
short int maximun(short int nb1,short int nb2){
    if(nb1 > nb2) return nb1;
    else return nb2;
}


/** \brief Calcul le minimum entre quatre nombres
 * \param nb1 short int
 * \param nb2 short int
 * \param nb3 short int
 * \param nb4 short int
 * \return short int
 *
 * \author Charles Bong.
 */
short int minimun4(short int nb1,short int nb2,short int nb3,short int nb4){
    short int result = nb1;
    result = minimun(result,nb2);
    result = minimun(result,nb3);
    result = minimun(result,nb4);
    return result;
}

/** \brief Calcul le minimum entre cinq nombres
 *
 * \param nb1 short int
 * \param nb2 short int
 * \param nb3 short int
 * \param nb4 short int
 * \param nb5 short int
 * \return short int
 *
 * \author Charles Bong.
 */
short int minimun5(short int nb1,short int nb2,short int nb3,short int nb4,short int nb5){
    short int result = nb1;
    result = minimun(result,nb2);
    result = minimun(result,nb3);
    result = minimun(result,nb4);
    result = minimun(result,nb5);
    return result;
}

/** \brief Calcul le minimum dans un tableau
 *
 * \param tab short int *
 * \param dim int
 * \return short int
 *
 * \author Charles Bong.
 */
short int minimunTab(short int * tab,int dim){
    short int result = tab[0];
    int i;
    for(i=0;i<dim;i++) result = minimun(result,tab[1]);
    return result;
}

/** \brief Calcul le maximum dans un tableau
 *
 * \param tab short int *
 * \param dim int
 * \return short int
 *
 * \author Charles Bong.
 */
short int maximunTab(short int * tab,int dim){
    short int result = tab[0];
    int i;
    for(i=0;i<dim;i++) result = maximun(result,tab[1]);
    return result;
}

/** \brief Fonction d'appel du calcul distance
 *
 * \param matriceOrgine short int** : Matrice d'origine
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return short int**
 *
 * \author Charles Bong.
 */
short int** fctCalculDistance(short int** matriceOrgine, int haut, int larg){
    seuillageNG(matriceOrgine,haut,larg,128);
    negatifImageNG(matriceOrgine,haut,larg);
    return calculDistance(matriceOrgine,haut,larg);
}


/*
 \brief Effectue le du calcul distance pour tout les niveaux de zoom
 * ATTENTION NON FONCTIONNEL !
 * \param short int ** matriceOrgine
 * \param haut int : Hauteur : Hauteur
 * \param larg int : Largeur : Largeur
 * \return short int **
 *
 * \author Charles Bong.
 */

/*
void fctallCalculDistance(short int ** matriceOrgine, int haut, int larg){
    DonneesImageRGB *img2 = NULL;
    short int** temp = NULL;
    int i,profmax;
    char nom_fichier_destination[150];

    seuillageNG(matriceOrgine,haut,larg,128);
    negatifImageNG(matriceOrgine,haut,larg);

    abquat* arbre = creeArbreNB(matriceOrgine,haut);
    profmax = profondeurArbre(arbre);

    for(i=0;i<=profmax;i++){
        temp = zoomNG(arbre,i);
        liberationmatrice(matriceOrgine,arbre->x1);
        matriceOrgine = temp;

        temp = fctCalculDistance(matriceOrgine,haut,larg);
        liberationmatrice(matriceOrgine,arbre->x1);
        matriceOrgine = temp;

        sprintf(nom_fichier_destination, "Dist.zoom%d.bmp", i);
        img2 = sauveImageNG(matriceOrgine,arbre->x1,arbre->y1);
        ecrisBMPRGB_Dans(img2,nom_fichier_destination);
        if(DEBUG == 5) printf("Image sauvegarde dans (dist) : %s\n",nom_fichier_destination);
        libereDonneesImageRGB(&img2);
    }
}*/

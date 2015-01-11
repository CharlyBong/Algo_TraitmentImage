/**
 * \file median.c
 * \brief Partie sur les couleurs médianes
 *
 * Fonctions liées au traitements des couleurs
 *
 * \author Charles Bong.
 * \date 22 octobre 2013
 */

#include "prototype.h"



/** \brief Effectue le lissage d'une matrice NG
 *
 * Crée une matrice en niveau de gris lisser avec la technique de la médiane
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return short int**
 *
 * \author Charles Bong.
 */
short int** medianGrisNxN(short int **matrice, int haut, int larg){
    int i,j;
    short int **matrice2 = (short int **) malloc(haut * sizeof(short int*));
    for(i=0;i<haut;i++){
        matrice2[i] = (short int *) malloc(larg * sizeof(short int));
    }
    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            if( (i==0)||(i==haut-1)||(j==0)||(j==larg-1) ) matrice2[i][j] = 0;
            else matrice2[i][j] = medianGriscase(matrice,i,j);
        }
    }
    return matrice2;
}


/** \brief Calcul de la médiane pour une case NG
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x int : coordonnée x du point à traiter
 * \param y int : coordonnée y du point à traiter
 * \return short int
 *
 * \author Charles Bong.
 */
short int medianGriscase(short int **matrice,int x, int y){
    int i, j, cas,retour;
    cas = 0;
    short int *table = (short int *) malloc(9 * sizeof(short int));
    for(i=x-1;i < x+2;i++){
        for(j=y-1;j < y+2;j++){
            table[cas] = matrice[i][j];
            cas++;
        }
    }
    retour = tritableau(table,9);
    free(table);
    return retour;
}

/** \brief tri un tableau et retourne la valeur médiane
 *
 * \param table short int* : Tableau à traiter
 * \param taille int : taille du tableau
 * \return short int
 *
 * \author Charles Bong.
 */
short int tritableau(short int * table,int taille){
    int i,test;
    short int k;
    do{
        test=0;
        for(i=0;i<taille-1;i++){
            if(table[i] > table[i+1]) {
                test++;
                k=table[i];
                table[i] = table[i+1];
                table[i+1] = k;
            }
        }
    }while(test!=0);
 	k = (short int) taille/2;
 	return table[k];
}

/** \brief retourne l'indice de la valeur minimum du tableau
 *
 * \param table short int* : Tableau à traiter
 * \param taille int : taille du tableau
 * \return int
 *
 * \author Charles Bong.
 */
int nimtableau(short int * table,int taille){
    int i;
    int k = table[0];
    int indice = 0;
    for(i=1;i<taille;i++){
        if(k > table[i]) {
            k=table[i];
            indice = i;
        }
    }
 	return indice;
}


/** \brief Effectue le lissage d'une matrice couleur
 *
 * Crée une matrice en couleur (RGB) lisser avec la technique de la médiane
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param matriceR2 short int** : Matrice destination rouge
 * \param matriceG2 short int** : Matrice destination verte
 * \param matriceB2 short int** : Matrice destination bleu
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \return void
 *
 * \author Charles Bong.
 */
void medianCouleurNxN2(short int **matriceR,short int **matriceG,short int **matriceB,short int **matriceR2,short int **matriceG2,short int **matriceB2, int haut, int larg){
    int i,j;
    int ti = time(NULL), tu = 0;
    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            if( (i==0)||(i==haut-1)||(j==0)||(j==larg-1) ) {
                    matriceR2[i][j] = 0;
                    matriceG2[i][j] = 0;
                    matriceB2[i][j] = 0;
                    }
            else {
                    medianCouleurcase2(matriceR,matriceG,matriceB,matriceR2,matriceG2,matriceB2,i,j);
            }
        }
    }
    tu = time(NULL)-ti;
    printf("\n%2dh%2dm%2ds\n",(tu/60/60)%24, (tu/60)%60, tu%60);
}


/** \brief Calcul de la médiane pour une case couleur
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param matriceR2 short int** : Matrice destination rouge
 * \param matriceG2 short int** : Matrice destination verte
 * \param matriceB2 short int** : Matrice destination bleu
 * \param x int : coordonnée x du point à traiter
 * \param y int : coordonnée y du point à traiter
 * \return void
 *
 * \author Charles Bong.
 */
void medianCouleurcase2(short int **matriceR,short int **matriceG,short int **matriceB,short int **matriceR2,short int **matriceG2,short int **matriceB2,int x, int y){
    int i, j, k,l, cas = 0,minresult,indice;
    int **table = (int **) malloc(9 * sizeof(int*));
    for(i=0;i<9;i++)
    {
        table[i] = (int*)malloc(3*sizeof(int));
    }

    for(i=x-1;i < x+2;i++){
        for(j=y-1;j < y+2;j++){
            table[cas][0] = 0;
            for(k=x-1;k < x+2;k++){
                    for(l=y-1;l < y+2;l++){
                            table[cas][0] += (int) (sqrt( (double) pow(matriceR[i][j]-matriceR[k][l],2) + pow(matriceG[i][j]-matriceG[k][l],2) + pow(matriceB[i][j]-matriceB[k][l],2) ) );}}
            table[cas][1] = i;
            table[cas][2] = j;
            cas++;
        }
    }
    minresult=table[0][0];
    indice=0;
    for(i=1;i<cas;i++){
        if(minresult > table[i][0]) {
            minresult=table[i][0];
            indice = i;
        }
    }
    matriceR2[x][y] = matriceR[table[indice][1]][table[indice][2]];
    matriceG2[x][y] = matriceG[table[indice][1]][table[indice][2]];
    matriceB2[x][y] = matriceB[table[indice][1]][table[indice][2]];

    free(table);
}


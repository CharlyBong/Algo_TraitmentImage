/**
 * \file quaternaire.c
 * \brief Partie sur les arbres quaternaires
 *
 * Fonction liées à la création et manipulation avec des arbres quaternaires
 *
 * \author Charles Bong.
 * \date 22 octobre 2013
 */

#include "prototype.h"

long long DIMTOTAL = 0;
float POURCENTAGE = 0;
//Utiliser pour les pourcentage de progression


/** \brief Calcul valeur médiane carre NB
 *
 * Calcul la valeur médiane d'un carre de dimension donnée dans une matrice binaire Noir et Blanc
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return short int
 *
 * \author Charles Bong.
 */
short int calculCarre(short int** matrice,int x0, int y0, int x1, int y1){
    int i,j;
    short int temp;
    temp = matrice[y0][x0];
    for(i=y0;i<y1;i++){
         for(j=x0;j<x1;j++){
            if(temp != matrice[i][j]) return (short int) 2;
        }
    }
    if(temp == 255) return (short int) 1; //blanc
    if(temp == 0) return (short int) 0;   //noir
    //else erreur !!!
    printf("Erreur");
    return temp;
}


/** \brief Fonction d'appel de création d'un arbre NB
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param dim int : dimension de l'image (Attention n*n)
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeArbreNB(short int** matrice, int dim){
    return creeationArbreNB(matrice,0,0,dim,dim);
}

/** \brief Allocation d'un nœud de l'arbre
 *
 * Création et allocation d'un espace pour le nœud de l'arbre quaternaire
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeNoeudArbreNB(short int** matrice, int x0, int y0, int x1, int y1){
    abquat* racine = (abquat *) malloc(sizeof(abquat));
    racine->x0 = x0;
    racine->y0 = y0;
    racine->x1 = x1;
    racine->y1 = y1;
    racine->fils1 = NULL;
    racine->fils2 = NULL;
    racine->fils3 = NULL;
    racine->fils4 = NULL;
    racine->valmediane = calculCarre(matrice,x0,y0,x1,y1);
    racine->valmediane1 = -1;
    racine->valmediane2 = -1;
    racine->epsi = EPSILON;
    return racine;
}


/** \brief Création d'un nœud de l'arbre
 *
 * Crée le nœud de l'arbre de le remplit, fait un appel récursif si besoin (carré non homogène)
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeationArbreNB(short int** matrice, int x0, int y0, int x1, int y1){
    abquat* racine = creeNoeudArbreNB(matrice,x0,y0,x1,y1);
    if(DEBUG == 1) printf("%d,%d -> %d,%d = %d\n",x0,y0,x1,y1,racine->valmediane);
    if (racine->valmediane == 2){
        racine->fils1 = creeationArbreNB(matrice, x0 , y0 , x0+(int)(x1-x0)/2 , y0+(int)(y1-y0)/2 );
        racine->fils2 = creeationArbreNB(matrice, x0+(int)(x1-x0)/2 , y0 , x1 , y0+(int)(y1-y0)/2 );
        racine->fils3 = creeationArbreNB(matrice, x0 , y0+(int)(y1-y0)/2 , x0+(int)(x1-x0)/2 , y1 );
        racine->fils4 = creeationArbreNB(matrice, x0+(int)(x1-x0)/2 , y0+(int)(y1-y0)/2 , x1 , y1 );
    }
    return racine;
}

/** \brief Fonction d'appel de création une matrice d'un arbre quaternaire NB
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \return short int**
 *
 * \author Charles Bong.
 */
short int** creeMatriceNB(abquat* racine){
    short int **matrice = allocationMatrice(racine->y1, racine->x1);
    creationMatriceNB(racine,matrice);
    return matrice;
}


/** \brief Remplissage d'une matrice à partir d'un arbre quaternaire NB
 *
 * Rempli une matrice avec l'arbre quaternaire NB, fait un appel récursif si besoin (carré non homogène)
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \param matrice short int** : Matrice niveau de gris
 * \return void
 *
 * \author Charles Bong.
 */
void creationMatriceNB(abquat* racine,short int** matrice){
    if(racine->valmediane != 2) creationMatriceCase(racine,matrice);
    else {
        creationMatriceNB(racine->fils1,matrice);
        creationMatriceNB(racine->fils2,matrice);
        creationMatriceNB(racine->fils3,matrice);
        creationMatriceNB(racine->fils4,matrice);
    }
}

/** \brief Remplissage matrice avec la couleur médiane
 *
 * Rempli un carré de la matrice avec la valeur de la médiane du nœud
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \param matrice short int** : Matrice niveau de gris
 * \return void
 *
 * \author Charles Bong.
 */
void creationMatriceCase(abquat* racine,short int** matrice){
    int i,j;
    short int couleur = racine->valmediane * 255;
    for(i=racine->y0;i<racine->y1;i++){
        for(j=racine->x0;j<racine->x1;j++){
            matrice[i][j] = couleur;
        }
    }
}



/** \brief Calcul la valeur médiane d'un carré NG
 *
 * Calcul la valeur médiane d'un carré de matrice en niveau de gris
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return short int
 *
 * \author Charles Bong.
 */
short int valeurMedianeNG(short int** matrice,int x0, int y0, int x1, int y1){
    int i,j;
    int taille = ((x1-x0)*(y1-y0));
    short int *table = (short int *) malloc(taille * sizeof(short int));
    int cas = 0;
    if(taille <= 1 ) return matrice[x0][y0];
    for(i=x0;i<x1;i++){
         for(j=y0;j<y1;j++){
            table[cas] = matrice[i][j];
            cas++;
        }
    }
    return tritableau(table,taille);
}

/** \brief Calcul la valeur médiane d'un carré RGB
 *
 * Calcul la valeur médiane d'un carré de matrice en couleur
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \param result short int* : tableau des résultats
 * \return void
 *
 * \author Charles Bong.
 */
void couleurMedianeRVB(short int **matriceR,short int **matriceG,short int **matriceB,int x0, int y0, int x1, int y1,short int * result){
    int i, j, k,l, cas,minresult,indice;

    long long dim = ((x1-x0)*(y1-y0));
    if(dim <= 1)//cas d'un carre de 1*1
    {
        result[0] = matriceR[x0][y0];
        result[1] = matriceG[x0][y0];
        result[2] = matriceB[x0][y0];
        //if((x1!=x0+1) || (y1!=y0+1)) printf(" ! UNE CASE ! : %d,%d = %d,%d\n",x0,y0,x1,y1);
    }
    else
    {
        cas = 0;
        int **table = (int **) malloc(dim * sizeof(int*));
        for(i=0;i<dim;i++)
            table[i] = (int*)malloc(3*sizeof(int));

        for(i=x0;i<x1;i++){
            for(j=y0;j<y1;j++){
                table[cas][0] = 0;

                if(j>y0){
                        if((matriceR[i][j-1]==matriceR[i][j])&&(matriceG[i][j-1]==matriceG[i][j])&&(matriceB[i][j-1]==matriceB[i][j])){
                            table[cas][1] = table[cas-1][1];
                            if(DEBUG == 2) printf("JUMP : %d,%d = %d,%d\n",i,j,i,j-1);}
                }
                else{
                    if(i>x0){
                        if((matriceR[i-1][j]==matriceR[i][j])&&(matriceG[i-1][j]==matriceG[i][j])&&(matriceB[i-1][j]==matriceB[i][j])){
                            table[cas][1] = table[cas-(y1-y0)][1];
                            if(DEBUG == 2) printf("JUMP : %d,%d = %d,%d\n",i,j,i-1,j);}
                    }
                    else{
                        for(k=x0;k<x1;k++){
                            for(l=y0;l<y1;l++){
                                table[cas][0] +=(int) (sqrt((double) pow(matriceR[k][l]-matriceR[i][j],2) + pow(matriceG[k][l]-matriceG[i][j],2) + pow(matriceB[k][l]-matriceB[i][j],2) ) );}}
                    }
                }

                table[cas][1] = i;
                table[cas][2] = j;
                cas++;
            }
        }

        indice=0;
        minresult=table[indice][0];
        for(i=1;i<cas;i++){
            if(minresult > table[i][0]) {
                minresult=table[i][0];
                indice = i;
            }
        }
        result[0] = matriceR[table[indice][1]][table[indice][2]];
        result[1] = matriceG[table[indice][1]][table[indice][2]];
        result[2] = matriceB[table[indice][1]][table[indice][2]];
    }
    if((DEBUG == 3)&&(dim>=1024)) printf("[%d][%d] - [%d][%d] = %d,%d,%d\n",x0,y0,x1,y1,result[1],result[2],result[0]);
}

/** \brief Vérifie si le carré est homogène NG
 *
 * Vérifie que la différence entre chaque pixel du carré de la matrice et la valeur médiane soit inférieur à &epsilon;
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \return short int
 *
 * \author Charles Bong.
 */
short int carreHomogeneNG(short int** matrice,int x0, int y0, int x1, int y1,abquat* racine){
    int i,j;
    racine->valmediane = valeurMedianeNG(matrice,x0,y0,x1,y1);
    int temp;
    for(i=y0;i<y1;i++){
         for(j=x0;j<x1;j++){
            temp = abs(racine->valmediane - matrice[i][j]);
            if( temp > EPSILON ) return 0;
        }
    }
    return 1;
}


/** \brief Vérifie si le carré est homogène RGB
 *
 * Vérifie que la différence entre chaque pixel du carré de la matrice et la valeur médiane soit inférieur à &epsilon;
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \return short int
 *
 * \author Charles Bong.
 */
short int carreHomogeneRVB(short int **matriceR,short int **matriceG,short int **matriceB,int x0, int y0, int x1, int y1,abquat* racine){
    int i,j;
    short int *couleurMediane = (short int *) malloc(3 * sizeof(short int));
    couleurMedianeRVB(matriceR,matriceG,matriceB,x0,y0,x1,y1,couleurMediane);
    racine->valmediane = couleurMediane[0];
    racine->valmediane1 = couleurMediane[1];
    racine->valmediane2 = couleurMediane[2];
    free(couleurMediane);
    short int temp;
    for(i=x0;i<x1;i++){
         for(j=y0;j<y1;j++){
            temp = abs(racine->valmediane - matriceR[i][j]);
            if( temp > EPSILON ) return 0;
            temp = abs(racine->valmediane1 - matriceG[i][j]);
            if( temp > EPSILON ) return 0;
            temp = abs(racine->valmediane2 - matriceB[i][j]);
            if( temp > EPSILON ) return 0;

        }
    }
    return 1;
}


/** \brief fonction d'appel de création de l'arbre NG
 *
 * Appel la fonction de création d'un arbre quaternaire à partir d'une matrice en niveau de gris
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param dim int : dimension de l'image (Attention n*n)
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeArbreNG(short int** matrice, int dim){
    int ti = time(NULL), tu = 0;
    DIMTOTAL = (dim*dim);
    POURCENTAGE = 0;

    abquat * retour = creeationArbreNG(matrice,0,0,dim,dim);

    tu = time(NULL)-ti;
    printf("\n%2dh%2dm%2ds\n",(tu/60/60)%24, (tu/60)%60, tu%60);
    return retour;
}


/** \brief Allocation d'un nœud de l'arbre quaternaire NG
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeNoeudArbreNG(short int** matrice, int x0, int y0, int x1, int y1){
    abquat* racine = (abquat *) malloc(sizeof(abquat));
    racine->x0 = x0;
    racine->y0 = y0;
    racine->x1 = x1;
    racine->y1 = y1;
    racine->fils1 = NULL;
    racine->fils2 = NULL;
    racine->fils3 = NULL;
    racine->fils4 = NULL;
    racine->valmediane = -1;
    racine->valmediane1 = -1;
    racine->valmediane2 = -1;
    racine->epsi = EPSILON;
    return racine;
}

/** \brief Création d'un nœud de l'arbre quaternaire NG
 *
 * Crée le nœud de l'arbre quaternaire en niveau de gris, fait un appel récursif pour construire l'arbre complet
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeationArbreNG(short int** matrice, int x0, int y0, int x1, int y1){
    abquat* racine = creeNoeudArbreNG(matrice,x0,y0,x1,y1);

    if((x0==x1-1)||(y0==y1-1)){
        racine->valmediane = valeurMedianeNG(matrice,x0,y0,x1,y1);
        if(DEBUG == 1) printf("%d,%d -> %d,%d = %d\n",x0,y0,x1,y1,racine->valmediane);
        POURCENTAGE += ( ( 100*(x1-x0)*(y1-y0) ) / DIMTOTAL )/3.6;
        printf("\t => %d%%\r",(int)POURCENTAGE);
        return racine;
    }

    if (carreHomogeneNG(matrice,x0,y0,x1,y1,racine) == 0){
        if(DEBUG == 1) printf("%d,%d -> %d,%d = %d\n",x0,y0,x1,y1,racine->valmediane);
        racine->fils1 = creeationArbreNG(matrice, x0 , y0 , x0+(int)(x1-x0)/2 , y0+(int)(y1-y0)/2 );
        racine->fils2 = creeationArbreNG(matrice, x0+(int)(x1-x0)/2 , y0 , x1 , y0+(int)(y1-y0)/2 );
        racine->fils3 = creeationArbreNG(matrice, x0 , y0+(int)(y1-y0)/2 , x0+(int)(x1-x0)/2 , y1 );
        racine->fils4 = creeationArbreNG(matrice, x0+(int)(x1-x0)/2 , y0+(int)(y1-y0)/2 , x1 , y1 );
    }
    POURCENTAGE += ( ( 100*(x1-x0)*(y1-y0) ) / DIMTOTAL )/3.6;
    printf("\t => %d%%\r",(int)POURCENTAGE);
    return racine;
}


/** \brief Fonction d'appel de création de l'arbre RGB
 *
 * Appel la fonction de création d'un arbre quaternaire à partir d'une matrice en couleur
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param dim int : dimension de l'image (Attention n*n)
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeArbreRVB(short int **matriceR,short int **matriceG,short int **matriceB, int dim){
    int ti = time(NULL), tu = 0;
    DIMTOTAL = (dim*dim);
    POURCENTAGE = 0;

    abquat * retour = creeationArbreRVB(matriceR,matriceG,matriceB,0,0,dim,dim);

    tu = time(NULL)-ti;
    printf("\n%2dh%2dm%2ds\n",(tu/60/60)%24, (tu/60)%60, tu%60);
    return retour;
}


/** \brief Allocation d'un nœud de l'arbre quaternaire RGB
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeNoeudArbreRVB(short int **matriceR,short int **matriceG,short int **matriceB, int x0, int y0, int x1, int y1){
    abquat* racine = (abquat *) malloc(sizeof(abquat));
    racine->x0 = x0;
    racine->y0 = y0;
    racine->x1 = x1;
    racine->y1 = y1;
    racine->fils1 = NULL;
    racine->fils2 = NULL;
    racine->fils3 = NULL;
    racine->fils4 = NULL;
    return racine;
}


/** \brief Création d'un nœud de l'arbre quaternaire RGB
 *
 * Crée le nœud de l'arbre quaternaire en couleur, fait un appel récursif pour construire l'arbre complet
 *
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param x0 int : coordonnée x0 du carré à traiter
 * \param y0 int : coordonnée y0 du carré à traiter
 * \param x1 int : coordonnée x1 du carré à traiter
 * \param y1 int : coordonnée y1 du carré à traiter
 * \return abquat*
 *
 * \author Charles Bong.
 */
abquat* creeationArbreRVB(short int **matriceR,short int **matriceG,short int **matriceB, int x0, int y0, int x1, int y1){
    abquat* racine = creeNoeudArbreRVB(matriceR,matriceG,matriceB,x0,y0,x1,y1);

    if (carreHomogeneRVB(matriceR,matriceG,matriceB,x0,y0,x1,y1,racine) == 0){
        if(DEBUG == 1) printf("%d,%d -> %d,%d = %d,%d,%d\n",x0,y0,x1,y1,racine->valmediane,racine->valmediane1,racine->valmediane2);
        racine->fils1 = creeationArbreRVB(matriceR,matriceG,matriceB, x0 , y0 , x0+(int)(x1-x0)/2 , y0+(int)(y1-y0)/2 );
        racine->fils2 = creeationArbreRVB(matriceR,matriceG,matriceB, x0+(int)(x1-x0)/2 , y0 , x1 , y0+(int)(y1-y0)/2 );
        racine->fils3 = creeationArbreRVB(matriceR,matriceG,matriceB, x0 , y0+(int)(y1-y0)/2 , x0+(int)(x1-x0)/2 , y1 );
        racine->fils4 = creeationArbreRVB(matriceR,matriceG,matriceB, x0+(int)(x1-x0)/2 , y0+(int)(y1-y0)/2 , x1 , y1 );
    }
        POURCENTAGE += ( ( 100*(x1-x0)*(y1-y0) ) / DIMTOTAL )/3.6;
        printf("\t => %d%%\r",(int)POURCENTAGE);
    return racine;
}



/** \brief Fonction d'appel de conversion arbre -> matrice NG
 *
 * Alloue une matrice pour la remplir avec un arbre quaternaire NG
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \param nn int : Niveau de l'arbre demandé
 * \return short int**
 *
 * \author Charles Bong.
 */
short int** creeMatriceNG(abquat* racine,int nn){
    short int **matrice = allocationMatrice(racine->y1, racine->x1);
    creationMatriceNG(racine,matrice,nn);
    return matrice;
}

/** \brief Remplissage de la matrice avec un arbre NG
 *
 * Rempli une matrice à partir d'un arbre quaternaire en niveau de gris, fait des appels récursif pour remplir toute la matrice
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \param matrice short int** : Matrice niveau de gris
 * \param nn int : Niveau de l'arbre demandé
 * \return void
 *
 * \author Charles Bong.
 */
void creationMatriceNG(abquat* racine,short int** matrice,int nn){
    if( (nn==0) || racine->fils1 == NULL ) creationMatriceCaseNG(racine,matrice);
    else {
        nn--;
        creationMatriceNG(racine->fils1,matrice,nn);
        creationMatriceNG(racine->fils2,matrice,nn);
        creationMatriceNG(racine->fils3,matrice,nn);
        creationMatriceNG(racine->fils4,matrice,nn);
    }
}

/** \brief Remplissage d'une case de la matrice NG
 *
 * Rempli une carré de la matrice à partir de l'arbre quaternaire en niveau de gris
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \param matrice short int** : Matrice niveau de gris
 * \return void
 *
 * \author Charles Bong.
 */
void creationMatriceCaseNG(abquat* racine,short int** matrice){
    int i,j;
    short int couleur = racine->valmediane;
    for(i=racine->x0;i<racine->x1;i++){
        for(j=racine->y0;j<racine->y1;j++){
            matrice[i][j] = couleur;
        }
    }
}


/** \brief Remplissage des matrices avec un arbre RGB
 *
 * Rempli une matrice à partir d'un arbre quaternaire en couleur, fait des appels récursif pour remplir toutes les matrices
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param nn int : Niveau de l'arbre demandé
 * \return void
 *
 * \author Charles Bong.
 */
void creationMatriceRVB(abquat* racine,short int** matriceR,short int** matriceG,short int** matriceB,int nn){
    if( (nn==0) || racine->fils1 == NULL ) creationMatriceCaseRVB(racine,matriceR,matriceG,matriceB);
    else {
        nn--;
        creationMatriceRVB(racine->fils1,matriceR,matriceG,matriceB,nn);
        creationMatriceRVB(racine->fils2,matriceR,matriceG,matriceB,nn);
        creationMatriceRVB(racine->fils3,matriceR,matriceG,matriceB,nn);
        creationMatriceRVB(racine->fils4,matriceR,matriceG,matriceB,nn);
    }
}


/** \brief Remplissage d'une case des matrices RGB
 *
 * Rempli une carré des matrices à partir de l'arbre quaternaire en couleur
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \return void
 *
 * \author Charles Bong.
 */
void creationMatriceCaseRVB(abquat* racine,short int** matriceR,short int** matriceG,short int** matriceB){
    int i,j;
    short int couleurR = racine->valmediane;
    short int couleurG = racine->valmediane1;
    short int couleurB = racine->valmediane2;
    for(i=racine->x0;i<racine->x1;i++){
        for(j=racine->y0;j<racine->y1;j++){
            matriceR[i][j] = couleurR;
            matriceG[i][j] = couleurG;
            matriceB[i][j] = couleurB;
        }
    }
}


/** \brief Calcul la profondeur d'un arbre
 *
 * Mesure la profondeur d'un arbre quaternaire, fait des appels récursifs
 *
 * \param racine abquat* : Noeud de l'arbre quaternaire
 * \return int
 *
 * \author Charles Bong.
 */
int profondeurArbre(abquat* racine){
    int nivProf = -1,temp;
    if(racine->fils1!=NULL){
        nivProf = profondeurArbre(racine->fils1);
        temp = profondeurArbre(racine->fils2);
        if(temp>nivProf) nivProf = temp;
        temp = profondeurArbre(racine->fils3);
        if(temp>nivProf) nivProf = temp;
        temp = profondeurArbre(racine->fils4);
        if(temp>nivProf) nivProf = temp;
    }
    return nivProf+1;
}

/** \brief Converti le k en nn
 *
 * Permet de passer le niveau de zoom demandé (2^-k) en niveau d'affichage à partir de la racine (nn)
 *
 * \param profondeur int : profondeur max de l'arbre
 * \param k int : Niveau du zoom demandé
 * \return int
 *
 * \author Charles Bong.
 * \date 13 novembre 2013
 */
int convknn(int profondeur, int k){
    if(k==0) return -1;
    //else
    return profondeur-k;
}


/** \brief Effectue le zoom sur un arbre RGB
 *
 * Permet de faire le zoom demandé sur une image, à partir d'un arbre quaternaire couleur
 *
 * \param arbre abquat* : Noeud de l'arbre quaternaire
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param k int : Niveau du zoom demandé
 * \return void
 *
 * \author Charles Bong.
 * \date 13 Novembre 2013
 */
void zoomCouleur(abquat* arbre,short int** matriceR,short int** matriceG,short int** matriceB,int k){
    int profmax = profondeurArbre(arbre);
    int nn = convknn(profmax,k);
    creationMatriceRVB(arbre,matriceR,matriceG,matriceB,nn);
}


/** \brief Effectue le zoom sur un arbre NG
 *
 * Permet de faire le zoom demandé sur une image, à partir d'un arbre quaternaire en niveau de gris
 *
 * \param arbre abquat* : Noeud de l'arbre quaternaire
 * \param k int : Niveau du zoom demandé
 * \return short int**
 *
 * \author Charles Bong.
 * \date 13 Novembre 2013
 */
short int** zoomNG(abquat* arbre,int k){
    int profmax = profondeurArbre(arbre);
    int nn = convknn(profmax,k);
    return creeMatriceNG(arbre,nn);
}


/** \brief Réalise tout les niveau de zoom d'un arbre RGB
 *
 * Sauvegarde toute les niveaux de zoom, à partir d'un arbre quaternaire couleur
 *
 * \param arbre abquat* : Noeud de l'arbre quaternaire
 * \param matriceR short int** : Matrice rouge
 * \param matriceG short int** : Matrice verte
 * \param matriceB short int** : matrice bleu
 * \param nom_fichier char* : nom du fichier d'origine
 * \return void
 *
 * \author Charles Bong.
 * \date 14 Novembre 2013
 */
void tousLesZoomsCouleur(abquat* arbre,short int** matriceR,short int** matriceG,short int** matriceB,char* nom_fichier){
    int i;
    char nom_fichier_destination[150];
    strcpy(nom_fichier_destination,nom_fichier);
    int profmax = profondeurArbre(arbre);
    DonneesImageRGB *img2 = NULL;
    for(i=0;i<=profmax;i++){
        zoomCouleur(arbre,matriceR,matriceG,matriceB,i);
        sprintf(nom_fichier_destination, "%s.zoom%d.bmp", nom_fichier, i);
        img2 = creeImage(matriceR,matriceG,matriceB,arbre->x1,arbre->y1);
        ecrisBMPRGB_Dans(img2,nom_fichier_destination);
        printf("Image sauvegarde dans (RGB) : %s\n",nom_fichier_destination);
        libereDonneesImageRGB(&img2);
    }
}


/** \brief Réalise tout les niveau de zoom d'un arbre NG
 *
 * Sauvegarde tous les niveaux de zoom, à partir d'un arbre quaternaire en niveau de gris
 *
 * \param arbre abquat* : Noeud de l'arbre quaternaire
 * \param matrice short int** : Matrice niveau de gris
 * \param nom_fichier char* : nom du fichier d'orgine
 * \return void
 *
 * \author Charles Bong.
 * \date 14 Novembre 2013
 */
void tousLesZoomsNG(abquat* arbre,short int** matrice,char* nom_fichier){
    int i;
    char nom_fichier_destination[150];
    short int** temp = NULL;
    strcpy(nom_fichier_destination,nom_fichier);
    int profmax = profondeurArbre(arbre);
    DonneesImageRGB *img2 = NULL;

    for(i=0;i<=profmax;i++){
        temp = zoomNG(arbre,i);
        liberationmatrice(matrice,arbre->x1);
        matrice = temp;
        sprintf(nom_fichier_destination, "%s.zoom%d.bmp", nom_fichier, i);
        img2 = sauveImageNG(matrice,arbre->x1,arbre->y1);
        ecrisBMPRGB_Dans(img2,nom_fichier_destination);
        printf("Image sauvegarde dans (NB) : %s\n",nom_fichier_destination);
        libereDonneesImageRGB(&img2);
    }
}

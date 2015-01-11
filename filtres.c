/**
 * \file filtres.c
 * \brief Fonctions de filtrages d'image (v2)
 *
 * Fonctions de filtrages d'une matrice NB
 *
 * \author Charles Bong.
 * \date 27 octobre 2013
 */

#include "prototype.h"

/** \brief Effectue une convolution sur une case d'une image, à partir d'un outil de dimension variable
            le boolen div indique s'il faut diviser le résultat par la somme des pixels traités
 *
 * \param image short int **
 * \param outil short int **
 * \param dimoutil int
 * \param div bool
 * \return short int
 *
 *
 * \author Charles Bong.
 */
short int convolutionCase(short int **image, short int **outil, int dimoutil, bool div){
    int i,j;
    short int result = 0;
    int coeffdiv = 0;
    for(i=0;i<dimoutil;i++){
        for(j=0;j<dimoutil;j++){
            result += image[i][j]*outil[i][j];
            coeffdiv += outil[i][j];
        }
    }
    result = ((div)?(result / coeffdiv):result);
    result = ((result > 255)? 255 : result);
    result = ((result < 0)? 0 : result);

    return result;
}

/** \brief Effectue une convolution sur une image, à partir d'un outil de dimension variable
            le boolen div indique s'il faut effectue une division lors du traitement d'une case
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \param outil short int **
 * \param dimoutil int
 * \param div bool
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** convolution(short int **matrice, int haut, int larg, short int **outil, int dimoutil,bool div){
    short int **Mconvolution = allocationMatrice(haut,larg);
    short int **temp = allocationMatrice(dimoutil,dimoutil);
    int i,j,k,l,suretoutil;
    suretoutil = (dimoutil-1)/2;
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            if(i-suretoutil<0 || j-suretoutil<0 || i+suretoutil>haut-1 || j+suretoutil>larg-1 )
                Mconvolution[i][j] = 0;
            else{
                for(k=0;k<dimoutil;k++){
                    for(l=0;l<dimoutil;l++){
                        temp[k][l] = matrice[i-suretoutil+k][j-suretoutil+l];
                        }}
                Mconvolution[i][j] = convolutionCase(temp,outil,dimoutil,div);
                //if(DEBUG == 2 ) printf("(%d,%d) %d != %d\n",i,j,Mconvolution[i][j],matrice[i][j]);
            }
        }
    }
    liberationmatrice(temp,dimoutil);
    return Mconvolution;
}

/** \brief Outil de test, permettant d'effectuer un filtre avec un outil qui de devrait pas modifier l'image
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtrenop(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            outil[i][j]=0;
        }
    }
    outil[1][1]=1;
    return medianGrisNxNVariable(matrice, haut, larg, outil,3);
}

/** \brief Outil de filtrage médian
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtreMedian(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            outil[i][j]=1;
        }
    }
    return medianGrisNxNVariable(matrice, haut, larg, outil,3);
}

/** \brief Outil de filtrage pour une convolution, pour effectuer une pondération moyenneur
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtrePondMoy(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            outil[i][j]=1;
        }
    }
    return convolution(matrice, haut, larg, outil,3,true);
}

/** \brief Outil de filtrage pour une convolution, pour effectuer une pondération de Gauss
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtrePondGauss(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    outil[0][0]=1;
    outil[0][1]=2;
    outil[0][2]=1;
    outil[1][0]=2;
    outil[1][1]=4;
    outil[1][2]=2;
    outil[2][0]=1;
    outil[2][1]=2;
    outil[2][2]=1;

    return convolution(matrice, haut, larg, outil,3,true);
}

/** \brief Outil de filtrage pour une convolution, pour effectuer un gradient de Roberts
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtreGraRoberts(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    outil[0][0]=0;
    outil[0][1]=0;
    outil[0][2]=0;
    outil[1][0]=1;
    outil[1][1]=-1;
    outil[1][2]=0;
    outil[2][0]=0;
    outil[2][1]=0;
    outil[2][2]=0;

    return convolution(matrice, haut, larg, outil,3,false);
}

/** \brief Outil de filtrage pour une convolution, pour effectuer une pondération de Prewitt
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtreGraPrewitt(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    outil[0][0]=-1;
    outil[0][1]=0;
    outil[0][2]=1;
    outil[1][0]=-1;
    outil[1][1]=0;
    outil[1][2]=1;
    outil[2][0]=-1;
    outil[2][1]=0;
    outil[2][2]=1;

    return convolution(matrice, haut, larg, outil,3,false);
}

/** \brief Outil de filtrage pour une convolution, pour effectuer une pondération de Sobel
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtreGraSobel(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    outil[0][0]=-1;
    outil[0][1]=0;
    outil[0][2]=1;
    outil[1][0]=-2;
    outil[1][1]=0;
    outil[1][2]=2;
    outil[2][0]=-1;
    outil[2][1]=0;
    outil[2][2]=1;

    return convolution(matrice, haut, larg, outil,3,false);
}

/** \brief Outil de filtrage pour une convolution, pour effectuer un Laplacien
 *
 * \param matrice short int **
 * \param haut int
 * \param larg int
 * \return short int **
 *
 *
 * \author Charles Bong.
 */
short int ** filtreLaplacien(short int **matrice, int haut, int larg){
    short int **outil = allocationMatrice(3,3);
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            outil[i][j]=-1;
        }
    }
    outil[1][1]=8;
    return convolution(matrice, haut, larg, outil,3,false);
}

/** \brief Effectue le lissage d'une matrice NG avec un outil de taille variable
 *
 * Crée une matrice en niveau de gris lisser avec la technique de la médiane
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param haut int : Hauteur
 * \param larg int : Largeur
 * \param outil short int ** : Outil à appliquer sur l'image
 * \param dimoutil int : Dimension de l'outil
 * \return short int **
 *
 * \author Charles Bong.
 */
short int ** medianGrisNxNVariable(short int **matrice, int haut, int larg, short int **outil, int dimoutil){
    short int **matrice2 = allocationMatrice(haut,larg);
    int i,j,suretoutil;
    suretoutil = (dimoutil-1)/2;
    for(i=0;i < haut;i++){
        for(j=0;j < larg;j++){
            if(i-suretoutil<0 || j-suretoutil<0 || i+suretoutil>haut-1 || j+suretoutil>larg-1 ) matrice2[i][j] = 0;
            else matrice2[i][j] = medianGriscaseVariable(matrice,i,j,outil,dimoutil);
        }
    }
    return matrice2;
}

/** \brief Calcul de la médiane pour une case NG avec un outil de taille variable
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param x int : coordonnée x du point à traiter
 * \param y int : coordonnée y du point à traiter
 * \param outil short int ** : Outil à appliquer sur l'image
 * \param dimoutil int : Dimension de l'outil
 * \return short int
 *
 * \author Charles Bong.
 */
short int medianGriscaseVariable(short int **matrice,int x, int y,short int **outil, int dimoutil){
    int i, j, k, l, cas, retour, suretoutil ;
    cas = 0;
    suretoutil = (dimoutil-1)/2;
    short int *table = (short int *) malloc(dimoutil * dimoutil * sizeof(short int));
    k = 0;
    for(i=x-suretoutil;i < x+suretoutil+1;i++){
            l = 0;
        for(j=y-suretoutil;j < y+suretoutil+1;j++){
            if(outil[k][l] == 1){
                table[cas] = matrice[i][j];
                cas++;
            }
            l++;
        }
        k++;
    }
    retour = tritableau(table,cas);
    free(table);
    return retour;
}

/** \brief Effectue une dilatation sur une case de la matrice sur une dimension variable
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param dimoutil int : Dimension de l'outil
 * \return short int
 *
 * \author Charles Bong.
 */
short int dilatationCase(short int **matrice, int dimoutil){
    int i,j,cas;
    short int *table = (short int *) malloc(dimoutil * dimoutil * sizeof(short int));
    cas = 0;
    for(i=0;i<dimoutil;i++){
        for(j=0;j<dimoutil;j++){
            table[cas] = matrice[i][j];
            cas++;
        }
    }
    return maximunTab(table,cas);
}

/** \brief Effectue une érosion sur une case de la matrice sur une dimension variable
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param dimoutil int : Dimension de l'outil
 * \return short int
 *
 * \author Charles Bong.
 */
short int erosionCase(short int **matrice, int dimoutil){
    int i,j,cas;
    short int *table = (short int *) malloc(dimoutil * dimoutil * sizeof(short int));
    cas = 0;
    for(i=0;i<dimoutil;i++){
        for(j=0;j<dimoutil;j++){
            table[cas] = matrice[i][j];
            cas++;
        }
    }
    return minimunTab(table,cas);
}

/** \brief Effectue un gradient sur une case de la matrice sur une dimension variable
 *
 * \param matrice short int** : Matrice niveau de gris
 * \param dimoutil int : Dimension de l'outil
 * \return short int
 *
 * \author Charles Bong.
 */
short int gradientCase(short int **matrice, int dimoutil){
    short int dila = dilatationCase(matrice,dimoutil);
    short int eros = erosionCase(matrice,dimoutil);
    return dila - eros;
}

/** \brief Effectue une dilatation sur une image avec un outil de dimension variable
 *
 * \param matrice short int ** : Matrice niveau de gris
 * \param haut int
 * \param larg int
 * \param dimoutil int : Dimension de l'outil
 * \return short int **
 *
 * \author Charles Bong.
 */
short int ** filtreDilatation(short int **matrice, int haut, int larg, int dimoutil){
    short int **Mresult = allocationMatrice(haut,larg);
    short int **temp = allocationMatrice(dimoutil,dimoutil);
    int i,j,k,l,suretoutil;
    suretoutil = (dimoutil-1)/2;
    if(DEBUG == 2) printf("(%d)\n",suretoutil);
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            if(i-suretoutil<0 || j-suretoutil<0 || i+suretoutil>haut-1 || j+suretoutil>larg-1 )
                Mresult[i][j] = 0;
            else{
                for(k=0;k<dimoutil;k++){
                    for(l=0;l<dimoutil;l++){
                        temp[k][l] = matrice[i-suretoutil+k][j-suretoutil+l];
                        }}
                Mresult[i][j] = dilatationCase(temp,dimoutil);
                //if(DEBUG == 2 ) printf("(%d,%d) %d != %d\n",i,j,Mresult[i][j],matrice[i][j]);
            }
        }
    }
    liberationmatrice(temp,dimoutil);
    return Mresult;
}

/** \brief Effectue une érosion sur une image avec un outil de dimension variable
 *
 * \param matrice short int ** : Matrice niveau de gris
 * \param haut int
 * \param larg int
 * \param dimoutil int : Dimension de l'outil
 * \return short int **
 *
 * \author Charles Bong.
 */
short int ** filtreErosion(short int **matrice, int haut, int larg, int dimoutil){
    short int **Mresult = allocationMatrice(haut,larg);
    short int **temp = allocationMatrice(dimoutil,dimoutil);
    int i,j,k,l,suretoutil;
    suretoutil = (dimoutil-1)/2;
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            if(i-suretoutil<0 || j-suretoutil<0 || i+suretoutil>haut-1 || j+suretoutil>larg-1 )
                Mresult[i][j] = 0;
            else{
                for(k=0;k<dimoutil;k++){
                    for(l=0;l<dimoutil;l++){
                        temp[k][l] = matrice[i-suretoutil+k][j-suretoutil+l];
                        }}
                Mresult[i][j] = erosionCase(temp,dimoutil);
                //if(DEBUG == 2 ) printf("(%d,%d) %d != %d\n",i,j,Mresult[i][j],matrice[i][j]);
            }
        }
    }
    liberationmatrice(temp,dimoutil);
    return Mresult;
}

/** \brief Effectue un gradient sur une image avec un outil de dimension variable
 *
 * \param matrice short int ** : Matrice niveau de gris
 * \param haut int
 * \param larg int
 * \param dimoutil int : Dimension de l'outil
 * \return short int **
 *
 * \author Charles Bong.
 */
short int ** filtreGradient(short int **matrice, int haut, int larg, int dimoutil){
    short int **Mresult = allocationMatrice(haut,larg);
    short int **temp = allocationMatrice(dimoutil,dimoutil);
    int i,j,k,l,suretoutil;
    suretoutil = (dimoutil-1)/2;
    for(i=0;i<haut;i++){
        for(j=0;j<larg;j++){
            if(i-suretoutil<0 || j-suretoutil<0 || i+suretoutil>haut-1 || j+suretoutil>larg-1 )
                Mresult[i][j] = 0;
            else{
                for(k=0;k<dimoutil;k++){
                    for(l=0;l<dimoutil;l++){
                        temp[k][l] = matrice[i-suretoutil+k][j-suretoutil+l];
                        }}
                Mresult[i][j] = gradientCase(temp,dimoutil);
                //if(DEBUG == 2 ) printf("(%d,%d) %d != %d\n",i,j,Mresult[i][j],matrice[i][j]);
            }
        }
    }
    liberationmatrice(temp,dimoutil);
    return Mresult;
}


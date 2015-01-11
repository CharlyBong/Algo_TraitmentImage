/**
 * \file main.c
 * \brief Main du programme
 * \author Charles Bong.
 * \date 15 octobre 2013
 */


#include "prototype.h"

/** \brief Main du programme
 *
 * Menu principal du programme
 *
 * \author Charles Bong.
 */

int main(int argc, char *argv[])
{
    char nom_fichier[100];
    char nom_fichier_destination[100];
    strcpy(nom_fichier,"toshy.bmp");
    strcpy(nom_fichier_destination,"imagefinal.bmp");

    DonneesImageRGB *img = lisBMPRGB(nom_fichier);
    int valeur,etatImgNB,seuil,profmax;

    short int **matriceR = allocationMatrice(img->hauteurImage,img->largeurImage);
    short int **matriceG = allocationMatrice(img->hauteurImage,img->largeurImage);
    short int **matriceB = allocationMatrice(img->hauteurImage,img->largeurImage);
    cree3matrices(img,matriceR,matriceG,matriceB);
    DonneesImageRGB *img2 = NULL;
    abquat * arbre = NULL;


    etatImgNB = 0;
    do
	{
		choixMenu(nom_fichier,valeur);
      	scanf("%d", &valeur);
		switch (valeur)
		{
			case 1:
			    if(etatImgNB == 0){
                    negatifImage(matriceR,matriceG,matriceB,img->hauteurImage,img->largeurImage);
                    printf("Votre image vient de passer en negatif\n");
                }
                else printf("Passer en Couleur !!!\n");
                break;
			case 2:
                couleur2NG(matriceR,matriceG,matriceB,img->hauteurImage,img->largeurImage);
                printf("Votre image vient de passer en NB\n");
                etatImgNB = 1;
				break;
			case 3:
                if(etatImgNB == 1){
                    printf("Entrer un nb (entre 0 et 255) ?");
                    scanf("%d", &seuil);
                    if(seuil>=0 && seuil <=255){
                        seuillageNG(matriceR, img->hauteurImage,img->largeurImage,seuil);
                        printf("Votre image a ete seuiller a %d\n",seuil);
                    }
                    else printf("Erreur !!!!!!\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 4:
                if(etatImgNB == 1){
                    matriceR = medianGrisNxN(matriceR, img->hauteurImage,img->largeurImage);
                    printf("Votre image (nb) a ete liser\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");

				break;
            case 5:
                if(etatImgNB == 0){
                    short int **matriceR2 = allocationMatrice(img->hauteurImage,img->largeurImage);
                    short int **matriceG2 = allocationMatrice(img->hauteurImage,img->largeurImage);
                    short int **matriceB2 = allocationMatrice(img->hauteurImage,img->largeurImage);
                    medianCouleurNxN2(matriceR,matriceG,matriceB,matriceR2,matriceG2,matriceB2,img->hauteurImage,img->largeurImage);
                    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
                    matriceR = matriceR2;
                    matriceG = matriceG2;
                    matriceB = matriceB2;
                    printf("Votre image (couleur) a ete lisee\n");
                }
                else printf("Passer en Couleur Avant !!!\n");

				break;

            case 6:
                if(etatImgNB == 1){
                    if(arbre != NULL) free(arbre);
                    arbre = creeArbreNB(matriceR,img->hauteurImage);
                    printf("Arbre cree !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 7:
                if(arbre != NULL){
                    short int** temp = creeMatriceNB(arbre);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Matrice cree a partir de l'arbre!\n");
                }
                else printf("Veuillez creer l'arbre avant !\n");
				break;


            case 8:
                if(etatImgNB == 1){
                    if(arbre != NULL) free(arbre);
                    arbre = creeArbreNG(matriceR,img->hauteurImage);
                    printf("Arbre cree !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 9:
                if(arbre != NULL){
                    printf("Entrer le nn ?");
                    scanf("%d", &seuil);
                    short int** temp = creeMatriceNG(arbre,seuil);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Matrice cree a partir de l'arbre!\n");
                }
                else printf("Veuillez creer l'arbre avant !\n");
				break;
            case 10:
                if(etatImgNB != 1){
                    if(arbre != NULL) free(arbre);
                    arbre = creeArbreRVB(matriceR,matriceG,matriceB,img->hauteurImage);
                    printf("Arbre RVB cree !\n");
                }
                else printf("Passer en Couleur Avant !!!\n");
				break;
            case 11:
                if(arbre != NULL){
                    printf("Entrer le nn ?");
                    scanf("%d", &seuil);
                    creationMatriceRVB(arbre,matriceR,matriceG,matriceB,seuil);
                    printf("Matrice RVB cree a partir de l'arbre!\n");
                }
                else printf("Veuillez creer l'arbre avant !\n");
				break;
            case 12:
                if(arbre != NULL){
                    profmax = profondeurArbre(arbre);
                    do{
                        printf("Entrer le niveau de zoom 2^-k (max %d) ?",profmax);
                        scanf("%d", &seuil);
                    }while(seuil<0 ||seuil>profmax);
                    if(arbre->valmediane1 == -1){
                        short int** temp = zoomNG(arbre,seuil);
                        liberationmatrice(matriceR,img->hauteurImage);
                        matriceR = temp;
                    }
                        else zoomCouleur(arbre,matriceR,matriceG,matriceB,seuil);
                    printf("Zoom 2^-%d ,niv de l'arbre %d\n",seuil,convknn(profmax,seuil));
                }
                else printf("Veuillez creer l'arbre avant !\n");
				break;
            case 13:
                if(arbre != NULL){
                    if(arbre->valmediane1 == -1) tousLesZoomsNG(arbre,matriceR,nom_fichier);
                        else tousLesZoomsCouleur(arbre,matriceR,matriceG,matriceB,nom_fichier);
                }
                else printf("Veuillez creer l'arbre avant !\n");
				break;
            case 15:
                if(etatImgNB == 1){
                    short int** temp = fctCalculDistance(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Image realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;

            // TP2 M1

            case 21://échantillonnage
                if(etatImgNB == 1){
                    do{
                        printf("Entrer le niveau d'echantillonnage (entre 2 et 255) ?");
                        scanf("%d", &seuil);
                    }while(seuil<1 ||seuil>255);
                    short int** temp = echantillonnagenb(matriceR,img->hauteurImage,img->largeurImage,seuil);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Echantillonnage realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 22://quantification
                if(etatImgNB == 1){
                    do{
                        printf("Entrer le niveau de quantification (entre 2 et 255) ?");
                        scanf("%d", &seuil);
                    }while(seuil<2 ||seuil>255);
                    //quantificationnb(matriceR,img->hauteurImage,img->largeurImage,seuil);
                    short int** temp = quantificationnb(matriceR,img->hauteurImage,img->largeurImage,seuil);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Quantification realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 23://statistiques
                if(etatImgNB == 1){
                    statistiquenb(matriceR,img->hauteurImage,img->largeurImage);
                    printf("statistiques realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 24://histogramme
                if(etatImgNB == 1){
                    short int** temp = histogrammenb(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    img->hauteurImage = 256;
                    img->largeurImage = 256;
                    printf("histogramme realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;

            // TP3 M1

            case 31://filtre pondéré moyenneur
                if(etatImgNB == 1){
                    short int** temp = filtrePondMoy(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage pondere moyenneur realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 32:// filtre pondéré Gaussien
                if(etatImgNB == 1){
                    short int** temp = filtrePondGauss(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage pondere Gaussien realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 33:// filtre Gradient Roberts
                if(etatImgNB == 1){
                    short int** temp = filtreGraRoberts(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage Gradiant Roberts realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 34:// filtre Gradient Prewitt
                if(etatImgNB == 1){
                    short int** temp = filtreGraPrewitt(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage Gradiant Prewitt realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 35:// filtre Gradient Sobel
                if(etatImgNB == 1){
                    short int** temp = filtreGraSobel(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage Gradiant Sobel realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 36:// filtre Laplacien
                if(etatImgNB == 1){
                    short int** temp = filtreLaplacien(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage Laplacien realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 37:// filtre Médian
                if(etatImgNB == 1){
                    short int** temp = filtreMedian(matriceR,img->hauteurImage,img->largeurImage);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage median realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 38:// filtre morphologique dilatation
                if(etatImgNB == 1){
                     do{
                        printf("Entrer les dimensions de l'outil (3 ou 5)?");
                        scanf("%d", &seuil);
                    }while(!(seuil==3 || seuil==5));
                    short int** temp = filtreDilatation(matriceR,img->hauteurImage,img->largeurImage,seuil);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage morphologique dilatation realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 39:// filtre morphologique erosion
                if(etatImgNB == 1){
                    do{
                        printf("Entrer les dimensions de l'outil (3 ou 5)?");
                        scanf("%d", &seuil);
                    }while(!(seuil==3 || seuil==5));
                    short int** temp = filtreErosion(matriceR,img->hauteurImage,img->largeurImage,seuil);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage morphologique erosion realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            case 40:// filtre morphologique gradient
                if(etatImgNB == 1){
                    do{
                        printf("Entrer les dimensions de l'outil (3 ou 5)?");
                        scanf("%d", &seuil);
                    }while(!(seuil==3 || seuil==5));
                    short int** temp = filtreGradient(matriceR,img->hauteurImage,img->largeurImage,seuil);
                    liberationmatrice(matriceR,img->hauteurImage);
                    matriceR = temp;
                    printf("Filtrage morphologique gradient realisee !\n");
                }
                else printf("Passer en Noir et Blanc Avant !!!\n");
				break;
            // Gestion de fichier !
            case 50:
                if(arbre!= NULL) free(arbre);
                arbre = NULL;
			    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
			    strcpy(nom_fichier,"toshy.bmp");
                changeimage(img,nom_fichier);
                matriceR = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceG = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceB = allocationMatrice(img->hauteurImage,img->largeurImage);
                cree3matrices(img,matriceR,matriceG,matriceB);
                etatImgNB = 0;
				break;
            case 51:
                if(arbre!= NULL) free(arbre);
                arbre = NULL;
			    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
			    strcpy(nom_fichier,"hoodoos.bmp");
                changeimage(img,nom_fichier);
                matriceR = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceG = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceB = allocationMatrice(img->hauteurImage,img->largeurImage);
                cree3matrices(img,matriceR,matriceG,matriceB);
                etatImgNB = 0;
				break;
			case 52:
			    if(arbre!= NULL) free(arbre);
                arbre = NULL;
			    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
			    strcpy(nom_fichier,"horseshoe.bmp");
                changeimage(img,nom_fichier);
                matriceR = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceG = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceB = allocationMatrice(img->hauteurImage,img->largeurImage);
                cree3matrices(img,matriceR,matriceG,matriceB);
                etatImgNB = 0;
				break;
			case 53:
			    if(arbre!= NULL) free(arbre);
                arbre = NULL;
			    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
			    strcpy(nom_fichier,"nenuphar.bmp");
                changeimage(img,nom_fichier);
                matriceR = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceG = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceB = allocationMatrice(img->hauteurImage,img->largeurImage);
                cree3matrices(img,matriceR,matriceG,matriceB);
                etatImgNB = 0;
				break;
			case 55:
			    if(arbre!= NULL) free(arbre);
                arbre = NULL;
			    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
			    do{
                    printf("Nom de l'image a charger (sans l'extension): ");
                    scanf("%s", nom_fichier);
                    sflush();
                    strcat(nom_fichier,".bmp");
			    }while(changeimage(img,nom_fichier) == -1);
			    matriceR = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceG = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceB = allocationMatrice(img->hauteurImage,img->largeurImage);
			    cree3matrices(img,matriceR,matriceG,matriceB);
                etatImgNB = 0;
				break;
            case 56:
			    if(arbre!= NULL) free(arbre);
                arbre = NULL;
			    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
                changeimage(img,nom_fichier);
                matriceR = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceG = allocationMatrice(img->hauteurImage,img->largeurImage);
                matriceB = allocationMatrice(img->hauteurImage,img->largeurImage);
                cree3matrices(img,matriceR,matriceG,matriceB);
                etatImgNB = 0;
				break;

            case 60:
                if(etatImgNB==0)img2 = creeImage(matriceR,matriceG,matriceB,img->hauteurImage,img->largeurImage);
                else img2 = sauveImageNG(matriceR, img->hauteurImage,img->largeurImage);

                ecrisBMPRGB_Dans(img2,nom_fichier_destination);
                printf("Image sauvegarde dans : %s",nom_fichier_destination);
				break;
            case 61:
                if(etatImgNB==0)img2 = creeImage(matriceR,matriceG,matriceB,img->hauteurImage,img->largeurImage);
                else img2 = sauveImageNG(matriceR, img->hauteurImage,img->largeurImage);
                printf("Nom de destination pour l'image: ");
                scanf("%s", nom_fichier_destination);
                sflush();
                strcat(nom_fichier_destination,".bmp");
                ecrisBMPRGB_Dans(img2,nom_fichier_destination);
                printf("Enregistrement dans : %s",nom_fichier_destination);
				break;

            case 0:
				valeur = 0 ;
                break;
            case 99 :
                break;
            case 110 :
                break;
            case 120 :
                break;
            case 130 :
                break;
            case 140 :
                break;
            case 150 :
                break;
            default:
               printf("  Valeur erronee \n") ;
               break;
		}
	}
	while ( valeur != 0 );

    /* ***Libération*** */
    liberationtrimatrice(matriceR,matriceG,matriceB,img->hauteurImage);
    libereDonneesImageRGB(&img);
    if(img2 != NULL) libereDonneesImageRGB(&img2);
    if(arbre != NULL) free(arbre);
    return 0;
}

/** \brief Affichage du menu de sélection
 *
 *  Affiche le menu de sélection
 *
 * \param  nomfichier Char*: permet l'affichage du fichier charger
 * \param  sousmenu int: permet de définir l'affichage du sous-menu
 * \return void
 * \author Charles Bong.
 */

void choixMenu(char * nomfichier,int sousmenu){
	printf("\n\t --- CIR_3 - Mini-Projet: BMP---\n");
	printf("\n\t --- %s ---\n\n",nomfichier);

	switch(sousmenu){
    case 110 :
        printf("\t110 <-> Sous-menu Fonctionnalites de Base :\n");
        printf("\t1   --> Negatif d'une image\n");
        printf("\t2   --> Transformation en niv de gris\n");
        printf("\t3   --> Seuillage\n");
        printf("\t4   --> Lisage NB\n");
        printf("\t5   --> Lisage Couleur\n");
        break;
    case 120 :
        printf("\t120 <-> Sous-menu Arbres quaternaire :\n");
        printf("\t6   --> Creation Arbre NB\n");
        printf("\t7   --> Creation Matrice a partir d'un arbre NB\n");

        printf("\t8   --> Creation Arbre NG\n");
        printf("\t9   --> Creation Matrice a partir d'un arbre NG\n");

        printf("\t10  --> Creation Arbre RVB\n");
        printf("\t11  --> Creation Matrice a partir d'un arbre RVB\n");
        printf("\t12  --> Zoom 2^-k\n");
        printf("\t13  --> Tous les Zoom 2^-k\n");

        printf("\t15  --> Calcul Distance\n");
        break;
    case 130:
        printf("\t130 <-> Sous-menu Stats et echantillonnage NB (v2) :\n");
        printf("\t21  --> Echantillonnage NB\n");
        printf("\t22  --> QuantificationNB\n");
        printf("\t23  --> Statistique NB\n");
        printf("\t24  --> Histogramme NB\n");
        break;
    case 140:
        printf("\t140 <-> Sous-menu Filtrages NB (v2) :\n");
        printf("\t31  --> Filtre pondere moyenneur\n");
        printf("\t32  --> Filtre pondere Gaussien\n");
        printf("\t33  --> Filtre gradient Roberts\n");
        printf("\t34  --> Filtre gradient Prewitt\n");
        printf("\t35  --> Filtre gradient Sobel\n");
        printf("\t36  --> Filtre Laplacien\n");
        printf("\t37  --> Filtre median\n");
        printf("\t38  --> Filtre morphologique dilatation\n");
        printf("\t39  --> Filtre morphologique erosion\n");
        printf("\t40  --> Filtre morphologique gradient\n");
        break;
    case 150:
        printf("\t150 <-> Sous-menu Chargement Rapide :\n");
        printf("\t50  --> Chargement de toshy.bmp\n");
        printf("\t51  --> Chargement de hoodoos.bmp\n");
        printf("\t52  --> Chargement de horseshoe.bmp\n");
        printf("\t53  --> Chargement de nenuphar.bmp\n");
        break;
    default:
        printf("\t110 --> Sous-menu Fonctionnalites de Base\n");
        printf("\t120 --> Sous-menu Arbres quaternaire\n");
        printf("\t130 --> Sous-menu Stats et echantillonnage NB (v2)\n");
        printf("\t140 --> Sous-menu Filtrages NB (v2)\n");
        printf("\t150 --> Sous-menu Chargement Rapide\n");
        break;
	}
	printf("\t----------------------\n");


	printf("\t55  --> Chargement du fichier de votre choix\n");
	printf("\t60  --> Enregistrement\n");
	printf("\t61  --> Chargement du fichier d'enregistrement\n");

    printf("\n\t99  --> Retour\n");
	printf("\t0   --> Quitter\n");
}

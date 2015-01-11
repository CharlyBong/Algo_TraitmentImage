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
		choixMenu(nom_fichier);
      	scanf("%d", &valeur);
		switch (valeur)
		{
			case 1:
			    if(etatImgNB == 0){
                    negatifImage(matriceR,matriceG,matriceB,img->hauteurImage,img->largeurImage);
                    printf("Votre image viens de passer en negatif\n");
                }
                else printf("Passer en Couleur !!!\n");
                break;
			case 2:
                couleur2NG(matriceR,matriceG,matriceB,img->hauteurImage,img->largeurImage);
                printf("Votre image viens de passer en NB\n");
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
                    printf("Votre image (couleur) a ete liser\n");
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

            // Gestion de fichier !

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
            default:
                   printf("  Valeur erronee \n") ;
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
 * \return void
 * \author Charles Bong.
 */

void choixMenu(char * nomfichier){
	printf("\n\t --- CIR_3 - Mini-Projet: BMP---\n");
	printf("\n\t --- %s ---\n\n",nomfichier);

	printf("\t1   --> Negatif d'une image\n");
	printf("\t2   --> Transformation en niv de gris\n");
	printf("\t3   --> Seuillage\n");
	printf("\t4   --> Lisage NB\n");
	printf("\t5   --> Lisage Couleur\n");

	printf("\t6   --> Creation Arbre NB\n");
	printf("\t7   --> Creation Matrice a partir d'un arbre NB\n");

	printf("\t8   --> Creation Arbre NG\n");
	printf("\t9   --> Creation Matrice a partir d'un arbre NG\n");

	printf("\t10  --> Creation Arbre RVB\n");
	printf("\t11  --> Creation Matrice a partir d'un arbre RVB\n");
	printf("\t12  --> Zoom 2^-k\n");
	printf("\t13  --> Tous les Zoom 2^-k\n");

	printf("\t15  --> Calcul Distance\n");

	printf("\t----------------------\n");
	//printf("\t51  --> Chargement de hoodoos.bmp\n");
	//printf("\t52  --> Chargement de horseshoe.bmp\n");
	//printf("\t53  --> Chargement de nenuphar.bmp\n");

	printf("\t55  --> Chargement du fichier de votre choix\n");
	printf("\t60  --> Enregistrement\n");
	printf("\t61  --> Chargement du fichier d'enregistrement\n");

	printf("\t0   --> Quitter ?\n");
}


 /**
 * \file doxymain.c
 * \brief Documentation doxygen mainpage
 *
 * Présentation du projet par une interface doxygen / HTML
 * Page principale
 *
 * \author Charles Bong.
 * \date 09 novembre 2014
 */


 /*! \mainpage Présentation
 * \section intro_sec Introduction
 *  Ce projet s'inscrit dans le cadre de notre formation d'ingénieur.<br/>
    Il a été fait sous la direction de Mme ROBERT-INACIO, notre professeur d'Algorithme Avancée et de Vision industrielle.<br/>
    J'ai commencé ce projet durant la 3éme année de ma formation d'ingénieur, en CIR3.<br/>
    Au cours de ma quatrième année (M1), il m'a été demander de reprendre mon travaille est d'y ajouter des fonctionnalités.<br/>
 *
 *
 * \section menu_sec Menu de l'application
 *  Le menu est découpé en sous menu de la manière suivante :
    <ul>
        <li>110 <-> Sous-menu Fonctionnalités de Base
        <ul><li>1   --> Négatif d'une image</li>
            <li>2   --> Transformation en niv de gris</li>
            <li>3   --> Seuillage</li>
            <li>4   --> Lisage NB</li>
            <li>5   --> Lisage Couleur</li>
        </ul></li>

	    <li>120 <-> Sous-menu Arbres quaternaire
	    <ul><li>6   --> Création Arbre NB</li>
            <li>7   --> Création Matrice à partir d'un arbre NB</li>
            <li>8   --> Création Arbre NG</li>
            <li>9   --> Création Matrice à partir d'un arbre NG</li>
            <li>10  --> Création Arbre RVB</li>
            <li>11  --> Création Matrice à partir d'un arbre RVB</li>
            <li>12  --> Zoom 2^-k</li>
            <li>13  --> Tous les niveaux de Zoom 2^-k</li>
            <li>15  --> Calcul Distance</li>
        </ul></li>

	    <li>130 <-> Sous-menu Stats et échantillonnage NB (v2)
	    <ul><li>21  --> Échantillonnage NB</li>
            <li>22  --> QuantificationNB</li>
            <li>23  --> Statistique NB</li>
            <li>24  --> Histogramme NB</li>
        </ul></li>

        <li>140 <-> Sous-menu Filtrages NB (v2)
        <ul><li>31  --> Filtre pondéré moyenneur</li>
            <li>32  --> Filtre pondéré Gaussien</li>
            <li>33  --> Filtre gradient Roberts</li>
            <li>34  --> Filtre gradient Prewitt</li>
            <li>35  --> Filtre gradient Sobel</li>
            <li>36  --> Filtre Laplacien</li>
            <li>37  --> Filtre médian</li>
            <li>38  --> Filtre morphologique dilatation</li>
            <li>39  --> Filtre morphologique érosion</li>
            <li>40  --> Filtre morphologique gradient</li>
        </ul></li>

        <li>150 <-> Sous-menu Chargement Rapide
        <ul><li>50  --> Chargement de toshy.bmp</li>
            <li>51  --> Chargement de hoodoos.bmp</li>
            <li>52  --> Chargement de horseshoe.bmp</li>
            <li>53  --> Chargement de nenuphar.bmp</li>
        </ul></li>

        <li>55  --> Chargement du fichier de votre choix</li>
        <li>60  --> Enregistrement</li>
        <li>61  --> Chargement du fichier d'enregistrement</li>
        <li>99  --> Retour</li>
        <li>0   --> Quitter</li>
    </ul>
    Les sous-menus, ne sont qu'un affichage. Vous n'avez besoin d'afficher un sous-menu pour lancer une action qui est l'intérieur d'un sous-menu.
 *
 *
 * \section utilisa_sec Utilisation de vos propres images
 *  Pour le traitement de vos propres images, elles doivent être au format BMP (24bits - R8 G8 B8).<br/>
    Puis être positionné dans le dossier racine du programme : "M1 - BONGIORNO - Projet\Programme".<br/>
    Attention plusieurs fonctions demandent des images carrées (n*n) de dimension de puissance deux.<br/><br/>
 *
 *
 * \section Sommaire_sec Sommaire
 *  \ref CIR3 : Documentation sur la partie effectué en CIR3<br/>
    \ref M1 : Documentation sur la version 2 du projet<br/>
 *
 *  <br/><br/><br/><br/>
 */


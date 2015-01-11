 /**
 * \file doxym1.c
 * \brief Documentation doxygen M1
 *
 * Pr�sentation du projet par une interface doxygen / HTML
 * Page pour le projet en M1
 *
 * \author Charles Bong.
 * \date 08 novembre 2014
 */


 /*! \page M1 Reprise du projet - M1
 * \section introm1_sec Introduction
 *  Dans le cadre de nos cours de Traitement d'Images en M1 (4�me ann�e), il nous a �t� demand� de reprendre ce projet pour y ajouter de nouvelles fonctionnalit�s.<br/>
    Il a �t� fait une fois de plus sous la direction de Mme ROBERT-INACIO, notre professeur de vision industrielle.<br/>
 *
 *
 * \section echan_sec �chantillonnage
 * \subsection echan_traitement_sec Traitement
 *  Cette fonctionnalit� permet de sous-�chantillonner une image en niveau de gris en rempla�ant un carr� de n*n pixels par un pixel.<br/>
    Pour cela, je parcours la matrice de mon image de n pixels en n pixels, et je colore cette ensemble de pixel par la valeur moyenne du groupement.
 *
 *
 * \subsection echan_resul_sec Comparaison des r�sultats
 *  <img height="500px" alt="ComparaisonEchantillonnage" src="images/CompaEchan.png">
    <SMALL><a href="images/CompaEchan.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \section quan_sec Quantification
 * \subsection quan_traitement_sec Traitement
 *  La quantification permet de passer de 256 niveaux de gris, � n niveau de gris avec ( 1 < n < 256).<br/>
    Pour r�aliser cette fonctionnalit�, je d�coupe mes 256 niveau en palier.
    Pour chaque pixels, je regarde de quel palier (celui inf�rieur ou sup�rieur) il se situe le plus proche.
 *
 *
 * \subsection quan_resul_sec Comparaison des r�sultats
 *  <img height="500px" alt="ComparaisonQuantification" src="images/CompaQuanti.png">
    <SMALL><a href="images/CompaQuanti.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \section Stats_sec Statistiques & Histogramme
 * \subsection Stats_Stats_sec Statistiques
 *  Pour la r�alisation des statistiques, j'effectue les op�rations suivantes :<br/>
    Moyenne = somme des valeurs des pixels / nb de pixels<br/>
    Variance = somme des diff�rences au carr� entre la valeur du pixel et la moyenne / nb de pixels<br/>
    �cart-type =  racine carr� de la variance.<br/>
    <br/>
    Pour l'image que j'ai l'habitude d'utiliser, voici les r�sultats trouv�s : <br/>
    <CODE>
        moyenne : 201<br/>
        variance : 1802<br/>
        �cart-type : 42.449971<br/>
    </CODE>
 *
 *
 * \subsection Stats_histo_sec Histogramme
 *  L'histogramme est un graphique repr�sentant la distribution des nuances de gris.<br/>
    Pour cela, je compte le nombre de pixel de chaque couleur, que je divise par la valeur la plus haute pour faire une mise � l'�chelle.
    Je met ensuite mes r�sultats dans une matrice image o� chaque colonne de pixels correspondra � une valeur des 256 nuances de gris.<br/>
    <br/>
    Voici l'histogramme de l'image que j'utilise habituellement : <br/>
    <img alt="Histogramme" src="images/histogramme.bmp">
    <SMALL><a href="images/histogramme.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \section Convol_sec Filtrages par convolution
 *  Lors d'un filtrage par convolution, nous appliquons une grille de pond�ration � chaque pixels.
    Cette grille nous donne les coefficients � appliquer aux pixels du voisinage de celui d'origine.
    Afin de rester dans la dynamique des couleurs de l'image (0-255), il faut diviser le r�sultat de l'op�ration par la somme des valeurs
    lorsque cette somme n'est pas �gale � z�ro (ex : Moyenneur = /9  ;  Gauss = /16).<br/>
 *
 * \subsection Convol_grille_sec Listes des grilles de filtrages
 *  Voici des grilles de coefficient des diff�rent outils de filtrage et leur r�sultat.
    <table><caption>Pond�ration Moyenneur</caption>
            <tr><td>1</td><td>1</td><td>1</td></tr>
            <tr><td>1</td><td>1</td><td>1</td></tr>
            <tr><td>1</td><td>1</td><td>1</td></tr></table>
    <img alt="FiltrePondeurMoyenneur" src="images/filtreMoy.bmp">
    <SMALL><a href="images/filtreMoy.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>

    <table><caption>Pond�ration de Gauss</caption>
            <tr><td>1</td><td>2</td><td>1</td></tr>
            <tr><td>2</td><td>4</td><td>2</td></tr>
            <tr><td>1</td><td>2</td><td>1</td></tr></table>
    <img alt="FiltrePondeurGauss" src="images/filtreGauss.bmp">
    <SMALL><a href="images/filtreGauss.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>

    <table><caption>Pond�ration de Roberts</caption>
            <tr><td>0</td><td>0</td><td>0</td></tr>
            <tr><td>1</td><td>-1</td><td>0</td></tr>
            <tr><td>0</td><td>0</td><td>0</td></tr></table>
    <img alt="FiltreGradientRoberts" src="images/filtreRoberts.bmp">
    <SMALL><a href="images/filtreRoberts.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>

    <table><caption>Pond�ration de Prewitt</caption>
            <tr><td>-1</td><td>0</td><td>1</td></tr>
            <tr><td>-1</td><td>0</td><td>1</td></tr>
            <tr><td>-1</td><td>0</td><td>1</td></tr></table>
    <img alt="FiltreGradientPrewitt" src="images/filtrePrewitt.bmp">
    <SMALL><a href="images/filtrePrewitt.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>

    <table><caption>Pond�ration de Sobel</caption>
            <tr><td>-1</td><td>0</td><td>1</td></tr>
            <tr><td>-2</td><td>0</td><td>2</td></tr>
            <tr><td>-1</td><td>0</td><td>1</td></tr></table>
    <img alt="FiltreGradientSobel" src="images/filtreSobel.bmp">
    <SMALL><a href="images/filtreSobel.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>

    <table><caption>Laplacien</caption>
            <tr><td>-1</td><td>-1</td><td>-1</td></tr>
            <tr><td>-1</td><td> 8</td><td>-1</td></tr>
            <tr><td>-1</td><td>-1</td><td>-1</td></tr></table>
    <img alt="FiltreLaplacien" src="images/filtreLaplacien.bmp">
    <SMALL><a href="images/filtreLaplacien.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \section median_sec Filtre M�dian
 *  Il nous a �t� demand� de refaire un filtrage m�dian, en utilisant une grille outil avec des coefficients 0 ou 1,
    indiquant si le point correspondant doit �tre pris en consid�ration ou non.
    Pour cela, j'ai en partie r�utiliser les fonctions d�velopper en 3�me ann�e, le d�tail du traitement se trouve ici : \ref medNG_details_sec <br/>
    Voici la grille que j'ai utilis� et le r�sultat. Avec cette grille, cela revient � faire un filtre pond�r�s moyenneur.
    <table><caption>M�dian</caption>
            <tr><td>1</td><td>1</td><td>1</td></tr>
            <tr><td>1</td><td>1</td><td>1</td></tr>
            <tr><td>1</td><td>1</td><td>1</td></tr></table>
    <img alt="FiltreMedian" src="images/m�dian.bmp">
    <SMALL><a href="images/m�dian.bmp" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \section Morpho_sec Filtres Morphologique
 * Il nous a �t� demand� de r�aliser trois filtres morphologiques, la dilatation, l'�rosion et le gradient.<br/>
 *
 * \subsection Morpho_trait_sec Traitement algorithmique
 *  Pour chacun de ces traitements, je travaille de la mani�re suivante:<br/>
    Je passe � ma fonction l'image (sous forme d'un tableau � deux dimensions, de short int) accompagn� de sa longueur et largeur.
    De plus, je joins les dimensions de mon outils (la taille de traitement). Ici par d�faut j'utilise un carr� de 3*3 mais en traitement d'image,
    il est courant d'utiliser du 5*5.<br/>
    Je parcours chaque pixels de l'image, en �vitant les bordures pour pas d�border de l'image lors du traitement. Ces pixels deviendront noir, c'est un choix arbitraire.<br/>
    Ensuite pour chaque pixels � traiter, je regarde ceux aux alentours, la distance varie en fonction des dimensions de l'outil.<br/>
    J'applique le traitement � effectuer, puis sauvegarde ce nouveau pixel dans une nouvelle image (qui sera encore un tableau � deux dimensions).
    Une fois l'ensemble des pixels parcouru, je reviens la nouvelle image aux programme principales,
    qui vous laissera le choix d'effectuer de nouveaux traitements ou de la sauvegarder.<br/>
 *
 * \subsection Morpho_expli_sec Explications
 *  Afin de mieux comprendre le rendu de ces filtres, voici quelques explications sur ceux-ci.<br/>
    Le premier, la dilatation consiste � pour chaque pixel, prendre la plus grande valeur entre le pixel et ceux aux alentours.
    Ce traitement a pour effet de faire ressortir les couleurs claire de l'image.<br/>
    Le deuxi�me, l'�rosion, au contraire, prendra la valeur inf�rieure. Il en r�sultera que les couleurs sombre ressortiront.<br/>
    Le troisi�me, le gradient, effectue la soustraction entre la dilatation et l'�rosion.
    On obtient alors, une approximation des contours internes et externes des objets de l'image originale<br/>
    <br/>
    Voici un comparatif entre les diff�rents filtrages : <br/>
    <img width="500px" alt="CompaMorpho" src="images/CompaMorpho.png">
    <SMALL><a href="images/CompaMorpho.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
    <br/>
    Voici maintenant une comparaison entre un traitement au voisinage de 3 et de 5 (sur l'�rosion) : <br/>
    <img width="500px" alt="CompaMorpho" src="images/CompaOutil.png">
    <SMALL><a href="images/CompaOutil.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 * <br/><br/><br/><br/>
 *
 */


 /**
 * \file doxycir3.c
 * \brief Documentation doxygen CIR3
 *
 * Présentation du projet par une interface doxygen / HTML
 * Page pour le projet en CIR3
 *
 * \author Charles Bong.
 * \date 12 novembre 2013
 */


 /*! \page CIR3 Projet d'Algorithme - CIR_3
 * \section introcir3_sec Introduction
 * Ce projet s'inscrit dans le cadre de notre formation d'ingénieur, en troisième année du Cycle d'Informatique & Réseau (CIR).<br/>
    Il a été fait sous la direction de Mme ROBERT-INACIO, notre professeur d'Algorithme Avancée.<br/>
 *
 *
 * \section obj_sec Objectifs
 * Le projet a été découpé en plusieurs parties.<br/>
 *\subsection p1_obj_sec Première partie
 * Cette partie correspond aux fonctions de gestion des images BMP, comme convertir une image en trois matrices (RGB).<br/>
 *\subsection p2_obj_sec Seconde partie
 * Cette partie correspond aux fonctions de base du traitement des matrices (RGB ou NG), comme :
     <ul><li>Négatif d'une image</li>
         <li>Transformation en niveau de gris</li>
         <li>Seuillage</li>
         <li>Filtre médian n*n NG</li>
         <li>Filtre médian n*n couleurs</li></ul>
 *\subsection p3_obj_sec Troisième partie
 * Cette partie correspond aux fonctions de traitement des matrices par des arbres quaternaire, d'image de dimension puissance 2.<br/>
    Cela consiste à convertir une matrice en arbre quaternaire puis à revenir sous forme de matrice.
    On doit faire ceci en NB, en NG et en couleur.<br/>
 *\subsection p4_obj_sec Quatrième partie
 * On doit réaliser un zoom de facteur 2^(-k).<br/>
    Cette partie est à réalisé sur des arbres quaternaires NG et RGB.<br/>
    De plus, nous une fonction qui va réaliser tout les niveaux de zoom possible.
 *\subsection p5_obj_sec Cinquième partie
 * C'est la partie personnelle du projet.<br/>
    Les images traitées ici sont binaires: chaque pixel est soit blanc (255) soit noir (0),
    pour obtenir un tel résultat, on peut appliquer un seuil à des images NG.<br/>
    Le traitement effectué ici va pour chaque pixel d'une image le transformer en niveau de noir
    proportionnellement à sa distance d'un pixel blanc. Ainsi un pixel blanc sera noir, un pixel noir très loin d'un pixel blanc sera blanc.<br/>
 *
 *
 * \section exmp_sec Exemples - Comparatifs
 * Dans cette section, je vais présenter des exemples de traitements fait avec le programme.<br/>
 * Dans certain cas, et pour des raisons de présentation, les images sont redimensionnées à l'affichage.
    Je vous invite donc à cliquer sur le lien en dessous de l'image, pour les voir en taille réel.<br/>
 *
 *
 *\subsection liss_exmp_sec Lissage Couleur
 *J'ai repris l'image du nénuphar (1024*1024) et avec un logiciel de retouche photo
    j'ai tracé un trait (1px) blanc sur l'image.
    J'ai ensuite traité mon image avec la fonction lissage couleur de mon programme.
    Après le lissage, le trait a disparu.<br/>
    <img height="500px" alt="Compalissage" src="images/compalissage.png">
    <SMALL><a href="images/compalissage.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \subsection quatcou_exmp_sec Quaternaire Couleur
 * Voici des tests sur la partie des arbres quaternaires couleurs et la restitution avec des niveaux de profondeur par rapport à la racine, différents.
    Pour ces tests, j'ai utilisé une image de 256px*256px.<br/>
    Les images qui vont suivre on été on reçu les traitements suivant:
    <ul><li>Conversion en trois matrices (RGB)</li>
        <li>Conversion en arbre quaternaire
        <ul><li>Calcul de la valeur médiane du carré <a href="#medRGB_details_sec">(voir Médiane Couleur)</a></li>
            <li>Découpage à l'aide d'une valeur médiane suivant un &epsilon; <a href="#hom_details_sec">(voir Homogénéité d'un carré)</a></li></ul></li>
        <li>Reconversion en matrices RGB suivant un niveau 'nn' <a href="#matquat_details_sec">(voir Restitution Matrice)</a></li>
        <li>Restitution en image bmp</li>
    </ul>
    <br/>
    Voici le comparatif avec &epsilon; = 90
    <img height="768px" alt="CompaEpi90" src="images/ToshCompaEpsi(90).png">
    <SMALL><a href="images/ToshCompaEpsi(90).png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
    Voici le même travail avec &epsilon; = 5
    <img height="768px" alt="CompaEpi5" src="images/ToshCompaEpsi(5).png">
    <SMALL><a href="images/ToshCompaEpsi(5).png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \subsection epsi_exmp_sec Epsilon
 * Lors du calcul de l'homogénéité d'un carré de l'arbre quaternaire (NG ou RGB), nous devons vérifier si la différence de couleur est inférieure à un &epsilon;.<br/>
    Ce dernier est fixé en dur dans le programme.<br/>
    Plus il est élevé, moins l'image sera précise.<br/>
    Voici un comparatif de la même image traitée avec des &epsilon; différents.
    <img alt="CompaEp" src="images/ToshCompaEpsi.png">
    <SMALL><a href="images/ToshCompaEpsi.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 *
 * \subsection calculdist_exmp_sec Calcul de distance
 * J'ai utilisé une image bmp de 400px*400px, similaire à celle montrée dans l'énoncé.<br/>
    Après avoir effectué le traitement du calcul de distance (algorithme donné dans l'énoncé),
    Voici ce que l'on obtient avec l'image d'origine (img 1), ce n'est pas le résultat souhaité .<br/>
    Pour obtenir des résultats plus proches de ce que l'on attend,
    J'ai ensuite retenté l'expérience avec le négatif de cette image (img 2).<br/>
    <img height="500px" alt="CompaCroix" src="images/compacroix.png">
    <SMALL><a href="images/compacroix.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \section details_sec Détails
 * Voici des explications sur les traitements effectués.
 *
 *
 * \subsection liss_details_sec Lissage
 * Lors du lissage d'une image, le but est de gommer les irrégularités sur une image.<br/>
    Pour cela, pour chaque pixel de l'image, nous allons regarder si les pixels proches ont la même couleur.<br/>
    Si une couleur diffère trop par rapport à ces voisins, on la remplace par une des couleurs voisines.<br/>
    L'inconvénient de cette méthode est de ne pas pouvoir traiter les bords de l'image. Ici, nous avons choisi de mettre une bordure noire.<br/>
 *
 *
 * \subsection medNG_details_sec Calcul Médiane NG
 * Pour obtenir la valeur médiane, on va parcourir la matrice entre les coordonnées x0-x1 et y0-y1.<br/>
    Nous récupérons ainsi toutes couleurs des pixels du carré, on les place ensuite dans un tableau de dimension ((x1-x0)*(y1-y0)).<br/>
    Après avoir trié le tableau par ordre croissant, nous récupérons la valeur se trouvant au milieu du tableau.<br/>
    Ainsi à la différence de la valeur moyenne, nous obtenons une valeur existante dans notre matrice.<br/>
 *
 *
 * \subsection medRGB_details_sec Calcul Médiane Couleur
 * <a class="quaternaire_8c.html" href="quaternaire_8c.html">Voir le détail de la fonction.</a><br/>
    Durant cette étape, on va parcourir les matrices (RGB) entre les coordonnées x0-x1 et y0-y1.<br/>
    Pour chaque case, on calculera la distance entre les couleurs deux à deux.<br/>
    Ainsi, pour chaque pixel de l'image, on parcourt une nouvelle fois l'image entre x0-x1 et y0-y1,
    et effectuons le calcul suivant:<br/>
    sqrt( (matriceR[k][l]-matriceR[i][j])² + (matriceG[k][l]-matriceG[i][j])² + (matriceB[k][l]-matriceB[i][j])² )<br/>
    avec i et k variant entre x0 et x1, j et l  variant entre y0 et y1.<br/>
    <br/>
    Dans un deuxième temps, et dans le but d'éviter une redondance de calcul pour gagner en temps de traitements, j'ai utilisé une optimisation;<br/>
    Généralement dans une image, les pixels ayant la même couleur sont proches (cote à cote).<br/>
    Ainsi avant de refaire une boucle et le calcul qui en suit d'un pixel, je vérifie si un pixel ayant la même couleur se trouve à coté,
    et si c'est le cas, je récupère la valeur du calcul directement.
    On obtient ainsi des résultats dans des délais plus courts.<br/>
 *
 *
 * \subsection hom_details_sec Homogénéité d'un carré
 * Lorsque de la création de l'arbre, nous devons calculer pour chaque nœud la valeur médiane.
    Si cette valeur est homogène par rapport au carré, le nœud est une feuille. Sinon, on découpe le carré en quatre, et on refait le traitement.<br/>
    La question de l'homogénéité est différente suivant les cas:
    Pour une image binaire (NB) : un carré est dit homogène si tous les pixels qui le constituent sont soit blancs soit noirs.<br/>
    Pour une image en niveau de gris (NG) : il faut que la différence entre la couleur de tous les pixels et la valeur médiane
    soit inférieure à un certain &epsilon;.<br/>
    Pour une image en couleur (RGB) : même méthode mais en prend en compte la répartition spatiale des couleurs.<br/>
 *
 *
 * \subsection matquat_details_sec Création matrice
 * Pour la restitution d'une matrice à partir d'un arbre quaternaire, nous utilisons la méthode suivante.<br/>
    L'utilisateur demande un niveau de profondeur souhaité (le nn).
    Nous allons ensuite parcourir l'arbre jusqu'a au niveau demandé, et afficher les couleurs médianes des nœuds.<br/>
    Si le chiffre entré est plus grand que le niveau de profondeur maximum, nous nous arrêtons sur les feuilles de l'arbre.<br/>
    Ainsi 0 donne la racine de l'arbre, 1 les quatre fils de la racine, etc ...<br/>
    De plus, pour -1 nous affichons le niveau maximum de l'arbre, c'est à dire toutes les feuilles de ce dernier.<br/>
 *
 *
 * \subsection zoom_details_sec Le Zoom
 * Cette partie est très similaire à la restitution d'arbre quaternaire.
    Ici la notion de niveau de profondeur par rapport à la racine est remplacer par celle du niveau de zoom.
    Nous demandons à l'utilisateur le niveau de zoom souhaité, nous soustrayons le nombre donné à la profondeur maximum de l'arbre,
    pour obtenir le niveau de profondeur par rapport à la racine.<br/>
    Nous utilisons ensuite les fonctions de la partie précédente pour la création d'une matrice à partir d'un arbre.

 *
 * \section concl_sec Conclusion
 * J'ai pris beaucoup de plaisir à réaliser ce projet, aussi bien la partie technique, que la partie documentation.<br/>
    J'ai beaucoup appris de ce projet sur la gestion et le traitement d'image.<br/>
    Ce travail nous a aussi permis de mettre en pratique la gestion des arbres en algorithme.<br/>
 * <br/><br/><br/><br/>
 *
 *
 *
 */


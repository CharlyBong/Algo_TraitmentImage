 /**
 * \file doxycir3.c
 * \brief Documentation doxygen CIR3
 *
 * Pr�sentation du projet par une interface doxygen / HTML
 * Page pour le projet en CIR3
 *
 * \author Charles Bong.
 * \date 12 novembre 2013
 */


 /*! \page CIR3 Projet d'Algorithme - CIR_3
 * \section introcir3_sec Introduction
 * Ce projet s'inscrit dans le cadre de notre formation d'ing�nieur, en troisi�me ann�e du Cycle d'Informatique & R�seau (CIR).<br/>
    Il a �t� fait sous la direction de Mme ROBERT-INACIO, notre professeur d'Algorithme Avanc�e.<br/>
 *
 *
 * \section obj_sec Objectifs
 * Le projet a �t� d�coup� en plusieurs parties.<br/>
 *\subsection p1_obj_sec Premi�re partie
 * Cette partie correspond aux fonctions de gestion des images BMP, comme convertir une image en trois matrices (RGB).<br/>
 *\subsection p2_obj_sec Seconde partie
 * Cette partie correspond aux fonctions de base du traitement des matrices (RGB ou NG), comme :
     <ul><li>N�gatif d'une image</li>
         <li>Transformation en niveau de gris</li>
         <li>Seuillage</li>
         <li>Filtre m�dian n*n NG</li>
         <li>Filtre m�dian n*n couleurs</li></ul>
 *\subsection p3_obj_sec Troisi�me partie
 * Cette partie correspond aux fonctions de traitement des matrices par des arbres quaternaire, d'image de dimension puissance 2.<br/>
    Cela consiste � convertir une matrice en arbre quaternaire puis � revenir sous forme de matrice.
    On doit faire ceci en NB, en NG et en couleur.<br/>
 *\subsection p4_obj_sec Quatri�me partie
 * On doit r�aliser un zoom de facteur 2^(-k).<br/>
    Cette partie est � r�alis� sur des arbres quaternaires NG et RGB.<br/>
    De plus, nous une fonction qui va r�aliser tout les niveaux de zoom possible.
 *\subsection p5_obj_sec Cinqui�me partie
 * C'est la partie personnelle du projet.<br/>
    Les images trait�es ici sont binaires: chaque pixel est soit blanc (255) soit noir (0),
    pour obtenir un tel r�sultat, on peut appliquer un seuil � des images NG.<br/>
    Le traitement effectu� ici va pour chaque pixel d'une image le transformer en niveau de noir
    proportionnellement � sa distance d'un pixel blanc. Ainsi un pixel blanc sera noir, un pixel noir tr�s loin d'un pixel blanc sera blanc.<br/>
 *
 *
 * \section exmp_sec Exemples - Comparatifs
 * Dans cette section, je vais pr�senter des exemples de traitements fait avec le programme.<br/>
 * Dans certain cas, et pour des raisons de pr�sentation, les images sont redimensionn�es � l'affichage.
    Je vous invite donc � cliquer sur le lien en dessous de l'image, pour les voir en taille r�el.<br/>
 *
 *
 *\subsection liss_exmp_sec Lissage Couleur
 *J'ai repris l'image du n�nuphar (1024*1024) et avec un logiciel de retouche photo
    j'ai trac� un trait (1px) blanc sur l'image.
    J'ai ensuite trait� mon image avec la fonction lissage couleur de mon programme.
    Apr�s le lissage, le trait a disparu.<br/>
    <img height="500px" alt="Compalissage" src="images/compalissage.png">
    <SMALL><a href="images/compalissage.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \subsection quatcou_exmp_sec Quaternaire Couleur
 * Voici des tests sur la partie des arbres quaternaires couleurs et la restitution avec des niveaux de profondeur par rapport � la racine, diff�rents.
    Pour ces tests, j'ai utilis� une image de 256px*256px.<br/>
    Les images qui vont suivre on �t� on re�u les traitements suivant:
    <ul><li>Conversion en trois matrices (RGB)</li>
        <li>Conversion en arbre quaternaire
        <ul><li>Calcul de la valeur m�diane du carr� <a href="#medRGB_details_sec">(voir M�diane Couleur)</a></li>
            <li>D�coupage � l'aide d'une valeur m�diane suivant un &epsilon; <a href="#hom_details_sec">(voir Homog�n�it� d'un carr�)</a></li></ul></li>
        <li>Reconversion en matrices RGB suivant un niveau 'nn' <a href="#matquat_details_sec">(voir Restitution Matrice)</a></li>
        <li>Restitution en image bmp</li>
    </ul>
    <br/>
    Voici le comparatif avec &epsilon; = 90
    <img height="768px" alt="CompaEpi90" src="images/ToshCompaEpsi(90).png">
    <SMALL><a href="images/ToshCompaEpsi(90).png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
    Voici le m�me travail avec &epsilon; = 5
    <img height="768px" alt="CompaEpi5" src="images/ToshCompaEpsi(5).png">
    <SMALL><a href="images/ToshCompaEpsi(5).png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \subsection epsi_exmp_sec Epsilon
 * Lors du calcul de l'homog�n�it� d'un carr� de l'arbre quaternaire (NG ou RGB), nous devons v�rifier si la diff�rence de couleur est inf�rieure � un &epsilon;.<br/>
    Ce dernier est fix� en dur dans le programme.<br/>
    Plus il est �lev�, moins l'image sera pr�cise.<br/>
    Voici un comparatif de la m�me image trait�e avec des &epsilon; diff�rents.
    <img alt="CompaEp" src="images/ToshCompaEpsi.png">
    <SMALL><a href="images/ToshCompaEpsi.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 *
 * \subsection calculdist_exmp_sec Calcul de distance
 * J'ai utilis� une image bmp de 400px*400px, similaire � celle montr�e dans l'�nonc�.<br/>
    Apr�s avoir effectu� le traitement du calcul de distance (algorithme donn� dans l'�nonc�),
    Voici ce que l'on obtient avec l'image d'origine (img 1), ce n'est pas le r�sultat souhait� .<br/>
    Pour obtenir des r�sultats plus proches de ce que l'on attend,
    J'ai ensuite retent� l'exp�rience avec le n�gatif de cette image (img 2).<br/>
    <img height="500px" alt="CompaCroix" src="images/compacroix.png">
    <SMALL><a href="images/compacroix.png" TARGET=_BLANK>(voir l'image)</a></SMALL><br/>
 *
 *
 * \section details_sec D�tails
 * Voici des explications sur les traitements effectu�s.
 *
 *
 * \subsection liss_details_sec Lissage
 * Lors du lissage d'une image, le but est de gommer les irr�gularit�s sur une image.<br/>
    Pour cela, pour chaque pixel de l'image, nous allons regarder si les pixels proches ont la m�me couleur.<br/>
    Si une couleur diff�re trop par rapport � ces voisins, on la remplace par une des couleurs voisines.<br/>
    L'inconv�nient de cette m�thode est de ne pas pouvoir traiter les bords de l'image. Ici, nous avons choisi de mettre une bordure noire.<br/>
 *
 *
 * \subsection medNG_details_sec Calcul M�diane NG
 * Pour obtenir la valeur m�diane, on va parcourir la matrice entre les coordonn�es x0-x1 et y0-y1.<br/>
    Nous r�cup�rons ainsi toutes couleurs des pixels du carr�, on les place ensuite dans un tableau de dimension ((x1-x0)*(y1-y0)).<br/>
    Apr�s avoir tri� le tableau par ordre croissant, nous r�cup�rons la valeur se trouvant au milieu du tableau.<br/>
    Ainsi � la diff�rence de la valeur moyenne, nous obtenons une valeur existante dans notre matrice.<br/>
 *
 *
 * \subsection medRGB_details_sec Calcul M�diane Couleur
 * <a class="quaternaire_8c.html" href="quaternaire_8c.html">Voir le d�tail de la fonction.</a><br/>
    Durant cette �tape, on va parcourir les matrices (RGB) entre les coordonn�es x0-x1 et y0-y1.<br/>
    Pour chaque case, on calculera la distance entre les couleurs deux � deux.<br/>
    Ainsi, pour chaque pixel de l'image, on parcourt une nouvelle fois l'image entre x0-x1 et y0-y1,
    et effectuons le calcul suivant:<br/>
    sqrt( (matriceR[k][l]-matriceR[i][j])� + (matriceG[k][l]-matriceG[i][j])� + (matriceB[k][l]-matriceB[i][j])� )<br/>
    avec i et k variant entre x0 et x1, j et l  variant entre y0 et y1.<br/>
    <br/>
    Dans un deuxi�me temps, et dans le but d'�viter une redondance de calcul pour gagner en temps de traitements, j'ai utilis� une optimisation;<br/>
    G�n�ralement dans une image, les pixels ayant la m�me couleur sont proches (cote � cote).<br/>
    Ainsi avant de refaire une boucle et le calcul qui en suit d'un pixel, je v�rifie si un pixel ayant la m�me couleur se trouve � cot�,
    et si c'est le cas, je r�cup�re la valeur du calcul directement.
    On obtient ainsi des r�sultats dans des d�lais plus courts.<br/>
 *
 *
 * \subsection hom_details_sec Homog�n�it� d'un carr�
 * Lorsque de la cr�ation de l'arbre, nous devons calculer pour chaque n�ud la valeur m�diane.
    Si cette valeur est homog�ne par rapport au carr�, le n�ud est une feuille. Sinon, on d�coupe le carr� en quatre, et on refait le traitement.<br/>
    La question de l'homog�n�it� est diff�rente suivant les cas:
    Pour une image binaire (NB) : un carr� est dit homog�ne si tous les pixels qui le constituent sont soit blancs soit noirs.<br/>
    Pour une image en niveau de gris (NG) : il faut que la diff�rence entre la couleur de tous les pixels et la valeur m�diane
    soit inf�rieure � un certain &epsilon;.<br/>
    Pour une image en couleur (RGB) : m�me m�thode mais en prend en compte la r�partition spatiale des couleurs.<br/>
 *
 *
 * \subsection matquat_details_sec Cr�ation matrice
 * Pour la restitution d'une matrice � partir d'un arbre quaternaire, nous utilisons la m�thode suivante.<br/>
    L'utilisateur demande un niveau de profondeur souhait� (le nn).
    Nous allons ensuite parcourir l'arbre jusqu'a au niveau demand�, et afficher les couleurs m�dianes des n�uds.<br/>
    Si le chiffre entr� est plus grand que le niveau de profondeur maximum, nous nous arr�tons sur les feuilles de l'arbre.<br/>
    Ainsi 0 donne la racine de l'arbre, 1 les quatre fils de la racine, etc ...<br/>
    De plus, pour -1 nous affichons le niveau maximum de l'arbre, c'est � dire toutes les feuilles de ce dernier.<br/>
 *
 *
 * \subsection zoom_details_sec Le Zoom
 * Cette partie est tr�s similaire � la restitution d'arbre quaternaire.
    Ici la notion de niveau de profondeur par rapport � la racine est remplacer par celle du niveau de zoom.
    Nous demandons � l'utilisateur le niveau de zoom souhait�, nous soustrayons le nombre donn� � la profondeur maximum de l'arbre,
    pour obtenir le niveau de profondeur par rapport � la racine.<br/>
    Nous utilisons ensuite les fonctions de la partie pr�c�dente pour la cr�ation d'une matrice � partir d'un arbre.

 *
 * \section concl_sec Conclusion
 * J'ai pris beaucoup de plaisir � r�aliser ce projet, aussi bien la partie technique, que la partie documentation.<br/>
    J'ai beaucoup appris de ce projet sur la gestion et le traitement d'image.<br/>
    Ce travail nous a aussi permis de mettre en pratique la gestion des arbres en algorithme.<br/>
 * <br/><br/><br/><br/>
 *
 *
 *
 */


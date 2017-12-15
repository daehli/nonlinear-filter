# TP4 : Filtres non-linéaires

 Réaliser par:

**Daehli Nadeau-Otis**

# Introduction

Dans ce TP, nous avons travaillés avec les filtres non-linéaires. Ils sont exprimés par une combinaison non-linéaire sur chaque pixel. Ces filtres donnent de meilleurs résultats que les filtres linéaires conventionnels.

## Organisation du repository

Tous les tests et les fonctions ont été réalisées dans le [`mainFiltreMedian.cpp`](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/mainFiltreMedian.cpp#L2-7). Dans le haut du fichier se trouve la manière de compiler et d'exécuter le programme. Dans les fichiers hpp et h, l'objet représente l'élément structurant. Ainsi, la déclaration de la classe et des fonctions se retrouve dans le fichier [`structel.h`](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/structel.h) et tout ce qui concerne la logique des fonctions est dans le fichier [`structel.hpp`](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/structel.hpp).

Compte tenu que les images de nos applications sont des extensions `.pgm`, j'ai réalisé un petit fichier exécutable en `bash` qui convertit les images `.pgm` en `.png`. Au début du [fichier exécutable](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/convert.sh#L6-10) se trouve en commentaire les commandes pour l'utiliser.

## Filtre Médian

Le filtre médian permet de réduire le bruit d'une image tout en conservant les contours de celle-ci.

Original | [Matrice 1](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/mainFiltreMedian.cpp#L44-48) | [Matrice 2](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/mainFiltreMedian.cpp#L50-54) |
---  | ---  | ---  |
![alt text][barrat4] |  ![alt text][filtreMedian1]|  ![alt text][filtreMedian2] |

Ce filtre permet de minimiser les données aberrantes à l'aide d'un masque. La médiane et ses voisins sont triés dans le tableau par ordre croissant.
Prenons la matrice suivante:
```c++
    uint8_t matrice2[9]  = {
                            5,6,7,
                            6,111,8,
                            7,8,9
                        };
```

Nous pouvons voir que la matrice contient une seule valeur aberrante, qui est `111`. Pour poursuivre, trions le tableau.

```c++
    uint8_t matrice2[9]  = {
                            5,6,6,
                            7,7,8,
                            8,9,111
                        };
    // Sous forme d'une liste
    // |5|6|6|7|7|8|8|9|111|
```
Prenons la valeur médiane, dans notre cas `7`, remplaçons-la par la valeur aberrante.
La matrice résultante devient donc :
```c++
    uint8_t matrice2[9]  = {
                            5,6,7,
                            6,7,8,
                            7,8,9
                        };
```

## Morphologie mathématique

Dans cette partie du travail, j'ai appliqué des fonctions morphologiques à mes images. Les fonctions primaires de la morphologie sont l'érosion et la dilatation. Ces fonctions nous permettent d'appliquer l'ouverture et la fermeture.

### Élément structurant

Tout d'abord, il nous a été demandé de créer une nouvelle classe qui allait définir nos éléments structurants. Cette classe ce retrouve dans les fichiers [structel.h](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/structel.h) et [structel.hpp](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/structel.hpp). Ceux-ci nous permettent de créer des éléments structurants qui serviront à modifier les images à l'aide des opérations morphologiques.

Nous retrouvons dans cette classe trois constructeurs différents. Le premier est le constructeur par [default](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/structel.hpp#L4-15), le deuxième est le constructeur par [recopie](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/structel.hpp#L16-27) et le dernier est le constructeur qui servira à former un [cercle](https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/structel.hpp#L28-53) comme élément structurant.

Pour créer un élément structurant qui à la forme **carré**, nous devons l'appeler comme ceci:
```c++
Structel<uint8_t> carre2(2);
// Créer un Carré 2X2
carre2.print();
// Voici ce qui sort
//
// --------
//   0|  0|
// --------
//   0|  0|
// --------
//
Structel<uint8_t> carre3(3);
// Créer un Carré 3X3
carre3.print();
// Voici ce qui sort
// ------------
//   0|  0|  0|
// ------------
//   0|  0|  0|
// ------------
//   0|  0|  0|
// ------------
```

Nous pouvons faire les mêmes actions pour créer un cercle.
```c++
// 1. Le rayon du cercle
// 2. La grandeur de la matrice qui va être multiplée (10*10)
Structel<uint8_t> cercleR3(3,10);
// Créer un cercle de grandeur 10X10 avec un rayon de 3
cercleR3.print();
// Voici ce qui sort
// ----------------------------------------
//   1|  1|  1|  1|  1|  1|  1|  1|  1|  1|
// ----------------------------------------
//   1|  1|  1|  1|  1|  1|  1|  1|  1|  1|
// ----------------------------------------
//   1|  1|  1|  1|  0|  0|  0|  1|  1|  1|
// ----------------------------------------
//   1|  1|  1|  0|  1|  1|  1|  0|  1|  1|
// ----------------------------------------
//   1|  1|  0|  1|  1|  1|  1|  1|  0|  1|
// ----------------------------------------
//   1|  1|  0|  1|  1|  1|  1|  1|  0|  1|
// ----------------------------------------
//   1|  1|  0|  1|  1|  1|  1|  1|  0|  1|
// ----------------------------------------
//   1|  1|  1|  0|  1|  1|  1|  0|  1|  1|
// ----------------------------------------
//   1|  1|  1|  1|  0|  0|  0|  1|  1|  1|
// ----------------------------------------
//   1|  1|  1|  1|  1|  1|  1|  1|  1|  1|
// ----------------------------------------
```

La délimitation du cercle est représentée par des zéros dans la matrice. De plus, la matrice est paire. Il faut donc le recentrer.

### Dilatation
La dilatation consiste à prendre un filtre et une image et à vérifier si le filtre est bien cadré dans notre [image](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP4/src/bas_niveau.hpp#L261-269). Ensuite, il faut déplacer le filtre sur l'image afin de récupérer les données de cette image. Les valeurs présentes sur l'image via le filtre sont prises en note et elles sont envoyées dans le vecteur pour les trier.

Pour finir, l'élément maximum de notre vecteur trié est repris et assigné aux coordonnées de l'image.

`imageResultat(x,y) = *max_element(listeFenetre.begin(),listeFenetre.end());`

Original | `Matrice 2X2` |  `Matrice 4X4`| `Matrice 5X5` |
---  | ---  | ---  |  ---|
![alt text][barrat4] |  ![alt text][imageDilatationCarre2barrat4]|  ![alt text][imageDilatationCarre4barrat4] | ![alt text][imageDilatationCarre5barrat4]

### Érosion

L'érosion est le petit frère de la dilatation. Il fait aussi partie des fonctions fondamentales de la morphologie d'image. Le but est d'itérer à travers tous les pixels de l'image. Les pixels présents dans notre filtre sont récupérés et le minimum des valeurs voisines est sélectionné. Ces valeurs sont placées dans un verteur et sont triées par la suite.

`imageResultat(x,y) = *min_element(listeFenetre.begin(),listeFenetre.end());`

Original | `Matrice 2X2` |  `Matrice 4X4`| `Matrice 5X5` |
---  | ---  | ---  |  ---|
![alt text][soil] |  ![alt text][imageErosionCarre2soil]|  ![alt text][imageErosionCarre4soil] | ![alt text][imageErosionCarre5soil]

### Ouverture
L'ouverture par $`B`$ est la compositon de l'érosion par $`B`$ (élément structurant), suivi de la dilatation  par $`B`$.

$`A\circ B = (A\ominus B)\oplus B,`$

Le but de l'ouverture est d'éliminer les éléments présents dans l'image qui sont plus petit que l'élément structurant.

Original | `Matrice 2X2` |  `Matrice 3X3`|
---  | ---  | ---  
![alt text][barrat4] |  ![alt text][imageOuvertureCarre2barrat4]|  ![alt text][imageOuvertureCarre3barrat4]


### Fermeture
La fermeture consite à faire une dilatation par l'élément structurant $`B`$  suivi d'une érosion du même élément structurant.

$`A\bullet B = (A\oplus B)\ominus B,`$

Le but de la fermeture est de remplir le fond de l'image par l'élément structurant $`B`$

Original | `Matrice 2X2` |  `Matrice 3X3`|
---  | ---  | ---  
![alt text][barrat4] |  ![alt text][imageFermetureCarre2barrat4]|  ![alt text][imageFermetureCarre3barrat4]

### Gradient Externe

Le gradient externe permet de délimiter les contours externes d'une image. La formule appliquée pour trouver le gradient externe est la suivante:

$`P_B^+(F)=\delta_B(B)-F`$

`Matrice 2X2`  | Soil  | Barrat4 | Pcb_Gray |
---  | --- | --- | ---
Résultat: | ![alt text][imageGradientExternesoil] | ![alt text][imageGradientExternebarrat4]| ![alt text][imageGradientExternepcb_gray]

### Gradient Interne
Le gradient interne permet de détecter les contours internes d'une image. La formule appliquée pour trouver le gradient externe est la suivante:

$`P_B^- (F)=F-\epsilon_B(F)`$

`Matrice 2X2`  | Soil  | Barrat4 | Pcb_Gray |
---  | --- | --- | ---
Résultat: | ![alt text][imageGradientInternesoil] | ![alt text][imageGradientInternebarrat4]| ![alt text][imageGradientInternepcb_gray]


## Application

### Filtrage morphologique

La meilleure fonction morphologique pour faire disparaître les lignes noires tout en conservant les ronds est la `dilatation`. Elle permet de rehausser les éléments qui sont inclus dans l'élément structurant. J'ai choisi un élément structurant rond qui me permettra de conserver les points blancs tout en éléminant les lignes noires.

Original | `Matrice 2X2` |  `Matrice 3X3`| `Matrice 4X4` |
---  | ---  | ---  |  ---|
![alt text][pcb_gray] |  ![alt text][imageDilatationCarre2pcb_gray]|  ![alt text][imageDilatationCarre3pcb_gray] | ![alt text][imageDilatationCarre4pcb_gray]


### Restauration

Pour la restauration, j'ai hésité entre 2 fonctions morphologiques: le filtre médian ou la fermeture morphologie. Le filtre médian rend l'image trop floue et n'élimine pas tout à fait les lignes noires de l'image.

La fermeture va boucher les lignes noires de l'image. L'image va devenir embrouillée, mais les lignes noires vont disparaître.


Original | `Matrice 2X2` |  `Matrice 3X3`| `Matrice 4X4` |  `Matrice 5X5`
---  | ---  | ---  |  ---  |  ---|
![alt text][barrat4] | ![alt text][imageFermetureCarre2barrat4]|  ![alt text][imageFermetureCarre3barrat4] | ![alt text][imageFermetureCarre4barrat4]|  ![alt text][imageFermetureCarre5barrat4]

### Fissures
Un bon moyen pour remplir une image est la `fermeture` à l'aide d'un élément structurant adéquat. Dans l'application qui suit, j'ai choisi d'appliquer la fermeture sur les fissures dans l'image.

Le but de la fermeture est de boucher ou remplir les éléments de l'image qui sont plus petits que l'élément structurant. J'ai choisi le carré comme élément structuant. On peut voir la réduction des fissures lorsque l'élément structurant grossi.


Original | `Matrice 2X2` |  `Matrice 3X3`|
---  | ---  | ---  
![alt text][soil] |  ![alt text][imageFermetureCarre2soil]|  ![alt text][imageFermetureCarre3soil]

## Conclusion

Ce TP sur les filtres non-linéaires à été très instructif. Je n'avais jamais manipulé d'images avant ce cours. J'ai adoré faire l'érosion, la dilataion, l'ouverture et la fermeture. Nous avons vu toutes les notions mathématiques reliées à ces concepts en cours ce qui m'a permis de mieux comprendre.

Les filtres non-linéaires sont décrits par 2 fonctions morphologiques de base: la dilatation et l'érosion. Elles permettent de faire des actions sur des images à l'aide de l'élément structurant.

On peut ensuite réutiliser ces 2 fonctions pour faire d'autres actions. Par exemple, l'ouverture est la composition de l'érosion suivi d'une dilatation par un élément structurant. La fermeture est décrite par la composition de la dilatation suivi de l'érosion par un l'élément structurant.


[filtreMedian1]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/filtreMedian/filtreMedianResultat1.png
[filtreMedian2]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/filtreMedian/filtreMedianResultat2.png
[filtreMedian3]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/filtreMedian/filtreMedianResultat3.png
[barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/base/barrat4.png
[barrat2]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/base/barrat2.png
[imageDilatationCarre2barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre2barrat4.png
[imageDilatationCarre3barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre3barrat4.png
[imageDilatationCarre4barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre4barrat4.png
[imageDilatationCarre5barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre5barrat4.png
[pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/base/pcb_gray.png
[imageErosionCarre2pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageErosionCarre2pcb_gray.png
[imageErosionCarre3pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageErosionCarre3pcb_gray.png
[imageErosionCarre4pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageErosionCarre4pcb_gray.png
[imageErosionCarre4pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageErosionCarre4pcb_gray.png
[imageErosionCercleR7pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageErosionCercleR7pcb_gray.png
[imageDilatationCarre2pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageDilatationCarre2pcb_gray.png
[imageDilatationCarre3pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageDilatationCarre3pcb_gray.png
[imageDilatationCarre4pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageDilatationCarre4pcb_gray.png
[imageDilatationCarre4pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageDilatationCarre4pcb_gray.png
[imageDilatationCercleR7pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageDilatationCercleR7pcb_gray.png
[imageFermetureCarre2pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageFermetureCarre2pcb_gray.png
[imageFermetureCarre3pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageFermetureCarre3pcb_gray.png
[imageOuvertureCarre2pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageOuvertureCarre2pcb_gray.png
[imageOuvertureCarre3pcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageOuvertureCarre3pcb_gray.png
[imageGradientExternepcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageGradientExternepcb_gray.png
[imageGradientInternepcb_gray]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/pcbGray/imageGradientInternepcb_gray.png

[soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/base/soil.png
[imageErosionCarre2soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageErosionCarre2soil.png
[imageErosionCarre3soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageErosionCarre3soil.png
[imageErosionCarre4soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageErosionCarre4soil.png
[imageErosionCarre5soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageErosionCarre5soil.png
[imageErosionCercleR7soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageErosionCercleR7soil.png
[imageDilatationCarre2soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageDilatationCarre2soil.png
[imageDilatationCarre3soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageDilatationCarre3soil.png
[imageDilatationCarre4soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageDilatationCarre4soil.png
[imageDilatationCarre5soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageDilatationCarre5soil.png
[imageDilatationCercleR7soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageDilatationCercleR7soil.png
[imageFermetureCarre2soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageFermetureCarre2soil.png
[imageFermetureCarre3soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageFermetureCarre3soil.png
[imageOuvertureCarre2soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageOuvertureCarre2soil.png
[imageOuvertureCarre3soil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageOuvertureCarre3soil.png
[imageGradientExternesoil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageGradientExternesoil.png
[imageGradientInternesoil]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/soil/imageGradientInternesoil.png

[barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/base/barrat4.png
[imageErosionCarre2barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageErosionCarre2barrat4.png
[imageErosionCarre3barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageErosionCarre3barrat4.png
[imageErosionCarre4barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageErosionCarre4barrat4.png
[imageErosionCarre5barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageErosionCarre5barrat4.png
[imageErosionCercleR7barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageErosionCercleR7barrat4.png
[imageDilatationCarre2barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre2barrat4.png
[imageDilatationCarre3barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre3barrat4.png
[imageDilatationCarre4barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre4barrat4.png
[imageDilatationCarre5barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCarre5barrat4.png
[imageDilatationCercleR7barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageDilatationCercleR7barrat4.png
[imageFermetureCarre2barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageFermetureCarre2barrat4.png
[imageFermetureCarre3barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageFermetureCarre3barrat4.png
[imageFermetureCarre4barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageFermetureCarre4barrat4.png
[imageFermetureCarre5barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageFermetureCarre5barrat4.png
[imageOuvertureCarre2barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageOuvertureCarre2barrat4.png
[imageOuvertureCarre3barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageOuvertureCarre3barrat4.png
[imageOuvertureCarre4barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageOuvertureCarre4barrat4.png
[imageOuvertureCarre5barrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageOuvertureCarre5barrat4.png
[imageGradientExternebarrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageGradientExternebarrat4.png
[imageGradientInternebarrat4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP4/src/images/barrat4/imageGradientInternebarrat4.png

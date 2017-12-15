#ifndef structel.h
#define structel.h

template<class T>
class Structel {
    /// classe générique codant une image de type T. T doit être précisé lors de l'instanciation.
    /// Exemple :
    /// Structel<uint8_t> image(10,5);  // instancie une image dont les pixels sont de type uint8_t, de taille 10x5
    /// Structel<float> image(512,512); // instancie une image dont les pixels sont de type float, de taille 512x512

private:
    int dx; /// largeur
    int dy; /// hauteur
    int size; /// nombre de pixels de l'image
    T *data; /// Pointeur vers les valeurs des pixels de l'image. Les pixels sont stockés ligne par ligne.
             /// Les valeurs des pixels ont le type T, qui est le paramètre de la classe générique.
             /// Par exemple, dans le cas d'une image 8 bits, le type est Structel<uint8_t> et les valeurs ont toutes le type uint8_t

public:
    /// construit une image de taille (dx,dy) (par défaut 0) avec le buffer data (optionnel)

    /// Constructeur Carré
    Structel(int n);
    // Constructeur Cercle
    /// http://www.cplusplus.com/forum/beginner/16080/
    /// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
    Structel(const int r,const int n);

    /// constructeur de copie, permettant d'écrire Structel B; Structel A(B);
    Structel(const Structel& image);

    /// opérateur d'affectation permettant d'écrire Structel B; Structel A=B;
    Structel& operator=(const Structel&);


    ///destructeur : instructions pour désallouer les ressources de la classe (ici, le pointeur data)
    ~Structel();
    int getDx() const;
    int getDy() const;
    int getSize() const;
    T *getData() const;

    /// affiche sur la sortie standard la valeur des pixels de l'image
    void print() const;

    /// surcharge de l'opérateur () permettant d'écrire une valeur à la position (x,y) : A(x,y)=v
    T &operator()(const int &x, const int &y);
    /// surcharge de l'opérateur () permettant de lire une valeur à la position (x,y) : v=A(x,y)
    T operator()  (const int &x, const int &y) const;
};

#include "structel.hpp"

#endif /* structel.h */

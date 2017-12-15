/*

    Pour compiler le fichier
    g++ mainFiltreMedian.cpp -o mainFiltreMedian

    ./mainFiltreMedian images/base/boat.pgm

*/

#include <fstream>
#include <iostream>
#include "bas_niveau.hpp"
#include <cstdint>

int main(int argc,const char * argv[]){

    if (argc != 2){
        std::cout << "Vous devez appelez le programme " << argv[0] << " avec 2 arguments \n";
        std::cout<< "Par exemple : \n" << argv[0] << " boat.pgm \n";
        system("pause");
        exit(EXIT_FAILURE);
    }

    std::string imageEntre = argv[1];
    Image<uint8_t> image = readPGM(imageEntre);
    //
    Structel<uint8_t> carre2(2);
    Structel<uint8_t> carre3(3);
    Structel<uint8_t> carre4(4);
    Structel<uint8_t> carre5(5);
    //
    //
    // Structel<uint8_t> cercleR8(8,20);
    Structel<uint8_t> cercleR7(7,15);
    Structel<uint8_t> cercleR3(3,10);
    //
    // cercleR8.print();
    cercleR3.print();
    // cercleR7.print();
    // carre2.print();
    // carre3.print();
    // carre4.print();


    uint8_t matrice[9]  = {
                            120,87,20,
                            15,32,54,
                            60,1,5
                        };

    uint8_t matrice2[9]  = {
                            5,6,7,
                            6,111,8,
                            7,8,9
                        };

    uint8_t matrice3[9]  = {
                            54,7,16,
                            14,20,50,
                            4,1,5
                        };

    Image<uint8_t> fenetreMasque(3,3,matrice);
    Image<uint8_t> fenetreMasque2(3,3,matrice2);
    Image<uint8_t> fenetreMasque3(3,3,matrice3);

    // Filtre Médian
    Image<uint8_t> filtreMedianResultat1 = filtreMedian(image,fenetreMasque);
    Image<uint8_t> filtreMedianResultat2 = filtreMedian(image,fenetreMasque2);
    Image<uint8_t> filtreMedianResultat3 = filtreMedian(image,fenetreMasque3);



    // Érosion
    Image<uint8_t> imageErosionCarre2 = erosion(image,carre2);
    Image<uint8_t> imageErosionCarre3 = erosion(image,carre3);
    Image<uint8_t> imageErosionCarre4 = erosion(image,carre4);
    Image<uint8_t> imageErosionCarre5 = erosion(image,carre5);
    Image<uint8_t> imageErosionCercleR7 = erosion(image,cercleR7);

    // Dilatation
    Image<uint8_t> imageDilatationCarre2 = dilatation(image,carre2);
    Image<uint8_t> imageDilatationCarre3 = dilatation(image,carre3);
    Image<uint8_t> imageDilatationCarre4 = dilatation(image,carre4);
    Image<uint8_t> imageDilatationCarre5 = dilatation(image,carre5);
    Image<uint8_t> imageDilatationCercleR7 = dilatation(image,cercleR7);

    // Ouverture
    Image<uint8_t> imageOuvertureCarre2 = ouverture(image,carre2);
    Image<uint8_t> imageOuvertureCarre3 = ouverture(image,carre3);
    Image<uint8_t> imageOuvertureCarre4 = ouverture(image,carre4);
    Image<uint8_t> imageOuvertureCarre5 = ouverture(image,carre5);

    // Fermeture
    Image<uint8_t> imageFermetureCarre2 = fermeture(image,carre2);
    Image<uint8_t> imageFermetureCarre3 = fermeture(image,carre3);
    Image<uint8_t> imageFermetureCarre4 = fermeture(image,carre4);
    Image<uint8_t> imageFermetureCarre5 = fermeture(image,carre5);

    // Morphologie Externe
    Image<uint8_t> imageGradientExterne = gradientExterne(image,carre2);
    Image<uint8_t> imageGradientExterneCarre3 = gradientExterne(image,carre3);

    Image<uint8_t> imageGradientInterne = gradientInterne(image,carre2);
    Image<uint8_t> imageGradientInterneCarre3 = gradientInterne(image,carre3);


    // Filtre Médian
    // writePGM(filtreMedianResultat1,"images/filtreMedian/filtreMedianResultat1.pgm");
    // writePGM(filtreMedianResultat2,"images/filtreMedian/filtreMedianResultat2.pgm");
    // writePGM(filtreMedianResultat3,"images/filtreMedian/filtreMedianResultat3.pgm");
    //

    // Restauration

    // writePGM(filtreMedianResultat1,"images/filtreMedian/filtreMedianResultat1")

    // writePGM(imageErosionCarre2,"images/soil/imageErosionCarre2soil.pgm");
    // writePGM(imageErosionCarre3,"images/soil/imageErosionCarre3soil.pgm");
    // writePGM(imageErosionCarre4,"images/soil/imageErosionCarre4soil.pgm");
    // writePGM(imageErosionCarre5,"images/soil/imageErosionCarre5soil.pgm");
    // writePGM(imageErosionCercleR7,"images/soil/imageErosionCercleR7soil.pgm");
    // writePGM(imageDilatationCarre2,"images/soil/imageDilatationCarre2soil.pgm");
    // writePGM(imageDilatationCarre3,"images/soil/imageDilatationCarre3soil.pgm");
    // writePGM(imageDilatationCarre4,"images/soil/imageDilatationCarre4soil.pgm");
    // writePGM(imageDilatationCarre5,"images/soil/imageDilatationCarre5soil.pgm");
    // writePGM(imageDilatationCercleR7,"images/soil/imageDilatationCercleR7soil.pgm");
    // writePGM(imageOuvertureCarre2,"images/soil/imageOuvertureCarre2soil.pgm");
    // writePGM(imageOuvertureCarre3,"images/soil/imageOuvertureCarre3soil.pgm");
    // writePGM(imageOuvertureCarre4,"images/soil/imageOuvertureCarre4soil.pgm");
    // writePGM(imageOuvertureCarre5,"images/soil/imageOuvertureCarre5soil.pgm");
    // writePGM(imageFermetureCarre2,"images/soil/imageFermetureCarre2soil.pgm");
    // writePGM(imageFermetureCarre3,"images/soil/imageFermetureCarre3soil.pgm");
    // writePGM(imageFermetureCarre4,"images/soil/imageFermetureCarre4soil.pgm");
    // writePGM(imageFermetureCarre5,"images/soil/imageFermetureCarre5soil.pgm");
    writePGM(imageGradientExterne,"images/soil/imageGradientExternesoil.pgm");
    writePGM(imageGradientExterneCarre3,"images/soil/imageGradientExterneCarre3soil.pgm");
    writePGM(imageGradientInterne,"images/soil/imageGradientInternesoil.pgm");
    writePGM(imageGradientInterneCarre3,"images/soil/imageGradientInterneCarre3soil.pgm");





    // On fait le redimenssionnage
    //Image<double> imageFinale = convolution(image,matriceIdentite);

    //writePGM(imageFinale,imageSortie);

    return 0;
}

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include "../../TP2/image.h"
#include "structel.h"
//////////////////////////////
/*
    Déclaration des fonctions pour l'interpréteur
*/
//////////////////////////////
Image<uint8_t> quantize(Image<uint8_t> &imageSource,uint8_t puissance);
Image<uint8_t> readPGM(const std::string &inputFile);
int writePGM(const Image<uint8_t> &image, const std::string &outputFile);
Image<uint8_t> resampleNN(Image<uint8_t> &imageEntre,double r);
Image<uint8_t> resampleBilinearInterpolation(Image<uint8_t>& imageEntre, double r);
Image<double> convolution(Image<uint8_t>& imageEntre,Image<double>& masque );
Image<uint8_t> filtreMedian(Image<uint8_t>& imageEntre,Image<uint8_t>& masque);
Image<double> gaussienMask(double sigma);
void printVector(std::vector<uint8_t>& liste);

//////////////////////////////
/*

    Corps des fonctions

*/
//////////////////////////////

Image<uint8_t> quantize(Image<uint8_t> &imageSource, uint8_t puissance){

    Image<uint8_t> imageRetour(imageSource.getDx(),imageSource.getDy());
    // Formule pour obtenir les segments selon la puissance
    double segment = ( 255 / ((1 << (8-puissance)) - 1) );
    // On itère sur tout les pixels de l'image et on l'assigne dans le bon segment
    for (int y = 0;y<imageSource.getDy();y++){
        for(int x = 0; x<imageSource.getDy();x++){
            float ensemble = imageSource(x,y) >> puissance;
            imageRetour(x,y) = (int)(ensemble*segment);
        }
    }
    return imageRetour;
}
Image <uint8_t> readPGM(const std::string &inputFile)
{
    Image <uint8_t> result;
    std::ifstream file(inputFile);
    if(file.is_open()) {
        std::string line;
        std::getline(file,line);
        // only binary, greyscale PGM
        if(line=="P5") {
            int dx,dy,maxValue;
            std::getline(file,line);
            // remove comments beginning by '#'
            while(line[0]=='#')
                std::getline(file,line);
            std::stringstream ss(line);
            ss >> dx >> dy;
            std::getline(file,line);
            ss.clear();
            ss.str(line);
            ss>>maxValue;
            std::cout << "Reading header.\nFile "<<inputFile<< "\ndx : "  << dx << "\ndy : " <<dy << "\nmaxValue : " << maxValue << "\n";
            int size=dx*dy;
            uint8_t *buffer=new uint8_t[size];
            file.read((char *)buffer,size);
            Image <uint8_t> result(dx,dy,buffer);
            delete[] buffer;
            return result;

        }
        file.close();
    }

    return result;
}

int writePGM(const Image<uint8_t> &image, const std::string &outputFile)
{
    std::ofstream file(outputFile,std::ios_base::trunc  | std::ios_base::binary);
    if(file.is_open()) {
        std::string line;

        int dx=image.getDx();
        int dy=image.getDy();
        int size=dx*dy;

        file << "P5\n" << dx << " " << dy << "\n" << "255" ;
        file << "\n";

        file.write((char *)image.getData(),size);

        file << "\n";

        file.close();
    }
    else return -1;

    return 0;
}

Image<uint8_t> resampleNN(Image<uint8_t> &imageEntre,double r){

    // On dimensionne l'image selon le radio
    int nX = imageEntre.getDx() * r;
    int nY = imageEntre.getDy() * r;

    imageEntre.print();
    // On créer l'image
    Image<uint8_t> imageFinale(nX,nY);

    for(int y = 0; y<nY;y++){
        for(int x = 0;x<nX;x++){
            imageFinale(x,y) = imageEntre(int(x/r),int(x/r));
        }
    }

    imageFinale.print();
    return imageFinale;
}

Image<uint8_t> resampleBilinearInterpolation(Image<uint8_t>& imageEntre, double r){


    // Nouvelle taille pour l'image
    // nX valeur de X
    // nY valeur de Y
    int nX = imageEntre.getDx() * r;
    int nY = imageEntre.getDy() * r;

    // Création de l'image avec la nouvelle taille
    Image<uint8_t> imageRedi(nX,nY);

    // On parcours toute les pixels
    for(int y =0;y<nY;y++){
        for(int x = 0; x< nX;x++){

            // Pixel de départ, sans arrondie. d=double
            double dX = x/r;
            double dY = y/r;
            std::cout << "dX dY : " << dX << " " << dY << "\n";
            // Pixel arrondie avec la fonction floor. e=entier
            int eX = floor(dX);
            int eY = floor(dY);

            std::cout << "eX eY : " << eX << " " << eY << "\n";
            // On récupère les valeurs décimals, r = reste
            double rX = dX-eX;
            double rY = dY-eY;

            std::cout << "rX rY : " << rX << " " << rY << "\n";
            // Position Initiale. On suppose que la distance entre deux points consécutifs est de + 1
            int Qx1y1 = imageEntre(eX,eY);
            int Qx1y2 = imageEntre(eX,eY+1);
            int Qx2y1 = imageEntre(eX+1,eY);
            int Qx2y2 = imageEntre(eX+1,eY+1);

            std::cout << "Qx1y1 Qx1y2 Qx2y1 Qx2y2 : " << Qx1y1 << " " << Qx1y2 << " " << Qx2y1 << " " << Qx2y2 << "\n";


            int R1 = (int)((1 - rX) * (1 - rY) * Qx1y1 + (rX) * (1 - rY) * Qx2y1 + (1 - rX) * (rY) * Qx1y2);
            int R2 =(int)((1 - rX) * (rY) * Qx1y2 + (rX) * (rY) * Qx2y2);

            imageRedi(x,y) = R1+R2;

        }
    }

    return imageRedi;
}
Image<uint8_t> filtreMedian(Image<uint8_t>& imageEntre,Image<uint8_t>& masque){

    Image<uint8_t> imageSortie(imageEntre.getDx(),imageEntre.getDy());
    int dim = masque.getSize()/2;

    if ((dim%2)==0)
        dim++;
    // Mettre les elements de la
    std::vector<uint8_t> listeFenetre;
    // Parcours de l'image
    for(int x = 0;x<imageEntre.getDx();x++){
        for(int y = 0;y<imageEntre.getDy();y++){
            for(int i = -dim;i<=dim;i++){
                for(int j = -dim;j<=dim;j++){
                    int indeX = x+i;
                    int indeY = y+j;
                    // Débordement
                    if(indeX >= 0 && indeY >= 0 && indeX <= imageEntre.getDx()-1 && indeY <= imageEntre.getDy()-1){
                        listeFenetre.push_back(imageEntre(indeX,indeY));
                    }
                }
            }

            sort(listeFenetre.begin(),listeFenetre.end());
            int positionTrier = listeFenetre.size()/2;
            imageSortie(x,y) = listeFenetre.at(positionTrier);
            listeFenetre.clear();
        }
    }

    return imageSortie;
}

void printVector(std::vector<uint8_t>& liste){
    std::cout << "Contenu du vecteur \n";

    for(std::vector<uint8_t>::iterator it=liste.begin();it!=liste.end();it++){
        std::cout << *it << "\n";
    }
}

/*
    https://en.wikipedia.org/wiki/Erosion_(morphology)
    http://stackoverflow.com/questions/1472768/implementing-erosion-dilation-in-c-c#1473457
    http://blog.ostermiller.org/dilate-and-erode
*/
Image<uint8_t> erosion(Image<uint8_t> imageEntre,Structel<uint8_t> element){
    Image<uint8_t> imageResultat(imageEntre.getDx(),imageEntre.getDy());
    std::vector<uint8_t> listeFenetre;
    int N = element.getDx()/2;

    if((N%2)==0)
        N++;

    for(int x = 0; x<imageEntre.getDx();x++){
        for(int y = 0;y<imageEntre.getDy();y++){
            for(int i =0;i<element.getDx();i++){
                for(int j=0;j<element.getDy();j++){
                    if(x+i > 0 || y+j > 0 || x+i <= imageEntre.getDx()-1 || y+j <= imageEntre.getDy()-1){
                        listeFenetre.push_back(imageEntre(x+i-N,y+j-N));
                    }
                }
            }

            sort(listeFenetre.begin(),listeFenetre.end());

            imageResultat(x,y) = *min_element(listeFenetre.begin(),listeFenetre.end());

            listeFenetre.clear();
        }
    }
    return imageResultat;

}
/*
    https://en.wikipedia.org/wiki/Dilation_(morphology)
    http://stackoverflow.com/questions/1472768/implementing-erosion-dilation-in-c-c#1473457
    http://blog.ostermiller.org/dilate-and-erode
*/
Image<uint8_t> dilatation(Image<uint8_t> imageEntre,Structel<uint8_t> element){
    Image<uint8_t> imageResultat(imageEntre.getDx(),imageEntre.getDy());
    std::vector<uint8_t> listeFenetre;
    int N = element.getDx()/2;

    if((N%2)==0)
        N++;

    for(int x = 0; x<imageEntre.getDx();x++){
        for(int y = 0;y<imageEntre.getDy();y++){
            for(int i =0;i<element.getDx();i++){
                for(int j=0;j<element.getDy();j++){
                    if(x+i > 0 || y+j > 0 || x+i <= imageEntre.getDx()-1 || y+j <= imageEntre.getDy()-1){
                        listeFenetre.push_back(imageEntre(x+i-N,y+j-N));
                    }
                }
            }

            sort(listeFenetre.begin(),listeFenetre.end());

            imageResultat(x,y) = *max_element(listeFenetre.begin(),listeFenetre.end());

            listeFenetre.clear();
        }
    }
    return imageResultat;

}

/*
    https://en.wikipedia.org/wiki/Opening_(morphology)
*/
Image<uint8_t> ouverture(Image<uint8_t> imageEntre,Structel<uint8_t> element){

    Image<uint8_t> imageResultatErosion = erosion(imageEntre, element);
    Image<uint8_t> imageResultatErosionDilatation = dilatation(imageResultatErosion, element);
    return imageResultatErosionDilatation;

}
/*
    https://en.wikipedia.org/wiki/Closing_(morphology)
*/
Image<uint8_t> fermeture(Image<uint8_t> imageEntre,Structel<uint8_t> element){

    Image<uint8_t> imageResultatDilatation = dilatation(imageEntre, element);
    Image<uint8_t> imageResultatDilatationErosion = erosion(imageResultatDilatation, element);
    return imageResultatDilatationErosion;
}

/*

    Gradient Externe

*/
Image<uint8_t> gradientExterne(Image<uint8_t> imageEntre,Structel<uint8_t> element){

    Image<uint8_t> imageResultatGradientExterne(imageEntre.getDx(),imageEntre.getDy());
    Image<uint8_t> imageResultatDilatation = dilatation(imageEntre, element);
    Image<uint8_t> imageResultatErosion = erosion(imageEntre, element);

    for(int x = 0;x<imageEntre.getDx();x++){
        for(int y = 0;y<imageEntre.getDy();y++){
            imageResultatGradientExterne(x,y) = (imageResultatDilatation(x,y)-imageEntre(x,y));
        }
    }

    return imageResultatGradientExterne;
}
/*

    Gradient Interne

*/
Image<uint8_t> gradientInterne(Image<uint8_t> imageEntre,Structel<uint8_t> element){
    Image<uint8_t> imageResultatGradientInterne(imageEntre.getDx(),imageEntre.getDy());
    Image<uint8_t> imageResultatDilatation = dilatation(imageEntre, element);
    Image<uint8_t> imageResultatErosion = erosion(imageEntre, element);
    for(int x = 0;x<imageEntre.getDx();x++){
        for(int y = 0;y<imageEntre.getDy();y++){

            imageResultatGradientInterne(x,y) = (imageEntre(x,y)-imageResultatErosion(x,y));
        }
    }

    return imageResultatGradientInterne;
}

#include <iostream>
#include <cstring> // memcpy

    template<class T>
Structel<T>::Structel(const int n)
{
    this->dx=n;
    this->dy=n;
    this->size=dx*dy;
    this->data = new T[this->size];
    for(int i= 0; i<this->getSize();i++){
        this->data[i]=0;
    }
}

    template<class T>
Structel<T>::Structel(const Structel<T> &image)
{
    this->dx=image.dx;
    this->dy=image.dy;
    this->size=image.size;
    this->data=new T[dx*dy];
    for(int i=0; i<dx*dy; ++i) {
        this->data[i]=image.data[i];
    }

}
/*
    https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
*/
template<class T>
Structel<T>::Structel(const int r,const int n)
{
    printf("Dans le constructeur de cercle \n");
    int nx = n/2;
    int ny = n/2;
    this->dx=n;
    this->dy=n;
    this->size=dx*dy;
    this->data = new T[this->size];
    for(int t = 0;t<dx*dy;t++){
        this->data[t]=1;
    }
    for(int i = nx-r;i<= nx+r;i++){
        for(int j = ny-r;j<= ny+r ;j++){
            if (((nx-i)*(nx-i)+(ny-j)*(ny-j) <= r*r+sqrt(r)) && ((nx-i)*(nx-i)+(ny-j)*(ny-j) >= r*r-r)){
                int position = j*this->dx+i;
                this->data[position]=0;
            }
        }
    }

}

/*
template<class T>
Structel<T>::carre(const int& n) const
{
    this->dx=n;
    this->dy=n;
    this->size=dx*dy;
    this->data = new T[this->size];
    for(int i= 0; i<this.   getSize();i++){
        this->data[i]=0;
    }
}
*/
    template<class T>
Structel<T> &Structel<T>::operator=(const Structel<T> &image)
{
    if(this!=&image)
    {
        if(this->data!=0) {
            delete[] data;
            data=0;
        }
        this->dx=image.dx;
        this->dy=image.dy;
        this->size=dx*dy;
        this->data=new T[dx*dy];
        for(int i=0; i<this->size; i++) {
            this->data[i]=image.data[i];
        }
    }
    return *this;
}

    template<class T>
Structel<T>::~Structel()
{
    if(data!=0)
    {
        delete[] data;
    }
}

template<class T>
int Structel<T>::getDx() const
{
    return dx;
}

template<class T>
int Structel<T>::getDy() const
{
    return dy;
}

template<class T>
int Structel<T>::getSize() const
{
    return size;
}

template<class T>
T* Structel<T>::getData() const
{
    return data;
}


template<class T>
void Structel<T>::print() const
{

    for(int x=0; x<dx; x++) {
        std::cout.width(3);
        std::cout << "----";
    }
    std::cout << "\n";

    for(int y=0; y<dy; y++) {
        for(int x=0; x<dx; x++) {
            std::cout.width(3);
            std::cout << (double)(*this)(x,y) << "|";
        }
        std::cout << "\n";
        for(int x=0; x<dx; x++) {
            std::cout.width(3);
            std::cout << "----";
        }
        std::cout << "\n";
    }
}

    template<class T>
T &Structel<T>::operator()(const int &x, const int &y)
{
    return data[y*dx+x];
}

template<class T>
T Structel<T>::operator() (const int &x, const int &y) const
{
    return data[y*dx+x];
}

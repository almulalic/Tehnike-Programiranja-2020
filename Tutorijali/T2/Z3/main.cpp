//TP 2018/2019: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>

int main ()
{
    
    int brojElemenata;
    
    std::cout << "Unesite broj elemenata: ";
    std::cin >> brojElemenata;
    std::cout << std::endl;
    
    int brojUnosa = 0;
    
    std::complex<double> unos;
    std::complex<double> suma;
    
    while(brojUnosa != brojElemenata) {
        std::cout << "Z_" << ++brojUnosa << " = ";
        std::cin >> unos;
        suma+=1./unos;
    }
    
    suma = 1./suma;
    
    std::cout << std::endl;
    
    std::cout << "Paralelna veza ovih elemenata ima impedansu Z_ = " << suma <<".";
     
	return 0;
}
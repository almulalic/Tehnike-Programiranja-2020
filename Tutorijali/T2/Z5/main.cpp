//TP 2018/2019: Tutorijal 2, Zadatak 4
#include <iostream>
#include <complex>

int main ()
{
    
    int brojElemenata;
    
    std::cout << "Unesite broj elemenata: ";
    std::cin >> brojElemenata;
    std::cout << std::endl;
    
    int brojUnosa = 0;
    
    double prividniOtpor,fazniPomak;
    double sumaAO=0,sumaPO=0;
    
    std::complex<double> impedansa;
    std::complex<double> suma;
    
    while(brojUnosa != brojElemenata) {
        
        std::cout << "Z" << ++brojUnosa << " = ";
        std::cin >> prividniOtpor;
        impedansa.real(prividniOtpor);
        
        std::cout << "fi" << brojUnosa << " = ";
        std::cin >> fazniPomak;
        impedansa.imag(fazniPomak);
        
        suma+=1./impedansa;
        
    }
    
    suma = 1./suma;
    
    std::cout << std::endl;
    std::cout << "Paralelna veza ovih elemenata ima Z = " << suma.real() << " i fi = " << suma.imag() << ".";
    
	return 0;
}
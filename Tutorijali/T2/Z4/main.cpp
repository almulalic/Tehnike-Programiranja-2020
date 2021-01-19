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
    double aktivniOtpor,pasivniOtpor;
    
    std::complex<double> impedansa;
    std::complex<double> suma;
    
    while(brojUnosa != brojElemenata) {
        
        std::cout << "R" << ++brojUnosa << " = ";
        std::cin >> aktivniOtpor;
        impedansa.real(aktivniOtpor);
        
        std::cout << "X" << brojUnosa << " = ";
        std::cin >> pasivniOtpor;
        impedansa.imag(pasivniOtpor);
        
        suma+=1./impedansa;
        
        std::cout << std::endl;
    }
    
    suma = 1./suma;
    
    std::cout << std::endl;
    std::cout << "Paralelna veza ovih elemenata ima R = " << suma.real() << " i X = " << suma.imag() << ".";
    
	return 0;
}
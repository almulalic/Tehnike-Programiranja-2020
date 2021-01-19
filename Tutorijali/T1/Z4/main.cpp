//TP 2016/2017: Tutorijal 1, Zadatak 4
#include <iostream>
#include <cmath>

int main ()
{
    
    const double epsilon = 0.00001;
    double n;
    
    for(;;) {
        std::cout << "Unesite prirodan broj ili 0 za kraj: ";
        while(!(std::cin >> n) || n < 0 ||  n - (int)n >= epsilon) {
            std::cout << "Niste unijeli prirodan broj!" << std::endl << "Unesite prirodan broj ili 0 za kraj: ";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        }
        
        int unos = (int) n;
        
        if(unos == 0) {
            std::cout << "Dovidjenja!";
            return 0;
        }
        
        int suma = 0;
        
        for(int i=1;i<n;i++) {
            if(unos%i==0)
                suma+=i;
        }
        
        std::cout << "Broj " << n << " je ";
    
        if(suma < unos)
            std::cout << "manjkav!" << std::endl;
        else if (suma == unos)
            std::cout << "savrsen!" << std::endl;
        else if (suma > unos)
            std::cout << "obilan!" << std::endl;
    }
    
return 0;
}
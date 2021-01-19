//TP 2018/2019: Ispit 2, Zadatak 2
#include <iostream>
#include <deque>
#include <vector>
#include <cmath>
#include <iomanip>

//3 AT

template <typename TipElemenata>
std::vector<double> IzdvojiElemente (std::deque<TipElemenata> dek) {
    
    std::vector<double> rezultat;
    int brojac(1);
    
    for(int i=0;i<dek.size();i++) {
        if(brojac == 3) {
            rezultat.push_back(pow(dek.at(i),2));
            brojac=0;
        } else {
            if(dek.at(i) <= 0)
                throw std::logic_error("Element vektora negativan!");
            else
                rezultat.push_back(log(dek.at(i)));
        }
        brojac++;
    }
    
    return rezultat;
} 

int main ()
{

    int n;
    std::cout << "Unesite broj elemenata deka: ";
    std::cin >> n;
    
    std::deque<int> niz(n,0);
    
    int unos;
    std::cout << "Unesite elemente deka: ";
    for(int i=0;i<n;i++) {
        std::cin >> unos;
        niz.at(i) = unos;
    }
    
    try {
        std::vector<double> rezultat = IzdvojiElemente(niz);
        
        std::cout << "Rezultujuci vektor: ";
        for(double broj:rezultat) {
            std::cout << std::setprecision(4) << broj << ' ';
        }
        
    } catch (std::logic_error err) {
        std::cout << "Problem: " << err.what();
    }
    
	return 0;
}
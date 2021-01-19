//TP 2018/2019: Tutorijal 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

bool DaLiJeProst(int n) {
    
    if (n<=1)
	    return false;

    for (int i=2;i<=sqrt(n);i++) {
        if(n%i==0)
            return false;
    }
    
    return true;
}

std::vector<int> ProstiBrojeviUOpsegu(int a,int b) {
    
    std::vector<int> rezultat;
    
    for(int i=a;i<=b;i++) {
        if(DaLiJeProst(i))
            rezultat.push_back(i);
    }
    
    return rezultat;
        
}


int main ()
{
   
   int poc,kraj;
   
   std::cout << "Unesite pocetnu i krajnju vrijednost: ";
   std::cin >> poc >> kraj;
   
    std::vector<int> rezultat = ProstiBrojeviUOpsegu(poc,kraj);
    
    if(rezultat.size() > 0) {
        std::cout << "Prosti brojevi u rasponu od " << poc << " do " << kraj << " su: ";
        for(int i=0;i<rezultat.size();i++) {
            if(i<rezultat.size()-1)
                std::cout << rezultat.at(i) << ", ";
            else 
                std::cout << rezultat.at(i);
        }
    } else 
        std::cout << "Nema prostih brojeva u rasponu od " << poc << " do " << kraj << "!";
    
    
    std::cout << std::endl;
    
return 0;
}
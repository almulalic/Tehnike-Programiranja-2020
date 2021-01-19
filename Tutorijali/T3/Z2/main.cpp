#include <iostream>
#include <vector>

int SumaCifara(int broj) {
    
    int suma(0);
    
    while(broj!=0) {
        suma+=broj%10;
        broj/=10;
    }
    
    return suma;
}

std::vector<int> IzdvojiElemente(std::vector<int> niz,bool logickaVrijednost) {
    
    std::vector<int> rezultat;
    
    if(logickaVrijednost) {
        for(int broj:niz) {
            if(SumaCifara(broj)%2==0)
                rezultat.push_back(broj);
        }
    } else {
        for(int broj:niz) {
            if(SumaCifara(broj)%2!=0)
                rezultat.push_back(broj);
        }
    }

    return rezultat;
    
}

int main() {
    
    int brojElemenata;
    
    std::cout << "Koliko zelite unijeti elemenata: ";
    std::cin >> brojElemenata;
    
    if(brojElemenata == 0) {
        std::cout << "Broj elemenata mora biti veci od 0!";
        return 0;
    }
    
    std::vector<int> niz;
    int unos;
    
    std::cout << "Unesite elemente: ";
    for(int i=0;i<brojElemenata;i++) {
        std::cin >> unos;
        niz.push_back(unos);
    }
    
    std::vector<int> b = IzdvojiElemente(niz,1);
    std::vector<int> c = IzdvojiElemente(niz,0);
    
    for(int i=0;i<b.size();i++)
        if(i<b.size()-1)
            std::cout << b.at(i) << ",";
        else
            std::cout << b.at(i);
    
    std::cout << std::endl;
    
    for(int i=0;i<c.size();i++)
        if(i<c.size()-1)
            std::cout << c.at(i) << ",";
        else
            std::cout << c.at(i);
    
    return 0;
}
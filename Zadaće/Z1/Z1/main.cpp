//TP 2018/2019: Tutorijal 2, Zadatak 1 // zadatak je kopiran jer je radjen na pogresnom mjestu, tacnije tutorial 2 zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

bool DaLiJeProst(int n) {

    for (int i=3;i<sqrt(n);i++) {
        if(n%i==0)
            return false;
    }
    
    return true;
}

bool DaLiJeSimetricanBroj(int n) {
    
    std::vector<int> cifre;
    
    while(n!=0) {
        cifre.push_back(n%10);
        n/=10;
    }
    
    int duzina = cifre.size();
    
    for(int i=0;i<duzina/2;i++){
        if(!(cifre.at(0+i) == cifre.at(duzina-1-i)))
            return false;
    }
        
    return true;

} 

bool DaLiJeSimetricanTernarni(std::vector<int> n) {
    
    int duzina = n.size();
    
    for(int i=0;i<duzina/2;i++){
        if(!(n.at(0+i) == n.at(duzina-1-i)))
            return false;
    }
        
    return true;

} 

std::vector<int> PretvoriUTernarni(int n) {
    std::vector<int> rezultat;
    
    while(n!=0) {
        rezultat.push_back((n%3));
        n/=3;
    }
    
    return rezultat;
}

std::vector<int> UkloniDuplikate(std::vector<int> vektor) {
    
    for(int i=0;i<vektor.size();i++) {
        for(int j=i+1;j<vektor.size();j++) {
           if(vektor.at(i) == vektor.at(j)) {
                 vektor.erase(vektor.begin()+j);
                 j--;
           }
        }
    }

    return vektor;
}

std::vector<int> IzdvojiSimetricneTernarne(std::vector<int> vektor,bool unesiSimetricne=true) {
    
    std::vector<int> simetricni;
    std::vector<int> nesimetricni;
    
    std::vector<int> rezultantniVektor;
    
    for(int broj:vektor){
        if(DaLiJeSimetricanBroj(broj))
            simetricni.push_back(broj);
        else
            nesimetricni.push_back(broj);
    }
    
    std::vector<int> izdvojeni = unesiSimetricne ? simetricni:nesimetricni;
    
    for(int broj:izdvojeni) {
        if(DaLiJeSimetricanTernarni(PretvoriUTernarni(abs(broj))))
            rezultantniVektor.push_back(broj);
    }
        
    return UkloniDuplikate(rezultantniVektor);
}

int main () {
    
    int brojElemenata;
    std::vector<int> niz;
    bool parametar;
    
    std::cout << "Unesite broj elemenata niza: ";
    std::cin >> brojElemenata;

    int unos;
    std::cout << "Unesite elemente niza: ";
    for(int i=0;i<brojElemenata;i++) {
        std::cin >> unos;
        niz.push_back(unos);
    }

    std::cout << "Unesite parametar (1 ili 0): ";
    std::cin >> parametar;
    
    std::vector<int> rezultantniVektor = IzdvojiSimetricneTernarne(niz,parametar);
    
    std::cout << "Izdvojeni elementi su: ";
    for(int i=0;i<rezultantniVektor.size();i++) {
        if(i!=rezultantniVektor.size() - 1)
            std::cout << rezultantniVektor.at(i) << ", ";
        else 
            std::cout << rezultantniVektor.at(i);
    }
    
    return 0;
}
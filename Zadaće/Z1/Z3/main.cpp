//TP 2016/2017: Zadaća 1, Zadatak 3
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef std::vector<double> VektorD;
typedef std::vector<std::vector<double>> MatricaD;
typedef std::vector<std::vector<std::vector<double>>> TrodimenzionalnaMD;

MatricaD MnozenjeMatrica(MatricaD prva, MatricaD druga) {
    
    MatricaD rezultantnaMatrica;
    
    if(prva.size() == 0 && druga.size() == 0)
        return rezultantnaMatrica;
        
    if((prva.size() == 0 || druga.size() == 0) || prva.at(0).size() != druga.size())
        throw std::domain_error("Nije moguce mnozenje matrica!");
    
    int prihvatljivaDuzina = prva.at(0).size();
    for(int i=1;i<prva.size() ;i++) {
        if(prva.at(i).size() != prihvatljivaDuzina)
            throw std::domain_error("Neispravna matrica!");
    }
    
    prihvatljivaDuzina = druga.at(0).size();
    for(int i=1;i<druga.size() ;i++) {
        if(druga.at(i).size() != prihvatljivaDuzina)
            throw std::domain_error("Neispravna matrica!");
    }
    
    double clan = 0;
    VektorD red;
    
    int visina = prva.size();
    int duzina = druga.at(0).size();
    int kolonePrva = prva.at(0).size();
    
    for(int i=0;i<visina;i++) {
        for(int j=0;j<duzina;j++) {
            for(int k=0;k<kolonePrva;++k) {
                clan += (prva.at(i).at(k) * druga.at(k).at(j));
            }
            red.push_back(clan);
            clan=0;
        }
        rezultantnaMatrica.push_back(red);
        red.clear();
    }
        
    return rezultantnaMatrica;
}

TrodimenzionalnaMD DoolitleLU(MatricaD H) {
    
    TrodimenzionalnaMD rezultat;
    
    if(H.size() == 0)
        return rezultat;
        
    if(H.size() != H.at(0).size())
        throw std::domain_error("Matrica mora biti kvadratnog oblika!");
    
    int prihvatljivaDuzina = H.at(0).size();
    for(int i=1;i<H.size();i++){
        if(H.at(i).size() != prihvatljivaDuzina)
            throw std::domain_error("Neispravna matrica!");
    }
    
    int n = H.size();
    double clan;
    
    MatricaD L(n,VektorD(n));
    MatricaD U(n,VektorD(n));
    
    for(int i=0;i<n;i++) {
        
        for(int j=i;j<n;j++) {
            clan = 0;
            for(int k=0;k<i;k++)
                clan += (L.at(i).at(k) * U.at(k).at(j));
            
            U.at(i).at(j) = H.at(i).at(j) - clan;
        }
        
        for(int l=i;l<n;l++) {
            if(i==l)
                L.at(i).at(i) = 1;
            else {
                clan = 0;
                for(int m=0;m<i;m++)
                    clan += (L.at(l).at(m) * U.at(m).at(i));
                
                L.at(l).at(i) = (H.at(l).at(i) - clan) / U.at(i).at(i);
            }
        }
        
    }
    
    rezultat.push_back(L);
    rezultat.push_back(U);
    
    return rezultat;
}

bool ProvjeriFaktorizaciju(MatricaD H,TrodimenzionalnaMD faktorisanaH) {
   
    if(H.size()==0 || faktorisanaH.size() == 0)
        return true;
    
    const double epsilon = 0.0001;
    int visina = H.size();
    int duzina = H.at(0).size();
    MatricaD LU;
    
    try {
        LU = MnozenjeMatrica(faktorisanaH.at(0),faktorisanaH.at(1));
    } catch(...) {
        return false;
    }
    
    for(int i=0;i<visina;i++) {
        for(int j=0;j<duzina;j++) {
            if(!(fabs(H.at(i).at(j) - LU.at(i).at(j)) < epsilon))
                return false;
        }
    }
    
    return true;
}

int main () {
    
    int n;
    std::cout << "Unesite dimenziju kvadratne matrice H: ";
    std::cin >> n;
    
    MatricaD H;
    VektorD red;
    
    std::cout << "Unesite elemente matrice H: " << std::endl;
    
    int unos;
    for(int i=0;i<n;i++) {
        std::cout << "Elementi " << i+1 << ". reda: ";
        for(int j=0;j<n;j++) {
            std::cin >> unos;
            red.push_back(unos);
        }
        H.push_back(red);
        red.clear();
    } 
    
	TrodimenzionalnaMD rezultat;
	
	try {
	    rezultat = DoolitleLU(H);
	} catch (const std::domain_error& e) {
	    std::cout << e.what() << std::endl;
	    return 1;
	}
    
	std::cout << "Matrica L: " << std::endl;
	for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            std::cout << std::setw(9) << std::setprecision(4) << std::fixed << rezultat.at(0).at(i).at(j);
        }
        std::cout << std::endl;
    }

    std::cout << "Matrica U: " << std::endl;
	for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            std::cout << std::setw(9) << std::setprecision(4) << std::fixed << rezultat.at(1).at(i).at(j);
        }
        std::cout << std::endl;
    }
    
	return 0;
}
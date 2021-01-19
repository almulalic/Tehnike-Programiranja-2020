//TP 2018/2019: Zadaća 2, Zadatak 4
#include <iostream>
#include <string>
#include <algorithm>

void SortirajRecenice(std::string *poc, std::string *kraj) {
	
	if(poc > kraj)
		throw std::domain_error("Nije moguce sortiranje");
		
	std::sort(poc,kraj,[](std::string a,std::string b) -> bool {
		int aLen = a.length(),bLen = b.length();
		
		if(aLen != bLen)
			return aLen < bLen;
		else  {
			int i=0;
			while(i != aLen) if(std::tolower(a.at(i)) != std::tolower(b.at(i))) return std::tolower(a.at(i)) < std::tolower(b.at(i)); else i++;
		}
		
		return false;
	});
	
}

int main () {
    
    int n(0);
    std::cout << "Unesite broj recenica: ";
	std::cin >> n;
	std::cin.ignore(10000,'\n');
	
	std::string *niz = nullptr;
	try {
	    niz = new std::string[n];
	    
	    std::cout << "Unesite recenice: " << std::endl;
	    for(int i=0;i<n;i++) {
	        std::string temp;
	    	std::getline(std::cin, temp);
	        niz[i] = temp;
	    }
	    
	    SortirajRecenice(niz,niz+n);
	    
	    std::cout << "Recenice nakon sortiranja: " << std::endl;

	    for(int i=0;i<n;i++) {
	    	std::cout << niz[i] << std::endl;
	    }
	    
	    std::cout << std::endl;
	    
	    std::string rijec;
	    std::cout << "Unesite recenicu za pretragu: ";
	    std::getline(std::cin,rijec);
	    
	    auto pozicija = std::find(niz,niz+n,rijec);
    	if(pozicija != niz+n) 
    		std::cout << "Recenica se nalazi na poziciji: " << (pozicija-niz);
    	else
    		std::cout << "Trazena recenica se ne nalazi u nizu!";
	    
	    delete[] niz;
	} catch (...) {
	    std::cout << "Izuzetak: Greska prilikom alokacije memorije!";
	    delete[] niz;
	}
	


	return 0;
}
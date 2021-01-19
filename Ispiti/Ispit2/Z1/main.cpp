//TP 2018/2019: Ispit 2, Zadatak 1
#include <iostream>
#include <deque>
#include <list>
#include <iomanip>

typedef std::deque<std::deque<double>> DekMatrica;

void swap (double &a,double &b) {
	auto temp = a;
	a = b;
	b = temp;
}

std::list<bool> TransformirajMatricu(DekMatrica &matrica) {
   
    int duzinaReda = matrica.at(0).size();

    for(int i=0;i<matrica.size();i++) {
        if(matrica.at(i).size() != duzinaReda)
            throw std::domain_error("Parametar nema formu matrice");
    }
    
    std::list<bool> rezultat;
    
    for(int i=0;i<matrica.size();i++) {
    	double produkt(1);
    	
    	for(int j=0;j<matrica.at(i).size();j++) {
    		produkt*=matrica.at(i).at(j);
    	}
    	
    	if(produkt > 0)
    		rezultat.push_back(true);
    	else 
    		rezultat.push_back(false);
    }
    
    for(int i=0;i<duzinaReda;i++)
    	swap(matrica.at(i).at(0),matrica.at(i).at(duzinaReda-1));
 
    for(int i=0;i<matrica.size();i++) {
    	for(int j=1;j<duzinaReda -1;j++) {
    		swap(matrica.at(i).at(j),matrica.at(i).at(j+1));
    	}
    }

    	
    
    
	return rezultat;   
}

int main ()
{
    
    int redovi,kolone;
    std::cout << "Unesite broj redova: ";
	std::cin >> redovi;
	
	std::cout << "Unesite broj kolona: ";
	std::cin >> kolone;
	
	DekMatrica matrica(redovi,std::deque<double>(kolone,0));
	double unos;
	
	std::cout << "Unesite elemente matrice: ";
	for(int i=0;i<redovi;i++) {
	    for(int j=0;j<kolone;j++) {
	        std::cin >> unos;
	        matrica.at(i).at(j) = unos;        
	    }
	}
	
	try {
		
		std::list<bool> listaLogickih = TransformirajMatricu(matrica);
	
		std::cout << "Transformirana matrica: " << std::endl;
		
		for(auto red:matrica) {
	    	for(double broj:red) {
	    		std::cout << std::setw(8) << broj << ' ';
	    	}
	    std::cout << std::endl;
		}
		
		std::cout << "Rezultujuca lista: ";
	
		for(bool logicka:listaLogickih) {
			std::cout << std::boolalpha << logicka << ' ';
		}
	
	
	} catch(std::domain_error err) {
		std::cout << err.what();
	}
	
	
	return 0;
}
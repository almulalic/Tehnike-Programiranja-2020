/* 
    TP 2018/2019: Tutorijal 6, Zadatak 1
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <cmath>
#include <limits> 


template <typename TipElemenata>
TipElemenata* GenerirajStepeneDvojke(int n) {
	if(n <= 0)
		throw std::domain_error("Broj elemenata mora biti pozitivan");
		
	TipElemenata *p = nullptr;
	
	try {
		p = new TipElemenata[n];
	} catch(...) {
		throw std::runtime_error("Alokacija nije uspjela");
		delete[] p;
	}
	
	TipElemenata max = std::numeric_limits<TipElemenata>::max()
	p[0] = 1;
	int stepen = 1;
	for(int i=1;i<n;i++) {
		p[i] = stepen*=2;
		if(stepen >= max)
			throw std::overflow_error("Prekoracen dozvoljeni opseg");
	}
	
	return p;
}

int main ()
{
	
	try {
		
		int n;
		std::cout << "Koliko zelite elemenata: ";
		std::cin >> n;
	
		long int *pok = GenerirajStepeneDvojke<long int>(n);
		
		for(int i=0;i<n;i++) {
			std::cout << pok[i] << ' ';
		}
		
	} catch(std::domain_error &de) {
		std::cout << "Izuzetak: " << de.what();
	} catch(std::runtime_error &re) {
		std::cout << "Izuzetak: " << re.what();
	}
	
	return 0;
}
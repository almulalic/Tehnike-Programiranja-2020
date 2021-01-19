/* 
    TP 2018/2019: Tutorijal 6, Zadatak 2
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <vector>

template <class iterator,typename TipElemenata>
TipElemenata* KreirajIzvrnutiNiz(iterator< p,iterator q) {
	
	TipElemenata *pok = nullptr;
	
	try {
		pok = new TipElemenata[q-p];
		
		int i=0;
		while(*q != *p) {
			pok[i++] = *q;
			q--;
		}
		pok[i] = *q;
	} catch(...) {
		throw std::bad_alloc();
		delete[] pok;
	}
	
	delete[] pok;
	return pok;
}

int main ()
{
	
	int n;
	std::cout << "Koliko zelite elemenata: ";
	std::cin >> n;
	
	double unos;
	std::vector<double> niz;
	for(int i=0;i<n;i++) {
		std::cin >> unos;
		niz.push_back(unos);
	}
	
	double *pok = KreirajIzvrnutiNiz(niz.begin(),niz.end());
	
	for(int i=0;i<n;i++) {
		std::cout << pok[i] << ' ';
	}
	
	return 0;
}
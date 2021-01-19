/* 
    TP 16/17 (Tutorijal 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/

 
#include <iostream>
#include <list>
#include <iterator>

template <typename TipElemenata>
std::list<TipElemenata> SortirajListu(std::list<TipElemenata> lista) {
	std::list<TipElemenata> sortirana;			
	typename std::list<TipElemenata>::iterator it,it2;
	
	while(lista.size()) {
		it2 = lista.begin();
		for(it = sortirana.begin();it != sortirana.end(); it++) {
			if(*it > *it2)
				break;
		}
		sortirana.insert(it,*it2);
		lista.pop_front();
	}
	
	return sortirana;
}

int main ()
{
	int brojElemenata;
	std::cout << "Koliko ima elemenata: ";
	std::cin >> brojElemenata;
	
	std::list<int> elementi;
	std::cout << "Unesite elemente: ";
	int unos;

	for(int i=0;i<brojElemenata;i++) {
		std::cin >> unos;
		elementi.push_back(unos);		
	}
	
	std::list<int> sortirana = SortirajListu(elementi);
	
	std::cout << "Sortirana lista: ";
	for (auto it=sortirana.begin(); it!=sortirana.end(); it++) 
       std::cout << *it << " ";
	
	return 0;
}
/* 
    TP 16/17 (Tutorijal 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <set>
#include <iterator>
#include <string>

template <typename TipElemenata>
std::set<TipElemenata> Unija(std::set<TipElemenata>& skup1,std::set<TipElemenata>& skup2) {
	std::set<TipElemenata> unija = skup1;
	unija.insert(skup2.begin(),skup2.end());
	return unija;
}

template <typename TipElemenata>
std::set<TipElemenata> Presjek(std::set<TipElemenata> skup1,std::set<TipElemenata> skup2) {
	std::set<TipElemenata> presjek;
	typename std::set<TipElemenata>::iterator it1=skup1.begin();
	typename std::set<TipElemenata>::iterator it2=skup2.begin();
	while((it1 != skup1.end()) && (it2 != skup2.end())) {
		if(*it1 < *it2) {
			skup1.erase(it1++);
		} else if(*it2 < *it1) {
			++it2;
		} else {
			++it1;
			++it2;
		}
	}
	
	skup1.erase(it1,skup1.end());
	return skup1;
}


int main ()
{
	std::set<std::string> prvi = {"Almir","test","testtest"};
	std::set<std::string> drugi = {"Almir","drugi","treci"};
	
	std::set<std::string> unija = Unija(prvi,drugi);
	for (auto it=unija.begin(); it != unija.end(); ++it) 
        std::cout << ' ' << *it; 
    
    std::cout << std::endl;
    
    std::set<std::string> presjek = Presjek(prvi,drugi);
	for (auto it=presjek.begin(); it != presjek.end(); ++it) 
        std::cout << ' ' << *it; 
	
	return 0;
}
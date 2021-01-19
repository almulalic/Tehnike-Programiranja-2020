/* 
    TP 16/17 (Tutorijal 12, Zadatak 2)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

#include <set>
#include <algorithm>

template <typename TipElemenata>
std::set<TipElemenata> operator+(const std::set<TipElemenata>& skup1,const std::set<TipElemenata>& skup2) {
	std::set<TipElemenata> unija = skup1;
	unija.insert(skup2.begin(),skup2.end());
	return unija;
}

template <typename TipElemenata>
std::set<TipElemenata> operator*(const std::set<TipElemenata> &skup1,const std::set<TipElemenata> &skup2) {
	std::set<TipElemenata> presjek;
	
	for(auto el:skup1) {
		if(std::find(skup2.begin(),skup2.end(),el) != skup2.end())
			presjek.insert(el);
	}
	
	return presjek;
}

template <typename TipElemenata>
std::ostream& operator << (std::ostream& tok,const std::set<TipElemenata> &set) {
	tok << "{";
	
	int i=0;
	for(auto br:set) {
		if(i < set.size()-1)
			tok << br << ",";
		else
			tok << br;
		i++;
	}
	
	tok << "}";
	
	return tok;
}

int main () {
	
	std::set<int> s1{3, 5, 1, 2, 8}, s2{7, 2, 8, 4};
	std::cout << s1 + s2 << std::endl; // Ispis {1,2,3,4,5,7,8}
	std::cout << s1 * s2 << std::endl; // Ispis {2,8}
	
	return 0;
}
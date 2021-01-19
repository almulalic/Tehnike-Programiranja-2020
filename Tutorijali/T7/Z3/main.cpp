/* 
    TP 16/17 (Tutorijal 7, Zadatak 3)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>


int main ()
{

	int broj_recenica;
	std::cout << "Koliko zelite recenica: ";
	std::cin >> broj_recenica;
	std::cin.ignore(10000, '\n'); // Zbog '\n' u spremniku!
	int i;
	
	std::cout << "Unesite recenice: " << std::endl;
	try {
		std::vector<std::string*> recenice(broj_recenica);
		
		for(i=0;i<broj_recenica;i++) {
			std::string recenica;
	    	std::getline(std::cin, recenica);
	    	recenice.at(i) = new std::string(recenica);
		}
		
		std::sort(recenice.begin(),recenice.end(),[](std::string *string1,std::string *string2) {
			return *string1 < *string2;
		});
		
		std::cout << "Sortirane recenice: " << std::endl;
		for(std::string *rec:recenice) {
			std::cout << *rec << std::endl;
		}
	
		for(int j=0;j<recenice.size();j++) delete recenice.at(j);
		recenice.clear();
	} catch(...) {
		std::cout << "Problemi s memorijom!";
	}
	
	return 0;
}
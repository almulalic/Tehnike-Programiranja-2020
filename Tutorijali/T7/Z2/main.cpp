/* 
    TP 16/17 (Tutorijal 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>

int main ()
{

	int broj_recenica;
	std::cout << "Koliko zelite recenica: ";
	std::cin >> broj_recenica;
	std::cin.ignore(10000, '\n'); // Zbog '\n' u spremniku!
	char **recenice{};
	int i;
	
	std::cout << "Unesite recenice: " << std::endl;
	try {
		recenice = new char*[broj_recenica]{};
		
		for(i=0;i<broj_recenica;i++) {
			char radni_prostor[1000];
			std::cin.getline(radni_prostor, 999);
		 	recenice[i] = new char[std::strlen(radni_prostor) + 1];
			std::strcpy(recenice[i], radni_prostor);

		}
		
		std::sort(recenice,recenice+i,[](char* string1,char* string2) {
			return strcmp(string1,string2) < 0;
		});
		
		std::cout << "Sortirane recenice: " << std::endl;
		for(int m=0;m<i;m++)
			std::cout << recenice[m] << std::endl;
		
		for(int n=0;n<i;n++) delete[] recenice[n];
		delete[] recenice;
		
	} catch(...) {
		for(int j=0;j<i;j++) delete[] recenice[j];
		delete[] recenice;
		std::cout << "Problemi s memorijom!";
	}
		
	return 0;
}
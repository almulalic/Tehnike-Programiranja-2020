/* 
    TP 16/17 (Tutorijal 7, Zadatak 1)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>

int uporediString(const char *string1,const char *string2) {
	
	while(*string1 != '\0') {
		if(tolower(*string2) < tolower(*string1))
			return 1;
		else if(tolower(*string2) != tolower(*string1))
		    return 0;
		
		string1++;
		string2++;
		
		if(*string2 == '\0')
			return 1;
	}	
	
	return 0;
}

int main ()
{

	int broj_recenica;
	std::cout << "Koliko zelite recenica: ";
	std::cin >> broj_recenica;
	std::cin.ignore(10000, '\n'); // Zbog '\n' u spremniku!
	char **recenice{};
	int i;
	char* pomocna,*max;
	int maxIndex;
	
	std::cout << "Unesite recenice: " << std::endl;
	try {
		recenice = new char*[broj_recenica]{};
		
		for(i=0;i<broj_recenica;i++) {
			char radni_prostor[1000];
			std::cin.getline(radni_prostor, 999);
		 	recenice[i] = new char[std::strlen(radni_prostor) + 1];
			std::strcpy(recenice[i], radni_prostor);

		}
		
		for(int k=0;k<i-1; k++) {
			max = recenice[k];
			maxIndex = k;
			for(int l=k+1;l<i;l++) {
				if(uporediString(max,recenice[l])) {
					max = recenice[l];
					maxIndex = l;
				}
			}
			pomocna = recenice[k];
			recenice[k] = recenice[maxIndex];
			recenice[maxIndex] = pomocna;
		} 
		
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
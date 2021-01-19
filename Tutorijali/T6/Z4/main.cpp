/* 
    TP 2018/2019: Tutorijal 6, Zadatak 3
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>

int **KreirajTrougao(int n) {

	try {
		if(n <=0)
			throw std::domain_error("Broj redova mora biti pozitivan");
	
		int **p = new int* [n];
		
		for(int i=0;i<n;i++) {
			p[i] = new int[2*i+1];
			for(int j=0;j<2*i+1;j++) {
				if(j<(2*i+2)/2) {
					p[i][j] = j+1;
				} else {
					p[i][j] = (2*i+2)-j-1;
				}
			}
		}
		
	return p;
		
	} catch(...) {
		throw std::runtime_error("Alokacija nije uspjela");
	} 
}

int main ()
{
	
	try {
		int n;
		std::cout << "Koliko zelite redova: ";
		std::cin >> n;
		
		int**trougao{KreirajTrougao(n)};
		
		for(int i=0;i<n;i++) {
			for(int j=0;j<i+i+1;j++) {
				std::cout << trougao[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		
	} catch(const char s[]) {
		std::cout << s;
	}
	
	return 0;
}
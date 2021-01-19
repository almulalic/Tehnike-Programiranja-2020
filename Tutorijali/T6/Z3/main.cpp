/* 
    TP 2018/2019: Tutorijal 6, Zadatak 3
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>

int **KreirajTrougao(int n) {
	
	int ** p = nullptr;
	
	if(n <=0)
		throw std::domain_error("Broj redova mora biti pozitivan");

	try {
		
		try {
			p = new int*[n];
		} catch(...) {
			for(int i=0;i<n;i++)
				delete p[i];
		}
		
		for(int i=0;i<n;i++)
			p[i]= nullptr;
		
		for(int i=0;i<n;i++)
			p[i] = new int[2*i+1];
			
		for(int i=0;i<n;i++) {
			for(int j=0;j<2*i+1;j++) {
				if(j<(2*i+2)/2) {
					p[i][j] = (i+2)-j-1;
				} else {
					p[i][j] = j-i+1;
				}
			}
		}
	
	return p;
	
	} catch(...) {
		for(int i=0;i<n;i++)
			delete p[i];
		
		delete[] p;
		throw std::runtime_error("Nedovoljno memorije!");
	} 
}

int main ()
{
	
	// try {
	// 	int n;
	// 	std::cout << "Koliko zelite redova: ";
	// 	std::cin >> n;
		
	// 	int**trougao{KreirajTrougao(n)};
		
	// 	for(int i=0;i<n;i++) {
	// 		for(int j=0;j<i+i+1;j++) {
	// 			std::cout << trougao[i][j] << ' ';
	// 		}
	// 		std::cout << std::endl;
	// 	}
		
	// } catch(std::domain_error& de) {
	// 	std::cout << "Izuzetak: " << de.what();
	// } catch(std::runtime_error& re) {
	// 	std::cout << "Izuzetak: " << re.what();
	// }
	
	int m = 5;
	for(int i=0;i<9;i++) {
		if(i < 9/2) {
			std::cout << m;
			m--;
		} else {
			std::cout << m;
			m++;
		}
	}
	
	return 0;
}
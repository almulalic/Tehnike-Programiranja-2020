/* 
    TP 2018/2019: Tutorijal 5, Zadatak 3
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <algorithm>
#include <cmath>

bool jeMinimum(int n,int min) {
	return n==min;
}

int main ()
{

	int niz[1000];
	int n;
	std::cout << "Unesite broj elemenata (max. 1000): ";
	std::cin >> n;
	
	std::cout << "Unesite elemente: ";
	for(int i=0;i<n;i++)
		std::cin >> niz[i];
	
	std::cout << "Najveci element u nizu je: " << *std::max_element(niz,niz+n) << std::endl;
	
	int* min=std::min_element(niz,niz+n);
	int najmenjiPonavljanja = std::count(niz,niz+n,*min);
	
	std::cout << "Najmanji element niza se pojavljuje " << najmenjiPonavljanja << " puta u nizu" << std::endl;
	
	auto potpuniKvadrat = std::count_if(niz,niz+n,[](int broj) {
		for(int i=0;i<broj;i++) {
			if(pow(2,i)==broj) return true;
		}
		return false;
	});
	
	std::cout << "U nizu ima " << potpuniKvadrat << " brojeva koji su potpuni kvadrati" << std::endl;
	
	auto nisuTrocifreni = std::count_if(niz,niz+n,[](int a) {
		return log(a) + 1 != 3;

	});
	
	std::cout << "Elementi koji nisu trocifreni su: ";
	std::for_each(nisuTrocifreni,nisuTrocifreni+n,[](int a) {
		std::cout << a;
	})
	
	
	int brojac =0;
	for(int i=0;i<n;i++) {
		int broj = niz[i];
		broj/=10;
		if(broj==0) brojac++;
		broj/=10;
		if(broj!=0) brojac++;
	}
	
	int niz1[10000],k{0};
	for(int i=0;i<n;i++) {
		if(log(niz1[i])+1 > 2) {
			niz1[k] = niz1[i];
			k++;
		}
	}
	
	for(int i=0;i<brojac;i++)
		std::cout << niz[i] << ' ';
	
	
	return 0;
}
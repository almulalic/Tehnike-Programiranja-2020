/* 
    TP 16/17 (Tutorijal 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

std::string IzvrniBezRazmaka(std::string recenica) {
	std::string pomocni;
	std::remove_copy(recenica.rbegin(),recenica.rend(),std::back_inserter(pomocni),' ');
	return pomocni;
}

int main ()
{
	std::string test = "Evo pada kisa";
	std::cout << IzvrniBezRazmaka(test);
	
	return 0;
}
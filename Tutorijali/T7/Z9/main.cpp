/* 
    TP 16/17 (Tutorijal 7, Zadatak 9)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>

std::function<double(double)> plus2(double a){
    return[a] (double b){
    	return a + b; 
    };
}


std::function<std::function<double(double)>(double)> plus3(double a) {
	return [a] (double b) {
		return [a,b] (double c) {
			return a+b+c;
		};
	};
}

int main ()
{
	
	double a=1.1,b=2.2,c=3.3;
	
	std::cout << (plus2(a))(b);
	std::cout << std::endl;
	std::cout << plus3(a)(b)(c);
	
	return 0;
}
/* 
    TP 16/17 (Tutorijal 11, Zadatak 1)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>

class NeobicnaKlasa {
	private:
		int broj;
	
	public:
		explicit NeobicnaKlasa(const int br) : broj(br) { 
		    std::cout << "Direktna inicijalizacija" << std::endl;
		}
		
		NeobicnaKlasa& operator=(const NeobicnaKlasa& num){
            if(this != &num){
                std::cout << "= oprator used" << std::endl;
                this->number = num.number;
            }
            return *this;
        }

		
};		

int main () {
	
	NeobicnaKlasa k1(5);
	NeobicnaKlasa k2 = 5;
	
	return 0;
}
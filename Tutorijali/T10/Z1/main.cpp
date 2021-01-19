/* 
    TP 16/17 (Tutorijal 10, Zadatak 1)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

class StedniRacun {
	double stanjeRacuna;
	public:
		StedniRacun(double novoStanje = 0) { if(novoStanje < 0) throw std::logic_error("Nedozvoljeno pocetno stanje"); stanjeRacuna = novoStanje; }
		void Ulozi(double iznos) { if(stanjeRacuna + iznos < 0) throw std::logic_error("Transakcija odbijena"); stanjeRacuna += iznos; }
		void Podigni(double iznos) { if(iznos > stanjeRacuna) throw std::logic_error("Transakcija odbijena"); stanjeRacuna-=iznos;}
		double DajStanje() { return stanjeRacuna; }
		void ObracunajKamatu (double kamatnaStopa) { if(kamatnaStopa < 0) throw std::logic_error("Nedozvoljena kamatna stopa"); stanjeRacuna += (stanjeRacuna*kamatnaStopa/100); }
};

int main ()
{
	
	double unosStanja;
	std::cout << "Unesite novo stanje racuna: ";
	std::cin >> unosStanja;
	
	StedniRacun sr{};
	
	try {
		sr = StedniRacun(unosStanja);
	} catch(std::logic_error e) {
		std::cout << e.what();
	}
	
	std::cout << "Vas novi iznos racuna je " << sr.DajStanje() << std::endl;;

	int meniIzbor;
	std::cout << "Unesite 1 za ulog a 2 za podizanje: ";
	std::cin >> meniIzbor;
	
	double iznos;
	std::cout << "Unesite iznos: " << std::endl;;
	
	std::cin >> iznos;
	
	if(meniIzbor == 1) {
		sr.Ulozi(iznos);
	} else {
		try {
			sr.Podigni(iznos);
		} catch(std::logic_error e) {
			std::cout << e.what();
		}
	}
	
	std::cout << "Vas novi iznos racuna je " << sr.DajStanje() << std::endl;
		
	sr.ObracunajKamatu(2);
	sr.DajStanje();

	return 0;
}
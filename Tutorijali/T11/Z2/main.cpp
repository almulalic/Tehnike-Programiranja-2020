/* 
    TP 16/17 (Tutorijal 11, Zadatak 2)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

int test::count = 0;

class StedniRacun {
	double stanjeRacuna;
	static int count;

	public:
		StedniRacun() { *brojKreiranih++; }
		StedniRacun(double novoStanje = 0) {if(novoStanje < 0) throw std::logic_error("Nedozvoljeno pocetno stanje"); stanjeRacuna = novoStanje;  brojKreiranih = new int (1);}
		void Ulozi(double iznos) { if(stanjeRacuna + iznos < 0) throw std::logic_error("Transakcija odbijena"); stanjeRacuna += iznos; }
		void Podigni(double iznos) { if(iznos > stanjeRacuna) throw std::logic_error("Transakcija odbijena"); stanjeRacuna-=iznos;}
		double DajStanje() { return stanjeRacuna; }
		void ObracunajKamatu (double kamatnaStopa) { if(kamatnaStopa < 0) throw std::logic_error("Nedozvoljena kamatna stopa"); stanjeRacuna += (stanjeRacuna*kamatnaStopa/100); }
		int DajBrojKreiranih() { return *brojKreiranih; }
		~StedniRacun() {if(--(*brojKreiranih) == 0) { brojKreiranih = nullptr; delete brojKreiranih;  }  }
};

int main ()
{
	
	// double unosStanja;
	// std::cout << "Unesite novo stanje racuna: ";
	// std::cin >> unosStanja;
	
	// StedniRacun sr{};
	// StedniRacun sr2{};
	
	// std::cout << sr.DajBrojKreiranih();
	
	// try {
	// 	sr = StedniRacun(unosStanja);
	// } catch(std::logic_error e) {
	// 	std::cout << e.what();
	// }
	
	// std::cout << "Vas novi iznos racuna je " << sr.DajStanje() << std::endl;;

	// int meniIzbor;
	// std::cout << "Unesite 1 za ulog a 2 za podizanje: ";
	// std::cin >> meniIzbor;
	
	// double iznos;
	// std::cout << "Unesite iznos: " << std::endl;;
	
	// std::cin >> iznos;
	
	// if(meniIzbor == 1) {
	// 	sr.Ulozi(iznos);
	// } else {
	// 	try {
	// 		sr.Podigni(iznos);
	// 	} catch(std::logic_error e) {
	// 		std::cout << e.what();
	// 	}
	// }
	
	// std::cout << "Vas novi iznos racuna je " << sr.DajStanje() << std::endl;
		
	// sr.ObracunajKamatu(2);
	// sr.DajStanje();
	StedniRacun s1(100), s2, s3(200), s4, s5;

s1.Podigni(50);
s2.Ulozi(555);
s3.Podigni(200);
		
try {
	s1.Podigni(50);
	s2.Podigni(555);
	s4.Ulozi(-10);
	s3.Ulozi(555);
	s1.Ulozi(50000);
	s4.Ulozi(33);
	s5.Ulozi(666);
}
catch(std::logic_error e)
{
	std::cout << e.what() << std::endl;
}
	
std::cout << s1.DajStanje() << " " << s2.DajStanje() << " " << s3.DajStanje() << " " << s4.DajStanje() << " " << s5.DajStanje() << std::endl;
std::cout << "Broj kreiranih: " << StedniRacun::DajBrojKreiranih() << std::endl;


	return 0;
}
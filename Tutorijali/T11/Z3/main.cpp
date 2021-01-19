/* 
    TP 16/17 (Tutorijal 11, Zadatak 3)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

#include <cstring>
#include <iomanip>

class Tim {
	char imeTima[20];
	int brojOdigranih,brojPobjeda,brojNerjsenih,brojPoraza,brojDatih,brojPrimljenih,brojPoena;
	
	public:
		Tim(const char ime[]) : brojOdigranih(0), brojPobjeda(0), brojNerjsenih(0), brojPoraza(0), brojDatih(0), brojPrimljenih(0),brojPoena(0) { if(strlen(ime) > 20) throw std::range_error("Predugacko ime tima"); strncpy(imeTima,ime,20);};
		void ObradiUtakmicu(int brojDatih,int brojPrimljenih);
		const char *DajImeTima() const { return imeTima; };
		int DajBrojPoena() const { return brojPoena; };
		int DajGolRazliku() const { return brojDatih - brojPrimljenih; };
		void IspisiPodatke() const;
		
};

void Tim::ObradiUtakmicu(int brojDatih,int brojPrimljenih) {
	if(brojDatih < 0 || brojPrimljenih < 0)
		throw std::range_error("Neispravan broj golova");
		
	brojOdigranih ++;
	this -> brojDatih += brojDatih;
	this -> brojPrimljenih += brojPrimljenih;
	if(brojDatih == brojPrimljenih) { brojPoena ++; brojNerjsenih++; }
	else if (brojDatih < brojPrimljenih) brojPoraza++;
	else { brojPoena += 3; brojPobjeda ++; }
}

void Tim::IspisiPodatke() const {
	std::cout << std::left << std::setw(20) << imeTima << std::right << std::setw(4) << brojOdigranih << std::setw(4) << brojPobjeda << std::setw(4) << brojNerjsenih << std::setw(4) << brojPoraza << std::setw(4)
	<< brojDatih << std::setw(4) << brojPrimljenih << std::setw(4) << brojPoena << std::endl;
	
}

int main ()
{
	try {
		Tim t1("FK Sarajevo");
		
		t1.ObradiUtakmicu(4,1);
		t1.ObradiUtakmicu(2,2);
		t1.ObradiUtakmicu(1,2);
		t1.ObradiUtakmicu(3,0);
		t1.ObradiUtakmicu(2,0);
		
		Tim t2("FK Velez Mostar");
		
		t2.ObradiUtakmicu(1,2);
		t2.ObradiUtakmicu(0,0);
		t2.ObradiUtakmicu(4,1);
		t2.ObradiUtakmicu(1,0);
		t2.ObradiUtakmicu(0,2);
		t2.ObradiUtakmicu(3,3);
			
		t1.IspisiPodatke();
		t2.IspisiPodatke();
	} catch(std::exception &err) {
		std::cout << err.what() << std::endl;
	}
	
	return 0;
}
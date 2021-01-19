/* 
    TP 16/17 (Tutorijal 11, Zadatak 5)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

#include <memory>
#include <cstring>
#include <iomanip>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <initializer_list>

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

class Liga {
	std::vector<std::shared_ptr<Tim>> timovi;
	
	static bool sortKriterij(Tim* a, Tim* b) {
        if(a->DajBrojPoena() > b->DajBrojPoena())
            return true;
    	
    	if(a->DajBrojPoena() == b->DajBrojPoena())
            if(a->DajGolRazliku() > b->DajGolRazliku())
            	return true;
            	
        if(a->DajBrojPoena() == b->DajBrojPoena())
            if(a->DajGolRazliku() == b->DajGolRazliku())
                if(strcmp(a->DajImeTima(),b->DajImeTima()) < 0) 
			        return true;
        
        return false;   
    }
	
	public:
		Liga() = default;
		
		explicit Liga(std::initializer_list<Tim> listaTimova);
		
<<<<<<<<< saved version

=========
		~Liga() { for(int i=0;i<timovi.size();i++) delete timovi.at(i);}
>>>>>>>>> local version
		Liga(const Liga &l) {
			
			for(int i=0;i<l.timovi.size();i++)
				timovi.push_back(new Tim(*l.timovi.at(i)));
			
		}
		
		Liga(Liga &&l) {
			timovi = l.timovi;
		}
		
		Liga& operator = (const Liga &l) {
			if(&l != this) {

				for(int i=0;i<l.timovi.size();i++)
					timovi.push_back(l.timovi.at(i));
			}
			
			return *this;
		}
		
		Liga& operator = (Liga &&l) {
		    timovi = l.timovi;
			return *this;
		}
		
		void DodajNoviTim(const char imeTima[]) {
			
			if(strlen(imeTima) > 20) 
				throw std::range_error("Predugacko ime tima");
			
			for(int i = 0; i < timovi.size(); i++)  {
				if(strcmp(timovi[i] -> DajImeTima(),imeTima) == 0)
					throw std::logic_error("Tim vec postoji");
			}
			
			timovi.push_back(new Tim(imeTima));
		}
		
		void RegistrirajUtakmicu(const char imePrvog[],const char imeDrugog[],int brojDatihPrvi,int brojDatihDrugi) {
			Tim* prvi(nullptr), *drugi(nullptr);

			for(int i = 0; i < timovi.size(); i++)  {
				
				if(strcmp(timovi.at(i) -> DajImeTima(),imePrvog) == 0)
					prvi = timovi.at(i);
				else if (strcmp(timovi.at(i) -> DajImeTima(),imeDrugog) == 0) 
					drugi = timovi.at(i);
					
			}
			
			if(!prvi || !drugi) throw std::logic_error("Tim nije nadjen");

			if(brojDatihPrvi < 0 || brojDatihDrugi < 0) 
				throw std::range_error("Neispravan broj golova");
				
			prvi -> ObradiUtakmicu(brojDatihPrvi,brojDatihDrugi);
			drugi -> ObradiUtakmicu(brojDatihDrugi,brojDatihPrvi);
		}
		
		void IspisiTabelu() {
			std::sort(timovi.begin(),timovi.end(),sortKriterij);
			for(int i=0;i<timovi.size();i++) timovi.at(i) -> IspisiPodatke();
		}
};

Liga::Liga(std::initializer_list<Tim> listaTimova){

	for(int i=0;i<listaTimova.size();i++) timovi.push_back(nullptr);

	try {
		int j=0;
		for(auto i:listaTimova) {
			timovi.at(j) = new Tim(i);
			j++;
		}
	} catch(std::exception &err) {
		std::cout << err.what();
		for(int i=0;i<timovi.size();i++)
			delete timovi.at(i);
		throw;
	}

}

int main ()
{
	// AT1: Testiranje da li se kopirajuci konstruktor ponasa konzistentno i da li je ispravno implementirano duboko kopiranje
	 
	Liga l1{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo", "FK Sloboda", "FK Krupa", "FK Radnik Bijeljina"};
	// l1.RegistrirajUtakmicu("NK Zeljeznicar", "HSK Zrinjski",2,0);
	Liga l2(l1);
	
	std::cout << "Orginalna Liga za Prvaka: " << std::endl;
	l1.IspisiTabelu();
	std::cout << std::endl << "Kopija Lige za Prvaka: " << std::endl;
	l2.IspisiTabelu();
	
	l2.RegistrirajUtakmicu("FK Krupa", "FK Sloboda",1,1);
	
	std::cout << std::endl << "Nakon izmjene kopije: " << std::endl << std::endl;
	
	std::cout << "Orginalna Liga za Prvaka: " << std::endl;
	l1.IspisiTabelu();  
	std::cout << std::endl << "Kopija Lige za Prvaka: " << std::endl;
	l2.IspisiTabelu();
	
	return 0;
}


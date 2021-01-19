/* 
    TP 16/17 (Tutorijal 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <initializer_list>
#include <cstring>
#include <iomanip>
#include <algorithm>

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
	const int maxBrojTimova;
	int brojTimova;
	Tim** timovi;
	
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
		explicit Liga(int velicinaLige) : maxBrojTimova(velicinaLige),brojTimova(velicinaLige),timovi(new Tim*[velicinaLige]) {
			for(int i=0;i<maxBrojTimova;i++) timovi[i] = nullptr;
		}
		
		explicit Liga(std::initializer_list<Tim> listaTimova);
		
		~Liga() { for(int i=0;i < brojTimova;i++) delete timovi[i]; delete[] timovi; }
		
		Liga(const Liga &l) : maxBrojTimova(l.maxBrojTimova),brojTimova(l.brojTimova),timovi(new Tim*[l.maxBrojTimova]) {
			for(int i=0;i<maxBrojTimova;i++) timovi[i] = nullptr;
			try {
				for(int i=0;i<brojTimova;i++)
					timovi[i] = new Tim(*l.timovi[i]);
			} catch(...) {
				for(int i=0;i<maxBrojTimova;i++) 
					delete timovi[i];
				
				delete[] timovi;
				throw;
			}
		}
		
		Liga(Liga &&l) : maxBrojTimova(l.maxBrojTimova),brojTimova(l.brojTimova) {
			timovi = l.timovi;
			l.timovi = nullptr;
		}
		
		Liga& operator = (const Liga &l) {
			if(&l != this) {
				
				if(maxBrojTimova != l.maxBrojTimova)
					throw std::logic_error("Nesaglasni kapaciteti liga");

				for(int i=0;i<l.brojTimova;i++)
					*timovi[i] = *l.timovi[i];
				
				brojTimova = l.brojTimova;

			}
			
			return *this;
		}
		
		Liga& operator = (Liga &&l) {
			if(maxBrojTimova != l.maxBrojTimova)
				throw std::logic_error("Nesaglasni kapaciteti liga");
					
		    brojTimova = l.brojTimova;
		    timovi = l.timovi;
		    l.timovi = nullptr;
			
			return *this;
		}

		
		void DodajNoviTim(const char imeTima[]) {
			if(brojTimova == maxBrojTimova)
				throw std::range_error("Liga popunjena");
			
			if(strlen(imeTima) > 20) 
				throw std::range_error("Predugacko ime tima");
			
			for(int i = 0; i < brojTimova; i++)  {
				if(strcmp(timovi[i] -> DajImeTima(),imeTima) == 0)
					throw std::logic_error("Tim vec postoji");
			}
			
			timovi[brojTimova++] = new Tim(imeTima);
		}
		
		void RegistrirajUtakmicu(const char imePrvog[],const char imeDrugog[],int brojDatihPrvi,int brojDatihDrugi) {
			Tim* prvi(nullptr), *drugi(nullptr);
			
			for(int i = 0; i < brojTimova; i++)  {
				
				if(strcmp(timovi[i] -> DajImeTima(),imePrvog) == 0)
					prvi = timovi[i];
				else if (strcmp(timovi[i] -> DajImeTima(),imeDrugog) == 0) 
					drugi = timovi[i];
			}
			
			if(!prvi || !drugi) throw std::logic_error("Tim nije nadjen");
			
			
			
			if(brojDatihPrvi < 0 || brojDatihDrugi < 0) 
				throw std::range_error("Neispravan broj golova");
				
			prvi -> ObradiUtakmicu(brojDatihPrvi,brojDatihDrugi);
			drugi -> ObradiUtakmicu(brojDatihDrugi,brojDatihPrvi);
		}
		
		void IspisiTabelu() {
			std::sort(timovi,timovi+brojTimova,sortKriterij);
			for(int i=0;i<brojTimova;i++) timovi[i] -> IspisiPodatke();
		}
};

Liga::Liga(std::initializer_list<Tim> listaTimova):maxBrojTimova(listaTimova.size()),brojTimova(listaTimova.size()),timovi(new Tim*[listaTimova.size()]) {
	for(int i=0;i<listaTimova.size();i++) timovi[i] = nullptr;
		try {
			int j=0;
			for(auto i:listaTimova) {
				timovi[j] = new Tim(i);
				j++;
			}
		} catch(std::exception &err) {
			std::cout << err.what();
			for(int i=0;i<maxBrojTimova;i++)
				delete timovi[i];
			
			delete[] timovi;
			throw;
		}
}

int main ()
{
	Liga l1{"Borac", "Celik", "Jedinstvo","Sarajevo","Zeljeznicar","Zrinjski"};
	
	for(;;) {
		char imePrvog[20],imeDrugog[20];
		std::cout << "Unesite ime prvog time (ENTER za kraj): ";
		std::cin.getline(imePrvog,20);
		std::cout << "Unesitei me drugog tima: ";
		std::cin.getline(imeDrugog,20);
		
		int postignutiPrvi,postignutiDrugi;
		std::cout << "Unesite broj postignutih golova za oba tima: ";
		std::cin >> postignutiPrvi >> postignutiDrugi;
		
		try {
			l1.RegistrirajUtakmicu(imePrvog,imeDrugog,postignutiPrvi,postignutiDrugi);
		} catch(std::exception &err) {
			std::cout << err.what() << std::endl;
		}
		
		std::cout << std::endl;
		l1.IspisiTabelu();
		std::cout << std::endl;
	}
	
	return 0;
}


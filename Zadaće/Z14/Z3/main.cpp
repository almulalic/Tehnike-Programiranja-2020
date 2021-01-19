//TP 2018/2019: Tutorijal 14, Zadatak 3
#include <iostream>

#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
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
		friend std::ostream& operator << (std::ostream& izlaz, const Tim& tim);
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

std::ostream& operator << (std::ostream& izlaz, const Tim& tim) {
    izlaz << std::left << std::setw(20) << tim.imeTima << std::right << std::setw(4) << tim.brojOdigranih << std::setw(4) << tim.brojPobjeda << std::setw(4) << tim.brojNerjsenih << std::setw(4) << tim.brojPoraza << std::setw(4)
	<< tim.brojDatih << std::setw(4) << tim.brojPrimljenih << std::setw(4) << tim.brojPoena << std::endl;
	
	return izlaz;
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
		
		void ObrisiSve() { for(int i=0;i < brojTimova;i++) delete timovi[i]; }
		
		void SacuvajStanje(std::string imeDatoteke);
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

void Liga::SacuvajStanje(std::string imeDatoteke) {
    std::ofstream izlaz(imeDatoteke,std::ios::out);
    for(int i=0;i<this -> brojTimova;i++) 
    	izlaz << *(timovi[i]);
}

int main () {
    
    Liga l1{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo", "FK Sloboda", "FK Krupa", "FK Radnik Bijeljina"};
	  
	l1.RegistrirajUtakmicu("FK Sloboda", "HSK Zrinjski",1,1);
	l1.RegistrirajUtakmicu("FK Sarajevo", "HSK Zrinjski",1,2);
	l1.RegistrirajUtakmicu("FK Krupa", "FK Radnik Bijeljina",1,1);
	l1.RegistrirajUtakmicu("NK Zeljeznicar","FK Krupa",1,0);
	l1.RegistrirajUtakmicu("FK Radnik Bijeljina", "FK Sloboda",0,1);
	l1.RegistrirajUtakmicu("FK Sarajevo", "NK Zeljeznicar",0,3);
	  
	std::cout << "Orginalna Liga za Prvaka: " << std::endl;
	l1.IspisiTabelu();
	l1.SacuvajStanje("BINARNA.DAT");
    
	return 0;
}
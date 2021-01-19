//TP 2018/2019: Zadaća 4, Zadatak 5
#include <iostream>

#include <string>
#include <map>

struct Korisnik {
    std::string ime;
    std::string prezime;
    std::string adresa;
    std::string telefon;
};

class Knjiga {
    std::string naslov;
    std::string imePisca;
    std::string zanr;
    int godinaIzdavanja;
    Korisnik* zaduzenaOsoba;

public:
    Knjiga(std::string naslov,std::string imePisca,std::string zanr,int godinaIzdavanja) : naslov(naslov), imePisca(imePisca), zanr(zanr), godinaIzdavanja(godinaIzdavanja), zaduzenaOsoba(nullptr) {}

    std::string DajNaslov() { return naslov; }
    std::string DajAutora() { return imePisca; }
    std::string DajZanr() { return zanr; }
    int DajGodinuIzdavanja() { return godinaIzdavanja; }
    Korisnik* DajKodKogaJe() { return zaduzenaOsoba; }
    
    void ZaduziKnjigu(Korisnik &korisnik) {
        zaduzenaOsoba = &korisnik;
    }
    
    void RazduziKnjigu() {
        zaduzenaOsoba = nullptr;
    }
    
    bool DaLiJeZaduzena() { return zaduzenaOsoba != nullptr; }
};

class Biblioteka {
    
    std::map<int,Korisnik*> korisnici;
    std::map<int,Knjiga*> knjige;

public:
    
    Biblioteka() {}

    ~Biblioteka() {
        for(auto it=korisnici.begin();it != korisnici.end(); ++it) {
            delete it -> second;
        }      
        
        for(auto it=knjige.begin();it != knjige.end(); ++it) {
            delete it -> second;
        }      
    }
 
    Biblioteka &operator =(const Biblioteka &biblioteka) {
        
        if(&biblioteka != this) {
            
            for(auto it = korisnici.begin();it != korisnici.end(); ++it) {
                it -> second = nullptr;
            }
            
            for(auto it = knjige.begin();it != knjige.end(); ++it) {
                it -> second = nullptr;
            }
            
            korisnici.clear();
            knjige.clear();
            
            for(auto it = biblioteka.korisnici.begin();it != biblioteka.korisnici.end(); ++it) {
                korisnici.insert(std::make_pair(it -> first,it -> second));
            }
            
            for(auto it = biblioteka.knjige.begin();it != biblioteka.knjige.end(); ++it) {
                knjige.insert(std::make_pair(it -> first,it -> second));
            }   
        }
        
        return *this;
    }

    Biblioteka &operator =(Biblioteka &&novaBiblioteka) {
        
        if(&novaBiblioteka != this) {
            std::swap(korisnici,novaBiblioteka.korisnici);
            std::swap(knjige,novaBiblioteka.knjige);
        }
        
        return *this;
    }
    
    Biblioteka(const Biblioteka &novaBiblioteka){
        
        for(auto it = korisnici.begin();it != korisnici.end(); ++it) {
            it -> second = nullptr;
        }
        
        for(auto it = knjige.begin();it != knjige.end(); ++it) {
            it -> second = nullptr;
        }
        
        korisnici.clear();
        knjige.clear();
        
        for(auto it = novaBiblioteka.korisnici.begin();it != novaBiblioteka.korisnici.end(); ++it) {
            korisnici.insert(std::make_pair(it -> first,it -> second));
        }
        
        for(auto it = novaBiblioteka.knjige.begin();it != novaBiblioteka.knjige.end(); ++it) {
            knjige.insert(std::make_pair(it -> first,it -> second));
        }   

    }

    Biblioteka(Biblioteka &&novaBiblioteka) {
        std::swap(korisnici,novaBiblioteka.korisnici);
        std::swap(knjige,novaBiblioteka.knjige);
    }
    
    void RegistrirajNovogKorisnika(int clanskiBroj,std::string ime,std::string prezime,std::string adresa,std::string brojTelefona) {
        if(korisnici.find(clanskiBroj) != korisnici.end())
            throw std::logic_error("Korisnik vec postoji");
        
  
        korisnici.insert(std::make_pair(clanskiBroj,new Korisnik{ime,prezime,adresa,brojTelefona}));
    }
    
    void RegistrirajNovuKnjigu(int evidencijskiBrojKnjige,std::string naslov,std::string imePisca,std::string zanr,int godinaIzdavanja) {
        if(knjige.find(evidencijskiBrojKnjige) != knjige.end())
            throw std::logic_error("Knjiga vec postoji");
        
        knjige.insert(std::make_pair(evidencijskiBrojKnjige,new Knjiga(naslov,imePisca,zanr,godinaIzdavanja)));
    }
    
    Korisnik& NadjiKorisnika(int clanskiBroj) {
        auto korisnik = korisnici.find(clanskiBroj);
        
        if(korisnik == korisnici.end())
            throw std::logic_error("Korisnik nije nadjen");
       
       return *(korisnik -> second);     
    }
    
    Knjiga& NadjiKnjigu(int evidencijskiBrojKnjige) {
        auto knjiga = knjige.find(evidencijskiBrojKnjige);
        
        if(knjiga == knjige.end())
            throw std::logic_error("Knjiga nije nadjena");
       
       return *(knjiga -> second);     
    }
    
    void ZaduziKnjigu(int evidencijskiBrojKnjige,int clanskiBroj) {
        if(knjige.find(evidencijskiBrojKnjige) == knjige.end())
            throw std::logic_error("Knjiga nije nadjena");
        else if(korisnici.find(clanskiBroj) == korisnici.end())
            throw std::logic_error("Korisnik nije nadjen");
        else if(knjige.find(evidencijskiBrojKnjige) -> second -> DaLiJeZaduzena())
            throw std::logic_error("Knjiga vec zaduzena");
        
        knjige.find(evidencijskiBrojKnjige) -> second -> ZaduziKnjigu(*korisnici.find(clanskiBroj) -> second);
    }
    
    void RazduziKnjigu(int evidencijskiBrojKnjige) {
        if(knjige.find(evidencijskiBrojKnjige) == knjige.end())
            throw std::logic_error("Knjiga nije nadjena");
        else if(!knjige.find(evidencijskiBrojKnjige) -> second -> DaLiJeZaduzena())
            throw std::logic_error("Knjiga nije zaduzena");
            
        knjige.find(evidencijskiBrojKnjige) -> second -> RazduziKnjigu();    
    }
    
    void IzlistajKorisnike() const {
        for(auto it=korisnici.begin();it!=korisnici.end();++it) {
            std::cout << "Clanski broj: " << it -> first << std::endl;
            std::cout << "Ime i prezime: " << it -> second -> ime << " " << it -> second -> prezime << std::endl;
            std::cout << "Adresa: " << it -> second -> adresa << std::endl;
            std::cout << "Broj telefona: " << it -> second -> telefon << std::endl;
            std::cout << std::endl;
        }   
    }
    
    void IzlistajKnjige() const {
        for(auto it=knjige.begin();it!=knjige.end();++it) {
            std::cout << "Evidencijski broj: " << it -> first << std::endl;
            std::cout << "Naslov: " << it -> second -> DajNaslov() << std::endl;
            std::cout << "Pisac: " << it -> second -> DajAutora() << std::endl;
            std::cout << "Zanr: " << it -> second -> DajZanr() << std::endl;
            std::cout << "Godina izdavanja: " << it -> second -> DajGodinuIzdavanja() << std::endl;
            if(it -> second -> DaLiJeZaduzena()) {
                Korisnik* zaduzeni = it -> second -> DajKodKogaJe();
                std::cout << "Zaduzena kod korisnika: " << zaduzeni -> ime << " " << zaduzeni -> prezime << std::endl; 
            }
            std::cout << std::endl;
        }   
    }
    
    void PrikaziZaduzenja(int clanskiBroj) {
        if(korisnici.find(clanskiBroj) == korisnici.end())
            std::cout << "Korisnik nije nadjen";
        
        Korisnik korisnik = *korisnici.find(clanskiBroj) -> second;
        bool barJedanIspis(false);
        
        for(auto it = knjige.begin();it != knjige.end(); ++it) {
            if(it -> second -> DaLiJeZaduzena()) {
                if(it -> second -> DajKodKogaJe() -> ime == korisnik.ime && it -> second -> DajKodKogaJe() -> prezime == korisnik.prezime ) {
                    std::cout << "Evidencijski broj: " << it -> first << std::endl;
                    std::cout << "Naslov: " << it -> second -> DajNaslov() << std::endl;
                    std::cout << "Pisac: " << it -> second -> DajAutora() << std::endl;
                    std::cout << "Zanr: " << it -> second -> DajZanr() << std::endl;
                    std::cout << "Godina izdavanja: " << it -> second -> DajGodinuIzdavanja() << std::endl;
                    std::cout << std::endl;
                }
            }
        }
        
        if(!barJedanIspis)
            std::cout << "Nema zaduzenja za tog korisnika !";
    }
    
};


int main () {
    
    Biblioteka biblioteka;
    
    for(;;) {
        
        int unos;
        std::cout << "Unesite 1 za unos novog korisnika, 2 za unos nove knjige" << std::endl;
        std::cout << "Unesite 3 da pronadjete korisnika, 4 za pronalazak knjige" << std::endl;
        std::cout << "Unesite 5 da zaduzite knjigu, 6 da razduzite knjigu" << std::endl;
        std::cout << "Uneiste 7 da izlistate korisnike, 8 da izlistate knjige ili 9 da prikazete zaduzenja" << std::endl;
        
        std::cin >> unos;
        
        if(unos == -1)
            break;
        else if(unos == 1) {
            
            int clanskiBroj;
            std::string ime,prezime,adresa,telefon;
            
            std::cout << "Unesite clanski broj: ";
            std::cin >> clanskiBroj;
            std::cin.ignore(10000,'\n');
            std::cout << "Unesite ime: ";
            std::getline(std::cin, ime);
            std::cout << "Unesite prezime: ";
            std::getline(std::cin, prezime);
            std::cout << "Unesite adresu: ";
            std::getline(std::cin, adresa);
            std::cout << "Uneiste broj telefona: ";
            std::getline(std::cin, telefon);
            
            biblioteka.RegistrirajNovogKorisnika(clanskiBroj,ime,prezime,adresa,telefon);
            
        } else if(unos == 2) {
            
            int evidencijskiBrojKnjige,godinaIzdavanja;
            std::string naslov,imePisca,zanr;
            
            std::cout << "Unesite evidencijski broj knjige: ";
            std::cin >> evidencijskiBrojKnjige;
            std::cin.ignore(10000,'\n');
            std::cout << "Unesite naslov: ";
            std::getline(std::cin, naslov);
            std::cout << "Unesite ime pisca: ";
            std::getline(std::cin, imePisca);
            std::cout << "Unesite zanr: ";
            std::getline(std::cin, zanr);
            std::cout << "Uneiste godinu izdavanja: ";
            std::cin >> godinaIzdavanja;
            
            biblioteka.RegistrirajNovuKnjigu(evidencijskiBrojKnjige,naslov,imePisca,zanr,godinaIzdavanja);    
            
        } else if(unos == 3) {

            int clanskiBroj;
            std::cout << "Unesite clanski broj: ";
            std::cin >> clanskiBroj;
            
            Korisnik k = biblioteka.NadjiKorisnika(clanskiBroj);
            std::cout << k.ime;
            
        } else if(unos == 4) {

            int evidencijskiBrojKnjige;
            std::cout << "Unesite evidencijski broj: ";
            std::cin >> evidencijskiBrojKnjige;
            
            Knjiga k = biblioteka.NadjiKnjigu(evidencijskiBrojKnjige);
            std::cout << k.DajAutora();
    
        } else if(unos == 5) {
            
            int clanskiBroj,evidencijskiBrojKnjige;
            
            std::cout << "Unesite clanski broj studenta koji zaduzuje: ";
            std::cin >> clanskiBroj;
            
            std::cout << "Unesite evidencijski broj knjige koji se zaduzuje: ";
            std::cin >> evidencijskiBrojKnjige;
            
            biblioteka.ZaduziKnjigu(clanskiBroj,evidencijskiBrojKnjige);
            
        } else if(unos == 6) {
            
            int clanskiBroj,evidencijskiBrojKnjige;
            
            std::cout << "Unesite clanski broj studenta koji razducuje: ";
            std::cin >> clanskiBroj;
            
            std::cout << "Unesite evidencijski broj knjige koji se razduzuje: ";
            std::cin >> evidencijskiBrojKnjige;
            
            biblioteka.RazduziKnjigu(evidencijskiBrojKnjige);

        } else if (unos == 7) {
            biblioteka.IzlistajKorisnike();
        } else if(unos == 8) {
            biblioteka.IzlistajKnjige();
        } else if(unos == 9) {
            
            int clanskiBroj;
            
            std::cout << "Unesite clanski broj studenta: ";
            std::cin >> clanskiBroj;
            
            biblioteka.PrikaziZaduzenja(clanskiBroj);
            
        } else {
            std::cout << "Pogresan unos, pokusajte ponovo";
        }
        
    }
    
	return 0;
}
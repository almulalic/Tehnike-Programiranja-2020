//TP 2018/2019: Tutorijal 14, Zadatak 2
#include <iostream>

#include <algorithm>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>

class Spremnik {
protected:
    double tezina;
    char nazivPredmeta[40];
    double tezinaPredmeta;

public:
    Spremnik(double tezina,const char naziv[], double tezinaPred) : tezina(tezina), tezinaPredmeta(tezinaPred) { 
        strcpy(nazivPredmeta,naziv); 
    };
    
    virtual ~Spremnik() {};
    virtual Spremnik *DajKopiju() const = 0;
    
    virtual double DajTezinu() const { return tezina; }
    virtual double DajUkupnuTezinu() const { return tezina + tezinaPredmeta; }
    virtual void Ispisi() const { std::cout << "Default ispis"; };
    
    virtual bool operator <(const Spremnik& spremnik) {
        return this -> DajUkupnuTezinu() < spremnik.DajUkupnuTezinu();
    }
};

class Sanduk final : public Spremnik {
    int brojPredmeta;

public: 
    Sanduk(double tezina,const char naziv[],int brojPredmeta,double tezinaPredmeta) : Spremnik(tezina,naziv,tezinaPredmeta), brojPredmeta(brojPredmeta) { };
    Spremnik *DajKopiju() const override { return new Sanduk(*this); };
    double DajUkupnuTezinu() const override { return tezina + (brojPredmeta * tezinaPredmeta); } 
    
    void Ispisi() const {
        std::cout << "Vrsta spremnika: Sanduk" << std::endl;
        std::cout << "Sadrzaj: " << nazivPredmeta << std::endl;
        std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
    }
};

class Bure final : public Spremnik {

public:    
    Bure(double tezina,const char naziv[], double tezinaPredmeta) : Spremnik(tezina,naziv,tezinaPredmeta) {}

    Spremnik *DajKopiju() const override { return new Bure(*this); };

    void Ispisi() const {
        std::cout << "Vrsta spremnika: Bure" << std::endl;
        std::cout << "Sadrzaj: " << nazivPredmeta << std::endl;
        std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
    }
};

class Skladiste {
    int maksimalnaKolicina;
    int trenutnaKolicina;
    Spremnik **spremnik;

public:
    Skladiste(int maks) : maksimalnaKolicina(maks),trenutnaKolicina(0),spremnik(new Spremnik*[maks]{}) {}
    
    ~Skladiste() {
        for(int i=0;i<trenutnaKolicina;i++) {
            delete spremnik[i];
        }
        delete[] spremnik;
    }
    
    Skladiste(const Skladiste &s);
    
    Skladiste(Skladiste &&s);
    
    Skladiste& operator=(Skladiste &s);
    
    Skladiste& operator=(Skladiste &&s);
    
    void DodajSanduk(double tezina,const char naziv[],int brojPredmeta,double tezinaPredmeta);
    
    void DodajBure(double tezina,const char naziv[], double tezinaPredmeta);
    
    Spremnik& DajNajlaksi();

    Spremnik& DajNajtezi();
    
    int BrojPreteskih(int zadanaTezina) const;
    
    void IzlistajSkladiste() const;
    
    void UcitajIzDatoteke(const char [8]);
};

// Skladiste Skladiste::operator=(Skladiste &s) {
//     if(&s != this) {
//         for(int i=0;i<trenutnaKolicina;i++) delete spremnik[i];
        
//         delete[] spremnik;
        
//         spremnik = new Spremnik*[s.maksimalnaKolicina]{};
        
//         if(trenutnaKolicina < s.trenutnaKolicina) {
//             try {
//                 for(int i=trenutnaKolicina;i<s.trenutnaKolicina;i++)
//                     spremnik[i] = s.spremnik[i] -> DajKopiju();
//             } catch(...) {
//                 for(int i=trenutnaKolicina;i<s.trenutnaKolicina;i++)
//                     delete spremnik[i];
//             }
//         } else {
//             for(int i=s.trenutnaKolicina;i<trenutnaKolicina;i++) delete spremnik[i];
//         }
        
//         trenutnaKolicina = s.trenutnaKolicina;
//         maksimalnaKolicina = s.maksimalnaKolicina;
        
//         for(int i=0;i<trenutnaKolicina;i++)
//             *spremnik[i] = *(s.spremnik[i]) -> DajKopiju();
//     }
    
//     return *this;
// } Manuelna verzija

Skladiste& Skladiste::operator=(Skladiste &s) {
    std::swap(trenutnaKolicina,s.trenutnaKolicina);
    std::swap(maksimalnaKolicina,s.maksimalnaKolicina);
    std::swap(spremnik,s.spremnik);
    return *this;
}

Skladiste::Skladiste(const Skladiste &s) : maksimalnaKolicina(s.maksimalnaKolicina), trenutnaKolicina(s.trenutnaKolicina), spremnik(new Spremnik*[s.maksimalnaKolicina]{}) {
    try {
        for(int i=0;i<trenutnaKolicina;i++)
            spremnik[i] = s.spremnik[i] -> DajKopiju();
    } catch (...) {
        for(int i=0;i<trenutnaKolicina;i++) delete spremnik[i];
        
        delete[] spremnik;
    }
}

Skladiste::Skladiste(Skladiste &&s) : maksimalnaKolicina(s.maksimalnaKolicina), trenutnaKolicina(s.trenutnaKolicina),spremnik(s.spremnik) {
    s.spremnik = nullptr;
    s.trenutnaKolicina = 0;
    s.maksimalnaKolicina = 0;
}

Skladiste& Skladiste::operator=(Skladiste &&s) {
    std::swap(trenutnaKolicina,s.trenutnaKolicina);
    std::swap(maksimalnaKolicina,s.maksimalnaKolicina);
    std::swap(spremnik,s.spremnik);
    return *this;
}

void Skladiste::DodajSanduk(double tezina,const char naziv[],int brojPredmeta,double tezinaPredmeta) {
    
    if(trenutnaKolicina == maksimalnaKolicina)
        throw std::domain_error("Popunjeno skladiste");
    
    Sanduk *novi = nullptr;
    try {
        novi = new Sanduk(tezina,naziv,brojPredmeta,tezinaPredmeta);
        spremnik[trenutnaKolicina] = novi;
        trenutnaKolicina++;

    } catch(...) {
        delete novi;
        std::cout << "Problemi sa memorijom";
        throw;
    }
    
}

void Skladiste::DodajBure(double tezina,const char naziv[], double tezinaPredmeta) {
    if(trenutnaKolicina == maksimalnaKolicina)
        throw std::domain_error("Popunjeno skladiste");
    
    Bure *novo = nullptr;
    try {
        novo = new Bure(tezina,naziv,tezinaPredmeta);
        spremnik[trenutnaKolicina] = novo;
        trenutnaKolicina++;
    } catch(...) {
        delete novo;
        std::cout << "Problemi sa memorijom";
        throw;
    }

}

Spremnik& Skladiste::DajNajlaksi() { 
    if(trenutnaKolicina == 0) 
        throw std::range_error("Skladiste prazno");
        
    return **std::min_element(spremnik,spremnik+trenutnaKolicina,[](Spremnik *a,Spremnik *b){
        return a -> DajTezinu() < b -> DajTezinu();
    }); 
}

Spremnik& Skladiste::DajNajtezi() { 
    if(trenutnaKolicina == 0) 
        throw std::range_error("Skladiste prazno");
    
    return **std::max_element(spremnik,spremnik+trenutnaKolicina,[](Spremnik *a,Spremnik *b){
        return a -> DajTezinu() < b -> DajTezinu();
    });
}

int Skladiste::BrojPreteskih(int zadanaTezina) const {
    return std::count_if(spremnik,spremnik+trenutnaKolicina,[zadanaTezina](Spremnik *trenutni){
        return trenutni -> DajUkupnuTezinu() > zadanaTezina;
    });
}

void Skladiste::IzlistajSkladiste() const { 
    auto temp(*this);
    std::sort(temp.spremnik,temp.spremnik+trenutnaKolicina,[](Spremnik *a, Spremnik *b){
        return a -> DajUkupnuTezinu() > b -> DajUkupnuTezinu();
    }); 
    
    for(int i=0;i<trenutnaKolicina;i++)
        temp.spremnik[i] -> Ispisi();
}

void Skladiste::UcitajIzDatoteke(const char imeDatoteke[8]) {
    std::ifstream ulaz(imeDatoteke,std::ios::in);
    
    if(!ulaz) {
        throw std::logic_error("Trazena datoteka ne postoji");
    }
    
    for(int i=0;i<trenutnaKolicina;i++) {
        delete spremnik[i];
    }
    
    trenutnaKolicina = 0;
    
    char tipSpremnika=' ';
    char imeProizvoda[40];
    std::vector<double> podaci;
    
    while(!ulaz.eof()) {
        ulaz >> tipSpremnika;
        ulaz.get();
        ulaz.getline(imeProizvoda,sizeof imeProizvoda);

        double tezina;
        while(true) {
            ulaz >> tezina;
            podaci.push_back(tezina);
            
            char separator;
            if((separator = ulaz.peek()) == ' ') {
                ulaz.get();
            } else {
                if(separator == EOF) ulaz.clear();
                break;
            }       
        }
        
        if(tipSpremnika != 'S' && tipSpremnika != 'B')
            throw std::logic_error("Datoteka sadrzi besmislene podatke");
        else if(podaci.size() <= 1)
            break;
        
        if(tipSpremnika == 'S') {
            DodajSanduk(podaci.at(0),imeProizvoda,(int) podaci.at(1), podaci.at(2));
        } else if (tipSpremnika == 'B') {
            DodajBure(podaci.at(0),imeProizvoda,podaci.at(1));
        } 
        
        podaci.clear();
        ulaz.clear();
        if(ulaz.get() == EOF) break;
        if(ulaz.bad()) 
            throw std::logic_error("Problemi pri citanju datoteke");
    }

}

int main () {
  //#include <string>
    {//AT6: samo jedan podtak u datoteci
        Skladiste s (10);
        std::ofstream g ("DEF.TXT");
        g << "S Burgije" << std::endl
          << "80 24995 1" << std::endl;
        g.close();
        s.UcitajIzDatoteke("DEF.TXT");
        s.IzlistajSkladiste();
        std::cout << "---------------------" << std::endl;
        //radi vaseg testiranja, sta ako je datoteka prazna?
        //necemo nastimati da pada AT zbog toga, ali je jako korisno
        //da imate i takav AT. Ocekivano je da Skladiste bude PRAZNO
        //ali ce biti priznavano i ako se prijavi greska
        //ipak, krahiranje programa **ne dolazi u obzir**
        std::ofstream f ("ABC.TXT");
        f.close();
        std::string p;
        try {s.UcitajIzDatoteke("ABC.TXT"); s.IzlistajSkladiste();}
        catch (const std::logic_error &e) {p = e.what();}
        if (p == "Datoteka sadrzi besmislene podatke" || p == "Problemi pri citanju datoteke")
            std::cout << "Alternativni izlaz: i ovo je OK!";
    }
	return 0;
}
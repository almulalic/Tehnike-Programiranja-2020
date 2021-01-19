//TP 2018/2019: Zadaća 5, Zadatak 3
#include <iostream>

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h> 

class Narudzba {
    char nazivObroka[40];
    double cijenaObroka;
    char narucioc[40];
  
public:
    
      Narudzba(const char no[],double cijena,const char ni[]) : cijenaObroka(cijena) {
        strcpy(nazivObroka,no);
        strcpy(narucioc,ni);
      }
      
      virtual ~Narudzba() {}
      
      virtual std::string DajNazivObroka() const { return nazivObroka; }
      
      virtual double DajCijenuObroka() const { return cijenaObroka; }
      
      virtual std::string DajNarucioca() const { return narucioc; }
      
      virtual void Ispisi() const;
      
      virtual double DajUkupnuCijenu() const { return cijenaObroka; }
      
      virtual Narudzba *DajKopiju() const { return new Narudzba(*this); }
    
};

void Narudzba::Ispisi() const {
    std::cout << "Obrok: " << nazivObroka << std::endl 
    << "Cijena: " << cijenaObroka << " KM" << std::endl
    << "Narucilac: " << narucioc;
}

class NarudzbaSaPicem : public Narudzba {
    char nazivPica[40];
    double cijenaPica;

public:
  
    NarudzbaSaPicem(const char no[],double cijena,const char ni[],const char np[],double cijenaPica) : Narudzba(no,cijena,ni), cijenaPica(cijenaPica) {
      strcpy(nazivPica,np);
    }
    
    std::string DajNazivPica() const { return nazivPica; }
    
    void  Ispisi() const;
    
    double DajCijenu() const { return cijenaPica; }
    
    NarudzbaSaPicem *DajKopiju() const override { return new NarudzbaSaPicem(*this); }

};

void NarudzbaSaPicem::Ispisi() const {
    std::cout << "Obrok: " << DajNazivObroka() << std::endl 
    << "Pice: " << nazivPica << std::endl
    << "Cijena: " << DajCijenuObroka() << " KM" << std::endl
    << "Cijena pica: " << cijenaPica << " KM" << std::endl
    << "Ukupna cijena: " << DajUkupnuCijenu() + cijenaPica << " KM" << std::endl
    << "Narucilac: " << DajNarucioca(); 
}

class Narudzbe {

  std::vector<Narudzba*> narudzbe;

public:
    
    explicit Narudzbe() {};
    
    Narudzbe(const Narudzbe &n);
    
    Narudzbe operator=(const Narudzbe &n);
    
    ~Narudzbe() { for(int i=0;i<narudzbe.size();++i) delete narudzbe.at(i); }
    
    void NaruciObrok(const char no[],double cijena,const char ni[]);
    
    void NaruciObrokSaPicem(const char no[],double cijena,const char ni[],const char np[],double cijenaPica);
    
    void ObradiNarudzbu();
    
    bool DaLiImaNarudzbi() const;
    
    double operator[](std::string ime) const;
    
    void UcitajIzDatoteka(std::string imePrve,std::string imeDruge);
};

Narudzbe::Narudzbe(const Narudzbe &n) {
    if(narudzbe.size() > n.narudzbe.size()) {
        for(int i=n.narudzbe.size();i<narudzbe.size();++i)
            delete narudzbe.at(i);
    } else {
        try {
            for(int i=narudzbe.size();i<n.narudzbe.size();++i)
                narudzbe.at(i) = new Narudzba(*n.narudzbe.at(i));
        } catch(...) {
            std::cout << "Problemi sa memorijom";
            return;
        }
    }
    
    for(int i=0;i<narudzbe.size();i++)
        *narudzbe.at(i) = *n.narudzbe.at(i);
}

Narudzbe Narudzbe::operator=(const Narudzbe &n) {
    if(&n != this) {
        if(narudzbe.size() > n.narudzbe.size()) {
            for(int i=n.narudzbe.size();i<narudzbe.size();++i)
                delete narudzbe.at(i);
        } else {
            try {
                for(int i=narudzbe.size();i<n.narudzbe.size();++i)
                    narudzbe.at(i) = new Narudzba(*n.narudzbe.at(i));
            } catch(...) {
                std::cout << "Problemi sa memorijom";
                throw;
            }
        }
        
        for(int i=0;i<narudzbe.size();i++)
            *narudzbe.at(i) = *n.narudzbe.at(i);
    }
    
    return *this;
}

void Narudzbe::NaruciObrok(const char no[],double cijena,const char ni[]) {
    try {
        narudzbe.push_back(new Narudzba(no,cijena,ni));
    } catch(...) {
        std::cout << "Problemi sa memorijom";
    }
}

void Narudzbe::NaruciObrokSaPicem(const char no[],double cijena,const char ni[],const char np[],double cijenaPica) {
    try {
        narudzbe.push_back(new NarudzbaSaPicem(no,cijena,ni,np,cijenaPica));
    } catch(...) {
        std::cout << "Problemi sa memorijom";
    }
}

void Narudzbe::ObradiNarudzbu() {
    if(narudzbe.size() == 0)
        throw std::range_error("Nema vise narudzbi");
    
    narudzbe.at(0) -> Ispisi();
    
    delete narudzbe.at(0);
    
    narudzbe.erase(narudzbe.begin(),narudzbe.begin()+1);
}

bool Narudzbe::DaLiImaNarudzbi() const {
    return narudzbe.size();
}

double Narudzbe::operator[](std::string ime) const {
    
    double suma(0);
    
    for(Narudzba *n :narudzbe) {
        if(n -> DajNarucioca() == ime) {
            suma+=(n -> DajUkupnuCijenu());
        }
    }
    
    return suma;
}

void Narudzbe::UcitajIzDatoteka(std::string narudzbe,std::string cijene) {
    
   std::ifstream ulazNarudzbe(narudzbe);

    if(!ulazNarudzbe)
        throw std::logic_error("Trazena datoteka ne postoji");
    
    while(!ulazNarudzbe.eof()) {
        std::string narucioc,jelo,pice;
        std::getline(ulazNarudzbe,narucioc);
        std::getline(ulazNarudzbe,jelo);
        std::getline(ulazNarudzbe,pice);
        
        bool obrokSaPicem(!pice.empty());
        
        std::ifstream ulazCijene(cijene);
        
        if(!ulazCijene)
            throw std::logic_error("Trazena datoteka ne postoji");
        
        std::string ucitaniObrok;
        double cijenaObroka;
        
        while(ulazCijene.eof()) {
            std::getline(ulazCijene,ucitaniObrok);
            ulazCijene >> cijenaObroka;
            if(!ulazCijene)
                ulazCijene.ignore(10000,'\n');
            
            if(jelo == ucitaniObrok) break;
        }
        
        if(obrokSaPicem) {
            ulazCijene.close();
            ulazCijene.open(cijene);
            
            std::string ucitanoPice;
            double cijenaPica;
            bool imaPice(false);
            
            while(ulazCijene.eof()) {
                std::getline(ulazCijene,ucitanoPice);
                ulazCijene >> cijenaPica;
                
                if(!ulazCijene)
                    ulazCijene.ignore(9999,'\n');
                
                if(pice == ucitanoPice) { imaPice = true; break; }
            }
            
            NaruciObrokSaPicem(jelo.c_str(), cijenaObroka, narucioc.c_str(), pice.c_str(),cijenaPica);
        } else 
            NaruciObrok(jelo.c_str(),cijenaObroka,narucioc.c_str());
    }
}

int main () {
    
    try {
        Narudzbe n;
        
        n.NaruciObrok("Burek",2.5,"Bil Klinton");
        n.NaruciObrokSaPicem("Cevapi",3,"Esad Plavi","Coca-Cola", 2.5);
        n.NaruciObrok("Pizza",4,"Redzep");
        n.NaruciObrokSaPicem("Cheesburger",3,"Enes Begovic","Sprite",1.5);
        
        Narudzbe noveNarudzbe(n);
        
        std::cout << n["Esad plavi"];
        
        Narudzbe noveNarudzbe2(std::move(noveNarudzbe));
        
        noveNarudzbe = std::move(noveNarudzbe2);
        
        std::cout << noveNarudzbe2.DaLiImaNarudzbi() << std::endl;
        
        while(noveNarudzbe.DaLiImaNarudzbi()) {
            noveNarudzbe.ObradiNarudzbu();
            std::cout << std::endl;
        }
        
        Narudzbe noveNaruzbe3;
        
        noveNaruzbe3.NaruciObrok("Tarhana",3,"Zeljko Joksimovic");
        noveNaruzbe3 = n;
        
        for(int i=0;i<4;++i) noveNaruzbe3.ObradiNarudzbu();
        
        Narudzba anesova("Hamburger",4, "Anes");
        
        std::cout << anesova.DajUkupnuCijenu() << std::endl;
        
        auto p(anesova.DajKopiju());
        
        p -> Ispisi();
        
        delete p;
        
        Narudzbe narudzbe;
        narudzbe.UcitajIzDatoteka("NARUDZBE.TXT","CIJENE.TXT");
        
        while(narudzbe.DaLiImaNarudzbi())
            narudzbe.ObradiNarudzbu();
    } catch(std::logic_error e) {
        std::cout << e.what();
    } catch(std::range_error e) {
        std::cout << e.what();
    }
    
	return 0;
}
//TP 2018/2019: Zadaća 5, Zadatak ss
#include <iostream>

#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <initializer_list>

class ApstraktnoVozilo {
protected:

    int tezinaVozila;
    
public:
    ApstraktnoVozilo(int tezinaVozila) : tezinaVozila(tezinaVozila) {}
    
    virtual ~ApstraktnoVozilo() {}
    
    virtual int DajTezinu() const { return tezinaVozila; }
    
    virtual int DajUkupnuTezinu() const =0;
    
    virtual ApstraktnoVozilo *DajKopiju() const =0;
    
    virtual void IspisiPodatke() const=0;
};


class Automobil : public ApstraktnoVozilo {
    
    std::vector<int> tezinePutnika;
    int tezinaPutnika;
    
public:

    Automobil(int tezina, std::vector<int> tezine) : ApstraktnoVozilo(tezina), tezinePutnika(tezine) {
        int suma(0);
        for(int broj:tezine)
            suma += broj;
        
        tezinaPutnika = suma;
    }
    
    int DajTezinu() const  { return tezinaVozila; }
    
    int DajUkupnuTezinu() const override { return tezinaVozila + tezinaPutnika; }
    
    Automobil *DajKopiju() const override{ return new Automobil(*this); }
    
    void IspisiPodatke() const override;
    
};

void Automobil::IspisiPodatke() const {
    std::cout << "Vrsta vozila: Automobil" << std::endl
    << "Vlastita tezina: " << tezinaVozila << " kg" << std::endl
    << "Tezine putnika: ";
    for(int i=0;i<tezinePutnika.size();++i) {
            std::cout << tezinePutnika.at(i) << " kg";
        if(i < tezinePutnika.size())
            std::cout << ", ";
        else
            std::cout << std::endl;
    }
    
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg";
}


class Kamion : public ApstraktnoVozilo {
  
  int tezinaTereta;
  
public:
    
    Kamion(int tezinaVozila, int tezinaTereta) : ApstraktnoVozilo(tezinaVozila), tezinaTereta(tezinaTereta) {} 
    
    ~Kamion() {}
    
    int DajTezinu() const override { return tezinaVozila; }
    
    int DajUkupnuTezinu() const override { return tezinaVozila + tezinaTereta; }
    
    Kamion *DajKopiju() const override { return new Kamion(*this); }
    
    void IspisiPodatke() const override;
};

void Kamion::IspisiPodatke() const {
    
    std::cout << "Vrsta vozila: Kamion" << std::endl
    << "Vlastita tezina: " << tezinaVozila << " kg" << std::endl
    << "Tezina tereta: " << tezinaTereta << " kg" << std::endl
    << "Ukupna tezina: " << DajUkupnuTezinu() << " kg";
    
}


class Autobus : public ApstraktnoVozilo {
   int ukupanBrojPutnika;
   int prosjecnaTezinaPutnika;
        
public:
    
    Autobus(int tezinaVozila,int ukupanBrojPutnika, int prosjecnaTezinaPutnika) : ApstraktnoVozilo(tezinaVozila) , ukupanBrojPutnika(ukupanBrojPutnika), prosjecnaTezinaPutnika(prosjecnaTezinaPutnika) {}
    
    int DajTezinu() const override { return tezinaVozila; }
         
    int DajUkupnuTezinu() const override { return tezinaVozila + (ukupanBrojPutnika * prosjecnaTezinaPutnika); }
    
    Autobus *DajKopiju() const override { return new Autobus(*this); }
    
    void IspisiPodatke() const override;
};

void Autobus::IspisiPodatke() const  {
    
    std::cout << "Vrsta vozila: Autobus" << std::endl
    << "Vlastita tezina: " << tezinaVozila << " kg" << std::endl
    << "Broj putnika: " << ukupanBrojPutnika << std::endl
    << "Prosjecna tezina putnika: " << prosjecnaTezinaPutnika << " kg" << std::endl
    << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
    
}


class Vozilo {
    ApstraktnoVozilo *vozilo;
    
public:
    Vozilo() : vozilo(nullptr) {}
    
    ~Vozilo() { delete vozilo; }
    
    Vozilo(const ApstraktnoVozilo &av) : vozilo(av.DajKopiju()) {}
    
    Vozilo(const Vozilo &v);
    
    Vozilo(Vozilo &&v);
    
    Vozilo operator =(const Vozilo &v);
    
    Vozilo operator =(Vozilo &&v);
    
    int DajTezinu() const { if(vozilo) return vozilo -> DajTezinu(); else return 0; }
    int DajUkupnuTezinu() const { if(vozilo) return vozilo -> DajUkupnuTezinu(); else return 0; }
    void IspisiPodatke() const { if(vozilo) vozilo -> IspisiPodatke(); else return; }
};

Vozilo::Vozilo(const Vozilo &v) {
    if(!v.vozilo) 
        vozilo = nullptr;
    else 
        vozilo = v.vozilo -> DajKopiju();
}

Vozilo::Vozilo(Vozilo &&v) {
    vozilo = v.vozilo;
    v.vozilo = nullptr;
}

Vozilo Vozilo::operator =(const Vozilo &v) {
    if(&v != this) {
        delete vozilo;
        
        if(!vozilo) 
            vozilo = nullptr;
        else
            vozilo = v.vozilo -> DajKopiju();
    }
    
    return *this;
}

Vozilo Vozilo::operator =(Vozilo &&v) {
    if(&v != this) {
        delete vozilo;
        
        vozilo = v.vozilo;
        v.vozilo = nullptr;
    }
    
    return *this;
}
    
int main () {
    try {
        std::vector<Vozilo> vozila;
        
        std::ifstream ulaz("VOZILA.TXT");
        
        if(!ulaz)
            throw std::logic_error("Datoteka ne postoji");
        
        while(!ulaz.eof()) {
            std::string vozilo;
            std::getline(ulaz,vozilo);
            
            if(vozilo[0] == 'A') {
                vozilo.erase(vozilo.begin());
                vozilo+=" -1";
                std::vector<int> brojevi;
                std::istringstream tok(vozilo);
                
                while(true) {
                    int broj;
                    tok >> broj;
                    
                    if(broj == -1)
                        break;
                        
                    brojevi.push_back(broj);
                }
                
                int tezina(brojevi[0]);
                
                brojevi.erase(brojevi.begin(), brojevi.begin() + 2);
                Automobil a(tezina,brojevi);
                
                vozila.emplace_back(a);
                
            } else if(vozilo[0] == 'K') {
                vozilo.erase(vozilo.begin());
                vozilo+=" -1";
                std::vector<int> brojevi;
                std::istringstream tok(vozilo);
                
                while(true) {
                    int broj;
                    tok >> broj;
                    if(broj == -1)
                        break;
                    
                    brojevi.push_back(broj);
                }
                
                Kamion k(brojevi[0],brojevi[1]);
                vozila.emplace_back(k);
            } else if(vozilo[0] == 'B') {
                vozilo.erase(vozilo.begin());
                vozilo += " -1";
                
                std::vector<int> brojevi;
                std::istringstream tok(vozilo);
                
                while(true) {
                    int broj;
                    tok >> broj;
                    
                    if(broj == -1)
                        break;
                    
                    brojevi.push_back(broj);
                }
                
                Autobus b(brojevi[0],brojevi[1],brojevi[2]);
                vozila.emplace_back(b);
            }
        }
        
        for(Vozilo v: vozila) {
            v.IspisiPodatke();
            std::cout << std::endl;
        }
        
        std::sort(vozila.begin(), vozila.end(), [](const Vozilo &v1, const Vozilo &v2) { return v1.DajUkupnuTezinu() < v2.DajUkupnuTezinu(); });
        std::cout << "Ukupne tezine vozila nakon sortiranja " << std::endl;
        
        for(Vozilo v:vozila) {
            std::cout << v.DajUkupnuTezinu() << std::endl;
        }
    } catch(std::logic_error e) {
        std::cout << e.what();
    }
    
	return 0;
}
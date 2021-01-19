//TP 2018/2019: Ispit 6, Zadatak 3
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// 4/5 AT

class Razlomak {
    int brojnik;
    int nazivnik;

    static void ValidirajUnos(int nazi) { if(nazi == 0) throw std::domain_error("Nevaljatinesto"); };
    
public:
    
    Razlomak(int bro,int naz = 1) {
        
        try {
            this -> ValidirajUnos();
        } catch(std::domain_error err) {
            throw err;
        }
        
        brojnik = bro;
        nazivnik = naz;
    }
    
    int DajBrojnik() const { return brojnik; }
    
    int DajNazivnik() const { return nazivnik; }
    
    void PostaviBrojnik(int novi) {
        try {
            ValidirajUnos(novi);
        } catch(std::domain_error err) {
            throw err;
        }
        
        brojnik = novi; 
        
    }
    
    void PostaviNazivnik(int novi) {
         try {
            ValidirajUnos(novi);
        } catch(std::domain_error err) {
            throw err;
        }
        
        nazivnik = novi; 
    
    }
    
};

Razlomak operator+(const Razlomak &a,const Razlomak &b) {
    return c(a.brojnik + b.brojnik, a.nazivnik + b.nazivnik);
}

Razlomak operator*(const Razlomak &a,const Razlomak &b) {
    return c(a.brojnik * b.brojnik, a.nazivnik * b.nazivnik);
}

bool operator>(const Razlomak &a,const Razlomak &b) {
    return a.brojnik / a.nazivnik > b.brojnik / b.nazivnik;
}

bool operator<(const Razlomak &a,const Razlomak &b) {
    return !(a > b);
}

bool operator==(const Razlomak &a,const Razlomak &b) {
    return a.brojnik / a.nazivnik == b.brojnik / b.nazivnik;
}

bool operator!=(const Razlomak &a,const Razlomak &b) {
     return !(a.brojnik == b.brojnik);
}

std::ostream& operator<<(std::ostream& sda, const Razlomak &a) {
    return sda << a.brojnik << "/" << a.nazivnik;
}

std::istream& operator<<(std::istream& sdp, const Razlomak &a) {
    std::cout << "Unesi brojnik:";
    sdp >> a.brojnik;
}



class Spremnik {
protected:
    double tezina;
    
public:
    virtual &Spremnik() {}
    double DajTezinu() const { return tezina; }
    virtual double DajUkupnuTezinu() const { return tezina; }
    virtual void Ispisi() const { std::cout << "Default ispis"; }
};

class Sanduk : public Spremnik {
    std::string nazivPredmeta;
    int brojPredmeta;
    double tezinaPredmeta;
    
public:

    Sanduk(double t,std::string np,int bp,double tp) {
        if(t < 0 || bp < 0 || tp < 0)
            throw std::domain_error("Neispravni parametri");
        
        tezina = t;
        nazivPredmeta = np;
        brojPredmeta = bp;
        tezinaPredmeta = tp;
    }
    
    double DajUkupnuTezinu() const override { 
        return tezina + (tezinaPredmeta * brojPredmeta);
    }
    
    void Ispisi() const {
        std::cout << "Sanduk " << tezina << " " << nazivPredmeta << " " << brojPredmeta << " " << tezinaPredmeta << std::endl;  
    }
    
};

class Bure : public Spremnik {
    std::string nazivTecnosti;
    double tezinaTecnosti;

public:
    Bure(double t,std::string nt,double tt) {
        if(t < 0 || tt < 0)
            throw std::domain_error("Neispravni parametri");
        
        tezina = t;
        nazivTecnosti = nt;
        tezinaTecnosti = tt;
    }
    
     double DajUkupnuTezinu() const override { 
        return tezina + tezinaTecnosti;
    }
    
    void Ispisi() const {
        std::cout << "Bure " << tezina << " " << nazivTecnosti << " " << tezinaTecnosti << std::endl;   
    }
};

class MuzickiZnak {
    Razlomak trajanje; 
    virtual std::string opis = "ImplementirajMetoduDebilu";
    
public:

    explicit MuzickiZnak(Razlomak trajanjeTemp) : trajanje(trajanje);
    
    Razlomak DajTrjanje() const { return trajanje; }
    
}
    Razlomak operator+(const MuzickiZnak& prvi,const MuzickiZnak& drugi) {
        return prvi.DajTrajanje() + drugi.DajTrajanje();
    }
    
    MuzickiZnak operator+(const MuzickiZnak& prvi,const MuzickiZnak& drugi) {
        MuzickiZnak novi = MuzickiZnak(prvi.DajTrajanje() + drugi.DajTrajanje())
        return novi;
    }
    
    virtual void opisZnaka()  { std::cout << opis << "(" << trajanje << ")"; } 
}    


class Skladiste  {
    std::vector<std::shared_ptr<Spremnik>> spremnik;
  
public:
    Skladiste() {}
    
    Skladiste(Skladiste &s) {
        spremnik.resize(s.spremnik.size());
        
        for(int i=0;i<s.spremnik.size();++i)
            spremnik.at(i) = s.spremnik.at(i);
    }
    
    Skladiste(Skladiste &&s) {
        spremnik.resize(s.spremnik.size());
        std::swap(spremnik,s.spremnik);
    }
    
    Skladiste& operator=(Skladiste &s) {
        if(&s != this) {
            spremnik.resize(s.spremnik.size());
            
            for(int i=0;i<s.spremnik.size();++i)
            spremnik.at(i) = s.spremnik.at(i);
        }
        
        return *this;
    }
    
    Skladiste& operator=(Skladiste &&s) {
        spremnik.resize(s.spremnik.size());
        std::swap(spremnik,s.spremnik);
    }
    
    int DajBrojObjekata() const { return spremnik.size(); }
    
    void DodajSanduk(double tezina,std::string nazivPredmeta,int brojPredmeta,double tezinaPredmeta) {
        if(tezina < 0 || brojPredmeta < 0 || tezinaPredmeta < 0)
            throw std::domain_error("Neispravni parametri");
        
        spremnik.push_back(std::make_shared<Sanduk>(tezina,nazivPredmeta,brojPredmeta,tezinaPredmeta));
    }
    
    void DodajBure(double tezina,std::string nazivTecnosti,double tezinaTecnosti) {
        if(tezina < 0 || tezinaTecnosti < 0)
            throw std::domain_error("Neispravni parametri");
        
        spremnik.push_back(std::make_shared<Bure>(tezina,nazivTecnosti,tezinaTecnosti));
    }
    
    Spremnik& DajNajlaksi() const {
        return **std::min_element(spremnik.begin(),spremnik.end(),[](std::shared_ptr<Spremnik> a,std::shared_ptr<Spremnik> b) {
            return a -> DajTezinu() < b -> DajTezinu();
        });
    }
    
    int DajBrojPreteskih(double zadanaTezina) const {
        return std::count_if(spremnik.begin(),spremnik.end(),[zadanaTezina](std::shared_ptr<Spremnik> s) {
            return s -> DajUkupnuTezinu() > zadanaTezina;
        });
    }
    
    Spremnik& operator[](int index) const {
        if(index < 0 || index > spremnik.size())
            throw std::range_error("Neispravan indeks");
        
        return *spremnik.at(index - 1);
    }
    
    void Ispisi() const {
        auto sp = this -> spremnik;
        
        std::sort(sp.begin(),sp.end(),[](std::shared_ptr<Spremnik> a,std::shared_ptr<Spremnik> b) {
            return a -> DajUkupnuTezinu() > b -> DajUkupnuTezinu();
        });
        
      for(auto s : sp) 
        s -> Ispisi();
    }
};

int main () {
    
    char input;
    
    double tezinaSanduka;
    std::string sadrzajSanduka;
    int brojPredmetaSanduka;
    double tezinaPredmetaSanduka;
    
    double tezinaBureta;
    std::string sadrzajBureta;
    double tezinaTecnostiBureta;
    
    Skladiste s;
    
    std::cout << "S - sanduk, B - bure, K - kraj: ";
    std::cin >> input;
    while(input != 'K') {
        if(input == 'S') {
            std::cout << "Tezina sanduka: ";
            std::cin >> tezinaSanduka;
            std::cout << "Sadrzaj: ";
            std::cin >> sadrzajSanduka;
            std::cout << "Broj predmeta: ";
            std::cin >> brojPredmetaSanduka;
            std::cout << "Tezina predmeta: ";
            std::cin >> tezinaPredmetaSanduka;
        
            s.DodajSanduk(tezinaSanduka,sadrzajSanduka,brojPredmetaSanduka,tezinaPredmetaSanduka);
            
        } else if(input == 'B') {
            std::cout << "Tezina bureta: ";
            std::cin >> tezinaBureta;
            std::cout << "Sadrzaj: ";
            std::cin >> sadrzajBureta;
            std::cout << "Tezina tecnosti: ";
            std::cin >> tezinaTecnostiBureta;
            
            s.DodajBure(tezinaBureta,sadrzajBureta,tezinaTecnostiBureta);     
        } else if(input == 'K') {
            break;
        }
        
        std::cout << "S - sanduk, B - bure, K - kraj: ";
        std::cin >> input;
    }
    
    s.Ispisi();
    
	return 0;
}
//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>

#include <cstring>
#include <utility>
#include <iomanip>
#include <cstring>
#include <iterator>
#include <algorithm>
#include <initializer_list>

class Let {
    static const int duzinaOdredista = 30;
    static const int duzinaOznake = 10;
    
    char nazivOdredista[duzinaOdredista];    
    char oznakaLeta[duzinaOznake];
    int brojKapije;
    std::pair<int,int> vrijemePolijetanja;
    int trajanjeLeta;
    int kasnjenje;
    
    static std::pair<int,int> UracunajKasnjenje(std::pair<int,int> vrijeme,int kasnjenje) {
        int minute = (vrijeme.second + kasnjenje) % 60;
        int sati = vrijeme.first + (int) ((vrijeme.second + kasnjenje) / 60);
        
        if(sati >= 24)
            sati = (int) sati % 24;
        
        return std::make_pair(sati,minute);
    }
    
    static void FormatirajVrijeme(std::pair<int,int> vrijeme,int podesiSirinu = 0) {
        if(podesiSirinu != 0) std::cout << "   ";
        std::cout << std::right << std::setw(2) << std::setfill('0') << vrijeme.first;
        std::cout << ":";
        std::cout << std::setw(2) << std::setfill('0') << vrijeme.second;
        std::cout << std::setfill(' ');
    }
    
public:
    Let(const char odrediste[],const char oznaka[],int kapija,int satPolaska,int minutaPolaska,int trajanje) : brojKapije(kapija),vrijemePolijetanja(std::make_pair(satPolaska,minutaPolaska)), trajanjeLeta(trajanje), kasnjenje(0) {
        if(strlen(odrediste) > duzinaOdredista)
            throw std::domain_error("Duzina naziva odredista preduga.");
        else if (strlen(oznaka) > duzinaOznake)
            throw std::domain_error("Duzina oznake leta preduga.");
        
        strcpy(nazivOdredista,odrediste);
        strcpy(oznakaLeta,oznaka);
    };
    
    void PostaviKasnjenje(int novoKasnjenje) {
        kasnjenje = novoKasnjenje;
    }
    
    bool DaLiKasni() const { return kasnjenje; }
    
    int DajTrajanjeLeta() const { return trajanjeLeta; }
    
    int DajKasnjenje() const { return kasnjenje; }
    
    std::pair<int,int> DajOcekivanoVrijemePolijetanja() const {
        if(kasnjenje)
            return UracunajKasnjenje(vrijemePolijetanja,kasnjenje);
        else
            return vrijemePolijetanja;
    };
    
    std::pair<int,int> DajOcekivanoVrijemeSlijetanja() const {
        return UracunajKasnjenje(vrijemePolijetanja,kasnjenje + trajanjeLeta);
    };
    
    void Ispisi() const {
        std::cout << std::left << std::setw(10) << oznakaLeta;
        
        if(strlen(nazivOdredista) >= 20)
            std::cout.write(nazivOdredista,20); 
        else
            std::cout << std::setw(20) << nazivOdredista;

        if(kasnjenje) {
            FormatirajVrijeme(DajOcekivanoVrijemePolijetanja(),3);
            std::cout << " (Planirano ";
            FormatirajVrijeme(vrijemePolijetanja);
            std::cout << ", Kasni " << kasnjenje << " min)";
        } else {
            FormatirajVrijeme(DajOcekivanoVrijemePolijetanja(),3);
            FormatirajVrijeme(DajOcekivanoVrijemeSlijetanja(),3);
            std::cout << std::setw(6) << brojKapije;
        }
        
        std::cout << std::endl;
    };
    
};

class Letovi {
    int maxBrojLetova;
    int brojLetova;
    Let** letovi;
    
public:
    explicit Letovi(int maxBrLetova) : maxBrojLetova(maxBrLetova), brojLetova(0), letovi(new Let*[maxBrojLetova]{}) {
        for(int i=0;i<maxBrojLetova;i++) letovi[i] = nullptr;
    };
    
    Letovi(std::initializer_list<Let> listaLetova);
    
    ~Letovi() {
      for(int i=0;i<brojLetova;i++) delete letovi[i];
      delete[] letovi;
    }
    
    Letovi(const Letovi &noviLetovi);
    
    Letovi(Letovi &&noviLetovi);
  
    Letovi &operator =(const Letovi &noviLetovi) {
        
        if(&noviLetovi != this) {
            
            for(int i=0;i<maxBrojLetova;i++) delete letovi[i];
            
            delete[] letovi;
            
            letovi = new Let*[noviLetovi.maxBrojLetova] {};
            
            if(brojLetova < noviLetovi.DajBrojLetova()) {
                try {
                    for(int i=brojLetova;i<noviLetovi.DajBrojLetova();i++)
                        letovi[i] = new Let(*noviLetovi.letovi[i]);
                } catch(...) {
                    for(int i=brojLetova;i<noviLetovi.DajBrojLetova();i++) {
                        delete letovi[i];
                        letovi[i] = nullptr; 
                    }
                }
                
            } else {
                for(int i=noviLetovi.DajBrojLetova();i<brojLetova;i++) {
                    delete letovi[i];
                    letovi[i] = nullptr;
                }
            } 
            
            brojLetova = noviLetovi.DajBrojLetova();
            maxBrojLetova = noviLetovi.maxBrojLetova;
            
            for(int i=0;i<brojLetova;i++) 
                *letovi[i] = *noviLetovi.letovi[i];
        }
        
        return *this;
    }
    

    Letovi &operator =(Letovi &&noviLetovi) {
        
        if(&noviLetovi != this) {
            std::swap(maxBrojLetova,noviLetovi.maxBrojLetova);
            std::swap(brojLetova,noviLetovi.brojLetova);
            std::swap(letovi,noviLetovi.letovi);
        }
        return *this;
    }
  
    void RegistrirajLet(const char odrediste[],const char oznakaLeta[],int kapija,int satPolaska,int minutaPolaska,int trajanjeLeta);
    
    void RegistrirajLet(Let *let);
    
    int DajBrojLetova() const { return brojLetova; }
    
    int DajBrojLetovaKojiKasne() const { 
        if(brojLetova == 0) 
            throw std::domain_error("Nema registriranih letova");
            
        return std::count_if(letovi,letovi+brojLetova,[](Let *l) { return l -> DaLiKasni(); });
    }
    
    int DajProsjecnoTrajanjeLetova() const {
        if(brojLetova == 0) 
                throw std::domain_error("Nema registriranih letova");
        
        int suma(0);
        
        for(int i=0;i<brojLetova;i++)
            suma += letovi[i] -> DajTrajanjeLeta();
    
        return suma / brojLetova;
    }
    
    Let& DajPrviLet() const { 
        if(brojLetova == 0) 
            throw std::domain_error("Nema registriranih letova");
        
        return **std::min_element(letovi,letovi+brojLetova);
       
    }
    
    Let& DajPosljednjiLet() const { 
        if(brojLetova == 0) 
            throw std::domain_error("Nema registriranih letova");

        return **std::max_element(letovi,letovi+brojLetova);
    }
    
    void IsprazniKolekciju() {
        for(int i=0;i<brojLetova;i++) { delete letovi[i]; }; 
        
        brojLetova = 0;
    };
    
    void Ispisi(int sati = 0,int minute = 0) const;
    
};
 
Letovi::Letovi(const Letovi &noviLetovi):maxBrojLetova(noviLetovi.maxBrojLetova),brojLetova(noviLetovi.brojLetova), letovi(new Let*[maxBrojLetova]{}) {
        int alocirani(0);
            
        try {
            for(int i=0;i<noviLetovi.brojLetova;++i) {
                letovi[i] = new Let(*noviLetovi.letovi[i]);
                alocirani++;
            }
        } catch(...) {
            for(int i=0;i<alocirani;i++) {
                delete letovi[i];
            }
        }
    }

Letovi::Letovi(Letovi &&noviLetovi) {
        std::swap(maxBrojLetova,noviLetovi.maxBrojLetova);
        std::swap(brojLetova,noviLetovi.brojLetova);
        std::swap(letovi,noviLetovi.letovi);
    }
    
Letovi::Letovi(std::initializer_list<Let> listaLetova):maxBrojLetova(listaLetova.size()), brojLetova(listaLetova.size()), letovi(new Let*[listaLetova.size()]{}) {
        try {
            int j=0;
            for(auto l : listaLetova) {
                letovi[j++] = new Let(l);
            }
        } catch(...) {
            for(int i=0;i<maxBrojLetova;i++) {
                delete letovi[i];
            }
            
            delete[] letovi;
        }
    }

void Letovi::RegistrirajLet(const char odrediste[],const char oznakaLeta[],int kapija,int satPolaska,int minutaPolaska,int trajanjeLeta) {
        
        if(brojLetova == maxBrojLetova)
            throw std::range_error("Dostignut maksimalni broj letova");
            
        letovi[brojLetova] = new Let(odrediste,oznakaLeta,kapija,satPolaska,minutaPolaska,trajanjeLeta);
        brojLetova++;
    }

void Letovi::RegistrirajLet(Let *let) { 
        if(brojLetova == maxBrojLetova)
            throw std::range_error("Dostignut maksimalni broj letova");
            
        letovi[brojLetova] = let; 
        brojLetova++; 
    }

void Letovi::Ispisi(int sati,int minute) const { 
        std::sort(letovi,letovi+brojLetova,[](Let *a,Let *b) { return a -> DajOcekivanoVrijemePolijetanja() < b -> DajOcekivanoVrijemePolijetanja(); });
        
        std::pair<int,int> tempVrijeme;
        
        for(int i=0;i<brojLetova;i++) {
            tempVrijeme = letovi[i] -> DajOcekivanoVrijemePolijetanja();
            if(tempVrijeme.first >= sati && tempVrijeme.second >= minute)
                letovi[i] -> Ispisi();
        }
    }
    
int main () {
    
    Letovi letovi(10);
    
    int meniUnos(0);
    int brojLetova(10);
    
    for(;;) {
        std::cout << std::endl;
        std::cout << "Slobodnih mjesta za letove: " << brojLetova << std::endl << std::endl;
        std::cout << "Unesite 1 da dodate let, 2 da dobijete broj letova, 3 da dobijete broj letova koji kasne" << std::endl;
        std::cout << "4 za prosjecno trajanje letova, 5 da ispraznite listu, 6 da ispisete letove" << std::endl;
        std::cout << "a -1 za izlaz: " << std::endl;
        
        std::cin >> meniUnos;
        
        if(meniUnos == 1) {
            char odrediste[30],oznakaLeta[10];
            int kapija,satPolaska,minutePolaska,trajanjeLeta;
            
            std::cin.ignore(10000,'\n');
            
            std::cout << "Unesite odrediste: ";
            std::cin.getline(odrediste,30);
            
            std::cout << "Unesite oznaku leta: ";
            std::cin.getline(oznakaLeta,10);
            
            std::cout << "Unesite kapiju: ";
            std::cin >> kapija;
            
            std::cout << "Unesite sat i minute polaska";
            std::cin >> satPolaska  >> minutePolaska;
            
            std::cout << "Unesite trajanje leta (u minutama): ";
            std::cin >> trajanjeLeta;;
            
            try {
                letovi.RegistrirajLet(odrediste,oznakaLeta,kapija,satPolaska,minutePolaska,trajanjeLeta);
                brojLetova--;
            } catch(...) {
                std::cout << "Doslo je do problema prilikom kreiranja leta, molimo ponovite unos.";
            }
        } else if (meniUnos == 2) {
            std::cout << letovi.DajBrojLetova() << std::endl;
        } else if (meniUnos == 3) {
            std::cout << letovi.DajBrojLetovaKojiKasne() << std::endl;
        } else if (meniUnos == 4) {
            std::cout << letovi.DajProsjecnoTrajanjeLetova() << std::endl;
        } else if (meniUnos == 5) {
            letovi.IsprazniKolekciju();
        } else if (meniUnos == 6) {
            letovi.Ispisi();
        } else if(meniUnos == -1) {
            break;
        } else {
            std::cout << "Pogresan unos, pokusajte ponovo!";
        }
        
        std::cout << std::endl;
    }
	
    return 0;
}
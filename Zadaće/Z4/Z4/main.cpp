//TP 2018/2019: Zadaća 4, Zadatak 4
#include <iostream>

#include <vector>
#include <memory>
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
    std::vector<std::shared_ptr<Let>> letovi;

public:
    
    Letovi() {};
    
    Letovi(std::initializer_list<Let> listaLetova);

    Letovi(const Letovi &noviLetovi);
    
    Letovi(Letovi &&noviLetovi);
  
    Letovi &operator =(const Letovi &noviLetovi) {
        
        if(&noviLetovi != this) {
            
            letovi.resize(noviLetovi.letovi.size());
            
            for(int i=0;i<noviLetovi.letovi.size();++i) 
                letovi.push_back(std::make_shared<Let>(*noviLetovi.letovi.at(i)));
                
        }
        
        return *this;
    }

    Letovi &operator =(Letovi &&noviLetovi) {
        
        if(&noviLetovi != this) {
            std::swap(letovi,noviLetovi.letovi);
        }
        
        return *this;
    }
  
    void RegistrirajLet(const char odrediste[],const char oznakaLeta[],int kapija,int satPolaska,int minutaPolaska,int trajanjeLeta);
    
    void RegistrirajLet(std::shared_ptr<Let> let);
    
    int DajBrojLetova() const { return letovi.size(); }
    
    int DajBrojLetovaKojiKasne() const { 
        if(letovi.size() == 0) 
            throw std::domain_error("Nema registriranih letova");
            
        return std::count_if(letovi.begin(),letovi.end(),[](std::shared_ptr<Let> l) { return l -> DaLiKasni(); });
    }
    
    int DajProsjecnoTrajanjeLetova() const {
        if(letovi.size() == 0) 
                throw std::domain_error("Nema registriranih letova");
        
        int suma(0);
        
        for(int i=0;i<letovi.size();i++)
            suma += letovi.at(i) -> DajTrajanjeLeta();
    
        return suma / letovi.size();
    }
    
    Let& DajPrviLet() const { 
        if(letovi.size() == 0) 
            throw std::domain_error("Nema registriranih letova");
        
        return **std::min_element(letovi.begin(),letovi.end());
       
    }
    
    Let& DajPosljednjiLet() const { 
        if(letovi.size() == 0) 
            throw std::domain_error("Nema registriranih letova");

        return **std::max_element(letovi.begin(),letovi.end());
    }
    
    void IsprazniKolekciju() {
        letovi.clear();
    };
    
    void Ispisi(int sati = 0,int minute = 0) const;
    
};
 
Letovi::Letovi(const Letovi &noviLetovi){
        letovi.resize(noviLetovi.letovi.size());
        
        for(auto let:noviLetovi.letovi)
            letovi.push_back(std::make_shared<Let>(*let));
    }

Letovi::Letovi(Letovi &&noviLetovi) {
        std::swap(letovi,noviLetovi.letovi);
    }
    
Letovi::Letovi(std::initializer_list<Let> listaLetova) {
        for(auto let:listaLetova) letovi.push_back(std::make_shared<Let>(let));
    }

void Letovi::RegistrirajLet(const char odrediste[],const char oznakaLeta[],int kapija,int satPolaska,int minutaPolaska,int trajanjeLeta) {
        letovi.push_back(std::make_shared<Let>(Let(odrediste,oznakaLeta,kapija,satPolaska,minutaPolaska,trajanjeLeta)));
    }

void Letovi::RegistrirajLet(std::shared_ptr<Let> let) { 
        letovi.push_back(std::make_shared<Let>(*let)); 
    }

void Letovi::Ispisi(int sati,int minute) const {
        
        std::vector<std::shared_ptr<Let>> temp = letovi;
        
        std::sort(temp.begin(),temp.end(),[](std::shared_ptr<Let> a,std::shared_ptr<Let> b) { return a -> DajOcekivanoVrijemePolijetanja() < b -> DajOcekivanoVrijemePolijetanja(); });
        
        std::pair<int,int> tempVrijeme;
        
        for(auto let:temp) {
            tempVrijeme = let -> DajOcekivanoVrijemePolijetanja();
            if(tempVrijeme.first >= sati && tempVrijeme.second >= minute)
                let -> Ispisi();
        }
    }
    
int main () {
    
 Letovi letovi;
    
int meniUnos(0);

for(;;) {
    std::cout << std::endl;
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
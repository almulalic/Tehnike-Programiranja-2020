//TP 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>

#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>

typedef std::map<std::string, std::vector<std:: string>> Knjiga;
typedef std::map<std::string,std::set<std::tuple<std::string,int,int>>> Indeksi;

std::vector<std::string> Split(std::string recenica,char delimiter = ' ') {
    std::string rijec;
    std::vector<std::string> split;
    
    for(char c : recenica) {
        if(c != delimiter) {
            rijec.push_back(c);
        } else {
            split.push_back(rijec);
            rijec.clear();
        }
    }
    
    split.push_back(rijec);
    return split;
}

Indeksi KreirajIndeksPojmova(Knjiga knjiga) {
    
    Indeksi indeksi;
    
    std::string stranica; 
    std::string tekst;
    std::vector<std::string> rijeciUTekstu;
    std::tuple<std::string,int,int> ntorka;

    for (auto it = knjiga.begin(); it != knjiga.end(); ++it) { 
        
        for(int i=0;i<(it->second).size();i++) {
            if(i==0)
                tekst += " " + (it->second).at(i) + " ";
            else 
                tekst += (it->second).at(i) + " ";
            (it->second).at(i).insert(0," ");
            (it->second).at(i).append(" ");
            std::transform((it->second).at(i).begin(), (it->second).at(i).end(), (it->second).at(i).begin(),
            [](unsigned char c){ return std::tolower(c); });
        }
        
        std::transform(tekst.begin(), tekst.end(), tekst.begin(),
        [](unsigned char c){ return std::tolower(c); });
        
        rijeciUTekstu = Split(tekst);
        std::set<std::string> unikatneRijeci(rijeciUTekstu.begin(),rijeciUTekstu.end());
        std::set<std::tuple<std::string,int,int>> skupRjesenja;
        
        for(auto rijec:unikatneRijeci) {
             
            for(int i=0;i<(it->second).size();i++) {
               
                std::size_t poz = (it->second).at(i).find(" " + rijec + " ",0);
                    
                while(poz != std::string::npos) {
                    skupRjesenja.insert(std::make_tuple((it->first),i+1,poz));
                    poz = (it->second).at(i).find(" " + rijec + " ",poz+1);
                }
                
            }
            if(skupRjesenja.size() > 0)
                indeksi.insert({rijec,skupRjesenja});
            skupRjesenja.clear();
        }
        tekst.clear();
    }
    
    return indeksi;
}

void IspisiIndeksPojmova(Indeksi indeksi) {
    
    std::string poglavlje;
    int stranica,broj;
    
    for (auto it = indeksi.begin(); it != indeksi.end(); ++it) { 
        std::cout << it -> first << ": ";
        for (auto it2 = (it -> second).begin(); it2 != (it -> second).end(); ++it2) {
            std::tie(poglavlje,stranica,broj) = *it2;
            if(next(it2) != (it->second).end())
                std::cout << poglavlje << "/" << stranica << "/" << broj << ", ";
            else
                std::cout << poglavlje << "/" << stranica << "/" << broj;
        }
        std::cout << std::endl;
    }
}

std::set<std::tuple<std::string,int,int>> PretraziIndeksPojmova(Indeksi indeksi,std::string trazenaRijec) {
    
    Indeksi::iterator trazena = indeksi.find(trazenaRijec);
    
    if(trazena == indeksi.end())
        throw std::logic_error("Unesena rijec nije nadjena!");
    else
        return trazena -> second;
}

int main () {
    Knjiga knjiga;
    std::string unosPoglavlja;
    std::vector<std::string> tempStranice;
    std::string tempStranica;
    
    int i(0);
    while(true) {
        std::cout << "Unesite naziv poglavlja: ";
        std::getline(std::cin,unosPoglavlja);
        
        if(unosPoglavlja == ".")
            break;

        i=0;
        while(true) {
            std::cout << "Unesite sadrzaj stranice " << i+1 << ": ";
            std::getline(std::cin,tempStranica);
        
            if(tempStranica == ".")
                break;
                
            tempStranice.push_back(tempStranica);
            i++;
        }
        
        knjiga.insert({unosPoglavlja,tempStranice});
        tempStranice.clear();
        
    }
    
    Indeksi indeksi = KreirajIndeksPojmova(knjiga);
  
    std::string poglavlje;
    int stranica,broj;
    
    std::cout << std::endl;
    std::cout << "Kreirani indeks pojmova: " << std::endl;
    IspisiIndeksPojmova(indeksi);
    
    for(;;) {
        
        std::cout << "Unesite rijec: ";
        std::string unesenaRijec;
        std::cin >> unesenaRijec;
        
        if(unesenaRijec == ".")
            break;
            
        try {
            std::set<std::tuple<std::string,int,int>> pip = PretraziIndeksPojmova(indeksi,unesenaRijec);
            for (auto it2 = pip.begin(); it2 != pip.end(); ++it2) {
                std::tie(poglavlje,stranica,broj) = *it2;
                std::cout << poglavlje << "/" << stranica << "/" << broj << " ";
            }
        } catch(std::logic_error err) {
            std::cout << err.what();
        }
        
        std::cout << std::endl;
    }
    
    
	return 0;
}
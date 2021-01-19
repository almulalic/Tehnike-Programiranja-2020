//TP 2018/2019: Tutorijal 14, Zadatak 1
#include <iostream>

#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

class Datum {
    int dan,mjesec,godina;

public: 
    bool operator <(const Datum& datum) const;
    bool operator ==(const Datum& datum) const;
    friend std::istream& operator >> (std::istream& ulaz, Datum& datum);
    friend std::ostream& operator << (std::ostream& izalz, const Datum& datum);
    int getDan() const { return dan; }
    int getMjesec() const { return mjesec; }
    int getGodina() const { return godina; }
};

bool Datum::operator<(const Datum& datum) const {
    if(this -> godina == datum.godina) {
        if(this -> mjesec == datum.mjesec) {
            return this -> dan < datum.dan;
        } else return this -> mjesec < datum.mjesec;
    } else return this -> godina < datum.godina;
}

bool Datum::operator == (const Datum& datum) const {
    return this -> dan == datum.dan && this -> mjesec == datum.mjesec && this -> godina == datum.godina;
}

std::istream& operator >> (std::istream& ulaz,Datum& datum) {
    char kosaCrta;
    ulaz >> datum.dan >> kosaCrta >> datum.mjesec >> kosaCrta >> datum.godina; 
    return ulaz;
}

std::ostream& operator << (std::ostream& izlaz, const Datum& datum) {
    return izlaz << datum.dan << "/" << datum.mjesec << "/" << datum.godina; 
}

class Mjerenje {
    Datum datumMjerenja;
    std::string imeStanice;
    std::vector<double> mjerenja;
public:
    friend std::istream& operator >>(std::istream& ulaz, Mjerenje& mjerenje);
    friend std::ostream& operator <<(std::ostream& izlaz, const Mjerenje& m);
    double DajProsjecnu() const { return accumulate(mjerenja.begin(), mjerenja.end(), .0) / mjerenja.size(); }
    double DajMinimalnu() const { if(mjerenja.size() == 1) return mjerenja.at(0); else return *min_element(mjerenja.begin(),mjerenja.end()); }
    double DajMaksimalnu() const { if(mjerenja.size() == 1) return mjerenja.at(0); else return *max_element(mjerenja.begin(),mjerenja.end()); }
    bool operator < (const Mjerenje& m) const { 
        if(m.datumMjerenja == datumMjerenja)
            return DajProsjecnu() < m.DajProsjecnu();
        else 
            return datumMjerenja < m.datumMjerenja;
    }
};

std::istream& operator >> (std::istream& ulaz, Mjerenje&m) {
    
    if(!(ulaz >> m.datumMjerenja)) return ulaz;
    
    ulaz.ignore(10000,'\n');
    std::getline(ulaz, m.imeStanice);
    
    double jednoMjerenje;
    m.mjerenja = std::vector<double>();
    
    while(true) {
        if(!(ulaz >> jednoMjerenje)){
            std::cout << "Problemi pri citanju datoteke TEMPERATURE.TXT" << std::endl;
            break;
        }
        
        m.mjerenja.push_back(jednoMjerenje);
        
        char separator;
        if((separator = ulaz.peek()) == ',') {
            ulaz.get();
        } else {
            if(separator == EOF) ulaz.clear();
            break;
        }
        
        if(ulaz.bad()) {
            std::cout << "Problemi pri citanju datoteke TEMPERATURE.TXT"<< std::endl;
            break;
        }
    }
    
    return ulaz;
}

std::ostream& operator << (std::ostream& izlaz, const Mjerenje& m) {
    izlaz << m.imeStanice << std::endl;
    
    for(int i=0;i<m.imeStanice.size();i++) {
        izlaz << "-";
    }
    
    izlaz << std::endl;
    izlaz << "Datum mjerenja: " << m.datumMjerenja << std::endl;
    izlaz << "Minimalna temperatura: " << m.DajMinimalnu() << std::endl;
    izlaz << "Maksimalna temperatura: " << m.DajMaksimalnu() << std::endl;
    izlaz << "Prosjecna temperatura: " << std::setprecision(2) << std::fixed << m.DajProsjecnu() << std::endl;
    izlaz.unsetf(std::ios_base::floatfield);
    izlaz << std::endl;
       
    return izlaz;
}

int main () {
    
    std::ifstream ulazni_tok("TEMPERATURE.TXT",std::ios::in);
    
    if(!ulazni_tok) {
        std::cout << "Datoteka TEMPERATURE.TXT ne postoji!" << std::endl;
        return 1;
    }
    
    std::vector<Mjerenje> mjerenjaStanica;

    Mjerenje mjerenjeStanice;
    while(ulazni_tok >> mjerenjeStanice) {
        mjerenjaStanica.push_back(mjerenjeStanice);
        
        if(ulazni_tok.bad()) {
            std::cout << "Problemi pri citanju datoteke TEMPERATURE.TXT";
            return 1;
        }
    }

    std::sort(mjerenjaStanica.begin(),mjerenjaStanica.end());
    std::ofstream izlaz("IZVJESTAJ.TXT",std::ios::out);
    
    for(Mjerenje& m:mjerenjaStanica) {
        izlaz << m;
    }
    
	return 0;
}
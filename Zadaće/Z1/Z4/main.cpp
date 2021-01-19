//TP 2016/2017: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

bool DaLiJeSamoglasnik(char c) {
    return c=='A' || c=='a' || c=='E' || c=='e' || c=='I' || c=='i' || c=='O' || c=='o' || c=='U' || c=='u';
}

bool DaLiJeRitmicna(std::string rijec) {
    
    if(rijec.length() < 2)
        return false;
        
    bool samoglasnik(DaLiJeSamoglasnik(rijec.at(0)));
    
    for(int i=1;i<rijec.length();i++){
        if(samoglasnik && DaLiJeSamoglasnik(rijec.at(i)))
            return false;
        else if (!samoglasnik && !DaLiJeSamoglasnik(rijec.at(i)))
            return false;
            
        samoglasnik=!samoglasnik;
    }
    
    return true;
}

std::string IstakniSavrsenoRitmicneRijeci(std::string recenica) {
    
    std::vector<std::string> rijeci;
    std::string rijec;
    std::string istaknutaRecenica;
    int i=0;
    int duzina = recenica.size();
  
    while(i < duzina) {
        
        if( (i==0 && recenica.at(i) != ' ') || (i>0 && recenica.at(i-1) == ' ' && recenica.at(i) != ' ')) {
            
            rijec.clear();

            while(recenica.at(i) != ' ') {
                rijec += recenica.at(i);
                i++;
                if(i == duzina)
                    break;
            }
            
            if(DaLiJeRitmicna(rijec)) rijec = '(' + rijec + ")";
            if(i+1 < duzina) rijec += " ";
        
            rijeci.push_back(rijec);
                
        } else rijeci.push_back(" ");
        
        i++;
    }
    
    for(std::string rijec:rijeci) 
        istaknutaRecenica+=rijec;
    
    return istaknutaRecenica;
}


int main () {
    
    std::string recenica;
    
    std::cout << "Unesite recenicu (ENTER za kraj): ";
    std::getline(std::cin, recenica);
    
    std::cout << "Recenica sa istaknutim savrseno ritmicnim rijecima glasi: " << std::endl;
    std::cout << IstakniSavrsenoRitmicneRijeci(recenica);
	
	return 0;
}
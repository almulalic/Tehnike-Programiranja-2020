//TP 2018/2019: Tutorijal 4, Zadatak 3
#include <iostream>
#include <vector>
#include <string>


void IzdvojiKrajnjeRijeci(std::vector<std::string> VS, std::string &a, std::string &b) {
    
    std::string min = VS.at(0),max = VS.at(0);
    
    if(VS.size()==0) {
        a = " ";
        b = " ";
        return; 
    }
    
    std::string temp1,temp2,temp3;
    
    for(auto s: VS) {
        
        temp1 = s;
        temp2 = min;
        temp3 = max;
        
        for(auto &c : temp1) c = toupper(c);
        for(auto &c : temp2) c = toupper(c);
        for(auto &c : temp3) c = toupper(c);
        
        if(temp1<temp2) min=s;
        if(temp1>temp3) max=s;
        
    }
    
    a=min;
    b=max;
            
}

void ZadrziDuplikate(std::vector<std::string> &VS) {
    
    std::vector<std::string> v;
    std::string s1,s2;
    bool dodaj;
    
    for(int i=0;i<VS.size();i++) {
        s1=VS.at(i);
        for(int j=i+1;j<VS.size();j++) {
            s2=VS.at(j);
            if(s1==s2) {
                dodaj = true;
                
                for(int k=0;k<v.size();k++) {
                    std::string s3=v.at(k);
                    if(s1==s3) {
                        dodaj = false;
                        break;
                    }
                }
                if(dodaj) v.push_back(s1);
                break;
            }
        }
    }
    
    VS=v;
}

int main ()
{
    
    std::cout << "Koliko zelite unijeti rijeci: ";
    
    int n;
    std::cin >> n;
    
    std::cout << "Unesite rijeci: ";
    std::vector<std::string> vs;
    
    std::string unos;
    for(int i=0;i<n;i++) {
        std::cin >> std::ws;
        std::cin >> unos;
        vs.push_back(unos);
    }
    
    std::string a,b;
    IzdvojiKrajnjeRijeci(vs,a,b);
    
    std::cout << "Prva rijec po abecednom poretku je: " << a << std::endl;
    std::cout << "Posljednja rijec po abecednom poretku je: " << b << std::endl;
    
    ZadrziDuplikate(vs);
    
    std::cout << "Rijeci koje se ponavljaju su: ";
    for(auto s:vs) std::cout << s << " ";
    
	return 0;
}
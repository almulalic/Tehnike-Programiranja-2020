//TP 2018/2019: Tutorijal 8, Zadatak 4
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string ZamijeniPremaRjecniku(std::string recenica,std::map<std::string, std::string> mapa) {
    
    std::vector<std::string> rijeci;
    std::string rijec;
    
    int i=0,duzina = recenica.length();
    while( i < duzina) {
    
        if( (i==0 && recenica.at(i) != ' ') || (i>0 && recenica.at(i-1) == ' ' && recenica.at(i) != ' ')) {
        
            rijec.clear();
        
            while(recenica.at(i) != ' ') {
                rijec += recenica.at(i);
                i++;
                if(i == duzina)
                    break;
            }
            
            std::map<std::string, std::string>::iterator it = mapa.find(rijec);
            
            if(it == mapa.end()) 
                rijeci.push_back(rijec + " ");
            else 
                rijeci.push_back(it->second + " "); 
            
        } else rijeci.push_back(" ");
    
        i++;
    }
    
    std::string zamjenjeneRijeci;
    
    for(std::string rijec:rijeci) 
        zamjenjeneRijeci+=rijec;
    
    return zamjenjeneRijeci;
}

int main () {
    
    std::map<std::string, std::string> moj_rjecnik{{"jabuka", "apple"},{"da", "yes"}, {"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};
    
    std::cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik);


	return 0;
}
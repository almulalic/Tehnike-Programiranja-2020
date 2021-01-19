//TP 2018/2019: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>


int TestPerioda (std::vector<double> niz,int p) {
    
    int velicinaNiza = niz.size();
    
    if(velicinaNiza-p==0 || velicinaNiza == 1)
        return false;
        
    for(int i=0;i<velicinaNiza-p;i++) {
        if(niz.at(i)== niz.at(i+p))
            continue;
        else
            return false;
    }
    
    return true;
}

int OdrediOsnovniPeriod(std::vector<double> niz) {
    
    int minPeriod(0);
    int velicinaNiza = niz.size();
    
    if(velicinaNiza <= 1)
        return minPeriod;
    
    for(int i=velicinaNiza-1;i>1;i--) {
        if(TestPerioda(niz,i)) minPeriod = i;
    }
    
    return minPeriod;
}


int main ()
{
    
    std::vector<double> niz;
    double unos;
    int osnovniPeriod;
    
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    
    do {
        std::cin >> unos;
        if(unos==0) break;
        niz.push_back(unos);
    } while(unos!=0);
	
	osnovniPeriod = OdrediOsnovniPeriod(niz);
	
	if(osnovniPeriod != 0)
	    std::cout << "Slijed je periodican sa osnovnim periodom " << osnovniPeriod << ".";
    else
        std::cout << "Slijed nije periodican!";

return 0;
}
//TP 2018/2019: Tutorijal 4, Zadatak 4
#include <iostream>

template <typename Tip> void UnosBroja (const char unesi[], const char pogresno[], Tip &broj) {
    
    Tip temp;
    
    do {
        std::cout << unesi;
        std::cin >> temp;
        
        if(std::cin.peek() != '\n') {
            std::cout << pogresno << std::endl;
            std::cin.clear();
            std::cin.ignore(1000,'\n');
             std::cout << std::endl;
        } else break;
    } while(true);
    
    broj = temp;
}

int main ()
{
    
    double broj;
    int eksp;
    UnosBroja("Unesite bazu: ","Neispravan unos, pokusajte ponovo...",broj);
    std::cout << std::endl;
    UnosBroja("Unesite cjelobrojni eksponent: ", "Neispravan unos, pokusajte ponovo...",eksp);
    
    auto rezultat = broj;
    rezultat=1;
    int n = eksp;
    
    n=abs(n);
    
    for(int i=0;i<n;i++) rezultat*=broj;
    if(eksp < 0) rezultat=1/rezultat;

    std::cout << broj << " na " << eksp << " iznosi " << rezultat;
	return 0;
}
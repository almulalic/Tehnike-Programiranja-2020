//TP 2018/2019: Tutorijal 4, Zadatak 2
#include <iostream>
#include <string>

void IzvrniString(std::string &recenica) {
    
    int duzina = recenica.length();
    char temp;
    
    for(int i=0;i<duzina/2;i++) {
        temp = recenica[i];
        recenica[i] = recenica[duzina-1-i];
        recenica[duzina-1-i] = temp;
    }
}

int main ()
{
    
    std::string unos;
    
    std::cout << "Unesi string: ";
    std::getline(std::cin, unos);
    
    IzvrniString(unos);
    
    std::cout << "Izvrnuti string je: "; 
    std::cout << unos;

	return 0;
}
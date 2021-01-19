//TP 2018/2019: Tutorijal 14, Zadatak 4
#include <iostream>

#include <fstream>
#include <string>

void IzvrniDatoteku(std::string imeDatoteke) {
    
    std::ifstream ulaz(imeDatoteke,std::ios::in);
    
    if(!ulaz) {
        throw std::logic_error("Datoteka ne postoji");
    }
}


int main ()
{
	return 0;
}
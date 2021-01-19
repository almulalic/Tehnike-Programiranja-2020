//TP 2016/2017: Tutorijal 1, Zadatak 1
#include <iostream>
#include <cmath>

int main(){
    int duz;
    int sir;
    int dub;
    int ploc;
    int kolicina;
    
    std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin>>duz>>sir>>dub;
    std::cout<<"Unesite sirinu plocice u centimetrima: " << std::endl;
    std::cin>>ploc;

    int dno = duz * sir;
    int veciZid = 2 *(sir * dub);
    int manjiZid = 2 *(duz * dub);
    int povBazen = (dno + veciZid + manjiZid) * 10000 ;
    int povPlocice = ploc*ploc;

    kolicina = povBazen/povPlocice;

    if(povBazen % povPlocice==0){
        std::cout<<"Za poplocavanje bazena dimenzija "<<duz<<"x"<<sir<<"x"<<dub<<
        "m sa plocicama dimenzija "<<ploc<<"x"<<ploc << "cm" << std::endl;
        std::cout << "potrebno je "<<kolicina<<" plocica.";
    } else {
        std::cout<<"Poplocavanje bazena dimenzija "<<duz<<"x"<<sir<<"x"<<dub<<
        "m sa plocicama dimenzija "<<ploc<<"x"<<ploc<<"cm" << std::endl;
        std::cout << "nije izvodljivo bez lomljenja plocica!";
    }

return 0;
}
//TP 2018/2019: Tutorijal 8, Zadatak 1
#include <iostream>

struct Vrijeme {
  int sati,minute,sekunde;
};

void TestirajVrijeme(Vrijeme vrijeme) {
    if(vrijeme.sati < 0 || vrijeme.sati > 23 || vrijeme.minute < 0 || vrijeme.minute > 59 || vrijeme.sekunde < 0 || vrijeme.sekunde > 59)
        throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(Vrijeme vrijeme) {
    
    try {
        TestirajVrijeme(vrijeme);
    } catch(std::domain_error err) {
        throw;
    }
    
    if(vrijeme.sati >= 0 && vrijeme.sati <= 9)
        std::cout << "0" << vrijeme.sati;
    else
        std::cout << vrijeme.sati;
    
    std::cout << ":";
    
     if(vrijeme.minute >= 0 && vrijeme.minute <= 9)
        std::cout << "0" << vrijeme.minute;
    else
        std::cout << vrijeme.minute;
        
    std::cout << ":";
    
     if(vrijeme.sekunde >= 0 && vrijeme.sekunde <= 9)
        std::cout << "0" << vrijeme.sekunde;
    else
        std::cout << vrijeme.sekunde;
}

Vrijeme SaberiVrijeme(Vrijeme prvo,Vrijeme drugo) {
    Vrijeme rezultat;
    
    try {
        TestirajVrijeme(prvo);
        TestirajVrijeme(drugo);
    } catch(std::domain_error err) {
        std::cout << err.what() << std::endl;
    }
    
    rezultat.sekunde = (prvo.sekunde + drugo.sekunde) % 60;
    rezultat.minute = (prvo.minute + drugo.minute) % 60 + ((prvo.sekunde + drugo.sekunde) / 60);
    rezultat.sati = (prvo.sati + drugo.sati) % 24 + ((prvo.minute + drugo.minute) / 60) ;

    if(rezultat.minute == 60)
        rezultat.minute = 0;
        
    if(rezultat.sati == 23)
        rezultat.sati = 0;
    
    return rezultat;
}

int main () {
    
    Vrijeme prvo;
    std::cout << "Unesite prvo vrijeme (h m s): ";
    std::cin >> prvo.sati >> prvo.minute >> prvo.sekunde;

    try {
        TestirajVrijeme(prvo);
    } catch(std::domain_error err) {
        std::cout << err.what();
        return 1;
    }
     
    Vrijeme drugo;
    std::cout << "Unesite drugo vrijeme (h m s): ";
    std::cin >> drugo.sati >> drugo.minute >> drugo.sekunde;
    
    try {
        TestirajVrijeme(drugo);
    } catch(std::domain_error err) {
        std::cout << err.what();
        return 1;
    }
    
    std::cout << "Prvo vrijeme: ";
    IspisiVrijeme(prvo);
    
    std::cout << std::endl;
    
    std::cout << "Drugo vrijeme: ";
    IspisiVrijeme(drugo);
  
    std::cout << std::endl;
    
    std::cout << "Zbir vremena: ";
   
    IspisiVrijeme(SaberiVrijeme(prvo,drugo));
   
    
	return 0;
}
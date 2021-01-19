//TP 2018/2019: Zadaća 2, Zadatak 1
#include <iostream>
#include <vector>

typedef std::vector<std::vector<std::vector<char>>> Polja;
typedef std::vector<std::vector<char>> Polje;
typedef std::vector<char> Red;

std::vector<int> FinalniRezultat(Polje trenutnoPolje,int brojRobota) {
    
    std::vector<int> rezultat(brojRobota,0);
    
    for(int i=0;i<trenutnoPolje.size();i++) {
        for(int j=0;j<trenutnoPolje.at(i).size();j++) {
            if(trenutnoPolje.at(i).at(j) >= 'A' && trenutnoPolje.at(i).at(j) <= 'A'+15 && trenutnoPolje.at(i).at(j) != 'O') {
                rezultat.at(((int)trenutnoPolje.at(i).at(j)-'A'))++;
            }
        }
    }
    
    
    std::vector<int> finalniRezultat({0,0,0});
    int increment(1);
    for(int i=0;i<rezultat.size();i++) {
        if(rezultat.at(i) == increment) {
            finalniRezultat.at(2)++;
        } else if(rezultat.at(i) == 0) {
            finalniRezultat.at(0)++;
        } else {
            finalniRezultat.at(1)++;
        }
        increment++;
    }
    
    return finalniRezultat;
}

bool ProvjeriPogodak(Polje &trenutnoPolje,int x,int y) {
    
    char znak = trenutnoPolje.at(x).at(y);
    
    trenutnoPolje.at(x).at(y) = 'X';
    
    for(int i=0;i<=x;i++) {
        if(trenutnoPolje.at(x).at(i) == znak)
            return false;
    }
    
    for(int i=0;i<=y;i++) {
        if(trenutnoPolje.at(i).at(y) == znak)
            return false;
    }
    
    
    return true;
}

bool ProvjeriIPostavi(Polje &trenutnoPolje,int x1,int y1,int x2,int y2,int duzinaRobota) {
    
    int dimenzije(trenutnoPolje.at(0).size());
    
    if(x1 < 0 ||  y1 < 0 ||  x2 < 0 || y2 < 0 ) 
        return false;
    else if(x1 >= dimenzije ||  y1 >= dimenzije || x2 >= dimenzije ||  y2 >= dimenzije) 
        return false;
    if(x1 != x2 && y1 != y2)
        return false;
        
    int pravac,tacka1,tacka2;
    
    if(y1 == y2) {
        pravac = y1;
        if(x1>x2) {
            tacka1=x2;
            tacka2=x1;
        } else {
            tacka1=x1;
            tacka2=x2;
        }
    } else {
        pravac = x1;
        if(y1>y2) {
            tacka1=y2;
            tacka2=y1;
        } else {
            tacka1=y1;
            tacka2=y2;
        }
    }
   
    // if(tacka2-tacka1 != duzinaRobota && tacka1-tacka2 != duzinaRobota)
    //     return false;
        
    for(int i=tacka1;i<tacka2;i++) {
        if(pravac == y1 && pravac == y2) {
            if(trenutnoPolje.at(pravac).at(i) != '-')
                return false;
        } else { 
            if(trenutnoPolje.at(i).at(pravac) != '-')
                return false;
        }
    }
    
    for(int i=tacka1;i<=tacka2;i++) {
        if(y1==y2)
            trenutnoPolje.at(pravac).at(i) = 'A'+duzinaRobota;
        else
            trenutnoPolje.at(i).at(pravac) = 'A'+duzinaRobota;
    }
    
    return true;
}

Polja KreirajMatrice(int m,int n) {
    if(m <= 0 || n <= 0) 
        throw std::domain_error("Dimenzije matrica moraju biti pozitivne");
    else if(m >= 100 || n >= 100)
        throw std::domain_error("Prevelike dimenzije");
    else if(m != n)
        throw std::domain_error("Matrice moraju biti kvadratne");
        
    return Polja(2,Polje(m,Red(n,'-')));
}

void Nacrtaj(Polja trenutnaPolja,int igrac) {
    
    for(Red red:trenutnaPolja.at(igrac)) {
        for(char znak:red) {
            if(znak == 'O')
                std::cout << 'O' << ' ';
            else if ( znak == 'X')
                std::cout << 'X' << ' ';
            else if ( znak == '-')
                std::cout << '-' << ' ';
            else 
                std::cout << 'R' << ' ';
        }
        std::cout << std::endl;
    }
    
}

bool PogadjanjeRobota(Polja &trenutnaPolja,int brojRobota) {
    bool igraAlina(false);
    int poeniNaida(0),poeniAlina(0),maxPoena((brojRobota * (brojRobota+1)/2.));
    int x,y;
    int dimenzije(trenutnaPolja.at(0).size());
    
    for(;;) {
        std::cout << (igraAlina ? "Alina" : "Naida") << " unesi koordinate koje zelis gadjati:" << std::endl;
        std::cin >> y >> x;
        
        if(x == -1 && y == -1) {
            std::vector<int> statistikaNaida = FinalniRezultat(trenutnaPolja.at(igraAlina),brojRobota);
            std::cout << "Naida ima " << statistikaNaida.at(0) << " unistenih, " << statistikaNaida.at(1) << " ostecenih i " << statistikaNaida.at(2) << " citavih robota.";
            std::cout << std::endl;
            std::vector<int> statistikaAlina = FinalniRezultat(trenutnaPolja.at(!igraAlina),brojRobota);
            std::cout << "Alina ima " << statistikaAlina.at(0) << " unistenih, " << statistikaAlina.at(1) << " ostecenih  i " << statistikaAlina.at(2) << " citavih robota.";
            return false;
        }
        else if (x == -2 && y == -2) 
            Nacrtaj(trenutnaPolja,igraAlina);
        else { 
            if(x < 0 || y < 0 || x > dimenzije || y > dimenzije) {
                std::cout << "Pogresne koordinate gdje zelite gadjati polje" << std::endl;
            } else if (trenutnaPolja.at(!igraAlina).at(x).at(y) == 'O' || trenutnaPolja.at(!igraAlina).at(x).at(y) == 'X') 
                std::cout << "Vec ste pogidili ovo polje"  << std::endl;
            else if(trenutnaPolja.at(!igraAlina).at(x).at(y) >= 'A'  && trenutnaPolja.at(!igraAlina).at(x).at(y) <= 'A' + 15) {
                    
                if(ProvjeriPogodak(trenutnaPolja.at(!igraAlina),x,y))
                    std::cout << "Unisteno" << std::endl;
                else
                    std::cout << "Pogodak" << std::endl;
                
                if(igraAlina)
                    poeniAlina++;
                else
                    poeniNaida++;
                
                if(poeniAlina == maxPoena) {
                    std::cout << "Alina je pobijedila. ";
                    Nacrtaj(trenutnaPolja,!igraAlina);
                    std::vector<int> statistika = FinalniRezultat(trenutnaPolja.at(!igraAlina),brojRobota);
                    std::cout << "Alina ima " << statistika.at(0) << " unistenih, " << statistika.at(1) << " ostecenih  i " << statistika.at(2) << " citavih robota.";
                    return true;
                } else if(poeniNaida == maxPoena) {
                    std::cout << "Naida je pobijedila. ";
                    std::vector<int> statistika = FinalniRezultat(trenutnaPolja.at(igraAlina),brojRobota);
                    std::cout << "Naida ima " << statistika.at(0) << " unistenih, " << statistika.at(1) << " ostecenih i " << statistika.at(2) << " citavih robota.";
                    return true;
                }
                    

            } else if(trenutnaPolja.at(!igraAlina).at(x).at(y) == '-') {
                trenutnaPolja.at(!igraAlina).at(x).at(y) = 'O';
                std::cout << "Promasaj" << std::endl;
            }
            
        igraAlina = !igraAlina;
            
        }
        
    }
    
    return false;
}

void Unos(Polja &trenutnaPolja,int brojRobota) {
    if(trenutnaPolja.size() == 0)
        throw std::domain_error("Matrica ne postoji");
    else if (trenutnaPolja.size() != 2) 
        throw std::range_error("3D matrica ima pogrešne dimenzije");
    else if(trenutnaPolja.at(0).size() == 0 || trenutnaPolja.at(1).size() == 0)
        throw std::domain_error("Neka od dvije matrice je prazna");
    
    for(int i=0;i<trenutnaPolja.at(0).size();i++) {
        if(trenutnaPolja.at(0).at(i).size() != trenutnaPolja.at(0).at(0).size() || trenutnaPolja.at(1).at(i).size() != trenutnaPolja.at(1).at(0).size())
            throw std::domain_error("Neka matrica je grbava");
    }
    
    if(trenutnaPolja.at(0).at(0).size() != trenutnaPolja.at(0).at(1).size()  || trenutnaPolja.at(1).at(0).size() != trenutnaPolja.at(1).at(1).size()) 
        throw std::domain_error("Neka od matrica nije kvadratna");
    if(trenutnaPolja.at(0).size() != trenutnaPolja.at(1).size()) 
        throw std::domain_error("Matrice nemaju iste dimenzije");
    
    if(((brojRobota * (brojRobota+1))/2) > (trenutnaPolja.at(0).at(0).size()*2))
        throw std::overflow_error("Zelite igrati sa previse robota.");
    if(brojRobota > 15)
        throw std::range_error("Zelite igrati sa previse robota");
    else if(brojRobota <= 0)
        throw std::domain_error("Ne mozete igrati bez robota");
    
    bool igraAlina(false);
    int brojUnosa(0);
    int x1,y1,x2,y2;
    int preostaloPolja = trenutnaPolja.at(0).at(0) * 2;
    int zauzetoPolja = 0;
    int velicinaTrenutnog = 0;
    
    for(int i=0;i<2;i++) {
        
        while(brojUnosa != brojRobota) {
            std::cout << (igraAlina ? "Alina":"Naida") << " unesi pocetne i krajnje koordinate " << brojUnosa + 1 << ". robota:" << std::endl;
            std::cin >> x1 >> y1 >> x2 >> y2;
            
            if(x1 == -2 && y1 == -2 && x2 == -2 && y2 == -2) 
                Nacrtaj(trenutnaPolja,igraAlina);
            else {
                if(ProvjeriIPostavi(trenutnaPolja.at(igraAlina),x1,y1,x2,y2,brojUnosa)) {
                    brojUnosa++;
                    zauzetoPolja = (brojUnosa + 1) * velicinaTrenutnog; 
                    preostaloPolja--;
                    if(preostaloPolja == brojUnosa)
                        throw std::overflow_error("Nemoguce dovrsiti postavljanje robota");
                } else {
                    std::cout << "Pogresne koordinate gdje zelite smjestiti robota" << std::endl;
                }
            }
            
        }
        igraAlina = !igraAlina;
        brojUnosa = 0;
        preostaloPolja = trenutnaPolja.at(0).at(0).size() * 2;
    }
    
    std::cout << "Uspjesno ste unijeli pozicije robota. Sada moze poceti pogadjanje." << std::endl;
    PogadjanjeRobota(trenutnaPolja,brojRobota);
}

int main ()
{
    
    int m,n;
    bool errorFlag(true);
    Polja poljaIgraca;
     
    while(errorFlag == true) {
        std::cout << "Igra je pocela, unesite dimenzije matrica (dva broja):" << std::endl;
        std::cin >> m >> n;
        
        try {
            poljaIgraca = KreirajMatrice(m,n);
            errorFlag = false;
        } catch(const std::exception &exc) {
            std::cout << exc.what() << std::endl;;
            errorFlag = true;
        }
        
    }
    
    errorFlag = true;
    
    int brojRobota(0);

    while(errorFlag == true) {
        std::cout << "Unesite broj robota:" << std::endl;
        std::cin >> brojRobota;
    
        try {
            Unos(poljaIgraca,brojRobota);
            errorFlag = false;
        } catch(const std::exception &exc) {
            std::cout << exc.what() << std::endl;
            errorFlag = true;
        }
    }
        
	return 0;
}


















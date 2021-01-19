//TP 2018/2019: Ispit 6, Zadatak 1
#include <iostream>

// 3/5 AT

enum class Pravci {Sjever, Istok, Jug, Zapad};

class Robot {
    int x,y;
    Pravci pravac;

public:
    Robot() {
        pravac = Pravci::Sjever;
        x = 0;
        y = 0;
    }
    
    Robot(int x,int y, Pravci pravac = Pravci::Sjever) : x(x),y(y),pravac(pravac) {}
    
    Robot& PostaviPoziciju(int noviX,int noviY) {
        x = noviX;
        y = noviY;
        
        return *this;
    }
    
    Robot& PostaviPoziciju(std::pair<int,int> koordinate) {
        x = koordinate.first;
        y = koordinate.second;
        
        return *this;
    }
    
    Robot& PostaviOrijentaciju(Pravci noviPravac) {
        pravac = noviPravac;
        
        return *this;
    }
    
    std::pair<int,int> DajPoziciju() const { return std::make_pair(x,y); }
    
    Pravci DajOrijentaciju() const { return pravac; }
    
    Robot& operator +=(int brojKoraka) {
        
      switch(pravac) {
        case Pravci::Sjever:
            y += brojKoraka;
            break;
        case Pravci::Istok:
            x += brojKoraka;
            break;
        case Pravci::Zapad:
            x -= brojKoraka;
            break;
        case Pravci::Jug:
            y -= brojKoraka;
            break;
        }
          
        return *this;
    }   
    
    Robot& operator -=(int brojKoraka) {
        switch(pravac) {
            case Pravci::Sjever:
                y -= brojKoraka;
                break;
            case Pravci::Istok:
                x -= brojKoraka;
                break;
            case Pravci::Zapad:
                x += brojKoraka;
                break;
            case Pravci::Jug:
                y += brojKoraka;
                break;
        }
        
        return *this;
    }
    
    Robot operator +(int brojKoraka) const {
        Robot novi = *this;
        
          switch(novi.pravac) {
            case Pravci::Sjever:
                novi.y += brojKoraka;
                break;
            case Pravci::Istok:
                novi.x += brojKoraka;
                break;
            case Pravci::Zapad:
                novi.x -= brojKoraka;
                break;
            case Pravci::Jug:
                novi.y -= brojKoraka;
                break;
        }
        
        return novi;
    }
    
    Robot operator -(int brojKoraka) const {
        Robot novi = *this;
        
         switch(novi.pravac) {
            case Pravci::Sjever:
                novi.y -= brojKoraka;
                break;
            case Pravci::Istok:
                novi.x -= brojKoraka;
                break;
            case Pravci::Zapad:
                novi.x += brojKoraka;
                break;
            case Pravci::Jug:
                novi.y += brojKoraka;
                break;
        }
        
        return novi;
    }
    
    Robot& operator ++() {
        if((int) pravac - 1 < 0) pravac = Pravci(3);
        else pravac = Pravci((int) pravac - 1);
        
        return *this;
    }
    
    Robot& operator --() {
        if((int) pravac + 1 >= 4) this -> pravac = Pravci(0);
        else this -> pravac = Pravci((int) pravac + 1);
        
        return *this;
    }
    
    Robot operator ++(int) {
        Robot temp = *this;
        if((int) pravac - 1 < 0) pravac = Pravci(3);
        else pravac = Pravci((int) pravac - 1);
        
        return temp;
    }
    
    Robot operator --(int) {
        Robot temp = *this;
        if((int) pravac + 1 >= 4) this -> pravac = Pravci(0);
        else this -> pravac = Pravci((int) pravac + 1);
        
        return temp;
    }
};  

bool operator==(Robot prvi,Robot drugi) {
    return prvi.DajPoziciju() == drugi.DajPoziciju() && prvi.DajOrijentaciju() == drugi.DajOrijentaciju();
}

bool operator!=(Robot prvi,Robot drugi) {
    return !(prvi==drugi);
}

std::ostream& operator <<(std::ostream& ulaz,Robot r) {
    ulaz << "Robot se nalazi na poziciji (" << r.DajPoziciju().first << "," << r.DajPoziciju().second << ") i gleda na ";

    switch(r.DajOrijentaciju()) {
        case Pravci::Sjever:
            ulaz << "sjever.";
            break;
        case Pravci::Istok:
            ulaz << "istok.";
            break;
        case Pravci::Zapad:
            ulaz << "zapad.";
            break;
        case Pravci::Jug:
            ulaz << "jug.";
            break;
    }
    
    ulaz << std::endl;
    
    return ulaz;
}

int main ()
{
    
    Robot r;
    
    std::cout << r;
    
    r.PostaviPoziciju(std::make_pair(1,1));
    r.PostaviOrijentaciju(Pravci::Zapad);
    
    r+=2;
    
    std::cout << r.DajPoziciju().first << r.DajPoziciju().second << std::endl;;
    
    r.operator+(2).operator-(-2);
    
    std::cout << r.DajPoziciju().first << r.DajPoziciju().second << std::endl;;
    
    std::cout << (int) r.DajOrijentaciju() << std::endl;;
    
    r.operator--().operator++(); // ista pozicija;
    
    std::cout << (int) r.DajOrijentaciju() << std::endl;
    
    Robot r2(1,1,Pravci::Sjever);
    
    if(r == r2) std::cout << "Isti"; else if(r != r2) std::cout << "Nisu isti";

	return 0;
}

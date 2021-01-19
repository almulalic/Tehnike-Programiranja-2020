//TP 2018/2019: Zadaća 4, Zadatak 1
#include <iostream>

#include <algorithm>
#include <cmath>

typedef std::pair<double, double> Tacka; 
enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno}; 
enum Smjer {Nalijevo, Nadesno}; 
  
class Pravougaonik {
   Tacka doleLijevo,goreLijevo,doleDesno,goreDesno;
   double horizontala,vertikala;
   
public:
    Pravougaonik(const Tacka &t1,const Tacka &t2);
    void Postavi(const Tacka &t1,const Tacka &t2);
    void Postavi(Pozicija p,const Tacka &t);
    void Centriraj(const Tacka &t);
    Tacka DajTjeme(Pozicija p) const;
    Tacka DajCentar() const;
    double DajHorizontalnu() const;
    double DajVertikalnu() const;
    double DajObim() const;
    double DajPovrsinu() const;
    static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
    void Transliraj(double deltaX,double deltaY);
    void Rotiraj(const Tacka &t,Smjer s);
    void Ispisi() const;
    friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};

Pravougaonik::Pravougaonik(const Tacka &t1,const Tacka &t2) {
    
    if(t1.first < t2.first && t1.second > t2.second) {
        doleLijevo = std::make_pair(t1.first, t2.second);
        goreLijevo = std::make_pair(t1.first, t1.second);
        doleDesno = std::make_pair(t2.first, t2.second);
        goreDesno = std::make_pair(t2.first, t1.second);
    } else if(t1.first < t2.first && t1.second < t2.second) {
        doleLijevo = std::make_pair(t1.first, t1.second);
        goreLijevo = std::make_pair(t1.first, t2.second);
        doleDesno = std::make_pair(t2.first, t1.second);
        goreDesno = std::make_pair(t2.first, t2.second);
    } else if (t1.first > t2.first && t1.second < t2.second) {
        doleLijevo = std::make_pair(t2.first, t1.second);
        goreLijevo = std::make_pair(t2.first, t2.second);
        doleDesno = std::make_pair(t1.first, t1.second);
        goreDesno = std::make_pair(t1.first, t2.second);
    } else if(t1.first > t2.first && t1.second > t2.second) {
        doleLijevo = std::make_pair(t2.first, t2.second);
        goreLijevo = std::make_pair(t2.first, t1.second);
        doleDesno = std::make_pair(t1.first, t2.second);
        goreDesno = std::make_pair(t1.first, t2.second);
    } else if(t1.first == t2.first && t1.first != t2.first) {
        doleLijevo = std::make_pair(t1.first,t1.second);
        goreLijevo = std::make_pair(t2.first,t2.second);
        doleDesno = std::make_pair(t1.first,t1.second);
        goreDesno = std::make_pair(t2.first,t2.second);
    } else if(t1.first != t2.first && t1.first == t2.first) {
        doleLijevo = std::make_pair(t2.first,t2.second);
        goreLijevo = std::make_pair(t1.first,t1.second);
        doleDesno = std::make_pair(t2.first,t2.second);
        goreDesno = std::make_pair(t1.first,t1.second);
    } else {
        doleLijevo = std::make_pair(t1.first,t1.second);
        goreLijevo = std::make_pair(t1.first,t1.second);
        doleDesno = std::make_pair(t1.first,t1.second);
        goreDesno = std::make_pair(t1.first,t1.second);
    }
    
    horizontala = abs(goreDesno.first - goreLijevo.first);
    vertikala = abs(goreLijevo.second - doleLijevo.second);
}

void Pravougaonik::Postavi(const Tacka &t1,const Tacka &t2) {
    
    if(t1.first < t2.first && t1.second > t2.second) {
        doleLijevo = std::make_pair(t1.first, t2.second);
        goreLijevo = std::make_pair(t1.first, t1.second);
        doleDesno = std::make_pair(t2.first, t2.second);
        goreDesno = std::make_pair(t2.first, t1.second);
    } else if(t1.first < t2.first && t1.second < t2.second) {
        doleLijevo = std::make_pair(t1.first, t1.second);
        goreLijevo = std::make_pair(t1.first, t2.second);
        doleDesno = std::make_pair(t2.first, t1.second);
        goreDesno = std::make_pair(t2.first, t2.second);
    } else if (t1.first > t2.first && t1.second < t2.second) {
        doleLijevo = std::make_pair(t2.first, t1.second);
        goreLijevo = std::make_pair(t2.first, t2.second);
        doleDesno = std::make_pair(t1.first, t1.second);
        goreDesno = std::make_pair(t1.first, t2.second);
    } else if(t1.first > t2.first && t1.second > t2.second) {
        doleLijevo = std::make_pair(t2.first, t2.second);
        goreLijevo = std::make_pair(t2.first, t1.second);
        doleDesno = std::make_pair(t1.first, t2.second);
        goreDesno = std::make_pair(t1.first, t2.second);
    } else if(t1.first == t2.first && t1.first != t2.first) {
        doleLijevo = std::make_pair(t1.first,t1.second);
        goreLijevo = std::make_pair(t2.first,t2.second);
        doleDesno = std::make_pair(t1.first,t1.second);
        goreDesno = std::make_pair(t2.first,t2.second);
    } else if(t1.first != t2.first && t1.first == t2.first) {
        doleLijevo = std::make_pair(t2.first,t2.second);
        goreLijevo = std::make_pair(t1.first,t1.second);
        doleDesno = std::make_pair(t2.first,t2.second);
        goreDesno = std::make_pair(t1.first,t1.second);
    } else {
        doleLijevo = std::make_pair(t1.first,t1.second);
        goreLijevo = std::make_pair(t1.first,t1.second);
        doleDesno = std::make_pair(t1.first,t1.second);
        goreDesno = std::make_pair(t1.first,t1.second);
    }
    
    horizontala = abs(goreDesno.first - goreLijevo.first);
    vertikala = abs(goreLijevo.second - doleLijevo.second);
}

void Pravougaonik::Postavi(Pozicija p,const Tacka &t) {
     
}

void Pravougaonik::Centriraj(const Tacka &t) {
    Tacka trenutniCentar = DajCentar();
    Tacka poluprecnik = std::make_pair(goreLijevo.first - trenutniCentar.first, goreLijevo.second - trenutniCentar.second);
   
    doleLijevo.first = t.first - poluprecnik.first;
    doleLijevo.second = t.second - poluprecnik.second;
    
    goreLijevo.first = t.first - poluprecnik.first;
    goreLijevo.second = t.second + poluprecnik.second;
    
    doleDesno.first = t.first + poluprecnik.first;
    doleDesno.second = t.second - poluprecnik.second;
    
    goreDesno.first = t.first + poluprecnik.first;
    goreDesno.second = t.second + poluprecnik.second;

}

double Pravougaonik::DajHorizontalnu() const { return horizontala; }

double Pravougaonik::DajVertikalnu() const { return vertikala; }

double Pravougaonik::DajObim() const {
    return 2.*vertikala + 2.*horizontala;
}

double Pravougaonik::DajPovrsinu() const {
    return vertikala * horizontala;
}

Tacka Pravougaonik::DajCentar() const {
    return std::make_pair((goreLijevo.first + doleDesno.first)/2.,(goreLijevo.second + doleDesno.second)/2.);
}

void Pravougaonik::Transliraj(double deltaX, double deltaY) {
    doleLijevo.first += deltaX;
    doleLijevo.second += deltaY;
    
    goreLijevo.first += deltaX;
    goreLijevo.second += deltaY;
    
    doleDesno.first += deltaX;
    doleDesno.second += deltaY;
    
    goreDesno.first += deltaX;
    goreDesno.second += deltaY;
}

void Pravougaonik::Rotiraj(const Tacka &t, Smjer s) {
//     int smjer = s == Nalijevo ? -1 : 1;
    if(s == Nadesno) {
        
        doleLijevo.first = t.first + doleDesno.second + t.second;
        doleLijevo.second = t.first - doleLijevo.first;
        
        goreLijevo.first = t.first + doleLijevo.second - t.second;
        goreLijevo.second = t.first + t.second - doleLijevo.first;
        
        doleDesno.first = t.first + goreDesno.second - t.second;
        doleDesno.second = t.first + t.second - goreDesno.first;
        
        goreDesno.first = t.first + doleLijevo.second - t.second;
        goreDesno.second = t.first + t.second - doleLijevo.first;
        
    }
//   if(t.first == goreDesno.first && t.second == goreDesno.second) {
//         doleDesno.first = (it -> first - t.second) * smjer; 
//         doleDesno.second = t.second();
//   } 
}

Tacka Pravougaonik::DajTjeme(Pozicija p) const {
    if(p == DoljeLijevo) return doleLijevo;
    else if (p == GoreLijevo) return goreLijevo;
    else if (p == DoljeDesno) return doleDesno;
    else if (p == GoreDesno) return goreDesno;
    
    return std::make_pair(0,0);
}

void Pravougaonik::Ispisi() const { std::cout << "{{" << goreLijevo.first << "," << goreLijevo.second << "},{" << doleDesno.first << "," << doleDesno.second << "}}"; }

bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2) {
    return p1.DajTjeme(GoreLijevo) == p2.DajTjeme(GoreLijevo) && p1.DajTjeme(DoljeDesno) == p2.DajTjeme(DoljeDesno);
}

bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2) {
    return (p1.DajHorizontalnu() == p2.DajHorizontalnu() && p1.DajVertikalnu() == p2.DajVertikalnu()) || (p1.DajHorizontalnu() == p2.DajVertikalnu() && p1.DajVertikalnu() == p2.DajHorizontalnu());
}
    
bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2) {
    double p1a = p1.DajHorizontalnu(),p1b = p1.DajVertikalnu();
    double p2a = p2.DajHorizontalnu(),p2b = p2.DajVertikalnu();
    
    double koeficijent1,koeficijent2;
    
    if(p1a > p1b) koeficijent1 = p1a / p1b;
    else koeficijent1 = p1b/p1a;
    
    if(p2a > p2b) koeficijent2 = p2a / p2b;
    else koeficijent2 = p2b / p2a;
    
    return fabs(koeficijent1-koeficijent2) < 0.0001;
}
    
int main () {
    
    int n;
    std::cout << "Unesite n: ";
    std::cin >> n;
    double tjeme11,tjeme12,tjeme21,tjeme22;
    
    int j=0;
    
    Pravougaonik** niz = new Pravougaonik*[n]();
    
    try {    
        for(int i=0;i<n;i++) {
            std::cout << "Unesite 1. tjeme pravougaonika " << i+1 << ": "; 
            std::cin >> tjeme11 >> tjeme12;
            std::cout << "Unesite 2. tjeme pravougaonika " << i+1 << ": ";
            std::cin >> tjeme21 >> tjeme22;
            
            niz[j++] = new Pravougaonik(std::make_pair(tjeme11,tjeme12),std::make_pair(tjeme21,tjeme22));
        }
    } catch (...) {
        std::cout << "Problemi sa memorijom";
        
        for(int i=0;i<j;i++) delete niz[i];
        delete[] niz;
    } 
    
    int dx,dy;
    std::cout << "Unesite podatke za transliranje (dx dy): ";
    std::cin >> dx >> dy;
    
    // std::transform(niz,niz+j,niz,[dx,dy](Pravougaonik *pravougaonik){
    //     return pravougaonik -> Transliraj(dx,dy);
    // });
    
    std::cout << "Pravougaonici, nakon transformacija: " << std::endl;
    for(int i=0;i<j;i++) {
        niz[i] -> Ispisi();
        std::cout << std::endl;
    }
    
    auto maxPovrsina = *std::max_element(niz,niz+j,[](Pravougaonik *a,Pravougaonik *b) {
        return a -> DajPovrsinu() < b -> DajPovrsinu();
    });
    
    std::cout << "Pravougaonik s najvecom povrsinom: ";
    maxPovrsina -> Ispisi();
    
    for(int i=0;i<j;i++) delete niz[i];
    delete[] niz;
    
	return 0;
}

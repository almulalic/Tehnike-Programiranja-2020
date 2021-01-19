//TP 2018/2019: Ispit 4, Zadatak 1
#include <iostream>

#include <cmath>

enum class Boja {Crna, Crvena, Zelena, Plava, Zuta, Smedja, Ljubicasta, Bijela};

const double EPSILON = 0.0000001;

class Tacka {

    double x,y;
    Boja boja;
    
public:
    Tacka(double x=0,double y=0,Boja boja = Boja::Crna) : x(x),y(y),boja(boja) {}
    
    double DajX() const { return x; }
    
    double DajY() const { return y; }
    
    Boja DajBoju() const { return boja; }
    
    Tacka& PostaviX(double noviX) { x = noviX; return *this; }
    
    Tacka& PostaviY(double noviY) { y = noviY; return *this; }
    
    Tacka& PostaviBoju(Boja novaBoja) { boja = static_cast<Boja>((int) novaBoja); return *this; }
    
    bool operator==(Tacka t) { return abs(x-t.x) < EPSILON && abs(y-t.y) < EPSILON; } 
    
    bool operator!=(Tacka t) { return !(*this == t); }
    
    bool operator!() { return abs(x-0) < EPSILON && abs(y-0) < EPSILON; } 
    
};

double operator*(Tacka &t) {
    return sqrt(pow(t.DajX(),2) + pow(t.DajY(),2));    
}

Tacka operator++(Tacka &t,int) {
    Tacka temp(t.DajX(),t.DajY(),t.DajBoju());
    
    if((int) t.DajBoju() == (int) Boja::Bijela)
        t.PostaviBoju(Boja::Crna);
    else 
        t.PostaviBoju( static_cast<Boja>((int) t.DajBoju() + 1));
    
    return temp;
}

Tacka& operator++(Tacka &t) {
    if((int) t.DajBoju() == (int) Boja::Bijela)
        t.PostaviBoju(Boja::Crna);
    else 
        t.PostaviBoju( static_cast<Boja>((int) t.DajBoju() + 1));
    
    return t;
}

std::ostream& operator<<(std::ostream& izlaz,Tacka t) {
    izlaz << "(" << t.DajX() << "," << t.DajY() << ")";
    
    return izlaz;
}


class Duz {
    Tacka t1,t2;
    
public:
    
    Duz(Tacka ta1,Tacka ta2) { 
        if(ta1.DajBoju() != ta2.DajBoju()) 
            throw std::domain_error("Nesaglasne boje krajeva");
        
        t1=ta1;
        t2=ta2;
        
    }
    
    Duz(double x1,double y1,double x2,double y2,Boja boja): t1(Tacka(x1,y1,boja)) , t2(Tacka(x2,y2,boja)) {}
    
    void Postavi(Tacka ta1,Tacka ta2) { 
        if((int) ta1.DajBoju() != (int)ta2.DajBoju())  
            throw std::domain_error("Nesaglasne boje krajeva");
            
        t1 = ta1;
        t2 = ta2;
    }
    
    void Postavi(int x1,int y1,int x2,int y2,Boja boja) {
        t1 = Tacka(x1,y1,boja);
        t2 = Tacka(x2,y2,boja);
    }
    
    Tacka DajLijeviKraj() const { if(abs(t1.DajX()-t2.DajX()) < EPSILON) return t1; if(t1.DajX() < t2.DajX()) return t1; else return t2; }
    
    Tacka DajDesniKraj() const { if(abs(t1.DajY()-t2.DajY()) < EPSILON) return t1; if(t1.DajY() < t2.DajY()) return t2; else return t1; }
    
    Boja DajBoju() const { return t1.DajBoju(); }
    
    bool operator==(Duz d)  {
        return (t1 == d.t1 && t2 == d.t2) || (t1 == d.t2 && t2 == d.t1);
    }
    
    bool operator!=(Duz d)  {
        return !(*this == d);
    }
    
    bool operator !() { return t1 == t2; }
    
    friend std::ostream& operator<<(std::ostream&, Duz d);
};

std::ostream& operator<<(std::ostream& izlaz,Duz d) {
    izlaz << d.t1 << "-" << d.t2;
    return izlaz;
}

Duz operator-(Tacka t1,Tacka t2) {
    if((int) t1.DajBoju() != (int)t2.DajBoju())  
        throw std::domain_error("Nesaglasne boje krajeva");
            
    return Duz(t1.DajX(),t1.DajY(),t2.DajX(),t2.DajY(),t1.DajBoju());
}


int main () {

 std::cout<<"----- AT 21 -----"<<std::endl;

    // AT 21: Test unarnog operatora !
    {
        // Operator mora biti izveden kao funkcija clanica
        Tacka t1(1,2);
        Tacka t2(3,4);
        Tacka t3(t1);

        Duz k1(t1,t2);
        Duz k2(t1,t3);

        std::cout<<std::boolalpha<<k1.operator!()<<" "<<k2.operator!();
    }

    std::cout<<std::endl<<"----- AT 22 -----"<<std::endl;

    // AT 22: Test operatora <<
    {
        Tacka t1(1,2);
        Tacka t2(3,4);

        Duz k(t1,t2);
        std::cout<<k;
    }

    std::cout<<std::endl<<"----- AT 23 -----"<<std::endl;

    // AT 23: Dodatni Test operatora << i ispravnosti metoda DajLijeviKraj i DajDesniKraj
    {
        Tacka t1(1,2);
        Tacka t2(-1,4);

        Duz k(t1,t2);
        std::cout<<k<<" ";

        k.Postavi(1,2,1,4,Boja::Zelena);
        std::cout<<k<<" ";
    }

    std::cout<<std::endl<<"----- AT 24 -----"<<std::endl;

    // AT 24: Test da li su inspektori zapravo implementirani kao inspektori
    {
        // Nece se testirati ispis, bitno je da se kod kompajlira kako bi se provjerila ispravnost
        Duz k1(1,2,3,4,Boja::Smedja);
        const Duz k(k1);
        const Duz k2(k1);
        k.DajLijeviKraj();
        k.DajDesniKraj();
        k.DajBoju();

        k.operator==(k2);
        k.operator!=(k2);

        std::cout<<"OK";
    }

    std::cout<<std::endl<<"----- AT 25 -----"<<std::endl;

    // AT 25: Test ispravnosti rada klasa i vecine operatora
    {
        Tacka t(5, 3, Boja::Zelena);
        std::cout << t.DajX() << " " << t.DajY() << " " << int(t.DajBoju()) << std::endl;
        Tacka t2 = t, t3(1, 1);
        std::cout << (t2 == t) << " " << (t3 == t) << std::endl;
        std::cout << *t << " " << !t << std::endl;
        t2++;
        ++t3;
        std::cout << t2.DajX() << " " << t2.DajY() << " " << int(t2.DajBoju()) << std::endl;
        std::cout << t3.DajX() << " " << t3.DajY() << " " << int(t3.DajBoju()) << std::endl;
        t.PostaviBoju(Boja::Smedja);
        t2.PostaviBoju(Boja::Smedja);
        Duz d(t, t2);
        Duz d2(4, 3, 2, 1, Boja::Crvena);
        std::cout << d << " " << d2 << std::endl;
        std::cout << d2.DajLijeviKraj() << " " << d2.DajDesniKraj()
                  << " " << int(d2.DajBoju()) << std::endl;
        std::cout << (d == d) << " " << (d == d2)  << std::endl;
        std::cout << !d << " " << !d2 << std::endl;
        std::cout << t - t2 << std::endl;
    }
    
    return 0;
}
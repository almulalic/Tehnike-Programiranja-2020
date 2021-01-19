//TP 2018/2019: Zadaća 5, Zadatak 2
#include <iostream>

#include <functional>
#include <algorithm>
#include <vector>

class Padavine {
  std::vector<int> padavine;
  int MAX_KOLICINE_PADAVINE;
  
public:
    explicit Padavine(int maksKolicinePadavine) {
        if(maksKolicinePadavine < 0)
            throw std::range_error("Ilegalna maksimalna kolicina");
        
        MAX_KOLICINE_PADAVINE = maksKolicinePadavine;
    }
    
    void RegistrirajPadavine(int kolicina) {
        if(kolicina < 0 || kolicina > MAX_KOLICINE_PADAVINE)
            throw std::range_error("Ilegalna kolicina padavina");
    
        padavine.push_back(kolicina);
    }
    
    int DajBrojRegistriranihPadavina() const { return padavine.size(); }
    
    void BrisiSve() { padavine.clear(); }
    
    int DajMinimalnuKolicinuPadavina() const {
        if(padavine.size() == 0)
            throw std::range_error("Nema registriranih padavina");
        
        return *std::min_element(padavine.begin(),padavine.end(),std::less<int>());
    }
    
    int DajMaksimalnuKolicinuPadavina() const {
        if(padavine.size() == 0)
            throw std::range_error("Nema registriranih padavina");
        
        return *std::max_element(padavine.begin(),padavine.end(),std::greater<int>());
    }
    
    void PostaviMaksimalanBrojPadavina(int noviMax) { MAX_KOLICINE_PADAVINE = noviMax; }
    
    int DajBrojDanaSaPadavinamaVecimOd(int kolicina) const {
        if(padavine.size() == 0)
            throw std::range_error("Nema registriranih padavina");
        
        return std::count_if(padavine.begin(),padavine.end(),std::bind2nd(std::greater<int> (), kolicina));
    }
    
    void Ispisi() const {
        auto sortirani = padavine;
        std::sort(sortirani.begin(),sortirani.end(),std::greater<int>());
        
        for(int padavina:sortirani) 
            std::cout << padavina << " ";
    }
 
    int operator[](int index) {
        if(index > padavine.size())
            throw std::range_error("Neispravan indeks");
        
        return padavine[index-1];
    }
    
    Padavine operator-(const Padavine &p) {
        Padavine nove(p.DajMaksimalnuKolicinuPadavina());
        
        return std::for_each(padavine.begin(),padavine.end(),std::bind2nd(std::minus<int> (p.DajMaksimalnuKolicinuPadavina())));
    }
    
    bool operator==(const Padavine &p) {
        if(padavine.size() != p.padavine.size())
            return false;
    }
    
    bool operator!=(const Padavine &p) {
        return!(padavine == p.padavine);
    }
    
    friend Padavine operator +(const Padavine &p1, const Padavine &p2);

    friend Padavine operator -(const Padavine &p1, const Padavine &p2);
    
    friend Padavine operator +(const Padavine &p, const int&broj);

    friend Padavine operator -(const Padavine &p, const int&broj);
    
    friend Padavine operator +(const int&broj,const Padavine &p);

    friend Padavine operator -(const int&broj,const Padavine &p);
};

Padavine operator +(const Padavine &p, const int&broj) {
    
    Padavine nove(p.padavine.size());
    
    for(int padavina:p.padavine) {
        if(padavina + broj < 0)
            throw std::domain_error("Nekorektan rezultat operacije");
            
        nove.padavine.push_back(padavina + broj);
    }
    
    nove.PostaviMaksimalanBrojPadavina(*std::max_element(nove.padavine.begin(),nove.padavine.end()));
    
    return nove;
}

Padavine operator -(const Padavine &p, const int&broj) {
    
    Padavine nove(p.padavine.size());
    
    for(int padavina:p.padavine) {
         if(padavina - broj < 0)
            throw std::domain_error("Nekorektan rezultat operacije");
        
        nove.padavine.push_back(padavina - broj);
    }
    
    nove.PostaviMaksimalanBrojPadavina(*std::max_element(nove.padavine.begin(),nove.padavine.end()));
    
    return nove;
}

Padavine operator +(const int&broj,const Padavine &p) {
    return p + broj;
}

Padavine operator -(const int&broj,const Padavine &p) {
    return p - broj;
}

Padavine operator -(const Padavine &p1, const Padavine &p2) {
    
    if(p1.padavine.size() != p2.padavine.size() && p1.DajMaksimalnuKolicinuPadavina() < p2.DajMaksimalnuKolicinuPadavina())
        throw std::domain_error("Nesaglasni operandi");
    
    Padavine nove(p1.DajMaksimalnuKolicinuPadavina());
    
    for(int i=0;i<p1.padavine.size();++i)
        nove.padavine.at(i) = p1.padavine.at(i) - p2.padavine.at(i);
    
    return nove;
}

int main () {
    Padavine t(10);
    Padavine t1(20);
    Padavine t2(10);
    for(int i= 5;i<=10;i++)
      {
        t.RegistrirajPadavine(i);
        t1.RegistrirajPadavine(i-1);
      }
    for(int i= 4;i>=1;i--)
      {
        t.RegistrirajPadavine(i);
        t1.RegistrirajPadavine(i-1);
      }
    // t-=t1;
    t.Ispisi();
    t2 = t-t;
    t2.Ispisi();

	return 0;
}
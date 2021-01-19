//TP 2018/2019: Ispit 4, Zadatak 2
#include <iostream>

#include <algorithm>
#include <cstring>
#include <vector>

struct Grad {
    char ime[50];
    int broj_stanovnika;
    
    Grad() : ime("nekoIme"), broj_stanovnika(0) {} 
};

class Gradovi {
    std::vector<Grad *> gradovi;
    
public:
    
    Gradovi() {} 
    
    void DodajGrad(const char ime[50],int broj_stanovnika) {
        if(strlen(ime) > 49)
            throw std::domain_error("Neisprani podaci");
        else if(broj_stanovnika <= 0)
            throw std::domain_error("Neispravni podaci");
        
        for(auto grad : gradovi)
            if(grad -> ime == ime)
                throw std::domain_error("Grad vec postoji");
        
        Grad *g;
        *g -> ime = ime;
        g -> broj_stanovnika = broj_stanovnika;
        gradovi.push_back(g);
    }
    
    void ObrisiGrad(const char ime[50]) {
        for(int i=0;i<gradovi.size();++i)
            if(gradovi.at(i) -> ime == ime) {
                gradovi.erase(gradovi.begin(),gradovi.begin() + i);
                break;
            }
    }
    
    int DajBrojGradova() const { return gradovi.size(); }
    
    Gradovi (Gradovi &noviGradovi) {
        gradovi = std::vector<Grad*>(noviGradovi.gradovi.size());
            
        if(gradovi.size() < noviGradovi.DajBrojGradova()) {
            try {
                for(int i=gradovi.size();i<noviGradovi.DajBrojGradova();i++)
                    gradovi.at(i) = new Grad(*noviGradovi.gradovi.at(i));
            } catch(...) {
                for(int i=gradovi.size();i<noviGradovi.DajBrojGradova();i++) {
                    delete gradovi.at(i);
                }
            }
            
        } else {
            for(int i=noviGradovi.DajBrojGradova();i<gradovi.size();i++) {
                delete gradovi.at(i);
            }
        } 
        
        for(int i=0;i<gradovi.size();i++) 
            gradovi.at(i) = noviGradovi.gradovi.at(i);
    }
    
    Gradovi &operator =(const Gradovi &noviGradovi) {
        
        if(&noviGradovi != this) {
            
            // for(int i=0;i<gradovi.size();i++) delete gradovi.at(i);
            
            gradovi = std::vector<Grad*>(noviGradovi.gradovi.size());
            
            if(gradovi.size() < noviGradovi.DajBrojGradova()) {
                try {
                    for(int i=gradovi.size();i<noviGradovi.DajBrojGradova();i++)
                        gradovi.at(i) = new Grad(*noviGradovi.gradovi.at(i));
                } catch(...) {
                    for(int i=gradovi.size();i<noviGradovi.DajBrojGradova();i++) {
                        delete gradovi.at(i);
                    }
                }
                
            } else {
                for(int i=noviGradovi.DajBrojGradova();i<gradovi.size();i++) {
                    delete gradovi.at(i);
                }
            } 
            
            for(int i=0;i<gradovi.size();i++) 
                gradovi.at(i) = noviGradovi.gradovi.at(i);
        }
        
        return *this;
    }
    
    Gradovi &operator =(Gradovi &&noviGradovi) {
        
        if(&noviGradovi != this) {
            std::swap(gradovi,noviGradovi.gradovi);
        }
        
        return *this;
    }
    
    ~Gradovi() { for(int i=0;i<gradovi.size();++i) delete gradovi.at(i); }
    
    int operator[](const char ime[50]) {
        int postoji(0);
        
        for(int i=0;i<gradovi.size();++i) {
            if(gradovi.at(i) -> ime == ime) {
                postoji = i;
                break;
            }
        }
        
        if(!postoji) throw std::range_error("Nepostojeci grad");
        
        return gradovi.at(postoji) -> broj_stanovnika;
    } 
    
    void SortirajGradove() {
        std::sort(gradovi.begin(),gradovi.end(),[](Grad *a,Grad *b) {
            return a -> broj_stanovnika < b -> broj_stanovnika;
        });
    }
    
    void Ispisi(std::ostream& izlaz = std::cout) const {
        for(auto grad:gradovi)
            izlaz << grad -> ime << ": " << grad -> broj_stanovnika; 
    }
    
};

int main () {
    
      std::cout << "AT1" << std::endl;
    {
        //AT1 - testiranje konstruktora klase Gradovi (potrebno je samo da se kompajlira)
        Gradovi g;
        std::cout << "OK" << std::endl;
    }

        std::cout << "AT15" << std::endl;
    {
        //AT15 - test strukture Grad
        struct Grad g1;
        char c[50]{"Tuzla"};
        std::strcpy(g1.ime, c);
        g1.broj_stanovnika = 130000;
        std::cout << g1.ime << " " << g1.broj_stanovnika << std::endl;
    }

    std::cout << "AT2" << std::endl;
    {
        //AT2 - testiranje funkcija članica DodajGrad, ObrisiGrad, DajBrojGradova
        Gradovi g;
        std::cout << g.DajBrojGradova() << " ";
        g.DodajGrad("Tuzla", 130000);
        std::cout << g.DajBrojGradova() << " ";
        g.ObrisiGrad("Tuzla");
        std::cout << g.DajBrojGradova() << " ";
        g.DodajGrad("Bihac", 50000);
        g.DodajGrad("Sarajevo", 350000);
        g.DodajGrad("Mostar", 100000);
        std::cout << g.DajBrojGradova() << " ";
        g.ObrisiGrad("Mostar");
        std::cout << g.DajBrojGradova() << std::endl;
    }

        std::cout << "AT3" << std::endl;
    {
        //AT3 - testiranje funkcija članica DodajGrad, ObrisiGrad, Ispisi
        Gradovi g;
        g.Ispisi();
        g.DodajGrad("Tuzla", 130000);
        g.Ispisi();
        g.ObrisiGrad("Tuzla");
        g.Ispisi();
        g.DodajGrad("Bihac", 50000);
        g.DodajGrad("Sarajevo", 350000);
        g.DodajGrad("Mostar", 100000);
        g.Ispisi();
        g.ObrisiGrad("Mostar");
        g.Ispisi();
    }

    std::cout << "AT4" << std::endl;
    {
        //AT4 - testiranje funkcije članice DodajGrad za izuzetkom
        Gradovi g;
        g.DodajGrad("Tuzla", 130000);
        
        try
        {
            g.DodajGrad("Tuzla", 130000);
            std::cout << "Ovo se ne smije ispisati!" << std::endl;
        } 
        catch (std::domain_error e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Pogresan izuzetak!" << std::endl;
        }
    }
    std::cout << "AT5" << std::endl;
    {
        //AT5 - testiranje funkcije članice DodajGrad za izuzetkom
        Gradovi g;
        g.DodajGrad("Tuzla", 130000);
        g.ObrisiGrad("Tuzl");
        g.Ispisi();
    }


	return 0;
}
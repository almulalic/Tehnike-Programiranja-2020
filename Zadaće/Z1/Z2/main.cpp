//TP 2016/2017: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <deque>

enum Smjer { Rastuci,Opadajuci };

void Zamjeni(double &a,double &b) {
    double temp = a;
    a = b;
    b = temp;
}

bool DaLiJeBalansiran(std::vector<double> podniz) {
    int n = podniz.size();
    const double epsilon = 0.00001;
    
    double sumaLijevo=0,sumaDesno=0;
    
    if(n%2==0) {
        for(int i=0;i<n;i++) {
            if(i<n/2)
                sumaLijevo += podniz.at(i);
            else if(i>=n/2)
                sumaDesno += podniz.at(i);
        }
    } else {
        for(int i=0;i<n;i++) {
            if(i<n/2)
                sumaLijevo += podniz.at(i);
            else if(i>n/2)
                sumaDesno += podniz.at(i);
        }
    }
    
    return (fabs(sumaDesno-sumaLijevo) < epsilon);
}

bool DaLiJeSadrzan(std::vector<double> prvi,std::vector<double> drugi) {
    const double epsilon = 0.00001;
        
    int brojac=0,j;
    
    for(int i=0;i<prvi.size();i++) {
        brojac=0;
        for(j=0;j<drugi.size();j++) {
            if(fabs(drugi.at(j) - prvi.at(i)) < epsilon){
                brojac++;
                i++;
                if(brojac == drugi.size())
                    return true;
                else if (i >= prvi.size())
                    return false;
            } else break;
        }
        
        i-=brojac;
        
        if(brojac==drugi.size())
            return true;

    }
    
    return false;
}

std::vector<double> TransformisiUBalansiran(std::vector<double> niz,Smjer izabraniSmjer) {
    int n = niz.size();
    bool neparan = n%2 == 1;
    
    std::vector<double> prvi,drugi;
    
    for(int i=0;i<n/2;i++)
        prvi.push_back(niz.at(i));
    
    for(int i=(neparan ? (n/2)+1 : n/2);i<n;i++)
        drugi.push_back(niz.at(i));
   
    for(int i=0;i<prvi.size();i++) {
        for(int j=i+1;j<prvi.size();j++) {
            if(izabraniSmjer == Rastuci && prvi.at(i) > prvi.at(j))
                Zamjeni(prvi.at(i),prvi.at(j));
            else if(izabraniSmjer == Opadajuci && prvi.at(i) < prvi.at(j))
                Zamjeni(prvi.at(i),prvi.at(j));
        }
    }
    
    for(int i=0;i<drugi.size();i++) {
        for(int j=i+1;j<drugi.size();j++) {
            if(izabraniSmjer == Rastuci && drugi.at(i) < drugi.at(j))
                Zamjeni(drugi.at(i),drugi.at(j));
            else if(izabraniSmjer == Opadajuci && drugi.at(i) > drugi.at(j))
                Zamjeni(drugi.at(i),drugi.at(j));
        }
    }
    
    
    std::vector<double> sortirani;
    for(int i=0;i<prvi.size();i++)
        sortirani.push_back(prvi.at(i));
    
    if(neparan)
        sortirani.push_back(niz.at(n/2));
        
    for(int i=0;i<drugi.size();i++)
        sortirani.push_back(drugi.at(i));
    

    return sortirani;
}

std::deque<std::vector<double>> IzbaciSadrzane(std::deque<std::vector<double>> dek) {
    
    std::deque<std::vector<double>> rezultat;
    int brojac=1;
    
    for(int i=0;i<dek.size();i++) {
        brojac=1;
        for(int j=0;j<dek.size();j++) {
            if(!DaLiJeSadrzan(dek.at(j),dek.at(i))) 
                brojac++;
        }

        if(brojac == dek.size())
            rezultat.push_back(dek.at(i));
    }
    
    return rezultat;
}

std::deque<std::vector<double>> MaksimalniBalansiraniPodniz(std::vector<double> niz){
    
    std::vector<double> podniz;
    std::deque<std::vector<double>> dek;
    
    for(int i=0;i<niz.size();i++) {
        for(int j=niz.size()-1;j>i;j--) {
            podniz.clear();
            for(int k=i;k<=j;k++)
                podniz.push_back(niz.at(k));
            if(DaLiJeBalansiran(podniz))
                dek.push_back(podniz);
        }
    }

    return IzbaciSadrzane(dek);
}

std::deque<std::vector<double>> Transformacija(std::deque<std::vector<double>> dek,Smjer odabraniSmjer) {
    
    for(int i=0;i<dek.size();i++) {
        if(!DaLiJeBalansiran(dek.at(i)))
            throw std::domain_error("Dek vektora je neispravan.");
    }
    
    std::deque<std::vector<double>> sortirani;
    
    for(int i=0;i<dek.size();i++) {
        sortirani.push_back(TransformisiUBalansiran(dek.at(i),odabraniSmjer));
    }
    
    return sortirani;
    
}

int main ()
{
    
    int n;
    std::cout << "Unesite broj elemenata niza: ";
    std::cin >> n;
    std::cout << "Unesite elemente niza: ";
    
    std::vector<double> niz;
    int unos;
    
    for(int i=0;i<n;i++) {
        std::cin >> unos;
        niz.push_back(unos);
    }
    
    int izabraniSmjer;
    std::cout << "Unesite tip: (1 - rastuci, 0 - opadajuci): " << std::endl;
    std::cin >> izabraniSmjer;
    Smjer smir = (Smjer) izabraniSmjer == 1 ? Rastuci : Opadajuci;
    
    std::deque<std::vector<double>> dek = MaksimalniBalansiraniPodniz(niz);
    std::cout << "Maksimalni balansirani podnizovi: " << std::endl;
    
    for(int i=0;i<dek.size();i++) {
            for(int j=0;j<dek.at(i).size();j++) {
                std::cout << dek.at(i).at(j) << ' ';
            }
        std::cout << std::endl;
    }

    std::cout << "Savrseni balansirani podnizovi nakon transformacije: " << std::endl;
    
    std::deque<std::vector<double>> sortirani = Transformacija(dek,smir);
    
    for(int i=0;i<sortirani.size();i++) {
            for(int j=0;j<sortirani.at(i).size();j++) {
                std::cout << sortirani.at(i).at(j) << ' ';
            } 
        std::cout << std::endl;
    }
    
	return 0;
}
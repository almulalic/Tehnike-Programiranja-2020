//TP 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>

#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

const double EPSILON = 0.000001;

std::function<double(double)> LagrangeovaInterpolacija(std::vector<std::pair<double,double>> parovi) {
    
    auto sortiraniParovi = parovi;
    std::sort(sortiraniParovi.begin(),sortiraniParovi.end());
    
    int n = parovi.size();
    for(int i=0;i<n-1;i++) {
        if(fabs(parovi.at(i+1).first - parovi.at(i).first) < EPSILON)
            throw std::domain_error("Neispravni cvorovi");
    }

    return [parovi,n](double x) {

        double suma(0),produkt;
        
        for(int i=0;i<n;i++) {
            produkt = 1;
            for(int j=0;j<n;j++) {
                if(j!=i) {
                    produkt *= (x-parovi.at(j).first) / (parovi.at(i).first - parovi.at(j).first);
                }
            }
            suma += parovi.at(i).second * produkt;
        }
        
        return suma;
    };
}

std::function<double(double)> LagrangeovaInterpolacija(std::function<double(double)> interpolacijskaFunkcija,int xMin,int xMax,double deltaX) {
    if(xMin > xMax || deltaX <= 0)
        throw std::domain_error("Nekorektni parametri");
        
    std::vector<std::pair<double,double>> parovi;
    int xMaxGranica = (fabs(std::fmod((xMax - xMin),deltaX) - 0) < EPSILON) ? xMax+deltaX : xMax;
    
    int multiplier(1);
    for(double i=xMin;i<=xMaxGranica;i+=deltaX) {
        parovi.push_back(std::make_pair(i,interpolacijskaFunkcija(i)));
        multiplier++;
    }
    
    
    return LagrangeovaInterpolacija(parovi);
    
}

double ZadanaFunkcija(double x) { return pow(x,2) + sin(x) + log(x+1);}

int main ()
{
    int meniIzbor;
    std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin >> meniIzbor;
    
    if(meniIzbor == 1) {
        int brojCvorova;
        std::vector<std::pair<double,double>> parovi;
        double tempParPrvi,tempParDrugi;
        
        std::cout << "Unesite broj cvorova: ";
        std::cin >> brojCvorova;
        
        if(brojCvorova <= 0 ) {
            std::cout << "Broj cvorova mora biti pozitivan broj!";
            return 1;
        }
        
        double xMin(0),xMax(0);
        
        std::cout << "Unesite cvorove kao parove x y: ";
        for(int i=0;i<brojCvorova;i++) {
            std::cin >> tempParPrvi >> tempParDrugi;
            
            if(i == 0) {
                xMin = tempParPrvi;
                xMax = tempParPrvi;
            } else {
                if(tempParPrvi < xMin)
                    xMin = tempParPrvi;
                if(tempParPrvi > xMax)
                    xMax = tempParPrvi;
            }
                
            parovi.push_back(std::make_pair(tempParPrvi,tempParDrugi));
        }
        
         try {
            auto FunckijaInterpolacije = LagrangeovaInterpolacija(parovi);
            
            std::string unos;
            for(;;) {
                std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
                std::cin >> unos;    
                if(unos == "kraj") 
                    break;
                
                std::cout << "f(" + unos + ") = " << FunckijaInterpolacije(std::stod(unos)) << ((std::stoi(unos) < xMin || std::stoi(unos) > xMax) ? " [ekstrapolacija]" : "") << std::endl;
            }
        
        } catch(std::domain_error err) {
            std::cout << "IZUZETAK: " << err.what() << "!" << std::endl;
            return 1;
        }
    
    } else if (meniIzbor == 2) {
        double xMin,xMax,deltaX;
        std::cout << "Unesite krajeve intervala i korak: ";
        std::cin >> xMin >> xMax >> deltaX;
        
         try {
             
            auto FunckijaInterpolacije = LagrangeovaInterpolacija(ZadanaFunkcija,xMin,xMax,deltaX);
            std::string unos;
            for(;;) {
                std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
                std::cin >> unos;    
                if(unos == "kraj") 
                    break;
                
                std::cout << "f(" + unos + ") = " <<  ZadanaFunkcija(std::stod(unos)) << " P(" + unos + ") = " << FunckijaInterpolacije(std::stod(unos)) << ((std::stod(unos) < xMin || std::stod(unos) > xMax) ? " [ekstrapolacija]" : "") << std::endl;
            }
            
         } catch(std::domain_error err) {
            std::cout << "IZUZETAK: " << err.what() << "!" << std::endl;
            return 1;
        }
            
    } else {
        std::cout << "Nepoznat slucaj!";
    }
    
    
	return 0;
}
//TP 2018/2019: Ispit 2, Zadatak 3
#include <iostream>
#include <string>

// 1 AT

int OgradiRijec(std::string &recenica,int n) {
  
  int duzina = recenica.size();
  int k(0),l(0);
  int rijec(0),i(0);
  bool izbrisana(false);
  
  if(recenica.at(0) != ' ')
    rijec++;
  
  if(n < 1)
    throw std::range_error("Nekorektan redni broj rijeci");
    
  while(i < duzina) {
    
    if(i!=0 && recenica.at(i) != ' ' && recenica.at(i-1) == ' ') {
        rijec++;
    }     
    
    if(rijec == n && !izbrisana) {
      k=i;
      l=i;
      while(recenica.at(l) != ' ') {
        if(l == duzina - 1)
          break;
        l++;
      }
      izbrisana = true;
    }
    
    if(i == duzina)
      break;
      
    i++;
  }
    
    if(n > rijec)
      throw std::range_error("Nekorektan redni broj rijeci");
      
    recenica.erase(recenica.begin() + k, recenica.begin() + l);
    
    return rijec;
}

int main ()
{
    
    std::string unos;
    std::cout << "Uneiste string: ";
    std::getline(std::cin,unos);
    
    int n;
    std::cout << "Redni broj rijeci: ";
    std::cin >> n;
    
    int broj = OgradiRijec(unos,n);

    std::cout << "Modificirani string: " << unos << std::endl;
    std::cout << "Broj rijeci: " << broj;
    
	return 0;
}
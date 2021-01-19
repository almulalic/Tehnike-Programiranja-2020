//TP 2018/2019: Tutorijal 3, Zadatak 7
#include <iostream>
#include <iomanip>
#include <vector>

typedef std::vector<int> vektor;
typedef std::vector<std::vector<int>> matrica;


matrica PascalovTrougao(int n){
    
    if(n==0)
        return matrica(0,vektor(0));
    if(n<=0)
        throw std::domain_error("Broj redova ne smije biti negativan");
    
    int kolone=1;
    
    matrica pascal(n,vektor(kolone));
    
    for(int i=0;i<n;i++){
        pascal.at(i).resize(kolone);
        for(int j=0;j<kolone;j++){
              if(i<2 || j==0 || j==kolone-1)
                pascal.at(i).at(j) = 1;
              else 
                pascal.at(i).at(j) = pascal.at(i).at(j) + pascal[i-1][j-1];
        }
        kolone++;
    }
    
    return pascal;

}

int NajvecaSirina(std::vector<std::vector<int>> matrica) {
    
    int max = matrica.at(0).at(0);
    
    for(int i=0;i<matrica.size();i++) {
        for(int j=0;j<matrica.at(i).size();j++) {
            if(matrica.at(i).at(j) > max) max = matrica.at(i).at(j);
        }
    }
    
    int cifre(1);
    
    while(max!=0) {
        cifre++;
        max/=10;
    }
    
    return cifre;
}

int main ()
{
    
    std::cout << "Unesite broj redova: ";
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> paskalovTrougao = PascalovTrougao(n);
    int sirina = NajvecaSirina(paskalovTrougao);
    
    for(int i=0;i<paskalovTrougao.size();i++) {
        for(int j=0;j<paskalovTrougao.at(i).size();j++) {
            std::cout << std::setw(sirina) << std::right << paskalovTrougao.at(i).at(j);
        }
        std::cout << std::endl;
    }
    
	return 0;
}
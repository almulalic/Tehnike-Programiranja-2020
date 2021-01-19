//TP 2018/2019: Zadaća 2, Zadatak 3
#include <iostream>
#include <iomanip>
#include <cmath>

int RekurzivniStriling(long long int n,long long int k) {
    
    if(n == 0 || k ==0 || k > n)
        return 0;
    if(k == 1 || k == n)
        return 1;
    
    return RekurzivniStriling(n-1,k-1) + (k*RekurzivniStriling(n-1,k));
}

int NajsiriBroj(long long int **mat,int n) {
    
    if(n < 0)
        throw std::domain_error("Izuzetak: Parametar ne smije biti negativan");
    
    n++;
        
    int najveci = 1;
    
    for(int i=0;i<n;i++) {
        for(int j=0;j<i+1;j++) {
            if(mat[i][j] != 0 && floor(log10(mat[i][j])+1) > najveci)
                najveci = floor(log10(mat[i][j])+1);
        }
    }
    
    return najveci+1;
}

long long int **StirlingoviBrojeviF(int n) {
    
    if(n < 0)
        throw std::domain_error("Parametar ne smije biti negativan");
    
    n++;
    
    try {
    
        long long int **mat = new long long int* [n];
        int brojac(0);
        
        try {
            while(brojac < n) mat[brojac++] = new long long int [n];
            
            mat[0][0] = 1;
            for(int i=1;i<n;i++) {
                mat[i][0] = 0;
                for(int j=1;j<i+1;j++) {
                    mat[i][j] = RekurzivniStriling(i,j);
                }
            }
            
            return mat;
            
        } catch (...) {
            for(int i =0;i<brojac;i++) delete[] mat[i];
            delete [] mat;
            throw;
        }
        
    } catch(...) {
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
    
    return nullptr;
}

long long int **StirlingoviBrojeviK(int n) {
    
    if(n < 0)
        throw std::domain_error("Izuzetak: Parametar ne smije biti negativan");
    
    n++;
    
    try {
        long long int ** mat = new long long int* [n];
        
        try {
            mat[0] = new long long int [n * n];
            for(int i=1;i<n;i++) mat[i] = mat[i-1] + i;
            
            mat[0][0] = 1;
            for(int i=1;i<n;i++) {
                mat[i][0] = 0;
                for(int j=0;j<n;j++) {
                    mat[i][j] = RekurzivniStriling(i,j);
                }
            }
            
            return mat;

        } catch (...) {
            delete[] mat[0];
            delete[] mat;
            throw;
        }
    } catch(...) {
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
 
    return nullptr;   
}
    
int main ()
{
    
    int n;
	std::cout << "Unesite broj n: ";
	std::cin >> n;
	
	long long int **matF = nullptr;
	
	try {
        matF = StirlingoviBrojeviF(n);
    } catch(std::exception &err) {
        std::cout<<"Izuzetak: "<< err.what() <<"!";
        return 1;
    }	
    
    int sirina = 0;
    try {
     sirina = NajsiriBroj(matF,n);
    } catch(std::exception &err) {
        std::cout<<"Izuzetak: "<< err.what() <<"!";
        return 1;
    } 
    
    std::cout << std::endl;
    	
	std::cout << "Stirlingovi brojevi - fragmentirana alokacija: " << std::endl;
    
    for(int i=0;i<n+1;i++) {
        for(int j=0;j<i+1;j++) {
            std::cout << std::setw(sirina) << matF[i][j];
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
	
	long long int **matK = nullptr;
	
	try {
	    matK = StirlingoviBrojeviK(n);
	} catch(std::exception &err) {
        std::cout<<"Izuzetak: "<< err.what() <<"!";
        return 1;
    }
    
	std::cout << "Stirlingovi brojevi - kontinualna alokacija: " << std::endl;
	
	for(int i=0;i<n+1;i++) {
        for(int j=0;j<i+1;j++) {
            std::cout << std::setw(sirina) << matK[i][j];
        }
        std::cout << std::endl;
    }
    
    // Fragmentirana delokacija
    
	for(int i=0;i<n+1;i++) delete[] matF[i];
    delete[] matF;
    
    // Kontinuinalna delokacija
    
    delete[] matK[0]; delete[] matK;
    
	return 0;
}
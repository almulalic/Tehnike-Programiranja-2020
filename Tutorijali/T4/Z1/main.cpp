//TP 2018/2019: Tutorijal 4, Zadatak 1
#include <iostream>

int Cifre(long long int n,int &c_min,int &c_max) {
    
    int brojCifara(0);
    int cifra;
    
    c_max=n%10;
    c_min=n%10;
    
    c_max=abs(c_max);
    c_min=abs(c_min);
    
     do {
        brojCifara++;
        cifra=n%10;
        
        if(cifra<0) cifra*=-1;
        if(cifra<c_min) c_min=cifra;
        if(cifra>c_max) c_max=cifra;
            
        n/=10;
    }while(n!=0);

    return brojCifara;
}


int main ()
{
    long long int broj;
    std::cout<<"Unesite broj: ";
    std::cin>>broj;
   
    int a,b;
    int e=Cifre(broj,a,b);
   
    std::cout<<"Broj "<<broj<<" ima "<< e <<" cifara, najveca je "<<b<<" a najmanja "<<a<<".";
   
    return 0;
}
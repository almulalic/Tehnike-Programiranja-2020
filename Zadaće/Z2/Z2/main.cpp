//TP 2018/2019: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>


template <typename TipElemenata>
TipElemenata ZbirProstihFaktora(TipElemenata broj) {
    
   TipElemenata suma(0);
   int i(2),prosli(0);
   while(broj != 1) {
       if(broj % i == 0) {
        if(i != prosli)
            suma+=i;
        prosli = i;
        broj/=i;
       } else i++;
   }
    
    return suma;
}

template <typename TipElemenata>
bool DaLiJeSlobodanKvadrat(TipElemenata broj) {
    
    if(broj % 2 == 0)
        broj = broj/2;
    
    if(broj % 2 == 0)
        return false;
        
    for(int i=3;i<=sqrt(broj);i=i+2) {
        if(broj % i == 0) {
            broj = broj/i;
            
            if(broj % i == 0)
                return false;
        }
    }
    
    return true;
}

template <typename TipElemenata>
TipElemenata* Izdvajanje(TipElemenata *p1,TipElemenata *&p2,int &rezultat) {
    
    TipElemenata* niz = nullptr;
    int duzina(0);
    TipElemenata *poc = p1,*kraj = p2;

    try {
      
        niz = new TipElemenata[kraj-poc];
    
        while(poc != kraj) {
            if(DaLiJeSlobodanKvadrat(*poc)) {
                niz[duzina] = *poc;
                duzina++;
            }
            poc++;
        }
        
        while(niz != niz+duzina) {
            int* temp = niz+1;
            while(temp != niz+duzina) {
                if(*niz == *temp) {
                    int* k = temp;
                    while(k!=niz+duzina) {
                        *k=*(k+1);
                        k++;
                    }
                    duzina--;
                }
                temp++;
            }
            niz++;
        }
        
        // std::for_each(p1,p2,[p1,p2](int prvi) {
        //     std::remove_if(p1,p2,[prvi](int drugi){
        //         return ZbirProstihFaktora(prvi) == ZbirProstihFaktora(drugi);
        //     });
        // });      
        // int duzina2 = (p2-p1);
        
        // for(int i=0;i<duzina2;i++) {
        //     for(int j=i+1;j<duzina2;j++) {
        //         if(ZbirProstihFaktora(p1[i]) == ZbirProstihFaktora(p1[j])) {
        //             for(int k=i;k<duzina2;k++)
        //                 p1[k] = p1[k+1];
        //             for(int k=j;k<duzina2;k++)
        //                 p1[k] = p1[k+1];
        //             duzina2-=2;
        //             p2-=2;
        //         }
        //     }
        // }
        
        p2--;
        rezultat = duzina;
 
    
    } catch(...) {
        throw std::range_error("Nedovoljno memorije!");
        delete[] niz;    
    }
    
    
    return niz;
}

int UmnozakCifara(int a) {
    int umnozak(1);
    while(a!=0) {
        umnozak*=a%10;
        a/=10;
    }
    
    return umnozak;
}

int main ()
{
    
    int brojevi[100];
    ZbirProstihFaktora(63);
    std::cout << "Unesite brojeve: ";
    int unos,duzina(0);
    
    for(;;) {
        
        std::cin >> unos;
        
        if(unos == -1)
            break;
        else {
            brojevi[duzina] = unos;
            duzina++;
        }
    }
    
    int rez(0);
    auto adresa = brojevi+duzina;
    int *p = Izdvajanje(brojevi,adresa,rez);
    
    std::cout << "Izdvojeni brojevi: ";
    for(int i=0;i<rez;i++) {
        if(i!=rez-1)
            std::cout << p[i] << ", ";
        else
            std::cout << p[i];
    }
    
    std::cout << std::endl;
    
    int *poc = brojevi,*pocSort = brojevi;
    std::cout << "Modificirani kontejner (prije sortiranja): ";
    while(poc != adresa) {
        if(poc != adresa-1)
            std::cout << *poc << ", ";
        else
            std::cout << *poc;
        poc++;
    }
    
    std::sort(pocSort,adresa,[](int a,int b)-> bool {
        return UmnozakCifara(a) < UmnozakCifara(b);
    });
    
    std::cout << std::endl;
    
    std::cout << "Modificirani kontejner (nakon sortiranja): ";
    while(pocSort != adresa) {
        if(pocSort != adresa-1)
            std::cout << *pocSort << ", ";
        else
            std::cout << *pocSort;
        pocSort++;
    }
    
    
    delete[] p;
	return 0;
}
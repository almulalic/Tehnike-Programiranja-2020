//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>

#include <set>
#include <list>

int Poglavica(int punoljetni,int korakRazbrajanja,bool ispis = false) {
    std::list<int> lista;
    
    for(int i=0;i<punoljetni;i++) {
        lista.push_back(i+1);
    }
    
    std::list<int>::iterator it=lista.begin();
    int brojac(1);
    
    for(;;) {
        
        if(brojac == korakRazbrajanja) {
            if(ispis) std::cout << *it << " ";
            it = lista.erase(it);
            brojac=1;
        } else {
            it++;
            brojac++;
        }
                    
        if(it==lista.end())
            it=lista.begin();
        
        if(lista.size() == 1)
            break;
    }

    return *it;
}

int SigurnoMjesto(int korakRazbrajanja,int rasponMin,int rasponMax) {
    
    std::set<int> biljeske;
    for(int i=rasponMin;i<rasponMax;i++) {
        biljeske.insert(Poglavica(i,korakRazbrajanja));
    }
    
    std::set<int>::iterator it = biljeske.begin();
    for(int i=1;i<=rasponMax;i++) {
        if(*it++ != i)
            return i;
    }
        
    return 0;
}

int main () {
    
    int punoljetni;
    std::cout << "Unesi broj punoljetnih clanova (N): ";
	std::cin >> punoljetni;
	
	int korakRazbrajanja;
	std::cout << "Unesi korak razbrajanja (M): ";
	std::cin >> korakRazbrajanja;
	
	int rasponMin,rasponMax;
	std::cout << "Unesi raspon (N1-N2): ";
	std::cin >> rasponMin >> rasponMax;
	
	
	std::cout << "Redni broj osobe koja postaje poglavica: " << Poglavica(punoljetni,korakRazbrajanja) << " ";
	std::cout << "Sigurno mjesto: " << SigurnoMjesto(korakRazbrajanja,rasponMin,rasponMax);

	return 0;
}
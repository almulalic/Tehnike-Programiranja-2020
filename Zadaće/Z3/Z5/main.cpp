//TP 2018/2019: Zadaća 3, Zadatak 5

#include <iostream>

#include <set>

struct Cvor {
 int redniBroj;
 Cvor *sljedeci;
};


int Poglavica(int punoljetni,int korakRazbrajanja,bool ispis = false) {
    
    Cvor *incPocetak = nullptr, *incPredhodni=nullptr;
    
    Cvor *novi = nullptr;
    for(int i=1;i<=punoljetni;i++) { 
        try {
            novi = new Cvor{i,nullptr};
            if(!incPocetak) incPocetak = novi;
            else if(i==punoljetni) { incPredhodni->sljedeci = novi; novi->sljedeci = incPocetak;}
            else incPredhodni->sljedeci = novi;
            incPredhodni = novi;
        } catch(...) {
            Cvor* pred = incPocetak,*p = incPocetak;
            while(p->sljedeci != nullptr) {
                pred = p;
                p = p -> sljedeci;
                delete pred;
            }
            delete novi;
            delete incPocetak;
            delete incPredhodni;
            throw;
        }
    }
    
    int brojac(1),i(0),noviPoglavica;
    Cvor *it = incPocetak,*itPred = incPocetak; 
    for(;;) {
            
        if(brojac == korakRazbrajanja) {
            if(ispis) std::cout << it -> redniBroj << " ";
            // Brisanje
            Cvor *temp = it;
            it = it -> sljedeci;
            itPred->sljedeci = itPred->sljedeci->sljedeci;
            temp -> sljedeci = nullptr;
            delete temp;
            brojac=1;
            i++;
            
        } else {
            itPred = it;
            it = it -> sljedeci;
            brojac++;
        }
        
        if(it->redniBroj == it->sljedeci->redniBroj) {
            noviPoglavica = it -> redniBroj;
            break;
        }
    }

    delete it;

    return noviPoglavica;
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
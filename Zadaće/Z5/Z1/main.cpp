//TP 2018/2019: Zadaća 5, Zadatak 1
#include <iostream>

#include <initializer_list>
#include <iomanip>
#include <vector>

template <class T> class SimetricnaMatrica {
    
    std::vector<std::vector<T>> elementi;
        
public:
    SimetricnaMatrica(SimetricnaMatrica& sm);
    
    SimetricnaMatrica(SimetricnaMatrica&& sm);
    
    SimetricnaMatrica(std::vector<std::vector<T>> vv);
    
    SimetricnaMatrica(std::initializer_list<std::initializer_list<T>> vv);
    
    explicit SimetricnaMatrica(int n=0);
    
    int DajDimenziju() const { return elementi.size(); }
    
    bool operator!();
    
    template <typename Tp1,typename Tp2>
    friend auto operator+(const SimetricnaMatrica<Tp1>& a, const SimetricnaMatrica<Tp2>& b) -> decltype(auto c = a.elementi.at(0) + b.elementi.at(0));
    
    template <typename Tp1,typename Tp2>
    friend auto operator-(const SimetricnaMatrica<Tp1>& a, const SimetricnaMatrica<Tp2>& b);

    template <typename Tp1,typename Tp2>
    friend auto operator*(const SimetricnaMatrica<Tp1>& a, const SimetricnaMatrica<Tp2>& b);
    
    template <typename Tp>
    friend bool operator==(const SimetricnaMatrica<Tp>&a,const SimetricnaMatrica<Tp>&b);
    
    template <typename Tp>
    friend  bool operator!=(const SimetricnaMatrica<Tp>&a,const SimetricnaMatrica<Tp>&b);
    
    template <typename Tp>
    friend std::ostream& operator<<(std::ostream& izlaz, const SimetricnaMatrica<Tp>& sm);
    
    template <typename Tp>
    friend std::istream& operator>>(std::istream& ulaz,SimetricnaMatrica<Tp>& sm);
};

template <class T>
SimetricnaMatrica<T>::SimetricnaMatrica(SimetricnaMatrica<T>& sm) {
   
    int count(1);

    for(int i=0;i<sm.elementi.size();++i) {
        if(sm.elementi.at(i).size() != count)
            throw std::logic_error("Nekorektna forma simetricne matrice");
        else
            count++;
    }
    
    elementi.clear();
    
    std::vector<T> tempRed;
    for(int i=0;i<sm.elementi.size();++i) {
        for(int j=0;j<sm.elementi.at(i).size();++j) {
            tempRed.push_back(sm.elementi.at(i).at(j));
        }
        elementi.push_back(tempRed);
        tempRed.clear();
    }
  
}

template <class T>
SimetricnaMatrica<T>::SimetricnaMatrica(SimetricnaMatrica<T>&& sm) {
   
    int count(1);

    for(int i=0;i<sm.elementi.size();++i) {
        if(sm.elementi.at(i).size() != count)
            throw std::logic_error("Nekorektna forma simetricne matrice");
        else
            count++;
    }
    
    elementi.clear();
    
    std::vector<T> tempRed;
    for(int i=0;i<sm.elementi.size();++i) {
        for(int j=0;j<sm.elementi.at(i).size();++j) {
            tempRed.push_back(sm.elementi.at(i).at(j));
        }
        elementi.push_back(tempRed);
        tempRed.clear();
    }
  
}

template <class T> 
SimetricnaMatrica<T>::SimetricnaMatrica(std::vector<std::vector<T>> vv){
    int count(1);
    
    for(auto red:vv) {
        if(red.size() != count)
            throw std::logic_error("Nekorektna forma simetricne matrice");
        else
            count++;
    }   
  
}

template <class T> 
SimetricnaMatrica<T>::SimetricnaMatrica(std::initializer_list<std::initializer_list<T>> vv) {
    int count(1);

    for(auto red:vv) {
        if(red.size() != count)
            throw std::logic_error("Nekorektna forma simetricne matrice");
        else
            count++;
    }
    
    std::vector<T> tempRed;
    for(auto red:vv) {
        for(auto broj:red) {
            tempRed.push_back(broj);
        }
        elementi.push_back(tempRed);
        tempRed.clear();
    }
  
}

template <class T> 
SimetricnaMatrica<T>::SimetricnaMatrica(int n) {
    if(n < 0)
        throw std::domain_error("Neispravna dimenzija");
    
    int limit(1);
    std::vector<T> tempRed;
    for(int i=0;i<n;++i) {
        for(int j=0;j<limit;++j) {
            tempRed.push_back(0);
        }
        elementi.push_back(tempRed);
        limit++;
    }
}

template <class T> 
bool SimetricnaMatrica<T>::operator!() {
    for(auto red:elementi) {
        for(auto broj:elementi) {
            if(broj != 0)
                return false;
        }
    }
    
    return true;
}

template <class Tp1, class Tp2> 
auto operator+(const SimetricnaMatrica<Tp1>& a, const SimetricnaMatrica<Tp2>& b) -> decltype(a.at(0).at(0) + b.at(0).at(0)) {
    if(a.elementi.size() != b.elementi.size())
        throw std::domain_error("Matrice nisu saglasne za trazenu operaciju");
    
    SimetricnaMatrica<Tr> c(a.elementi.size());
    
    for(int i=0;i<a.elementi.size();++i) {
        for(int j=0;j<a.elementi.at(i).size();++j) {
            c.elementi.at(i).at(j) = a.elementi.at(i).at(j) + b.elementi.at(i).at(j);
        }
    }
    
    return c;
}

template <class Tp1, class Tp2> 
auto operator-(const SimetricnaMatrica<Tp1>& a, const SimetricnaMatrica<Tp2>& b) -> decltype(a.at(0).at(0) + b.at(0).at(0)) {
    if(a.elementi.size() != b.elementi.size())
        throw std::domain_error("Matrice nisu saglasne za trazenu operaciju");
    
    SimetricnaMatrica<Tr> c(a.elementi.size());
    
    for(int i=0;i<a.elementi.size();++i) {
        for(int j=0;j<a.elementi.at(i).size();++j) {
            c.elementi.at(i).at(j) = a.elementi.at(i).at(j) - b.elementi.at(i).at(j);
        }
    }
    
    return c;
}

template <class Tr, class Tp1, class Tp2> 
auto operator*(const SimetricnaMatrica<Tp1>& a, const SimetricnaMatrica<Tp2>& b) -> decltype(a.at(0).at(0) + b.at(0).at(0)) {
    if(a.elementi.size() != b.elementi.size( ))
        throw std::domain_error("Matrice nisu saglasne za trazenu operaciju");
    
    SimetricnaMatrica<Tr> c(a.elementi.size());
    
    int clan;
    for(int i=0;i<a.elementi.size();++i) {
        for(int j=0;j<a.elementi.at(i).size();++j) {
            for(int k=0;k<a.elementi.at(i).size();++k) {
                clan += (a.elementi.at(i).at(k) * b.elementi.at(k).at(j));
            }
            c.elementi.at(i).at(j) = clan;
            clan=0;
        }
    }
    
    return c;
}

template <class T>
bool operator==(const SimetricnaMatrica<T>&a,const SimetricnaMatrica<T>&b) {
    if(a.elementi.size() != b.elementi.size())
        return false;
        
    for(int i=0;i<a.elementi.size();i++) {
        for(int j=0;j<a.elementi.at(i).size();j++) {
            if(a.elementi.at(i).at(j) != b.elementi.at(i).at(j))
                return false;
        }
    }
    
    return true;
}

template <class T>
bool operator!=(const SimetricnaMatrica<T>&a,const SimetricnaMatrica<T>&b)  {
    return !(a==b);
}

template <class T>
std::ostream& operator<<(std::ostream& izlaz, const SimetricnaMatrica<T>& sm) {
    int inputWidth = izlaz.width();
    
    for(int i=0;i<sm.elementi.size();++i) {
        for(int j=0;j<sm.elementi.size();++j) {
            if(j < sm.elementi.at(i).size())
                izlaz << std::setw(inputWidth) << sm.elementi.at(i).at(j);
            else 
                izlaz << std::setw(inputWidth) << sm.elementi.at(j).at(i);
        }
        izlaz << std::endl;
    }
    
    return izlaz;
}

template <class T>
std::istream& operator>>(std::istream& ulaz,SimetricnaMatrica<T>& sm) {
    
    int limit(1); 
    for(int i=0;i<sm.elementi.size();++i) {
        for(int j=0;j<limit;++j) {
            ulaz >> sm.elementi.at(i).at(j);
        }
        limit++;
    }
    
    return ulaz;
}


int main () {
    {//op+ i op-, trivijalan
    SimetricnaMatrica<int> m1 ({{1}, {3, 4}});
    SimetricnaMatrica<int> m2 ({{8}, {6, 5}});
    std::cout << std::setw(3) << m1 + m2;
    std::cout << std::setw(3) << m1 - m2;
}
    // SimetricnaMatrica<int> sm({{1},{1,2},{1,2,3}});
    // SimetricnaMatrica<int> sm2({{20},{20,30},{30,40,50}});
    
    
    // SimetricnaMatrica<int> zbir(3);
    // zbir = sm + sm2;
    
    // std::cout << std::setw(5) << zbir;
    
    // SimetricnaMatrica<int> razlika(3);
    // razlika = sm - sm2;
    
    // std::cout << std::setw(5) << razlika;
    // SimetricnaMatrica<int> razlike = sm - sm2;
    
    // std::cout << std::setw(15) << sm + sm2;
    
    // std::initializer_list<std::initializer_list<int>> l = {{1}, {0, 7}, {0, 0, -1}, {0, 0, 0, 17}};
    // std::vector<std::vector<int>> v = {{17}, {0, -3}, {0, 0, -7}, {0, 0, 0, 12}};
    // SimetricnaMatrica<int> A {l};
    // SimetricnaMatrica<int> B (v);
    // auto AB = A * B, BA = B * A;
    // std::cout << "AB:" << std::endl << std::setw(10) << AB << std::endl
    //           << std::endl << "BA:" << std::endl << std::left << std::setw (12) << BA;
    
	return 0;
}
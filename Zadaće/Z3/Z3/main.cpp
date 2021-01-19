//TP 2018/2019: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>

template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!
    char ime_matrice;
};
 
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}
    
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,char ime = 0) {
    
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova; mat.br_kolona = br_kolona;
    mat.ime_matrice = ime;
    mat.elementi = new TipElemenata*[br_redova]{};

    try {
        for(int i = 0; i < br_redova; i++)
        mat.elementi[i] = new TipElemenata[br_kolona];
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
        
    return mat;
}
 
template <typename TipElemenata>
void UnesiMatricu(Matrica<TipElemenata> &mat) {
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
        std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
        std::cin >> mat.elementi[i][j];
    }
}
 
template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> mat,int sirina_ispisa,int preciznost=6,bool trebaBrisati = false) {

    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];
        std::cout << std::endl;
    }
    
    if(trebaBrisati) UnistiMatricu<TipElemenata>(mat);
    
}
 
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije");
     
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
     
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
        
    return m3;
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> m1, const Matrica<TipElemenata> m2) {
        
    if((m1.br_redova == 0 || m2.br_kolona == 0) || m1.br_kolona != m2.br_redova)
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
        
    TipElemenata clan = 0;
    
    for(int i=0;i<m1.br_redova;i++) {
        for(int j=0;j<m2.br_kolona;j++) {
            for(int k=0;k<m2.br_kolona;++k) {
                clan += (m1.elementi[i][k] * m2.elementi[k][j]);
            }
            m3.elementi[i][j] = clan;
            clan=0;
        }
    }
        
    return m3;
}

template <typename TipElemenata>
void PomnoziSaSkalarom(const Matrica<TipElemenata> &m1,TipElemenata skalar) {
    
    for(int i=0;i<m1.br_redova;i++) {
        for(int j=0;j<m1.br_kolona;j++) {
            m1.elementi[i][j] = m1.elementi[i][j] * skalar;
        }
    }

}

template <typename TipElemenata>
void Kopiraj(const Matrica<TipElemenata> M,Matrica<TipElemenata> &O) {
    
    for(int i=0;i<M.br_redova;i++) {
        for(int j=0;j<M.br_kolona;j++) {
            O.elementi[i][j] = M.elementi[i][j];
        }
    }
    
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> &A,int n) {
    if(A.br_redova != A.br_kolona || A.br_redova != A.br_kolona) 
        throw std::domain_error("Matrica nije kvadratna");
    if(n < 0)
        throw std::domain_error("Pogresan paramtear n");
    
    Matrica<TipElemenata> rezultat = StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona);
    Kopiraj(A,rezultat);
    Matrica<TipElemenata> m3 = StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona);
    
    Matrica<TipElemenata> rez;   
    
    for(int i=2;i<=n;i++) {
        Kopiraj(A,m3);
        for(int j=1;j<i;j++) {    
            Kopiraj(rez = ProduktMatrica(A,m3),m3);
            UnistiMatricu(rez);
        }
        PomnoziSaSkalarom(m3,(double) 1/i);
        Kopiraj(rez = ZbirMatrica(m3,rezultat),rezultat);
        UnistiMatricu(rez);
    }
    
    UnistiMatricu(rez);
    UnistiMatricu(m3); 
  
    return rezultat;
}


int main () {
    
    Matrica<double> m(StvoriMatricu<double>(2,2,'m'));
    Matrica<double> n(StvoriMatricu<double>(2,2,'n'));
    Matrica<double> z;
    
    std::cout << "Unesite m matricu: " << std::endl;
    UnesiMatricu(m);
    
    std::cout << "Unesite n matricu: " << std::endl;
    UnesiMatricu(n);
    
    std::cout << "Matrica m1 prije modifikacije: " << std::endl;
    IspisiMatricu(m,6);
    
    std::cout << "Matrica m2 prije modifikacije: " << std::endl;
    IspisiMatricu(n,6);
    
    std::cout << "Produkt matrica je: " << std::endl;
    try {
        IspisiMatricu(z = ProduktMatrica(m,n),6,9);
    } catch(std::domain_error err) {
        std::cout << err.what();
    }
    
    std::cout << "Matricni harmonijski polinom matrice m iznosi: " << std::endl;
    try {
        IspisiMatricu(z = MatricniHarmonijskiPolinom(m,6),9,6,true);
    } catch(std::domain_error err) {
        std::cout << err.what();
    }
    
    UnistiMatricu(m);
    UnistiMatricu(n);
    UnistiMatricu(z);
    
	return 0;
}
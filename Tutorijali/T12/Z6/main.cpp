/* 
    TP 16/17 (Tutorijal 12, Zadatak 6)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

#include <new>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <stdexcept>

template <typename TipEl>
class Matrica {
	int br_redova, br_kolona;
	char ime_matrice;
	TipEl **elementi;
	static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	void KopirajElemente(TipEl **elementi);
	
	
public:
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m); 
	Matrica(Matrica &&m);
	Matrica &operator =(const Matrica &m);
	Matrica &operator =(Matrica &&m);
	~Matrica() { DealocirajMemoriju(elementi, br_redova); }
	template <typename Tip2>
	friend std::istream& operator >>(std::istream& ulaz,Matrica<Tip2>& m1);
	template <typename Tip2>
	friend std::ostream& operator <<(std::ostream& izlaz, Matrica<Tip2> m1);
	template <typename Tip2>
	friend Matrica<Tip2> operator +(const Matrica<Tip2> &m1,const Matrica<Tip2> &m2);
	template <typename Tip2>
	friend Matrica<Tip2> operator -(const Matrica<Tip2> &m1,const Matrica<Tip2> &m2);
	template <typename Tip2>
	friend Matrica<Tip2> operator *(const Matrica<Tip2> &m1,const Matrica<Tip2> &m2);
	template <typename Tip2>
	friend Matrica<Tip2> operator *(const Matrica<Tip2> &m1,const Matrica<Tip2> &m2);
	template <typename Tip2>
	friend Matrica<Tip2> operator *(const Matrica<Tip2> &m1, int skalar);
	template <typename Tip2>
	friend inline Matrica<Tip2> operator*(int skalar,const Matrica<Tip2> &m1);
	Matrica& operator +=(const Matrica &m1);
	Matrica& operator -=(const Matrica &m1);
	Matrica& operator *=(const Matrica m1);
	Matrica& operator *=(int skalar);
	TipEl* operator[](int i) const;
	TipEl& operator()(int i,int j) const;
	operator std::string() const;
};
 
template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
 
template <typename TipEl>
TipEl ** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
	TipEl **elementi = new TipEl*[br_redova]{};
	
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
	}
	catch(...) {
		DealocirajMemoriju(elementi, br_redova); throw;
	}
	
	return elementi;
}
 
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
	for(int i = 0; i < br_redova; i++) delete[] elementi[i];
	delete[] elementi;
}
 
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			Matrica::elementi[i][j] = elementi[i][j];
}
 
template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova), br_kolona(m.br_kolona), ime_matrice(m.ime_matrice), elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {
	KopirajElemente(m.elementi);
}
 
template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), ime_matrice(m.ime_matrice), elementi(m.elementi)  {
	m.br_redova = 0; m.elementi = nullptr;
}
 
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m) {
	
	if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
		TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
		DealocirajMemoriju(elementi, br_redova);
		elementi = novi_prostor;	
	}
	
	else if(br_redova > m.br_redova)
	
	for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
	
	br_redova = m.br_redova; br_kolona = m.br_kolona;
	ime_matrice = m.ime_matrice; KopirajElemente(m.elementi);
	
	return *this;
 }
 
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m) {
	std::swap(br_redova, m.br_redova); std::swap(br_kolona, m.br_kolona);
	std::swap(ime_matrice, m.ime_matrice); std::swap(elementi, m.elementi);
	return *this;
 }
 
template <typename TipEl>
std::istream& operator >>(std::istream& ulaz,Matrica<TipEl>& m1) {
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++) {
			std::cout << m1.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
		
	 ulaz >> m1.elementi[i][j];
	}
	
	return ulaz;
}

template <typename TipEl>
std::ostream& operator <<(std::ostream& izlaz, Matrica<TipEl> m1) {
	int sirina = izlaz.width();
	
	for(int i = 0; i < m1.br_redova; i++) {
		for(int j = 0; j < m1.br_kolona; j++)
			izlaz << std::setw(sirina) << m1.elementi[i][j];
			
		izlaz << std::endl;
	}
	
	return izlaz;
}

template <typename TipEl>
Matrica<TipEl> operator+(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	
	Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);

	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
			
	return m3;
}

template <typename TipEl>
Matrica<TipEl> operator-(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
		
	Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);

	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
			
	return m3;
}

template <typename TipEl>
Matrica<TipEl> operator*(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
	if((m1.br_redova == 0 || m2.br_kolona == 0) || m1.br_kolona != m2.br_redova)
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    
    Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
        
    TipEl clan = 0;
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

template <typename TipEl>
Matrica<TipEl> operator*(const Matrica<TipEl> &m1, int skalar) {
    Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
      
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] * skalar;
			
	return m3;
}

template <typename TipEl>
inline Matrica<TipEl> operator*(int skalar, const Matrica<TipEl> &m1) {
	return m1 * skalar;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator +=(const Matrica<TipEl> &m2) {
	if(this -> br_redova != m2.br_redova || this -> br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");

	for(int i = 0; i < this -> br_redova; i++)
		for(int j = 0; j < this -> br_kolona; j++)
			this -> elementi[i][j] += m2.elementi[i][j];
			
	return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator -=(const Matrica<TipEl> &m2) {
	if(this -> br_redova != m2.br_redova || this -> br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");

	for(int i = 0; i < this -> br_redova; i++)
		for(int j = 0; j < this -> br_kolona; j++)
			this -> elementi[i][j] -= m2.elementi[i][j];
			
	return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator *=(const Matrica<TipEl> m2) {
	if((br_redova == 0 || m2.br_kolona == 0) || br_kolona != m2.br_redova)
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    
    TipEl clan = 0;
    for(int i=0;i<br_redova;i++) {
        for(int j=0;j<m2.br_kolona;j++) {
            for(int k=0;k<m2.br_kolona;++k) {
                clan += (elementi[i][k] * m2.elementi[k][j]);
            }
            elementi[i][j] = clan;
            clan=0;
        }
    }
        
    return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator *=(int skalar) {
	
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			elementi[i][j] *= skalar;
			
	return *this;
}

template <typename TipEl>
TipEl* Matrica<TipEl>::operator[](int i) const {
	return elementi[i];
}

template <typename TipEl>
TipEl& Matrica<TipEl>::operator()(int i,int j) const {
	if((i == 0 || i > br_redova) || (j == 0 || j > br_kolona))
		throw std::range_error("Neispravan indeks");
		
	return elementi[i-1][j-1];
}

template <typename TipEl>
Matrica<TipEl>::operator std::string() const {
		std::stringstream ss1;
		ss1 << "{";
		int j=0;
		for(int i=0;i<br_redova;++i) {
			ss1 << "{";
			for(j=0;j<br_kolona-1;++j) {
				ss1 << elementi[i][j] << ",";
			}
			ss1 << elementi[i][j] << "}";
			if(i != br_redova - 1)
				ss1 << ",";
		}
		
		ss1 << "}";
		
		return ss1.str();
	}

int main() {
	
	//AT8 testiranje operatora *=, [] i unosa
	  int m,n;
	  std::cout << "Unesi broj redova i kolona za matrice:\n";
	  std::cin >> m >> n;
	  try {
	    Matrica<double> a(m, n, 'A'), b(m, n, 'B');
	    std::cout << "Unesi matricu A:\n";
	    std::cin >> a;
	    std::cout << "Unesi matricu B:\n";
	    std::cin >> b;
	a*=b;
	b*=10;
	for(int i = 0; i < 2; i++){
	      for(int j = 0; j < 2; j++)
	      std::cout << a[i][j] << " ";
	      std::cout << std::endl;
	}
	std::cout << "---------------" << std::endl;
	for(int i = 0; i < 2; i++){
	      for(int j = 0; j < 2; j++)
	      std::cout << b[i][j] << " ";
	      std::cout << std::endl;
	}
	}
	catch(std::bad_alloc) {
	    std::cout << "Nema dovoljno memorije!\n";
	  }
	    catch(std::domain_error e) {
	    std::cout << e.what();
	  }
	    catch(std::range_error e) {
	    std::cout << e.what();
	  }
	  
	return 0;
}

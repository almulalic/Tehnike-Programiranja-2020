/* 
    TP 16/17 (Tutorijal 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <memory>

class Lik {
protected:
	std::string naziv;
public:
	virtual ~Lik() {}
	virtual void IspisiSpecificnosti() const = 0;
	virtual double DajObim() const = 0;
	virtual double DajPovrsinu() const = 0;
	virtual void Ispisi() const = 0;
};

class Krug : public Lik {
	double r;
	static constexpr double PI = atan(1)*4;
public:
	explicit Krug(double r): r(r) { if(r <= 0) throw std::domain_error("Neispravni parametri"); naziv = "Krug"; };
	
	void IspisiSpecificnosti() const {
		std::cout << "Krug poluprecnika " << r;
	}
	
	double DajObim() const {
		return 2*r*PI;
	}
	
	double DajPovrsinu() const {
		return r*r*PI;
	}
	
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout << std::endl;
		std::cout << "Obim: " << DajObim() << " Povrsina: " << DajPovrsinu() << std::endl;
	}
	
};

class Pravougaonik : public Lik {
	double a,b;
	
public:
	
	explicit Pravougaonik(double a, double b) : a(a),b(b) { if(a <= 0 || b <= 0) throw std::domain_error("Neispravni parametri"); naziv = "Pravougaonik"; };
	
	void IspisiSpecificnosti() const {
		std::cout << naziv << " sa stranicama duzine " << a << " i " << b;
	}
	
	double DajObim() const {
		return 2 * (a+b);
	}
	
	double DajPovrsinu() const {
		return a*b;
	}
	
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout << std::endl;
		std::cout << "Obim: " << DajObim() << " Povrsina: " << DajPovrsinu() << std::endl;
	}
};

class Trougao : public Lik {
	double a,b,c;
public:
	explicit Trougao(double a, double b, double c) : a(a), b(b), c(c) { if(a <= 0 || b <= 0 || c <= 0  ||  a + b <= c || a + c <= b || b + c <= a) throw std::domain_error("Neispravni parametri"); naziv = "Trougao"; }
	
	void IspisiSpecificnosti() const {
		std::cout << naziv << " sa stranicama duzine " << a << ", " << b << " i " << c;
	}
	
	double DajObim() const {
		return a + b + c;
	}
	
	double DajPovrsinu() const {
		double s((a+b+c) / 2);
		return sqrt(s * (s-a) * (s-b) * (s-c));
	}
	
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout << std::endl;
		std::cout << "Obim: " << DajObim() << " Povrsina: " << DajPovrsinu()  << std::endl;
	}
};

int main ()
{
	
	int brojLikova;
	std::cout << "Koliko zelite likova: ";
	std::cin >> brojLikova;
	
	
	for(int i=0;i<brojLikova;i++) {
		std::cout << "Lik " << i+1 << ": ";
			
	}
	
	return 0;
}
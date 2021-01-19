/* 
    TP 16/17 (Tutorijal 9, Zadatak 1)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d {
 double x, y, z;
 
public:
	void Postavi(double x, double y, double z) {
		Vektor3d::x = x; Vektor3d::y = y; Vektor3d::z = z;
	}
	
	void Ocitaj(double &x, double &y, double &z) const {
		x = Vektor3d::x; y = Vektor3d::y; z = Vektor3d::z;
	 }
	 
	void Ispisi() const {
		std::cout << "{" << x << "," << y << "," << z << "}";
	}
	
	//Getteri
	double DajX() const { return x; }
	double DajY() const { return y; }
	double DajZ() const { return z; }
	double DajDuzinu() const { return std::sqrt(x * x + y * y + z * z); }
	
	//Setteri
	void PostaviX(double x) { Vektor3d::x = x; }
	void PostaviY(double y) { Vektor3d::y = y; }
	void PostaviZ(double z) { Vektor3d::z = z; }
	
	Vektor3d &PomnoziSaSkalarom(double s) { x *= s; y *= s; z *= s; return *this;}
	Vektor3d &SaberiSa(const Vektor3d &v) { x += v.x; y += v.y; z += v.z; return *this;}
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
 Vektor3d v3;
 v3.Postavi(v1.DajX() + v2.DajX(), v1.DajY() + v2.DajY(),
 v1.DajZ() + v2.DajZ());
 return v3;
}


int main ()
{
	
	double x,y,z;
	std::cout << "Unesite x,y,z koordinate vektora: ";
	std::cin >> x >> y >> z;
	
	Vektor3d novi;
	novi.Postavi(x,y,z);
	
	double x1,y1,z1;
	novi.Ocitaj(x1,y1,z1);
	
	std::cout << "Unjeli ste vektor sa koordiantama: ";
	novi.Ispisi();
	
	double x2,y2,z2;
	std::cout << "X,Y,Z koordinate su: " << x1 << " " << y1 << " " << z1 << std::endl;
	std::cout << "Duzina je " << novi.DajDuzinu();
	
	std::cout << "Unesite novu koorinatu x";
	std::cin >> x2;
	novi.PostaviX(x2);
	
	std::cout << "Unesite novu koorinatu y";
	std::cin >> y2;
	novi.PostaviY(y2);

	std::cout << "Unesite novu koorinatu z";
	std::cin >> z2;
	novi.PostaviX(z2);
	
	std::cout << "Nakon izmjena koordinate su: " << std::endl;
	std::cout << "x= " << novi.DajX() << std::endl;
	std::cout << "y= " << novi.DajY() << std::endl;
	std::cout << "z= " << novi.DajZ() << std::endl;
	
	std::cout << "Novi vektor pomnozen sa skalarom 2 iznosi "; 
	novi.PomnoziSaSkalarom(2);
	novi.Ispisi();
	
	std::cout << "Zbir prvog i drugog vektora iznosi ";
	Vektor3d stari;
	stari.Postavi(x1,y1,z1);
	
	// Vektor3d zbir = ZbirVektora(novi,stari);
	// std::cout << zbir.Ispisi();
	
	return 0;
}
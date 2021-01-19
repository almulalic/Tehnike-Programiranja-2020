/* 
    TP 16/17 (Tutorijal 9, Zadatak 2)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d {

private:
	double koordinate[3];
 
public:
	void Postavi(double x, double y, double z) {
		Vektor3d::koordinate[0] = x; Vektor3d::koordinate[1] = y; Vektor3d::koordinate[2] = z;
	}
	
	void Ocitaj(double &x, double &y, double &z) const {
		x = Vektor3d::koordinate[0]; y = Vektor3d::koordinate[1]; z = Vektor3d::koordinate[2];
	 }
	 
	void Ispisi() const {
		std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}";
	}
	
	//Getteri
	double DajX() const { return koordinate[0]; }
	double DajY() const { return koordinate[1]; }
	double DajZ() const { return koordinate[2]; }
	double DajDuzinu() const { return std::sqrt(koordinate[0] * koordinate[0] + koordinate[1] * koordinate[1] + koordinate[2] * koordinate[2]); }
	
	//Setteri
	void PostaviX(double x) { Vektor3d::koordinate[0] = x; }
	void PostaviY(double y) { Vektor3d::koordinate[1] = y; }
	void PostaviZ(double z) { Vektor3d::koordinate[2] = z; }
	
	Vektor3d &PomnoziSaSkalarom(double s) { koordinate[0] *= s; koordinate[1] *= s; koordinate[2 ]*= s; return *this;}
	Vektor3d &SaberiSa(const Vektor3d &v) { koordinate[0] += v.DajX(); koordinate[1] += v.DajY(); koordinate[2] += v.DajZ(); return *this;}
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
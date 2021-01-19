/* 
    TP 16/17 (Tutorijal 10, Zadatak 3)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>

class Vektor3d {

	double koordinate[3];
	static int brojIspisa;

 
public:
	
	Vektor3d(double x=0, double y=0, double z=0) {
		koordinate[0] = x; koordinate[1] = y; koordinate[2] = z;
	}
	
	void Postavi(double x, double y, double z) {
		Vektor3d::koordinate[0] = x; Vektor3d::koordinate[1] = y; Vektor3d::koordinate[2] = z;
	}
	
	void Ocitaj(double &x, double &y, double &z) const {
		x = Vektor3d::koordinate[0]; y = Vektor3d::koordinate[1]; z = Vektor3d::koordinate[2];
	 }
	 
	void Ispisi() const {
		std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}";
		Vektor3d::brojIspisa++;
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
	
	int DajBrojIspisa() const { return Vektor3d::brojIspisa; }
};

int Vektor3d::brojIspisa = 0;


int main ()
{
	return 0;
}
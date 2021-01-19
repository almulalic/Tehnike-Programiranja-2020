/* 
    TP 16/17 (Tutorijal 9, Zadatak 3)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>



class Vektor3d {

	double koordinate[3];
	private:
	static int brojIspisa;

 
public:
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

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
	Vektor3d v3;
	
	v3.Postavi(v1.DajX() + v2.DajX(), v1.DajY() + v2.DajY(),
	 v1.DajZ() + v2.DajZ());
	 
 return v3;
}

int Vektor3d::brojIspisa = 0;

int main ()
{
	Vektor3d v1, v2;
	v1.Postavi(3, 4, 2); v2.Postavi(2, 0, 5);
	v1.Ispisi(); v1.Ispisi(); v1.Ispisi(); v2.Ispisi(); v2.Ispisi();
	
	std::cout << std::endl;
	std::cout << "Objekat v1 je ispisan " << v1.DajBrojIspisa() << "puta , a objekat v2 " << v2.DajBrojIspisa() << " puta" << std::endl;
 
	return 0;
}
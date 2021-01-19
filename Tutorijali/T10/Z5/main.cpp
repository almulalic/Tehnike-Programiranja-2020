/* 
    TP 16/17 (Tutorijal 10, Zadatak 4)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cmath>


class Ugao {
	
	int stepeni,minute,sekunde;
	
    static constexpr double PI = 4 * atan(1);
    static constexpr double STEP_U_RAD_KONST = 2 * PI / 360;
    static constexpr double RAD_U_STEP_KONST = 1 / STEP_U_RAD_KONST;
    static double StepenURadijan(int stepeni, int minute, int sekunde) {
        return stepeni * STEP_U_RAD_KONST + minute * STEP_U_RAD_KONST / 60 + sekunde * STEP_U_RAD_KONST / 3600;
    }
    static double DecimalniDio(double a) {
        return a - int(a);
    }

	
	public:
		Ugao(double radijani = 0) { 
			if(radijani < 0) { radijani -= int(radijani/(2*PI)) * 2 * PI; radijani = 2 * PI + radijani; }
			else if(radijani != 2 * PI) radijani -= int(radijani / (2*PI)) * 2* PI; 
        	*this = Ugao(radijani * RAD_U_STEP_KONST, radijani * RAD_U_STEP_KONST / 60, int(radijani * RAD_U_STEP_KONST / 3600) % 60);
		}
		Ugao(int stepeni, int minute, int sekunde) {
			stepeni %= 360;
			if(stepeni < 0) stepeni = 360+stepeni; 
			this->stepeni = stepeni; 
			this-> minute = minute; 
			this -> sekunde = sekunde; 
		};
		void Postavi(double radijani) { *this = Ugao(radijani); }
		void Postavi(int stepeni, int minute, int sekunde) { *this = Ugao(stepeni,minute,sekunde); }
		double DajRadijane() const { return StepenURadijan(stepeni, minute, sekunde); };
		void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {stepeni=DajStepene(); minute = DajMinute(); sekunde = DajSekunde(); }
		int DajStepene() const { return stepeni;}
		int DajMinute()  const { return minute; }; 
    	int DajSekunde()  const { return sekunde; }; 
		void Ispisi() const { std::cout << std::fixed << std::setprecision(5) << StepenURadijan(stepeni,minute,sekunde); }
		void IspisiKlasicno() const { std::cout << (this-> DajStepene() == 360 ? 0 : this-> DajStepene()) << "deg " << this->DajMinute() << "min " << this->DajSekunde() << "sec"; }
		Ugao &SaberiSa(const Ugao &u) { return *this = Ugao(StepenURadijan(stepeni, minute, sekunde) + u.DajRadijane()); };
		Ugao &PomnoziSa(double x) { return *this = Ugao(StepenURadijan(stepeni, minute, sekunde) * x); }; 
		friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
		friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova( const Ugao  & u1,  const Ugao  & u2) {
    return Ugao(u1.DajRadijane() +  u2.DajRadijane());
}

Ugao ProduktUglaSaBrojem( const Ugao  & u,  double x) {
    return Ugao(u.DajRadijane() * x);
}

int main ()
{
	// Main ostaje isti zbog testiranja sa proslim zadatkom
	Ugao ugao(100);
	ugao.Ispisi();
	std::cout << std::endl;
	Ugao ugao2(430,2,8);
	ugao2.IspisiKlasicno();
	std::cout << std::endl;
	ugao.Postavi(ugao2.DajRadijane());
	ugao.Ispisi();
	std::cout << std::endl;
	ugao2.Postavi(ugao.DajStepene(),ugao.DajMinute(),ugao.DajSekunde());
	ugao2.IspisiKlasicno(); 
	std::cout << std::endl;
	ugao.SaberiSa(ugao2);
	ugao.Ispisi();
	std::cout << std::endl;
	ugao2.PomnoziSa(5);
	ugao2.Ispisi();
	std::cout << std::endl;
	ZbirUglova(8,1).Ispisi();
	std::cout << std::endl;
	ProduktUglaSaBrojem(4,6).Ispisi();
	
	return 0;
}
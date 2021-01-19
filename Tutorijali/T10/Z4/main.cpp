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
	
	double radijani;
	
	void Pretvori (double &n){
	 double stepen(n*180/PI);
		 if(stepen>360){
			while(stepen>360) stepen-=360;
		 }
		 if(stepen<0){
			 auto temp = stepen*-1;
			 while(temp>360) temp-=360;
			 stepen = temp-360;
		 }
		 if(stepen<0) stepen*=-1;
		 n=stepen*PI/180;
	 } // osigurat da je uvijek od 0 do 360 ugao
	 
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
		Ugao(double radijani = 0) { Pretvori(radijani); Ugao::radijani = radijani; }
		Ugao(int stepeni, int minute, int sekunde) { *this = (StepenURadijan(stepeni, minute, sekunde)); };
		void Postavi(double radijani) { Pretvori(radijani); *this = radijani; }
		void Postavi(int stepeni, int minute, int sekunde) { *this = Ugao(StepenURadijan(stepeni, minute, sekunde)); }
		double DajRadijane() const { return radijani; }
		void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde) {stepeni=DajStepene(); minute = DajMinute(); sekunde = DajSekunde(); }
		int DajStepene() const { return int((radijani*180/PI));}
		int DajMinute()  const { return DecimalniDio(radijani * RAD_U_STEP_KONST) * 60; }; 
    	int DajSekunde()  const { return int(DecimalniDio(radijani * RAD_U_STEP_KONST) * 3600) % 60 ; }; 
		void Ispisi() const { std::cout << std::fixed << std::setprecision(5) << radijani; }
		void IspisiKlasicno() const { std::cout << (this-> DajStepene() == 360 ? 0 : this-> DajStepene()) << "deg " << this->DajMinute() << "min " << this->DajSekunde() << "sec"; }
		Ugao &SaberiSa(const Ugao &u) { return *this = Ugao(radijani + u.DajRadijane()); }; 
		Ugao &PomnoziSa(double x) { return *this = Ugao(radijani * x); }; 
		friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
		friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova( const Ugao  & u1,  const Ugao  & u2) {
    return Ugao(u1.radijani +  u2.radijani);
}

Ugao ProduktUglaSaBrojem( const Ugao  & u,  double x) {
    return Ugao(u.radijani * x);
}

int main ()
{

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
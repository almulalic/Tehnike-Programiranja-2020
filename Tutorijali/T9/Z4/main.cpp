/* 
    TP 16/17 (Tutorijal 9, Zadatak 4)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>

class Sat {
	private:
		int sati,minute,sekunde;
	public:
		static bool DaLiJeIspravno(int sati,int minute,int sekunde) { 
			if(sati < 0 || sati > 23)
				return false;
			else if(minute < 0 || minute > 59)
				return false;
			else if(sekunde < 0 || sekunde > 59)
				return false;
			
			return true;			
		}
		
		void Postavi(int sati,int minute,int sekunde) {
			if(DaLiJeIspravno(sati,minute,sekunde)) {
				Sat::sati = sati; Sat::minute = minute; Sat::sekunde = sekunde;
			} else {
				throw std::domain_error("Neispravno vrijeme");
			}
		}
		
		void PostaviNormalizirano(int sati,int minute,int sekunde) {
			if(DaLiJeIspravno(sati,minute,sekunde)) {
				Postavi(sati,minute,sekunde);
			} else {
				Sat::sekunde = sekunde % 60;
				Sat::minute = (minute % 60) + (sekunde / 60);
				Sat::sati = (sati % 24) + (minute / 60);
			}

		}    
		
		Sat &Sljedeci() { 
			Sat::sekunde += 1;
			if(sekunde == 60) {
				Sat::sekunde = 0;
				Sat::minute += 1;
				if(Sat::minute == 60) {
					Sat::minute = 0;
					Sat::sati +=1;
					if(Sat::sati == 24) {
						Sat::sati = 0;
					}
				}
			}
			
			return *this;
		}
		
		Sat &Prethodni() { 
			Sat::sekunde -= 1;
			if(sekunde == -1) {
				Sat::sekunde = 59;
				Sat::minute -= 1;
				if(Sat::minute == -1) {
					Sat::minute = 59;
					Sat::sati -=1;
					if(Sat::sati  == -1) {
						Sat::sati = 23;
					}
				}
			}
			return *this;
		}
		
		Sat &PomjeriZa(int sekunde) {
			if(sekunde < 0) {
				for(int i=0;i<abs(sekunde);i++)
					this -> Prethodni();
			} else {
				for(int i=0;i<sekunde;i++)
					this -> Sljedeci();
			}
			
			return *this;
		}
		
		void Ispisi() {
			 if(sati >= 0 && sati <= 9)
		        std::cout << "0" << sati;
		    else
		        std::cout << sati;
		    
		    std::cout << ":";
		    
		     if(minute >= 0 && minute <= 9)
		        std::cout << "0" << minute;
		    else
		        std::cout << minute;
		        
		    std::cout << ":";
		    
		     if(sekunde >= 0 && sekunde <= 9)
		        std::cout << "0" << sekunde;
		    else
		        std::cout << sekunde; 
		}
		
		int DajSate() {
			return Sat::sati;
		}
		
		int DajMinute() {
			return Sat::minute;
		}
		
		int DajSekunde() {
			return Sat::sekunde;
		}
};

int main ()
{
	
	int sati1 = 59,minute1 = 5, sekunde1 = 1;
	std::cout << "Vrijeme 59 sati 5 minuta i 1 sekund " << (Sat::DaLiJeIspravno(sati1,minute1,sekunde1) ? "je ispravno." : "nije ispravno.") << std::endl;
	
	Sat novi;
	novi.PostaviNormalizirano(sati1,minute1,sekunde1);
	
	std::cout << "Normalizovano vrijeme 59 sati 5 minuta i 1 sekund glasi: ";
	novi.Ispisi();
	std::cout << std::endl;
	
	int sat2=1,minute2= 2,sekunde2 = 3;
	Sat novi2;
	novi2.Postavi(sat2,minute2,sekunde2);
	std::cout << "Za sate " << novi2.DajSate() << "  minute " << novi2.DajMinute() << " i sekunde " << novi2.DajSekunde() << "formatirano vrijeme glasi: ";
	novi2.Ispisi();
	std::cout << std::endl;
	
	std::cout << "Pet sekundi nakon prvog vremena je vrijeme: ";
	novi.Sljedeci().Sljedeci().Sljedeci().Sljedeci().Sljedeci();
	novi.Ispisi();
	
	std::cout << std::endl;
	
	std::cout << "Pet sekundi prije drugog vremena je vrijeme: ";
	novi2.Prethodni().Prethodni().Prethodni().Prethodni().Prethodni();
	novi2.Ispisi();
	
	std::cout << std::endl;
	
	std::cout << "Drugo vrijeme pomjereno za 3 sekunde unaprijed glasi: ";
	novi2.PomjeriZa(3);
	novi2.Ispisi();
	
	return 0;
}
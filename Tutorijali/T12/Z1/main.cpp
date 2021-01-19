/* 
    TP 16/17 (Tutorijal 12, Zadatak 1)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

#include <iomanip>

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
		
		Sat(): sati(0),minute(0),sekunde(0) {}
		
		Sat(int sati,int minute,int sekunde) {
			if(DaLiJeIspravno(sati,minute,sekunde)) {
				Postavi(sati,minute,sekunde);
			} else {
				Sat::sekunde = sekunde % 60;
				Sat::minute = (minute % 60) + (sekunde / 60);
				Sat::sati = (sati % 24) + (minute / 60);
			}
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
		
		Sat operator++(int) {
		
			Sat temp = *this;
			
			sekunde += 1;
			if(sekunde == 60) {
				sekunde = 0;
				minute += 1;
				if(minute == 60) {
					minute = 0;
					sati +=1;
					if(sati == 24) {
						sati = 0;
					}
				}
			}
				
			return temp;
		}
		
		Sat& operator++() {

			sekunde += 1;
			if(sekunde == 60) {
				sekunde = 0;
				minute += 1;
				if(minute == 60) {
					minute = 0;
					sati +=1;
					if(sati == 24) {
						sati = 0;
					}
				}
			}
				
			return *this;
		}
		
		Sat operator --(int) {
			
		Sat temp = *this;
			
			sekunde -= 1;
			if(sekunde == -1) {
				sekunde = 59;
				minute -= 1;
				if(minute == -1) {
					minute = 59;
					sati -=1;
					if(sati  == -1) {
						sati = 23;
					}
				}
			}
			
			return temp;
		}
		
		Sat& operator --() {
			
			sekunde -= 1;
			if(sekunde == -1) {
				sekunde = 59;
				minute -= 1;
				if(minute == -1) {
					minute = 59;
					sati -=1;
					if(sati  == -1) {
						sati = 23;
					}
				}
			}
			
			return *this;
		}
		
		Sat operator+=(Sat &sat) {
			
			if(sat.sekunde < 0) {
				for(int i=0;i<abs(sekunde);i++)
					sat++;
			} else {
				for(int i=0;i<sekunde;i++)
					sat--;
			}
			
			return sat;
		}
		
		Sat operator-=(Sat &sat) {
			
			if(sat.sekunde < 0) {
				for(int i=0;i<abs(sekunde);i++)
					sat--;
			} else {
				for(int i=0;i<sekunde;i++)
					sat++;
			}
			
			return sat;
		}
		
		Sat operator+=(int broj) {
			
			for(int i=0;i<broj;i++)
				(*this)++;
			
			return *this;
		}

		Sat operator-=(int broj) {
			
			for(int i=0;i<broj;i++)
				(*this)--;
			
			return *this;
		}

		friend std::ostream& operator << (std::ostream& tok, const Sat& s);
		
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

std::ostream& operator << (std::ostream& tok, const Sat& s) {

    tok << std::setw(2) << std::setfill('0') << s.sati
    
    << ":" << 
    
    std::setw(2) << std::setfill('0') << s.minute
        
    << ":" << 
    
    std::setw(2) << std::setfill('0') << s.sekunde;
    
    return tok;
}

int main ()
{
	
	Sat sat(12,21,41);
	
	std::cout << sat << std::endl;
	
	Sat sat2;
	
	std::cout << sat2 << std::endl;
	
	sat++;
	sat++;
	sat++;
	sat++;
	
	std::cout << sat << std::endl;
	
	sat2--;
	sat2--;
	sat2--;
	
	std::cout << sat2 << std::endl;
	
	sat+=sat2;
	sat+=sat2;
	
	std::cout << sat << std::endl;
	
	return 0;
}
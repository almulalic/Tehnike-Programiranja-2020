//TP 2018/2019: ZSR 1, Zadatak 1
#include <iostream>

enum class Pravci {Sjever, Istok, Jug, Zapad};

class Robot {
    int x,y;
    Pravci pravac;
public:
    Robot() {
        pravac = Pravci::Sjever;
        x = 0;
        y = 0;
    }
    
    Robot(int x,int y, Pravaci pravac = Pravaci::Sjever) : x(x),y(y),pravac(pravac) {}
    
    void PostaviPoziciju(int x,int y) {
        
    }
};  


int main () {
    
	return 0;
}
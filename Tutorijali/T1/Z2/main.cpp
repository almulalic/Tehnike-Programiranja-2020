//TP 2018/2019: Tutorijal 1, Zadatak 2 
#include <iostream>
#include <cmath>
#include <iomanip>

int main ()
{
    
    const double PI = 4*atan(1);
    
    std::cout << "Unesite tri broja: ";
    double a,b,c;
    std::cin >> a >> b >> c;
    
    if (( a > 0 && b > 0 && c > 0 ) && (((a+b)>c) && ((a+c)>b) && ((b+c)>a))) {
        
        double obimTrougla = a+b+c;
        
        double s=(a+b+c)/2, povrsinaTrougla = sqrt(s*(s-a)*(s-b)*(s-c));
        
        double ugaoAlfa,ugaoBeta,ugaoGama; 
        
        ugaoAlfa = acos((pow(c,2)+pow(b,2)-pow(a,2))/(2*c*b)) *  180 / PI;
        ugaoBeta = acos((pow(a,2)+pow(c,2)-pow(b,2))/(2*a*c)) *  180 / PI;
        ugaoGama = acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b)) *  180 / PI;
        
        double min(0);
        
        if((ugaoAlfa <= ugaoBeta) && (ugaoAlfa <= ugaoGama))
            min = ugaoAlfa;
        else if ((ugaoBeta <= ugaoAlfa) && (ugaoBeta <= ugaoGama))
            min = ugaoBeta;
        else
            min = ugaoGama;
            
        int stepeni,minute,sekunde,sekundePrim;
        
        stepeni = (int) min;
        minute = (int) ((min -stepeni) * 3600)/60;
        sekundePrim = (int)(min * 3600);
        sekunde = sekundePrim % 60;
        
        std::cout << "Obim trougla sa duzinama stranica " << a << ", " << b << " i " << c << " iznosi " << obimTrougla << ".";
        std::cout << std::endl << "Njegova povrsina iznosi "<< povrsinaTrougla << ".";
        std::cout << std::endl << "Njegov najmanji ugao ima " << stepeni << " stepeni, " << minute << " minuta i " << sekunde << " sekundi.";
    } else 
        std::cout << "Ne postoji trougao cije su duzine stranica " << a << ", " << b << " i " << c << "!";

	return 0;
}
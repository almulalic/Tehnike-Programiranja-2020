/* 
    TP 2018/2019: Tutorijal 5, Zadatak 2
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>

template<typename Tip>
void Razmjeni(Tip &prvi,Tip &drugi) {
	
	Tip temp(prvi);
	prvi = drugi;
	drugi = temp;
	
}

template<typename Tip1,typename Tip2>
Tip2 RazmijeniBlokove(Tip1 prviPocetak,Tip1 prviKraj, Tip2 drugi) {
	
	while( prviPocetak < prviKraj) {

		Razmjeni(*prviPocetak,*drugi);
		prviPocetak++;
		drugi++;
	}
	
	return drugi;
}

int main ()
{
	return 0;
}
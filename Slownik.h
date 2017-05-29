#pragma once
#include"Slowko.h"
class Slownik
{
	Slowko *tablica;
	int ilosc_slowek;
public:
	Slownik();
    bool wczytaj(string="C:\\Users\\Nikki\\Dysk Google\\Program\\Slowka_calosc.txt");
    const inline int DajIlosc(void) {return ilosc_slowek;}
    Slowko DajSlowko(int i);
	~Slownik();
};


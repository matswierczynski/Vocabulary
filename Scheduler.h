#pragma once
#include"Slownik.h"
#include<string>
#include<vector>
class Scheduler
{	
	Slownik *slownik;
    vector<Slowko> TablicaSlow;
    vector<Slowko> DoPowtorki;
    int level, words_number,punkty,suma;
    bool dobrze_czy_nie;

public:
	Scheduler();
	~Scheduler();
    const inline int DajIlosc(void) {return slownik->DajIlosc();}
    string Dodaj_do_powtorki();
    string Pozostalych_Slowek(void);
    string DajPunkty(void);
    void inline ZmniejszPunkty(void) {punkty--;}
    void DodajPunkty(bool poprawnosc);
    string DajSume(void);
    void SetWordsNumber();
    void Rozpocznij(int l_slowek, int poziom);
    void LosujSlowka();
    string Slowko_PL();
    string Slowko_ANG();
    string DajLitere(string sl_do_poprawy);
    bool SprawdzPoprawnosc(string answer);
    bool Zawartosc_listy();
    void Zdejmij_Ze_Stosu();
    void Jeszcze_raz();
    bool DodajSlownik(string nazwa_pliku);
    void UsunSlownik();
};


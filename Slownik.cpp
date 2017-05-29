#include "Slownik.h"
#include<iostream>
#include<fstream>
#include<string>
#include<list>
using namespace std;


Slownik::Slownik():tablica(NULL),ilosc_slowek(0)
{

}

bool Slownik::wczytaj(string nazwa_pliku)
{
    ifstream plik;
    bool poprawnosc_wczytania=true;
    plik.open(nazwa_pliku);
    if (plik.good())
    {
        poprawnosc_wczytania=true;
    }
    else
    {
        poprawnosc_wczytania=false;
        return false;
    }

    list<Slowko> lista_slowek;
    while (!plik.eof())
    {
        string slowko1,slowko2;
        getline(plik, slowko1);
        getline(plik, slowko2);
        Slowko temp(slowko1, slowko2);
        if(slowko1!="" && slowko2!="")
        lista_slowek.push_back(temp);

    }
    plik.close();

    ilosc_slowek = (int)lista_slowek.size();
    list < Slowko > ::iterator it = lista_slowek.begin();
    tablica = new Slowko[ilosc_slowek];
    for (int i = 0; i < ilosc_slowek; i++)
    {
        tablica[i] = *it++;
    }
    lista_slowek.clear();


    return poprawnosc_wczytania;


}

 Slowko Slownik::DajSlowko(int i)
 {
     return tablica[i];
 }


Slownik::~Slownik()
{
    if (tablica!=NULL)
    delete [] tablica;
}

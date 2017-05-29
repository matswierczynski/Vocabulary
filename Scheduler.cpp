#include "Scheduler.h"
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

Scheduler::Scheduler():words_number(0),level(0),punkty(0),suma(0),slownik(NULL), dobrze_czy_nie(false)
{
}

void Scheduler::Rozpocznij(int l_slowek, int poziom)
{
    words_number=l_slowek;
    level=poziom;
}

bool Scheduler::DodajSlownik(string nazwa_pliku)
{
   if(slownik==NULL)
   slownik = new Slownik;

   bool czy_wczytano;
   czy_wczytano=slownik->wczytaj(nazwa_pliku);
   return czy_wczytano;
}

void Scheduler::LosujSlowka()
{
    int *wyl_numery = new int[words_number];
    int temp;
    bool czy_wylosowana=false;
    srand( time( NULL ) );
    for (int i=0;i<words_number;i++)
    {
        do
    {
            czy_wylosowana=false;
            temp = (rand() % slownik->DajIlosc())+0;

        for (int k=0;k<i;k++)
        {
           if (temp==wyl_numery[k])
           {
              czy_wylosowana=true;
              break;
           }
        }
    }
        while(czy_wylosowana==true);

        wyl_numery[i]=temp;

    }

    for(int i=0;i<words_number;i++)
    {
        TablicaSlow.push_back(slownik->DajSlowko(wyl_numery[i]));
    }

    for(int i=0;i<DoPowtorki.size();i++)
    {
        TablicaSlow.push_back(DoPowtorki[i]);

    }

    DoPowtorki.clear();

    delete[] wyl_numery;

}
string Scheduler::Slowko_PL()
{
   Slowko temp = TablicaSlow[0];
   return temp.WypiszPL();
}


string Scheduler::Slowko_ANG()
{
    Slowko temporary = TablicaSlow.front();

    string ang_sl=temporary.WypiszANG();
    int il_znakow = ang_sl.size(); //ilosc wszystkich znaków
    vector<int> miejsca_spacji; //miejsca na których występują spacje

    for (int i=0;i<il_znakow;i++)
    {
        if (ang_sl[i]==' ')
        miejsca_spacji.push_back(i);
    }

    int il_spacji = miejsca_spacji.size(); //ilosć spacji

    int ilosc_liter=il_znakow-il_spacji; //ilosc znaków bez spacji
    string puste_slowko;
    puste_slowko.resize(2*il_znakow);
    for (int i=0;i<il_znakow;i++)
    {
        puste_slowko[2*i]='_';
        puste_slowko[(2*i)+1]=' ';
    }

    int trudnosc=0; //wartosc zmniejszająca ilość wyświetlanych liter
    switch (level)
    {
    case 1:
    {
        if (ilosc_liter<=3)
        {
            break;
        }
        else
        {
            if (ilosc_liter<6)
            trudnosc=2;
            else trudnosc=3;
            break;
        }
    }
     case 2:
    {
        if (ilosc_liter<=4)
        {
            break;
        }
        else
        {
            if (ilosc_liter<6)
            trudnosc=4;
            else trudnosc=2;
            break;
        }
    }
    case 3:
    {
        break;
    }

    default:
    break;
    }

    if (trudnosc==0)                    //zwrot pustego słówka
    {
        miejsca_spacji.clear();
        punkty=ilosc_liter;
        return puste_slowko;
    }


        int temp;
        int *zakrywane_litery = new int[ilosc_liter-trudnosc];  //losowanie miejsc zakrytych i odkrytych
        srand( time( NULL ) );
        bool czy_wylosowana = false;
        for (int i=0;i<ilosc_liter-trudnosc;i++)
        {
            do
        {
                czy_wylosowana=false;
                temp = (rand() % il_znakow )+0;

            for (int k=0;k<i;k++)
            {
               if (temp==zakrywane_litery[k])
               {
                  czy_wylosowana=true;
                  break;
               }
            }

            for(int z=0;z<il_spacji;z++)
            {
                if (temp==miejsca_spacji[z])
                {
                   czy_wylosowana=true;
                   break;
                }
            }
        }
            while(czy_wylosowana==true);

            zakrywane_litery[i]=temp;

        }


        for(int i=0;i<ang_sl.size();i++)
        {
          puste_slowko[2*i]=ang_sl[i];

        }
         for (int i=0;i<ilosc_liter-trudnosc;i++)                                           // przygotowanie słówka do wyświetlania
                puste_slowko[2*(zakrywane_litery[i])]='_';
         punkty=ilosc_liter-trudnosc;

           if (zakrywane_litery!=NULL)
           delete[] zakrywane_litery;
           miejsca_spacji.clear();

return puste_slowko;
}

string Scheduler::DajLitere(string sl_do_poprawy)
{
    if(Zawartosc_listy()==true)
    {
        return "Brak slowa";
    }

  Slowko temp=TablicaSlow.front();
  string aktualne_sl = temp.WypiszANG();
  string temp_sl;
  temp_sl.resize(2*(aktualne_sl.size()));
  for(int i=0;i<aktualne_sl.size();i++)
  {
      temp_sl[2*i]=aktualne_sl[i];
      temp_sl[2*i+1]=' ';
  }

  vector<int> roznice;
  for(int i=0;i<temp_sl.size();i++)
  {
      if (sl_do_poprawy[i]!=temp_sl[i])
          roznice.push_back(i);
  }

  if (roznice.size()==0) //brak różnic = zero punktów
      {
      roznice.clear();
       return "Koniec";
      }


  srand( time( NULL ) );
  int nowa_literka = (rand() % roznice.size() )+0;
  sl_do_poprawy[roznice[nowa_literka]]=temp_sl[roznice[nowa_literka]];
  roznice.clear();
  ZmniejszPunkty();
  return sl_do_poprawy;
}

void Scheduler::Zdejmij_Ze_Stosu()
{
    if (TablicaSlow.empty()==true)
        return;
    else
    TablicaSlow.erase(TablicaSlow.begin());
}

bool Scheduler::Zawartosc_listy()
{
    return TablicaSlow.empty();
}

string Scheduler::DajPunkty()
{
    stringstream ss;
    ss << punkty;
    string str = ss.str();
    return str;
}

string Scheduler::DajSume()
{
    stringstream ss;
    ss << suma;
    string str = ss.str();
    return str;
}

bool Scheduler::SprawdzPoprawnosc(string answer)
{
    Slowko temp = TablicaSlow.front();
    if (answer==temp.WypiszANG())
    {
        dobrze_czy_nie=true;
        return true; 
    }
    else
        return false;
}

void Scheduler::DodajPunkty(bool poprawnosc)
{
    if (poprawnosc==true)
       suma+=punkty;

    else
        return;

}

void Scheduler::Jeszcze_raz()
{
    TablicaSlow.clear();
    level=0;
    words_number=0;
    punkty=0;
    suma=0;
}

void Scheduler::UsunSlownik()
{
    if(slownik!=NULL)
    delete slownik;
    slownik=NULL;
    TablicaSlow.clear();
    words_number=0;
    suma=0;
    level=0;
}

string Scheduler::Pozostalych_Slowek()
{
    stringstream ss;
    ss << TablicaSlow.size();
    string str = ss.str();
    return str;
}

string Scheduler::Dodaj_do_powtorki()
{
    if (dobrze_czy_nie==false)
    {
        DoPowtorki.push_back(TablicaSlow.front());
    }
    else
        dobrze_czy_nie=false;

    stringstream ss;
    ss << DoPowtorki.size();
    string str = ss.str();
    return str;
}

Scheduler::~Scheduler()
{
    if(slownik!=NULL)
    delete[] slownik;
    TablicaSlow.clear();
    DoPowtorki.clear();
}



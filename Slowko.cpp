#include "Slowko.h"
#include<string>


Slowko::Slowko(string pol, string ang) : sl_pl(pol), sl_ang(ang)
{
}

string Slowko::WypiszPL()
{
    return sl_pl;
}

string Slowko::WypiszANG()
{
    return sl_ang;
}

Slowko::~Slowko()
{
}

ostream& operator<<(ostream &wyjscie, const Slowko &element)
{
	wyjscie << element.sl_pl<<" "<<element.sl_ang;
	return wyjscie;
}

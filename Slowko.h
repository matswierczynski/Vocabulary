#pragma once
#include<iostream>
#include<cstring>
using namespace std;
class Slowko
{
    string sl_pl;
    string sl_ang;
public:
    Slowko(string="jabłko", string ="apple");
	friend ostream& operator<<(ostream &wyjscie, const Slowko &element);
    string WypiszPL();
    string WypiszANG();
	~Slowko();
};


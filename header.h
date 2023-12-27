#pragma once
#pragma warning(suppress : 4996)
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
using namespace std;

class pineska
{
public:
	//  KLASA ODPOWIEDZIALNA ZA PINESKI, NIE W KOMPETENCJI DODAWANIA ZDARZENIA
	bool tak;
	pineska();
	void daj_czas_pin(bool test_pin);
}; 
class przypomnienie
{
public:
	bool tak;
	przypomnienie();
	//  KLASA ODPOWIEDZIALNA ZA PRZYPOMNINIA, NIE W KOMPETENCJI DODAWANIA ZDARZENIA
	void daj_czas_przy(bool test_przy);
};
class cyklicznosc
{
public:
	bool czy[2];
	friend class U_Zdarzenie;
	cyklicznosc();
};
class U_Zdarzenie
{
public:
	tm czas;
	tm koniec;
	pineska dane;
	przypomnienie przy;
	cyklicznosc cyk;
	friend class System_b;
	bool daj_czas_czy();
	/*
	* void dodaj();
	tm daj_czas_kiedy();
	void daj_czas_okres();
	void daj_czas_cykl();
	void daj_czas_pin();
	void daj_czas_przy();
	*/
	tm daj_czas_kiedy(int test_min, int test_hour, int test_mday, int test_mon, int test_year);
	void daj_czas_okres(int test_czas);
	void daj_czas_cykl(int test_cyk);
	void daj_czas_pin(bool test_pin);
	void daj_czas_przy(bool test_przy);
	U_Zdarzenie();
	bool dodaj(int test_min, int test_hour, int test_mday, int test_mon, int test_year, int test_czas, int test_cyk, bool test_pin, bool test_przy);
	void pokaz_zd();// debug
};
class System_b
{
	//ostatecznie baza danych, na potrzeby tego zadania nie zapisuje na sta³e
	U_Zdarzenie tab[10];
	int k;
	friend class U_Zdarzenie;
public:
	void pokaz_zd(U_Zdarzenie);
	void dodaj_zd(U_Zdarzenie a);
	bool daj_czas_czy(U_Zdarzenie a);
};
class ZdarzenieBuilder {
public:
	virtual void buildZD() = 0;
	virtual U_Zdarzenie getZD() const = 0;
};
class makeing {
public:
	void makePizza(ZdarzenieBuilder& builder)
	{
		builder.buildZD();
	}
};
class Builder2000_2001 : public ZdarzenieBuilder {
public:
	void buildZD() override
	{
		int test_min = 59;
		int test_hour = 23;
		int test_mday = 31;
		int test_mon = 11;
		int test_year = 2000;
		int test_czas = 11;
		bool test_pin = 1;
		bool test_przy = 1;
		int test_cyk = 2;
		a.dodaj(test_min, test_hour, test_mday, test_mon, test_year, test_czas, test_cyk, test_pin, test_przy);
	}

	U_Zdarzenie getZD() const override { return a; }
private:
	U_Zdarzenie a;
};
#include "header.h"

System_b System;

pineska::pineska()
{
	tak = 0;
}
przypomnienie::przypomnienie()
{
	tak = 0;
}
void System_b::pokaz_zd(U_Zdarzenie a) //debug
{
	tm koniec = a.czas;
	cout << "Poczatek:\n" << "y = " << (koniec.tm_year + 1900) << "\nm = " << (koniec.tm_mon + 1) << "\nd = " << koniec.tm_mday << "\nh = " << koniec.tm_hour << "\nm = " << koniec.tm_min << endl;
	koniec = a.koniec;
	cout << "Koniec:\n" << "y = " << (koniec.tm_year + 1900) << "\nm = " << (koniec.tm_mon + 1) << "\nd = " << koniec.tm_mday << "\nh = " << koniec.tm_hour << "\nm = " << koniec.tm_min << endl;

}

void System_b::dodaj_zd(U_Zdarzenie a)
{
	tab[k] = a;
	k++;
}
cyklicznosc::cyklicznosc()
{
	for (int i = 0; i < 2; i++)
	{
		czy[i] = 0;
	}
}

U_Zdarzenie::U_Zdarzenie()
{
	cyklicznosc b;
	cyk = b;
	czas = { 0 };
	koniec = { 0 };
	pineska d;
	dane = d;
	przypomnienie p;
	przy = p;
}

bool U_Zdarzenie::dodaj(int test_min, int test_hour, int test_mday, int test_mon, int test_year, int test_czas, int test_cyk, bool test_pin, bool test_przy)
{
	czas = this->daj_czas_kiedy(test_min, test_hour, test_mday, test_mon, test_year);
	koniec = czas;

	//pokaz_zd();
	this->daj_czas_okres(test_czas);
	this->daj_czas_cykl(test_cyk);
	if (this->daj_czas_czy())
	{
		cout << "Zdazenie pokrywa sie z innym zdarzeniem!!!" << endl;
		return true;
	}
	//pokaz_zd();
	this->daj_czas_pin(test_pin);
	this->daj_czas_przy(test_przy);
	System.dodaj_zd(*this);
	return 0;
}

void U_Zdarzenie::pokaz_zd()
{
	System.pokaz_zd(*this);
}

tm U_Zdarzenie::daj_czas_kiedy(int test_min, int test_hour, int test_mday, int test_mon, int test_year)
{
	//time_t timer;
	struct tm y2k = { 0 };
	//double seconds;

	//y2k.tm_hour = 0;   y2k.tm_min = 0; 
	y2k.tm_sec = 0;
//	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	y2k.tm_year = test_year -1900;
	y2k.tm_mon = test_mon;
	y2k.tm_mday = test_mday;
	y2k.tm_hour = test_hour;
	y2k.tm_min = test_min;

	//cout << "y = " << (y2k.tm_year + 1900) << "\nm = " << (y2k.tm_mon + 1) << "\nd = " << y2k.tm_mday << "\nh = " << y2k.tm_hour << "\nm = " << y2k.tm_min << endl;
	//time(&timer);  /* get current time; same as: timer = time(NULL)  */

	//seconds = difftime(timer, mktime(&y2k));

	//printf("%.f seconds since January 1, 2000 in the current timezone\n", seconds);
	return y2k;
}

void U_Zdarzenie::daj_czas_okres(int test_czas)
{
	double seconds;
	time_t timer;
	int a = test_czas;
	
	//koniec.tm_min = koniec.tm_min + a;

	koniec.tm_mon += 1;
	koniec.tm_min += a;
	
	while (1)
	{
		if (koniec.tm_min >= 60)
		{
			koniec.tm_min -= 60;
			koniec.tm_hour += 1;
			if (koniec.tm_hour >= 24)
			{
				koniec.tm_hour = 0;
				koniec.tm_mday += 1;
				if ((koniec.tm_mday >= 32 && (koniec.tm_mon == 1 || koniec.tm_mon == 3 || koniec.tm_mon == 5 || koniec.tm_mon == 7 || koniec.tm_mon == 8 || koniec.tm_mon == 10 || koniec.tm_mon == 12))||
					(koniec.tm_mday >= 31 && (koniec.tm_mon == 4 || koniec.tm_mon == 6 || koniec.tm_mon == 9 || koniec.tm_mon == 11))||
					(koniec.tm_mday >= 29 && (koniec.tm_mon == 2)&& !((koniec.tm_year % 400 == 0) ||((koniec.tm_year % 100 != 0)&&(koniec.tm_year % 4 == 0))))||
					(koniec.tm_mday >= 30 && (koniec.tm_mon == 2)))
				{
					koniec.tm_mday = 1;
					koniec.tm_mon += 1;
					if (koniec.tm_mon >= 12)
					{
						koniec.tm_mon = 1;
						koniec.tm_year += 1;
					}
				}
			}
		}
		else
		{
			break;
		}
	}
	koniec.tm_mon -= 1;
	
	//koniec.tm_mon -= 1;

	//printf("Straight: %d\nReference: %d\n", koniec.tm_year, &(koniec.tm_year));

	//cout << "y = " << (koniec.tm_year+1900) << "\nm = " << (koniec.tm_mon+1) << "\nd = " << koniec.tm_mday << "\nh = " << koniec.tm_hour << "\nm = " << koniec.tm_min << endl;
}

void U_Zdarzenie::daj_czas_cykl(int test_cykl)
{
	if (test_cykl == 1)
	{
		cyk.czy[0] = 1;
	}
	else if (test_cykl == 2)
	{
		cyk.czy[1] = 1;
	}
}

bool U_Zdarzenie::daj_czas_czy()
{
	return System.daj_czas_czy(*this);
}
bool System_b::daj_czas_czy(U_Zdarzenie a)
{
	for (int i = 0; i < k; i++)
	{
		if (((mktime(&(a.czas)) > mktime(&(tab[i].czas))) && (mktime(&(a.czas)) < mktime(&(tab[i].koniec)))) ||
			((mktime(&(a.koniec)) > mktime(&(tab[i].czas))) && (mktime(&(a.koniec)) < mktime(&(tab[i].koniec)))) ||
			(mktime(&(a.czas)) < mktime(&(tab[i].czas))) && (mktime(&(a.koniec)) > mktime(&(tab[i].koniec))))
		{
			return 1;
		}
	}
	return 0;
}

void U_Zdarzenie::daj_czas_pin(bool test_pin)
{
	if (test_pin)
	{
		dane.daj_czas_pin(test_pin);
	}
}
void pineska::daj_czas_pin(bool test_pin)
{
	tak = test_pin;
}

void U_Zdarzenie::daj_czas_przy(bool test_przy)
{
	if (test_przy)
	{
		przy.daj_czas_przy(test_przy);
	}
}
void przypomnienie::daj_czas_przy(bool test_przy)
{
	tak = test_przy;
}

/*
#include "header.h"

System_b System;

void System_b::pokaz_zd(U_Zdarzenie a)
{
	tm koniec = a.czas;
	cout << "Poczatek:\n" << "y = " << (koniec.tm_year + 1900) << "\nm = " << (koniec.tm_mon + 1) << "\nd = " << koniec.tm_mday << "\nh = " << koniec.tm_hour << "\nm = " << koniec.tm_min << endl;
	koniec = a.koniec;
	cout << "Koniec:\n" << "y = " << (koniec.tm_year + 1900) << "\nm = " << (koniec.tm_mon + 1) << "\nd = " << koniec.tm_mday << "\nh = " << koniec.tm_hour << "\nm = " << koniec.tm_min << endl;

}

void System_b::dodaj_zd(U_Zdarzenie a)
{
	tab[k] = a;
	k++;
}
cyklicznosc::cyklicznosc()
{
	for (int i = 0; i < 2; i++)
	{
		czy[i] = 0;
	}
}

U_Zdarzenie::U_Zdarzenie()
{
	cyklicznosc b;
	cyk = b;
	czas = { 0 };
	koniec = { 0 };
	pineska d;
	dane = d;
	przypomnienie p;
	przy = p;
}

void U_Zdarzenie::dodaj()
{
	czas = this->daj_czas_kiedy();
	koniec = czas;
	//pokaz_zd();
	this->daj_czas_okres();
	this->daj_czas_cykl();
	if (this->daj_czas_czy())
	{
		cout << "Zdazenie pokrywa sie z innym zdarzeniem!!!" << endl;
		return;
	}
	this->daj_czas_pin();
	this->daj_czas_przy();
	System.dodaj_zd(*this);
}
void U_Zdarzenie::pokaz_zd()
{
	System.pokaz_zd(*this);
}

tm U_Zdarzenie::daj_czas_kiedy()
{
	//time_t timer;
	struct tm y2k = { 0 };
	//double seconds;

	//y2k.tm_hour = 0;   y2k.tm_min = 0; 
	y2k.tm_sec = 0;
	//	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	int a;
	cout << "Podaj rok " << endl;
	cin >> a;
	a = a - 1900;
	y2k.tm_year = a;
	cout << "Podaj miesiac " << endl;
	cin >> a;
	a = a - 1;
	y2k.tm_mon = a;
	cout << "Podaj dzien " << endl;
	cin >> a;
	y2k.tm_mday = a;
	cout << "Podaj godzine " << endl;
	cin >> a;
	y2k.tm_hour = a;
	cout << "Podaj minute " << endl;
	cin >> a;
	y2k.tm_min = a;

	//cout << "y = " << (y2k.tm_year + 1900) << "\nm = " << (y2k.tm_mon + 1) << "\nd = " << y2k.tm_mday << "\nh = " << y2k.tm_hour << "\nm = " << y2k.tm_min << endl;
	//time(&timer);   get current time; same as: timer = time(NULL)  

	//seconds = difftime(timer, mktime(&y2k));

	//printf("%.f seconds since January 1, 2000 in the current timezone\n", seconds);
	return y2k;
}

void U_Zdarzenie::daj_czas_okres()
{
	double seconds;
	time_t timer;
	int a;
	cout << "Podaj jak dlugo (minuty)" << endl;
	cin >> a;

	//koniec.tm_min = koniec.tm_min + a;

	koniec.tm_mon += 1;
	koniec.tm_min += a;

	while (1)
	{
		if (koniec.tm_min >= 60)
		{
			koniec.tm_min -= 60;
			koniec.tm_hour += 1;
			if (koniec.tm_hour >= 24)
			{
				koniec.tm_hour = 0;
				koniec.tm_mday += 1;
				if ((koniec.tm_mday >= 32 && (koniec.tm_mon == 1 || koniec.tm_mon == 3 || koniec.tm_mon == 5 || koniec.tm_mon == 7 || koniec.tm_mon == 8 || koniec.tm_mon == 10 || koniec.tm_mon == 12)) ||
					(koniec.tm_mday >= 31 && (koniec.tm_mon == 4 || koniec.tm_mon == 6 || koniec.tm_mon == 9 || koniec.tm_mon == 11)) ||
					(koniec.tm_mday >= 29 && (koniec.tm_mon == 2) && !((koniec.tm_year % 400 == 0) || ((koniec.tm_year % 100 != 0) && (koniec.tm_year % 4 == 0)))) ||
					(koniec.tm_mday >= 30 && (koniec.tm_mon == 2)))
				{
					koniec.tm_mday = 1;
					koniec.tm_mon += 1;
					if (koniec.tm_mon >= 12)
					{
						koniec.tm_mon = 0;
						koniec.tm_year += 1;
					}
				}
			}
		}
		else
		{
			break;
		}
	}

	//koniec.tm_mon -= 1;

	//printf("Straight: %d\nReference: %d\n", koniec.tm_year, &(koniec.tm_year));

	//cout << "y = " << (koniec.tm_year+1900) << "\nm = " << (koniec.tm_mon+1) << "\nd = " << koniec.tm_mday << "\nh = " << koniec.tm_hour << "\nm = " << koniec.tm_min << endl;
}

void U_Zdarzenie::daj_czas_cykl()
{
	int a;
	cout << "Czy powtarzac co tydzien?(1-tak/0-nie)" << endl;
	cin >> a;
	if (a)
	{
		cyk.czy[0] = 1;
	}
	cout << "Czy powtarzac co dzien?(1-tak/0-nie)" << endl;
	cin >> a;
	if (a)
	{
		cyk.czy[1] = 1;
	}
}

bool U_Zdarzenie::daj_czas_czy()
{
	return System.daj_czas_czy(*this);
}
bool System_b::daj_czas_czy(U_Zdarzenie a)
{
	for (int i = 0; i < k; i++)
	{
		if (((mktime(&(a.czas)) > mktime(&(tab[i].czas))) && (mktime(&(a.czas)) < mktime(&(tab[i].koniec)))) ||
			((mktime(&(a.koniec)) > mktime(&(tab[i].czas))) && (mktime(&(a.koniec)) < mktime(&(tab[i].koniec)))) ||
			(mktime(&(a.czas)) < mktime(&(tab[i].czas))) && (mktime(&(a.koniec)) > mktime(&(tab[i].koniec))))
		{
			return 1;
		}
	}
	return 0;
}

void U_Zdarzenie::daj_czas_pin()
{
	int a;
	cout << "Czy pineska?(1-tak/0-nie)" << endl;
	cin >> a;
	if (a)
	{
		dane.daj_czas_pin();
	}
}
void pineska::daj_czas_pin()
{
	cout << "PIN" << endl;
}

void U_Zdarzenie::daj_czas_przy()
{
	int a;
	cout << "Czy przypomnienie?(1-tak/0-nie)" << endl;
	cin >> a;
	if (a)
	{
		przy.daj_czas_przy();
	}
}
void przypomnienie::daj_czas_przy()
{
	cout << "PRZY" << endl;
}
*/
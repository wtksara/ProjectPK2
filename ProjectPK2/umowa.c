#pragma once
#include "umowa.h"

int pliczba;
// Zmienna globalna okreslajaca numer podatkowy

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tworzenie nowych elementów

struct umowa* nowa_umowa(struct menu** pmenu)
{
	printf("\n                   DODAWANIE NOWEJ UMOWY \n\n");
	struct umowa * nowa = (struct umowa*)malloc(sizeof(struct umowa));
	nowa->numer = pliczba;
	pliczba++;

	// Sprawdzenie daty wystawienia umowy
	printf("                   DATA WYSTAWIENIA \n");
	ustaw_date(&nowa->datawystawienia);

	// Sprawdzenie daty zakonczenia  umowy
	printf("\n                   DATA ZAKONCZENIA \n");
	ustaw_date(&nowa->datazakonczenia);

	// Sprawdzenie czy data zakonczenia jest pozniej niz data wystawienia
	while (poprawnosc(&nowa->datawystawienia, &nowa->datazakonczenia,1) != true) {
		ustaw_date(&nowa->datazakonczenia);
	}
	system("cls");

	// Sprawdzenie wyboru rodzaju  umowy
	while (kto_umowa(&nowa->rodzaj,&*pmenu, &nowa) != true) {
	    kto_umowa(&nowa->rodzaj,&*pmenu, &nowa);
	}

	system("cls");

	// Sprawdzenie typu umowy
	while (rodzaj_umowy(&nowa->typ) != true) {
		rodzaj_umowy(&nowa->typ);
	}
	printf("                   NA CO WYSTAWIONA UMOWA (NAZWA PRZEDMIOTU / USLUGI) \n");
	scanf("%99s", &nowa->element);
	while (sprawdz_string(nowa->element) != true) {
		scanf("%99s", &nowa->element);
	}
	zmiana(&nowa->element);

	// Wprowadznie kwoty netto i stawki podatku vat
	printf("                   WPROWADZ KWOTE NETTO \n");
	scanf("%f", &nowa->kwotanetto);
	printf("                   WPROWADZ WARTOSC PODATKU VAT W % \n");
	scanf("%f", &nowa->stawkapodatku);
	nowa->kwotabrutto = nowa->kwotanetto + (nowa->kwotanetto * (nowa->stawkapodatku / 100));
	int stan = 0;
	printf("                   STAN UMOWY \n");
	printf("                   1.ZAPLACONA \n");
	printf("                   2.NIEZAPLACONA \n");
	scanf("%d", &stan);
	while ((stan !=1) ||(stan != 2)) {
		if (stan == 1) {
			nowa->stan = 1;
			break;
		}
		else if (stan == 2) {
			nowa->stan = 0;
			break;
		}
		printf("                   NIEPOPRAWNA OPCJA \n");
		scanf("%d", &stan);
	}

	return nowa;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rodzaje umow

bool kto_umowa(int* rodzaj, struct menu** pmenu, struct umowa** nowa_umowa) {

	// Funkcja przypisujaca odpowiednio odbiorcy / nadawcy odpowiedni element - czyli firme lub osobe
	// W zaleznosci od preferencji u¿ytkownika
	printf("                   UMOWA POMIEDZY \n \n");
	printf("                   1.OSOBA PRYWATNA - OSOBA PRYWATNA \n");
	printf("                   2.OSOBA PRYWATNA - FIRMA \n");
	printf("                   3.FIRMA - OSOBA PRYWATNA \n");
	printf("                   4.FIRMA- FIRMA \n");
	printf("                   WYBIERZ NUMER OPCJI \n");
	char option;
	int liczba = 0;
	int check = 0;
	int wybor = 0;
	scanf(" %c", &option);
	while ((liczba = getchar()) != '\n');
	switch (option)
	{
	case '1':
	{
		int numer = 0;
		printf("                   NABYWCA \n");
		(*nowa_umowa)->nabywca = nowa_osoba(&(*pmenu)->oglowa, &wybor,&numer, &check);
		while (check != 0) {
			(*nowa_umowa)->nabywca = nowa_osoba(&(*pmenu)->oglowa, &wybor, &numer, &check);
		}
		if (wybor == 1) {
			dodaj_do_listy_osob(&*pmenu, &(*nowa_umowa)->nabywca);
		}

		printf("\n                   DOSTAWCA \n");
		(*nowa_umowa)->dostawca = nowa_osoba(&(*pmenu)->oglowa, &wybor,&numer, &check);
		while (check != 0) {
			(*nowa_umowa)->dostawca = nowa_osoba(&(*pmenu)->oglowa, &wybor, &numer, &check);
		}
		if (wybor == 1) {
			dodaj_do_listy_osob(&*pmenu,&(*nowa_umowa)->dostawca);
		}
		
		*rodzaj = 1;
		return true;
		break;
	}
	case '2':
	{ 
		int numer = 0;
		printf("                   NABYWCA \n");
		(*nowa_umowa)->nabywca = nowa_osoba(&(*pmenu)->oglowa, &wybor, &numer, &check);
		while (check != 0) {
			(*nowa_umowa)->nabywca = nowa_osoba(&(*pmenu)->oglowa, &wybor, &numer, &check);
		}
		if (wybor == 1) {
			dodaj_do_listy_osob(&*pmenu, &(*nowa_umowa)->nabywca);
		}

		printf("\n                   DOSTAWCA \n");
		(*nowa_umowa)->dostawca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
		while (check != 0) {
			(*nowa_umowa)->dostawca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
		}
		if (wybor == 1) {
			dodaj_do_listy_firm(&*pmenu, &(*nowa_umowa)->dostawca);
		}

		*rodzaj = 2;
		return true;
		break;
	}
	case '3':
	{
		    int numer = 0;
			printf("                   NABYWCA \n");
			(*nowa_umowa)->nabywca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
			while (check != 0) {
				(*nowa_umowa)->nabywca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
			}
			if (wybor == 1) {
				dodaj_do_listy_firm(&*pmenu, &(*nowa_umowa)->nabywca);
			}

			printf("\n                   DOSTAWCA \n");
			(*nowa_umowa)->dostawca = nowa_osoba(&(*pmenu)->oglowa, &wybor, &numer, &check);
			while (check != 0) {
				(*nowa_umowa)->dostawca = nowa_osoba(&(*pmenu)->oglowa, &wybor, &numer, &check);
			}
			if (wybor == 1) {
				dodaj_do_listy_osob(&*pmenu, &(*nowa_umowa)->dostawca);
			}

		*rodzaj = 3;
		return true;
		break;
	}
	case '4':
	{
		int numer = 0;
		printf("                   NABYWCA \n");
		(*nowa_umowa)->nabywca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
		while (check != 0) {
			(*nowa_umowa)->nabywca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
		}
		if (wybor == 1) {
			dodaj_do_listy_firm(&*pmenu, &(*nowa_umowa)->nabywca);
		}

		printf("\n                   DOSTAWCA \n");
		(*nowa_umowa)->dostawca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
		while (check != 0) {
			(*nowa_umowa)->dostawca = nowa_firma(&(*pmenu)->fglowa, &wybor, &numer, &check);
		}
		if (wybor == 1) {
			dodaj_do_listy_firm(&*pmenu, &(*nowa_umowa)->dostawca);
		}
		*rodzaj = 4;
		return true;
		break;
	}

	default: {

		system("cls");
		printf("                   NIEPOPRAWNY NUMER OPCJI \n ");
		return false;
		break;
	}
	}
}

bool rodzaj_umowy (int* typ) {

	// Funkcja odpowiadaj¹ca za wybor rodzaju umowy
	printf("                   WYBIERZ RODZAJ UMOWY \n \n");
	printf("                   1.SPRZEDAZY \n");
	printf("                   2.USLUGI \n");
	printf("                   WYBIERZ NUMER OPCJI \n");

	char option;
	int liczba = 0;
	scanf(" %c", &option);
	while ((liczba = getchar()) != '\n');
	switch (option)
	{
	case '1':
	{
		*typ = 1;
		return true;
		break;
	}
	case '2':
	{
		*typ = 2;
		return true;
		break;
	}

	default: {

		system("cls");
		printf("                   NIEPOPRAWNY NUMER OPCJI \n ");
		return false;
		break;
	}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dodanie do listy

void dodaj_do_listy(struct menu** pmenu, int i, char* buffer)
{
	if ((*pmenu)->glowa == NULL) //sprawdzam czy istnieje ju¿ jakiœ element w liœcie 
	{ 
		if (i == 0) {
			(*pmenu)->glowa = nowa_umowa(&(*pmenu)); // Uzytkownik tworzy nowy element 
		}
		else {
			(*pmenu)->glowa = zaladuj_umowe(&(*pmenu),buffer); // Nowy element jest wczytywany z pliku
			pliczba++;
		}
		(*pmenu)->ogon = (*pmenu)->glowa;
		(*pmenu)->licznik++; // zwiêkszam licznik który mówi ile posiadam elementów listy 
		(*pmenu)->glowa->nastepny = NULL; //ustawiam wartoœæ wskaŸnika na nastêpny element listy  jako nullptr, poniewa¿ moja lista dodaje nowe elementy na koñcu 
		(*pmenu)->glowa->poprzedni = NULL; //z racji tego ¿e jest to pierwszy element listy wartoœæ wskaŸnika na poprzedni ustawiam jako nullpr

	}
	else //je¿eli istnieje jakiœ element w liœcie 
	{
		struct umowa* obecny_ele = (struct umowa*)malloc(sizeof(struct umowa));
		obecny_ele = (*pmenu)->ogon; // Dodawanie na koniec listy
		if (i == 0) {
			(*pmenu)->ogon = nowa_umowa(&(*pmenu)); // Uzytkownik tworzy nowy element 
		}
		else {
			(*pmenu)->ogon = zaladuj_umowe(&(*pmenu),buffer); // Nowy element jest wczytywany z pliku
			pliczba++;
		}
		obecny_ele->nastepny = (*pmenu)->ogon;
		(*pmenu)->ogon->poprzedni = obecny_ele;
		(*pmenu)->ogon->nastepny = NULL;
	}
}


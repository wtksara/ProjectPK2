#pragma once
#include "osoba.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tworzenie nowych elementów

struct osoba* nowa_osoba(struct osoba** glowa, int* wybor, int* pnumer, int* check) {

	printf("                   1.NOWA OSOBA \n");
	printf("                   2.OSOBA Z BAZY  \n");
	printf("                   WYBIERZ NUMER OPCJI \n");
	char option;
	int liczba = 0;
	int c;
	scanf(" %c", &option);
	while ((liczba = getchar()) != '\n');
	switch (option)
	{
	case '1':
	{
		*wybor = 1;
		*check = 0;
		struct osoba* nowa = (struct osoba*)malloc(sizeof(struct osoba));
		printf("                   WPISZ IMIE \n ");
		scanf("%19s", &nowa->imie);
		while (sprawdz_string(nowa->imie) != true) {
			scanf("%19s", &nowa->imie);
		}
		zmiana(&nowa->imie);
		printf("                   WPISZ NAZWISKO \n ");
		scanf("%19s", &nowa->nazwisko);
		while (sprawdz_string(nowa->nazwisko) != true) {
			scanf("%19s", &nowa->nazwisko);
		}
		zmiana(&nowa->nazwisko);
		int numer = 0;
		while ((c = getchar()) != '\n' && c != EOF) {}
		printf("                   WPISZ NUMER PODATKOWY \n ");
		while (sprawdz_numer_podatkowy(&numer) != true) {
			sprawdz_numer_podatkowy(&numer);
		}
		// Sprawdzanie czy w bazie nie wystapila osoba z danym numerem podatkowym
		// Zak³adamy ¿e numery podatkowe nie mog¹ siê powtarzaæ
		while (sprawdz_numer_osoby(&*glowa, numer) != true) {
			printf("                   WPROWADZONO NIE POPRAWY NUMER PODAKOWY. SPROBUJ JESZCZE RAZ \n ");
			while ((c = getchar()) != '\n' && c != EOF) {}
			while (sprawdz_numer_podatkowy(&numer) != true) {
				sprawdz_numer_podatkowy(&numer);
			}
		}
		*pnumer = numer;
		nowa->numer = numer;
		return nowa;
		break;
	}
	case '2':
	{
		*wybor = 2;
		int numer = 0;
		// Wyswietenie wszystkich osob w bazie oprocz osoby która jest nadawca
		if (wszystkie_osoby(*glowa, *pnumer) != false) {
			*check = 0;
			printf("                   WYSZUKIWANIE PO NUMERZE PODATKOWYM. WPROWADZ NUMER \n ");
			while ((c = getchar()) != '\n' && c != EOF) {}
			while (sprawdz_numer_podatkowy(&numer) != true) {
				sprawdz_numer_podatkowy(&numer);
			}
			// Sprawdzanie czy w bazie nie wystapila osoba z danym numerem podatkowym
			// Zak³adamy ¿e numery podatkowe nie mog¹ siê powtarzaæ
			while (sprawdz_numer_osoby(&*glowa, numer) != false) {
				printf("                   WPROWADZONO NIE POPRAWY NUMER PODAKOWY. SPROBUJ JESZCZE RAZ \n ");
				while ((c = getchar()) != '\n' && c != EOF) {}
				while (sprawdz_numer_podatkowy(&numer) != true) {
					sprawdz_numer_podatkowy(&numer);
				}
			}
			struct osoba* temp = (struct osoba*)malloc(sizeof(struct osoba));
			temp = *glowa;
			// Znalezienie odpowiedniej osoby
			while (temp)
			{
				if (temp->numer == numer) {
					break;
				}
				temp = temp->nastepny;
			}
			return temp;
		}
		else {
			*check = 1;
		}
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

void dodaj_do_listy_osob(struct menu** pmenu, struct osoba** nowa)
{

	if ((*pmenu)->oglowa == NULL) //sprawdzam czy istnieje ju¿ jakiœ element w liœcie 
	{
		(*pmenu)->oglowa = *nowa; // tworzê nowy element 
		(*pmenu)->oogon = (*pmenu)->oglowa;
		(*pmenu)->oglowa->nastepny = NULL; //ustawiam wartoœæ wskaŸnika na nastêpny element listy  jako nullptr, poniewa¿ moja lista dodaje nowe elementy na koñcu 
		(*pmenu)->oglowa->poprzedni = NULL; //z racji tego ¿e jest to pierwszy element listy wartoœæ wskaŸnika na poprzedni ustawiam jako nullpr

	}
	else //je¿eli istnieje jakiœ element w liœcie 
	{
		struct osoba* obecny_ele = (struct osoba*)malloc(sizeof(struct osoba));
		obecny_ele = (*pmenu)->oogon; // Dodawanie na koniec listy
		(*pmenu)->oogon = *nowa;
		obecny_ele->nastepny = (*pmenu)->oogon;
		(*pmenu)->oogon->poprzedni = obecny_ele;
		(*pmenu)->oogon->nastepny = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Znajdz osobe

struct osoba** znajdz_osobe(struct menu** pmenu, int pnumer)
{
	struct osoba* temp = (struct osoba*)malloc(sizeof(struct osoba));
	temp = (*pmenu)->oglowa;
	while (temp)
	{
		if (temp->numer == pnumer) {
			return temp;
		}
		temp = temp->nastepny;
	}
	temp = NULL;
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprawdzanie numeru podatkowego

bool sprawdz_numer_osoby(struct osoba** glowa, int pnumer)

{   // Przeszukujemy czy nie ma ju¿ takiego numeru podatkowego

	struct osoba* temp = (struct osoba*)malloc(sizeof(struct osoba));
	temp = *glowa;
	while (temp)
	{
		if (temp->numer == pnumer) {
			temp = NULL;
			return false;

		}
		temp = temp->nastepny;
	}
	temp = NULL;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Wyœwietlanie danych

void dane_osoby(void** dane)
{
	struct osoba* posoba = (struct osoba*)malloc(sizeof(struct osoba));
	posoba = *dane;
	printf("                   IMIE: %s \n", posoba->imie);
	printf("                   NAZWISKO: %s \n", posoba->nazwisko);
	printf("                   NUMER PODATKOWY: %d \n", posoba->numer);
	posoba = NULL;
}

bool wszystkie_osoby(struct osoba* glowa, int numer) {

	printf("                   OSOBY W BAZIE DANYCH \n");
	struct osoba* temp = (struct osoba*)malloc(sizeof(struct osoba));
	temp = glowa;
	int i = 1;
	if (temp == NULL) {
		printf("                   BRAK OSOB W BAZIE \n");
		return false;
	}
	else {
		while (temp)
		{
			if (temp->numer != numer) {
				printf("                   %d. %s %s , %d \n", i, temp->imie, temp->nazwisko, temp->numer);
				i++;
			}
			temp = temp->nastepny;
		}
	}
	temp = NULL;
	return true;
}
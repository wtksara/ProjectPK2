#pragma once
#include "firma.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tworzenie nowych elementów

struct firma* nowa_firma(struct firma** glowa, int* wybor, int* pnumer, int* check) {

	printf("                   1.NOWA FIRMA \n");
	printf("                   2.FIRMA Z BAZY  \n");
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
		struct firma* nowa = (struct firma*)malloc(sizeof(struct firma));
		printf("                   WPISZ NAZWE \n ");
		scanf("%24s", &nowa->nazwa);
		while (sprawdz_string(nowa->nazwa) != true) {
			scanf("%24s", &nowa->nazwa);
		}
		zmiana(&nowa->nazwa);
		int numer;
		printf("                   WPISZ NUMER PODATKOWY \n ");
		while ((c = getchar()) != '\n' && c != EOF) {}
		while (sprawdz_numer_podatkowy(&numer) != true) {
			sprawdz_numer_podatkowy(&numer);
		}
		// Sprawdzanie czy w bazie nie wystapila firma z danym numerem podatkowym
		// Zak³adamy ¿e numery podatkowe nie mog¹ siê powtarzaæ
		while (sprawdz_numer_firmy(&*glowa, numer) != true) {
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
		int numer;
		// Wyswietenie wszystkich osob w bazie oprocz osoby która jest nadawca
		if (wszystkie_firmy(*glowa, *pnumer) != false) {
			*check = 0;
			printf("                   WYSZUKIWANIE PO NUMERZE PODATKOWYM. WPROWADZ NUMER \n ");
			while ((c = getchar()) != '\n' && c != EOF) {}
			while (sprawdz_numer_podatkowy(&numer) != true) {
				sprawdz_numer_podatkowy(&numer);
			}
			// Sprawdzanie czy w bazie nie wystapila firma z danym numerem podatkowym
			// Zak³adamy ¿e numery podatkowe nie mog¹ siê powtarzaæ 
			while (sprawdz_numer_firmy(&*glowa, numer) != false) {
				printf("                   WPROWADZONO NIE POPRAWY NUMER PODAKOWY. SPROBUJ JESZCZE RAZ \n ");
				while ((c = getchar()) != '\n' && c != EOF) {}
				while (sprawdz_numer_podatkowy(&numer) != true) {
					sprawdz_numer_podatkowy(&numer);
				}
			}
			struct firma* temp = (struct firma*)malloc(sizeof(struct firma));
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
			*check = 0;
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

void dodaj_do_listy_firm(struct menu** pmenu, struct firma** nowa) {

	if ((*pmenu)->fglowa == NULL) //sprawdzam czy istnieje ju¿ jakiœ element w liœcie 
	{
		(*pmenu)->fglowa = *nowa; // tworzê nowy element 
		(*pmenu)->fogon = (*pmenu)->fglowa;
		(*pmenu)->fglowa->nastepny = NULL; //ustawiam wartoœæ wskaŸnika na nastêpny element listy  jako nullptr, poniewa¿ moja lista dodaje nowe elementy na koñcu 
		(*pmenu)->fglowa->poprzedni = NULL; //z racji tego ¿e jest to pierwszy element listy wartoœæ wskaŸnika na poprzedni ustawiam jako nullpr

	}
	else //je¿eli istnieje jakiœ element w liœcie 
	{
		struct firma* obecny_ele = (struct firma*)malloc(sizeof(struct firma));
		obecny_ele = (*pmenu)->fogon; // Dodawanie na koniec listy
		(*pmenu)->fogon = *nowa;
		obecny_ele->nastepny = (*pmenu)->fogon;
		(*pmenu)->fogon->poprzedni = obecny_ele;
		(*pmenu)->fogon->nastepny = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Znajdz firme

struct firma** znajdz_firme(struct menu** pmenu, int pnumer) {
	struct firma* temp = (struct firma*)malloc(sizeof(struct firma));
	temp = (*pmenu)->fglowa;
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

bool sprawdz_numer_firmy(struct firma** glowa, int pnumer)

{   // Przeszukujemy czy nie ma ju¿ takiego numeru podatkowego
	struct firma* temp = (struct firma*)malloc(sizeof(struct firma));
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

void dane_firmy(void** dane)
{
	struct firma* pfirma = (struct firma*)malloc(sizeof(struct firma));
	pfirma = *dane;
	printf("                   NAZWA FIRMY: %s \n", pfirma->nazwa);
	printf("                   NUMER PODATKOWY: %d \n", pfirma->numer);
	pfirma = NULL;
}

bool wszystkie_firmy(struct firma* glowa, int numer) {

	printf("                   FIRMY W BAZIE DANYCH \n");
	struct firma* temp = (struct firma*)malloc(sizeof(struct firma));
	temp = glowa;
	int i = 1;
	if (temp == NULL) {
		printf("                   BRAK FIRM W BAZIE \n");
		return false;
	}
	else {
		while (temp)
		{
			if (temp->numer != numer) {
				printf("                   %d. %s %d \n", i, temp->nazwa, temp->numer);
				temp = temp->nastepny;
				i++;
			}
		}
	}
	temp = NULL;
	return true;
}

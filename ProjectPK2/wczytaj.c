#pragma once
#include "sprawdzanie.h"
#include "wczytaj.h"
#include "umowa.h"
#include "menu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Zaladowanie pliku do programu

// Zaladuj osobe
void zaladuj__osobe(struct menu** pmenu, char * buffer) {

	struct osoba* nowa = (struct osoba*)malloc(sizeof(struct osoba));

	char znak[] = ";";
	char* ptr = strtok(buffer, znak);
	int i = 0;
	// Uzupe³nienie danych osoby
	while (ptr != NULL)
	{
		if (i == 0) {
			strcpy(nowa->imie, ptr);	
		}
		else if (i == 1) {
			strcpy(nowa->nazwisko, ptr);
		}
		else { 
			nowa->numer = atoi(ptr);
		}
		i++;
		ptr = strtok(NULL, znak);
	}
	dodaj_do_listy_osob(&*pmenu, &nowa); // Dodanie do bazy osob
}

// Zaladuj firme
void zaladuj__firme(struct menu** pmenu, char* buffer) {

	struct firma* nowa = (struct firma*)malloc(sizeof(struct firma));

	char znak[] = ";";
	char* ptr = strtok(buffer, znak);
	int i = 0;
	// Uzupe³nienie danych firmy
	while (ptr != NULL)
	{
		if (i == 0) {
			strcpy(nowa->nazwa, ptr);
		}
		else {
			nowa->numer = atoi(ptr);
		}
		i++;
		ptr = strtok(NULL, znak);
	}
	dodaj_do_listy_firm(&*pmenu, &nowa); // Dodanie do bazy firm
}

// Zaladuj fakture
struct umowa* zaladuj_umowe(struct menu** pmenu, char* buffer) {

	struct umowa* nowa = (struct umowa*)malloc(sizeof(struct umowa));

	char znak[] = ";";
	char* ptr = strtok(buffer, znak);
	int i = 0;
	// Zczytwanie po kolei danych w zale¿nosci od przychodz¹cego elementu
	while (ptr != NULL)
	{
		switch (i) {
		case 0:
		{
			nowa->numer = atoi(ptr);
			break;
		}
		case 1:
		{   // Uzupe³nienie struktury zawieracej date i godzine umowy
			char info[3];
			char info1[4];
			strncpy(info, ptr, 2);
			info[2] = '\0';
				nowa->datawystawienia.tm_mday = atoi(info);
			strncpy(info, ptr+3, 2);
			info[2] = '\0';
			    nowa->datawystawienia.tm_mon = atoi(info);
			strncpy(info1, ptr + 6, 3);
			info1[3] = '\0';
				nowa->datawystawienia.tm_year = atoi(info1);
			strncpy(info, ptr + 10, 2);
			info[2] = '\0';
				nowa->datawystawienia.tm_hour = atoi(info);
			strncpy(info, ptr + 13, 2);
				nowa->datawystawienia.tm_min = atoi(info);
		
			int dzienroku = 0;
			int dtygodnia = dzienTygodnia(nowa->datawystawienia.tm_yday, nowa->datawystawienia.tm_mon, nowa->datawystawienia.tm_year, &dzienroku);
			nowa->datawystawienia.tm_sec = 0;
			nowa->datawystawienia.tm_yday = dzienroku;
			nowa->datawystawienia.tm_wday = dtygodnia;
			nowa->datawystawienia.tm_isdst = 1;
			break;
		}
		case 2:
		{ 
			// Uzupe³nienie struktury zawieracej date i godzine umowy
			char info[3];
			char info1[4];
			strncpy(info, ptr, 2);
			info[2] = '\0';
			nowa->datazakonczenia.tm_mday= atoi(info);
			strncpy(info, ptr + 3, 2);
			info[2] = '\0';
			nowa->datazakonczenia.tm_mon = atoi(info);
			strncpy(info1, ptr + 6, 3);
			info1[3] = '\0';
			nowa->datazakonczenia.tm_year = atoi(info1);
			strncpy(info, ptr + 10, 2);
			info[2] = '\0';
			nowa->datazakonczenia.tm_hour = atoi(info);
			strncpy(info, ptr + 13, 2);
			nowa->datazakonczenia.tm_min = atoi(info);

			int dzienroku = 0;
			int dtygodnia = dzienTygodnia(nowa->datazakonczenia.tm_yday, nowa->datazakonczenia.tm_mon, nowa->datazakonczenia.tm_year, &dzienroku);
			nowa->datazakonczenia.tm_sec = 0;
			nowa->datazakonczenia.tm_yday = dzienroku;
			nowa->datazakonczenia.tm_wday = dtygodnia;
			nowa->datazakonczenia.tm_isdst = 0;
			break;
		}
		case 3:
		{
			nowa->rodzaj = atoi(ptr);
			break;
		}
		case 4:
		{
		// Uzupe³nienie odpowiednio nabywcy w zaleznosci od rodzaju umowy (kto/kto)
		int numer_podatkowy = atoi(ptr);
		if (nowa->rodzaj == 1) {
			nowa->nabywca = znajdz_osobe(&(*pmenu), numer_podatkowy);
		}
		else if (nowa->rodzaj == 2) {
			nowa->nabywca = znajdz_osobe(&(*pmenu), numer_podatkowy);
		}
		else if (nowa->rodzaj == 3) {
			nowa->nabywca = znajdz_firme(&(*pmenu), numer_podatkowy);
		}
		else if (nowa->rodzaj == 4) {
			nowa->nabywca = znajdz_firme(&(*pmenu), numer_podatkowy);
		}

		break;
		}
		case 5:
		{
			// Uzupe³nienie odpowiednio dostawcy w zaleznosci od rodzaju umowy (kto/kto)
		int numer_podatkowy = atoi(ptr);
		if (nowa->rodzaj == 1) {
			nowa->dostawca = znajdz_osobe(&*pmenu, numer_podatkowy);
		}
		else if (nowa->rodzaj == 2) {
			nowa->dostawca = znajdz_firme(&*pmenu, numer_podatkowy);
		}
		else if (nowa->rodzaj == 3) {
			nowa->dostawca = znajdz_osobe(&*pmenu, numer_podatkowy);
		}
		else if (nowa->rodzaj == 4) {
			nowa->dostawca = znajdz_firme(&*pmenu, numer_podatkowy);
		}

		   break;
		}
		case 6:
		{
		   nowa->typ = atoi(ptr);
		    break;
		}
		case 7:
		{
			strcpy(nowa->element, ptr);
			break;
		}
		case 8:
		{
			
			nowa->kwotanetto = atof(ptr);
			break;
		}
		case 9:
		{
			nowa->stawkapodatku = atof(ptr);
			break;
		}
		case 10:
		{
			nowa->kwotabrutto = atof(ptr);
			break;
		}
		case 11:
		{
			nowa->stan = atoi(ptr);
			break;
		}
		}
		i++;
		ptr = strtok(NULL, znak);
	}
	return nowa; 
}

// Czytaj linia po lini
char* czytajlinie(FILE* input)
{
	char* buffer;
	int ch;
	int i = 0;
	size_t dlugosc = 0;

	buffer = malloc(dlugosc + 1);
	if (!buffer) return NULL;

	while ((ch = fgetc(input)) != '\n' && ch != EOF) // Zczytywanie do koñca lini lub konca pliku
	{
		dlugosc++;
		void* tmp = realloc(buffer, dlugosc + 1);
		if (tmp == NULL)
		{
			free(buffer);
			return NULL;
		}
		buffer = tmp;

		buffer[i] = (char)ch;
		i++;
	}
	buffer[i] = '\0';

	// Koniec
	if (ch == EOF && (i == 0 || ferror(input)))
	{
		free(buffer);
		return NULL;
	}
	return buffer;
}

// Zaladuj program
void zaladuj(struct menu** pmenu, FILE* input) {

	char znak = '#'; // Znak specjalny w celu odróznienia rodzaju danych
	int opcja = 0;
	char* s;
	while ((s = czytajlinie(input)) != NULL)
	{
		if (s[0] == znak) {
			memmove(s, s + 1, strlen(s)); 
			opcja++;
		}
		switch (opcja) {
            case 0:
			{   // Zerowe wystapienie znaku ladowanie bazy danych osob
				zaladuj__osobe(&(*pmenu), s);
				printf("                     LADOWANIE OSOBY \n");
				break;
			}
			case 1:
			{   // Pierwsze wystapienie znaku ladowanie bazy danych firm
				zaladuj__firme(&(*pmenu), s);
				printf("                     LADOWANIE FIRMY \n");
				break;
			}
			case 2:
			{   // Kolejne wystapienie znaku ladowanie bazy danych umow
				printf("                     LADOWANIE UMOWY \n");
				dodaj_do_listy(&(*pmenu), 1, s);
				break;
			}
		}
	}
	
}



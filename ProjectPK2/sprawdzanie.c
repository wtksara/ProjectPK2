#pragma once
#include "sprawdzanie.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprawdzanie informacji o dacie

void ustaw_date(struct tm* czasTM)
{
	int dzien, miesiac, rok, godzina, minuty, dzienroku;
	dzien = miesiac = rok = dzienroku = godzina = minuty = 0;
	while (sprawdz_date(&dzien, &miesiac, &rok) != true) {};
	int dtygodnia = dzienTygodnia(dzien, miesiac, rok, &dzienroku);
	if (dtygodnia == 6) {
		dtygodnia = 0;
	}
	else {
		dtygodnia++;
	}
	while (sprawdz_godzine(&godzina, &minuty) != true) {};

	czasTM->tm_mday = dzien;
	czasTM->tm_mon = miesiac - 1;
	czasTM->tm_year = rok - 1900;
	czasTM->tm_hour = godzina;
	czasTM->tm_min = minuty;
	czasTM->tm_sec = 0;
	czasTM->tm_yday = dzienroku;
	czasTM->tm_wday = dtygodnia;
	czasTM->tm_isdst = 1;
}

void pokaz_date(struct tm* czasTM) {

	if (czasTM->tm_mday < 10) {
		printf("0%d.", czasTM->tm_mday);
	}
	else {
		printf("%d.", czasTM->tm_mday);
	}
	if ((czasTM->tm_mon + 1) < 10) {
		printf("0%d.", czasTM->tm_mon + 1);
	}
	else {
		printf("%d.", czasTM->tm_mon + 1);
	}
	printf("%d ", czasTM->tm_year + 1900);

	if (czasTM->tm_hour < 10) {
		printf("0%d:", czasTM->tm_hour);
	}
	else {
		printf("%d:", czasTM->tm_hour);
	}

	if (czasTM->tm_min < 10) {
		printf("0%d", czasTM->tm_min);
	}
	else {
		printf("%d", czasTM->tm_min);
	}
}

bool poprawnosc(struct tm* czaswystawienia, struct tm* czaszakonczenia, int i ) {

	time_t czasw = mktime(czaswystawienia);
	time_t czasz = mktime(czaszakonczenia);
	if (difftime(czasz, czasw) < 0) {
		if (i == 1) {
			printf("                   DATA ZAKONCZENIA NIE MOZE BYC PRZED DATA ROZPOCZECIA \n");
		}
		return false;
	}
	else {
		return true;
	}
}

bool sprawdz_date(int* dzien, int* miesiac, int* rok) {

	int dd, mm, yy;
	dd = mm = yy = 0;
	printf("                   WPROWADZ DATE W FORMACIE (DD/MM/YYYY): ");
	scanf("%d/%d/%d", &dd, &mm, &yy);

	// Sprawdzenie roku
	if (yy >= 1900 && yy <= 2030)
	{
		//check month
		if (mm >= 1 && mm <= 12)
		{
			//check days
			if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
				printf("                   DATA JEST POPRAWNA \n");
			else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
				printf("                   DATA JEST POPRAWNA \n");
			else if ((dd >= 1 && dd <= 28) && (mm == 2))
				printf("                   DATA JEST POPRAWNA \n");
			else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
				printf("                   DATA JEST POPRAWNA \n");
			else {
				printf("                   DZIEN JEST NIEPOPRAWNY \n");
				return false;
			}
		}
		else
		{
			printf("                   MIESIAC JEST NIEPOPRAWNY \n");
			return false;
		}
	}
	else
	{
		printf("                   ROK JEST NIEPOPRAWNY \n");
		return false;
	}
	*dzien = dd;
	*miesiac = mm;
	*rok = yy;
	return true;
}

bool sprawdz_godzine(int* godzina, int* minuty) {

	printf("                   WPROWADZ GODZINE W FORMACIE (GG:MM): ");
	int gg, mm;
	gg = mm = 0;
	scanf("%d:%d", &gg, &mm);
	// Sprawdzanie godziny
	if (gg >= 0 && gg <= 23)
	{   // Sprawdzenie minut
		if (mm >= 0 && mm <= 59)
		{
			printf("                   GODZINA JEST POPRAWNA \n");
		}
		else {
			printf("                   ILOSC MINUT JEST NIEPOPRAWNA \n");
			return false;
		}
	}
	else {
		printf(" NIEPOPRAWNA GODZINA \n");
		return false;
	}
	*godzina = gg;
	*minuty = mm;
	return true;
}

int przestepny(int rok) {
	return ((rok % 4 == 0 && rok % 100 != 0) || rok % 400 == 0);
}

int dzienTygodnia(int dzien, int miesiac, int rok, int* dzienroku) {
	int dzienRoku;
	int yy, c, g;
	int wynik;
	int liczbaDni[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	dzienRoku = dzien + liczbaDni[miesiac - 1];
	if ((miesiac > 2) && (przestepny(rok) == 1))
		dzienRoku++;

	yy = (rok - 1) % 100;
	c = (rok - 1) - yy;
	g = yy + (yy / 4);
	wynik = (((((c / 100) % 4) * 5) + g) % 7);
	wynik += dzienRoku - 1;
	wynik %= 7;
	*dzienroku = dzienRoku;
	return wynik;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operacje dotycz¹ce poprawnosci wpisywanego stringa

void zmiana(int* slowo[]) {
	slowo = _strupr(slowo);
}

bool sprawdz_string(char * s) {

	int i;
	bool flag = true;
	for (i = 0; i < strlen(s) && flag == true; i++)
	{
		if (isalpha(s[i])) {
			flag = true;
		}
		else {
			flag = false;
		}
	}
	if (!flag) {
		printf("                   NAPIS SKLADA SIE TYLKO Z LITER \n");
		return false;
	}
	else
	{
		return true;
	}
}

bool sprawdz_numer_podatkowy( int *liczba) {

	char c;
	char* s = zczytajnumer();
	int i;
	bool flag = true;

	int dlugosc = strlen(s);
	if (dlugosc == 4) {
		for (i = 0; i < dlugosc && flag == true; i++)
		{
			if (isdigit(s[i])) {
				flag = true;
			}
			else {
				flag = false;
			}
		}
		if (!flag) {
			printf("                   NUMER PODATKOWY SKLADA SIE TYLKO Z CYFR \n");
			return false;
		}
		else
		{
			*liczba= atoi(s);
			return true;
		}
	}
	else {
		printf("                   NUMER PODATKOWY JEST 4-CYFROWY \n");
		return false;
	}
}

char* zczytajnumer()
{
	char* buffer;
	int ch;
	int i = 0;
	size_t dlugosc = 0;
	buffer = malloc(dlugosc + 1);
	if (!buffer) return NULL;

	while ((ch = getchar()) != '\n' && ch != EOF) // Zczytywanie do koñca lini lub konca pliku
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
	return buffer;

}

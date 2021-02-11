#pragma once
#include "zapisz.h"
#include "menu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Zapis daty do pliku
void zapisz_date(struct tm* pstruktura, FILE* output) {

	// Zapis daty w odpowiednim formacie 
	if (pstruktura->tm_mday < 10) {
		fprintf(output, "0%d.", pstruktura->tm_mday);
	}
	else {
		fprintf(output, "%d.", pstruktura->tm_mday);
	}

	if (pstruktura->tm_mon < 10) {
		fprintf(output, "0%d.", pstruktura->tm_mon);
	}
	else {
		fprintf(output, "%d.", pstruktura->tm_mon);
	}

	if (pstruktura->tm_year < 10) {
		fprintf(output, "00%d.", pstruktura->tm_year);
	}
	else if ((pstruktura->tm_year < 100) && (pstruktura->tm_year > 10)) {
		fprintf(output, "0%d.", pstruktura->tm_year);
	}
	else {
		fprintf(output, "%d.", pstruktura->tm_year);
	}

	if (pstruktura->tm_hour < 10) {
		fprintf(output, "0%d.", pstruktura->tm_hour);
	}
	else {
		fprintf(output, "%d.", pstruktura->tm_hour);
	}

	if (pstruktura->tm_min < 10) {
		fprintf(output, "0%d;", pstruktura->tm_min);
	}
	else {
		fprintf(output, "%d;", pstruktura->tm_min);
	}
}

// Zapis do pliku
void zapisz(struct menu** pmenu, FILE* output)
{
	struct osoba* posoba = (struct osoba*)malloc(sizeof(struct osoba));
	posoba = (*pmenu)->oglowa;
	if (!posoba) {}
	else {
		while (posoba) // Zapisywanie do pliku kolejno osob
		{
			fprintf(output, "%s;%s;%d\n", posoba->imie, posoba->nazwisko, posoba->numer);
			posoba = posoba->nastepny;
		}
	}
	posoba = NULL;
	struct firma* pfirma = (struct firma*)malloc(sizeof(struct firma));
	pfirma = (*pmenu)->fglowa;
	fprintf(output, "#");
	if (!pfirma) {}
	else {
		while (pfirma) // Zapisywanie do pliku kolejno firm
		{
			fprintf(output, "%s;%d\n", pfirma->nazwa, pfirma->numer);
			pfirma = pfirma->nastepny;
		}
	}
	pfirma = NULL;
	struct umowa* pumowa = (struct umowa*)malloc(sizeof(struct umowa));
	pumowa = (*pmenu)->glowa;
	fprintf(output, "#");
	if (!pumowa) {}
	else {
		while (pumowa) // Zapisywanie do pliku kolejno umow
		{
			fprintf(output, "%d;", pumowa->numer);
			zapisz_date(&pumowa->datawystawienia, output);
			zapisz_date(&pumowa->datazakonczenia, output);
			fprintf(output, "%d;", pumowa->rodzaj);
			struct osoba* pos = (struct osoba*)malloc(sizeof(struct osoba));
			struct firma* pfa = (struct firma*)malloc(sizeof(struct firma));
			if (pumowa->rodzaj == 1) {
				pos = pumowa->nabywca;
				fprintf(output, "%d;", pos->numer);
				pos = pumowa->dostawca;
				fprintf(output, "%d;", pos->numer);
			}
			else if (pumowa->rodzaj == 2) {
				pos = pumowa->nabywca;
				fprintf(output, "%d;", pos->numer);
				pfa = pumowa->dostawca;
				fprintf(output, "%d;", pfa->numer);
			}
			else if (pumowa->rodzaj == 3) {
				pfa = pumowa->nabywca;
				fprintf(output, "%d;", pfa->numer);
				pos = pumowa->dostawca;
				fprintf(output, "%d;", pos->numer);
			}
			else if (pumowa->rodzaj == 4) {
				pfa = pumowa->nabywca;
				fprintf(output, "%d;", pfa->numer);
				pumowa->dostawca;
				fprintf(output, "%d;", pfa->numer);
			}
			pos = NULL;
			pfa = NULL;
			fprintf(output, "%d;%s;%f;%f;%f;%d\n", pumowa->typ, pumowa->element, pumowa->kwotanetto, pumowa->stawkapodatku, pumowa->kwotabrutto, pumowa->stan);
			pumowa = pumowa->nastepny;
		}
	}
	pumowa = NULL;
}

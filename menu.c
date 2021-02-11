#pragma once
#include "menu.h"


// Ustawienie wszystkich wskaŸników i zmiennych
struct menu* ustaw_menu()
{
	struct menu* pmenu = malloc(sizeof(*pmenu));
	pmenu->glowa = pmenu->ogon =(struct umowa*)malloc(sizeof(struct umowa));
	pmenu->glowa = pmenu->ogon = NULL;
	pmenu->oglowa = pmenu->oogon = (struct osoba*)malloc(sizeof(struct osoba));
	pmenu->oglowa = pmenu->oogon = NULL; 
	pmenu->fglowa = pmenu->fogon =(struct firma*)malloc(sizeof(struct firma));
	pmenu->fglowa = pmenu->fogon = NULL;
	pmenu->licznik = 0;
	return pmenu;
}

// Funkcja odpowiedzialna za menu programu
bool pomoc(struct menu ** pmenu)
{
	printf("\n                     UMOWNIA \n\n ");
	printf("                   1.DODAJ UMOWE \n ");
	printf("                   2.ZNAJDZ I WYSWIETL INFORMACJE O UMOWIE \n ");
	printf("                   3.USUN UMOWE \n ");
	printf("                   4.ZAPLAC UMOWE \n ");
	printf("                   5.LISTA WSZYSTKICH UMOW W SYSTEMIE \n ");
	printf("                   6.HISTORIA ZAPLACONYCH UMOW \n ");
	printf("                   7.NIEZAPLACONE I PO DACIE UMOWY \n ");
	printf("                   8.AKTUALNE UMOWY DO ZAPLATY \n ");
	printf("                   9.ZAMKNIJ PROGRAM \n \n ");
	printf("                   WYBIERZ NUMER OPCJI \n ");

	char option;
	int liczba = 0;
	scanf(" %c", &option);
	while ((liczba = getchar()) != '\n');
	
		switch (option)
		{
		case '1':
		{
			system("cls");
			dodaj_do_listy(&(*pmenu),0,".");
			return true;
			break;
		}
		case '2':
		{
			system("cls");
			znajdz_umowe(&(*pmenu), 1);
			return true;
			break;
		}
		case '3':
		{
			system("cls");
			usun_umowe(&(*pmenu));
			return true;
			break;
		}
		case '4':
		{
			system("cls");
			zaplac_umowe(&(*pmenu));
			return true;
			break;
		}
		case '5':
		{
			system("cls");
			pokaz_umowe(&(*pmenu));
			return true;
			break;
		}

		case '6':
		{   int wartosc = 1;
			system("cls");
			printf("                   HISTORIA ZAPLACONYCH UMOW \n ");
			przedawnione_umowy(&(*pmenu),&wartosc);
			return true;
			break;
		}
		case '7':
		{
			system("cls");
			niezaplacone_umowy(&(*pmenu));
			return true;
			break;
		}
		case '8':
		{  
			int wartosc = 2;
			system("cls");
			printf("                   AKTUALNE UMOWY DO ZAPLATY \n ");
			przedawnione_umowy(&(*pmenu), &wartosc);
			return true;
			break;
		}
		case '9': {

			system("cls");
			printf("                   PROGRAM ZOSTANIE ZAMKNIETY \n "); 
			return false;
			break;
		}

		default: {

			system("cls");
			printf("                   NIEPOPRAWNY NUMER OPCJI \n ");
			return true;
			break;
		}
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Znalezienie faktury

struct umowa** znajdz_umowe(struct menu** pmenu, int wybor) {

	// Funkcja wyszukuj¹ca dana umowe

	printf("                   WPROWADZ NUMER SZUKANEJ UMOWY \n ");
	int pnumer;
	scanf("%d", &pnumer);

	struct umowa* temp = (struct umowa*)malloc(sizeof(struct umowa));
	temp = (*pmenu)->glowa;
	if (temp == NULL) {
		printf("                   BRAK UMOWY W SYSTEMIE \n");
		return NULL;
	}
	else {
		while (temp)
		{
			if (temp->numer == pnumer) {
				// Jesli u¿ytkownik chce wyœwietliæ szczegó³owe informacje na temat danej umowy
				if (wybor == 1) {
					printf("                   NUMER UMOWY : %d \n", temp->numer);
					printf("                   DATA WYSTAWIENIA : ");
					pokaz_date(&temp->datawystawienia);
					printf("\n                   DATA ZAKONCZENIA : ");
					pokaz_date(&temp->datazakonczenia);
					printf("\n\n                   RODZAJ UMOWY \n");
					if (temp->rodzaj == 1) {
						printf("                   OSOBA PRYWATNA - OSOBA PRYWATNA \n\n");

						printf("                   NABYWCA\n");
						dane_osoby(&temp->nabywca);
						printf("\n                   DOSTAWCA\n");
						dane_osoby(&temp->dostawca);
					}
					else if (temp->rodzaj == 2) {
						printf("                   OSOBA PRYWATNA - FIRMA \n\n");

						printf("                   NABYWCA\n");
						dane_osoby(&temp->nabywca);
						printf("\n                   DOSTAWCA\n");
						dane_firmy(&temp->dostawca);
					}
					else if (temp->rodzaj == 3) {
						printf("                   FIRMA - OSOBA PRYWATNA \n\n");

						printf("                   NABYWCA\n");
						dane_firmy(&temp->nabywca);
						printf("\n                   DOSTAWCA\n");
						dane_osoby(&temp->dostawca);
					}
					else if (temp->rodzaj == 4) {
						printf("                   FIRMA - FIRMA \n\n");

						printf("                   NABYWCA\n");
						dane_firmy(&temp->nabywca);
						printf("\n                   DOSTAWCA\n");
						dane_firmy(&temp->dostawca);
					}
					printf("\n                   TYP UMOWY: ");
					if (temp->typ == 1) {
						printf("UMOWY SPRZEDAZY \n");
					}
					else if (temp->typ == 2) {
						printf("UMOWY NA USLUGE \n");
					}

					printf("                   NAZWA : %s \n", temp->element);
					printf("                   KWOTA NETTO : %.2f \n", temp->kwotanetto);
					printf("                   STAWKA VAT : %.2f \n", temp->stawkapodatku);
					printf("                   KWOTA BRUTTO : %.2f \n", temp->kwotabrutto);
					printf("                   STAN : ");
					if (temp->stan == 1) {
						printf("ZAPLACONA \n");
					}
					else {
						printf("NIEZAPLACONA \n");
					}
				}
				return temp;
			}
			temp = temp->nastepny;
		}
		printf("                   NIE MA W BAZIE DANEJ FAKTURY \n");
		return NULL;
	}
}

void usun_umowe(struct menu** pmenu) {

	// Funkcja odpowiadaj¹ca za usuniecie danej umowy z bazy danych 
	printf("                   USUWANIE DANEJ UMOWY Z BAZY DANYCH \n ");
	struct umowa* dousuniecia = (struct umowa*)malloc(sizeof(struct umowa));
	dousuniecia = znajdz_umowe(&(*pmenu), 0);
	if (dousuniecia != NULL) {

		if (dousuniecia == (*pmenu)->glowa) {
			if (dousuniecia == (*pmenu)->ogon) {
				(*pmenu)->glowa = NULL;
				(*pmenu)->ogon = NULL;
			}
			else {
				(*pmenu)->glowa = (*pmenu)->glowa->nastepny;
				(*pmenu)->glowa->poprzedni = NULL;
			}
		}
		else
		{
			if (dousuniecia == (*pmenu)->ogon) {
				(*pmenu)->ogon = (*pmenu)->ogon->poprzedni;
				(*pmenu)->ogon->nastepny = NULL;
			}
			else {
				struct umowa* poprzednik = (struct umowa*)malloc(sizeof(struct umowa));
				struct umowa* nastepnik = (struct umowa*)malloc(sizeof(struct umowa));
			    poprzednik = dousuniecia->poprzedni;
				nastepnik = dousuniecia->nastepny;
				nastepnik->poprzedni = poprzednik;
				poprzednik->nastepny = nastepnik;
				poprzednik = NULL;
				nastepnik = NULL;
			}
		}
		dousuniecia->nabywca = NULL;
		dousuniecia->dostawca = NULL;
		dousuniecia->nastepny = NULL;
		dousuniecia->poprzedni = NULL;
		free(dousuniecia);
	}
}

void zaplac_umowe(struct menu** pmenu) {

	printf("                   ZAPLAC UMOWY \n ");
	// Funkcja w celu zmieniania stanu umowy na zap³acona
	struct umowa* temp = (struct umowa*)malloc(sizeof(struct umowa));
	temp = znajdz_umowe(&(*pmenu), 0);
	if (temp)
	{
		if (temp->stan == 1) {
			printf("                   UMOWA JUZ ZOSTALA ZAPLACONA \n");
		}
		else {
			temp->stan = 1;
			printf("                   ZAPLACONO UMOWE \n");
		}
	}
	else {
		printf("                               BRAK DANEJ UMOWY W SYSTEMIE \n");
	}
	temp = NULL;
}

void pokaz_umowe(struct menu** pmenu) {

	printf("                               LISTA WSZYSTKICH UMOWY\n ");
	struct umowa* temp = (struct umowa*)malloc(sizeof(struct umowa));
	temp = (*pmenu)->glowa;
	if (!temp) {
		printf("                               NIE MA UMOWY W SYSTEMIE \n");
	}
	else {

		printf("                   |  NUMER  |  TYP  |  NAZWA  |  KWOTA BRUTTO  | \n");

		while (temp)
		{
			printf("                    |   %d   |", temp->numer);
			int typy = temp->typ;
			if (temp->typ == 1) {
				printf(" UMOWY SPRZEDAZY |");
			}
			else if (temp->typ == 2) {
				printf(" UMOWY NA USLUGE |");
			}
			printf(" %s |", temp->element);
			printf(" %.2f  | \n", temp->kwotabrutto);
			temp = temp->nastepny;
		}
	}
	temp = NULL;
}

void przedawnione_umowy(struct menu** pmenu, int* wybor)
{
	// Pokaz wszystkie umowy po aktualnej dacie - historia umow
	// Wyswietlanie zakonczonych umów czyli te które zawczasu zosta³y ju¿ ZAPLACONE, lub sa juz po dacie i ZAPLACONE.
	struct umowa* temp = (struct umowa*)malloc(sizeof(struct umowa));
	temp = (*pmenu)->glowa;

	if (!temp) {
		printf("                               NIE MA TAKICH UMOWY W SYSTEMIE \n");
	}
	else {

		time_t czas;
		struct tm* czasinfo;
		time(&czas);
		czasinfo = localtime(&czas);
		printf("                   AKTUALNY CZAS :  %s \n", asctime(czasinfo));
		struct tm pczas = *czasinfo;
		printf("                   |  NUMER  |      TERMIN     |  KWOTA BRUTTO  | \n");
		while (temp)
		{
			bool status = poprawnosc(&pczas, &temp->datazakonczenia, 0);
			// Wyswietlanie zakonczonych umów czyli te które zawczasu zosta³y ju¿ ZAPLACONE, lub sa juz po dacie i ZAPLACONE.
			if (((*wybor == 1) && (status == false) && (temp->stan == 1)) || ((*wybor == 1) && (status != false) && (temp->stan == 1))) {

				printf("                   |    %d    | ", temp->numer);
				pokaz_date(&temp->datazakonczenia);
				printf(" | %f |\n", temp->kwotabrutto);
			}
			// Pozwala róznie¿ wyœwietliæ te umowy, które s¹ aktualne i do zap³acy
			else if ((*wybor == 2) && (status != false) && (temp->stan == 0)) {

				printf("                   |    %d    | ", temp->numer);
				pokaz_date(&temp->datazakonczenia);
				printf(" | %.2f  |\n", temp->kwotabrutto);
			}
			temp = temp->nastepny;
		}
	}
	temp = NULL;
}

void niezaplacone_umowy(struct menu** pmenu)
{
	// Pokaz wszystkie niezaplacone umowy po aktualnej dacie. 
	printf("                   NIEZAPLACONE UMOWY PO TERMINIE \n ");
	struct umowa* temp = (struct umowa*)malloc(sizeof(struct umowa));
	temp = (*pmenu)->glowa;
	if (!temp) {
		printf("                               NIE MA NIE ZAPLACONYCH UMOWY W SYSTEMIE \n");
	}
	else {
		time_t czas;
		struct tm* czasinfo;
		time(&czas);
		czasinfo = localtime(&czas);
		printf("                   AKTUALNY CZAS :  %s \n", asctime(czasinfo));
		struct tm pczas = *czasinfo;
		printf("                   |  NUMER  |      TERMIN     |  KWOTA BRUTTO  | \n");
		while (temp)
		{

			if ((poprawnosc(&pczas, &temp->datazakonczenia, 0) == false) && (temp->stan == 0)) {

				printf("                   |    %d    | ", temp->numer);
				pokaz_date(&temp->datazakonczenia);
				printf(" | %.2f  |\n", temp->kwotabrutto);
			}
			temp = temp->nastepny;
		}
	}
	temp = NULL;
}

void zwolnij_pamiec(struct menu** pmenu) {

	// Zwalnianie pamieci w programie
	struct umowa* pumowa = (struct umowa*)malloc(sizeof(struct umowa));
	pumowa = (*pmenu)->glowa;
	if (pumowa == NULL) {
		printf("                   ZWALNIANIE PAMIECI - UMOWY. BRAK UMOWY \n");
	}
	else {
		printf("                   ZWALNIANIE PAMIECI - UMOWY \n");
		while (pumowa != NULL)
		{
			if (pumowa == (*pmenu)->ogon) {
				(*pmenu)->glowa = NULL;
				(*pmenu)->ogon = NULL;
				pumowa->nabywca = NULL;
				pumowa->dostawca = NULL;
				pumowa->nastepny = NULL;
				pumowa->poprzedni = NULL;
				free(pumowa);
				pumowa = NULL;
			}
			else {
				if ((*pmenu)->glowa != NULL) {
					(*pmenu)->glowa = (*pmenu)->glowa->nastepny;
				}
				pumowa->nabywca = NULL;
				pumowa->dostawca = NULL;
				pumowa->nastepny = NULL;
				pumowa->poprzedni = NULL;
				free(pumowa);
				pumowa = (*pmenu)->glowa;
			}
		}

	}
	////////////////////////////////////////////////////////
	struct osoba* posoba = (struct osoba*)malloc(sizeof(struct osoba));
	posoba = (*pmenu)->oglowa;
	if (posoba == NULL) {
		printf("                   ZWALNIANIE PAMIECI - OSOBY. BRAK OSOB \n");
	}
	else {
		printf("                   ZWALNIANIE PAMIECI - OSOBY \n");
		while (posoba != NULL)
		{
			if (posoba == (*pmenu)->oogon) {
				(*pmenu)->oglowa = NULL;
				(*pmenu)->oogon = NULL;
				posoba->nastepny = NULL;
				posoba->poprzedni = NULL;
				free(posoba);
				posoba = NULL;
			}
			else {
				if ((*pmenu)->oglowa != NULL) {
					(*pmenu)->oglowa = (*pmenu)->oglowa->nastepny;
				}
				posoba->nastepny = NULL;
				posoba->poprzedni = NULL;
				free(posoba);
				posoba = (*pmenu)->oglowa;
			}
		}
	}
	////////////////////////////////////////////////////////
	struct firma* pfirma = (struct firma*)malloc(sizeof(struct firma));
	pfirma = (*pmenu)->fglowa;
	if (pfirma == NULL) {
		printf("                   ZWALNIANIE PAMIECI - FIRMY. BRAK FIRM \n");
	}
	else {
		printf("                   ZWALNIANIE PAMIECI - FIRMY \n");
		while (pfirma != NULL)
		{
			if (pfirma == (*pmenu)->fogon) {
				(*pmenu)->fglowa = NULL;
				(*pmenu)->fogon = NULL;
				pfirma->nastepny = NULL;
				pfirma->poprzedni = NULL;
				free(pfirma);
				pfirma = NULL;
			}
			else {
				if ((*pmenu)->fglowa != NULL) {
					(*pmenu)->fglowa = (*pmenu)->fglowa->nastepny;
				}
				pfirma->nastepny = NULL;
				pfirma->poprzedni = NULL;
				free(pfirma);
				pfirma = (*pmenu)->fglowa;
			}
		}
	}
}

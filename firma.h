#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "menu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///     Struktura, ktora zawiera szczegolowe informacje na temat firmy
struct firma {
    /// Nazwa firmy
    char nazwa[25];
    /// Numer podatkowy firmy
    int numer; 
    /// Wskaznik na poprzedni element typu firma
    struct firma* poprzedni;
    /// Wskaznik na kolejny element typu firma
    struct firma* nastepny;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tworzenie nowych elementów
///
///  \brief     Tworzenie nowych elementow typu firma
///  @param glowa     Referencja do glowy listy firm
///  @param wybor     Okresla czy firma ma byc z bazy, czy nowa
///  @param pnumer     Numer podatkowy w przypadku wyszukiwania z bazy
///  @param check     Zmienna pomocnicza w przypadku nie znalezenia danej firmy w bazie
///  @returns     Zwraca nowy element typu firma
///
struct firma* nowa_firma(struct firma** glowa, int* wybor, int* pnumer, int* check); // Utworzenie nowej firmy

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dodanie do listy
///
///  \brief     Dodanie do listy danej firmy
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param nowa     Referencja do nowo utworzonej firmy
///  @returns     Nic nie zwraca
///
void dodaj_do_listy_firm(struct menu** pmenu, struct firma** nowa); // Dodanie elemenetu firma do bazy firm

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Znajdz  firme
///
///  \brief     Znajdz firme po numerze podatkowym w liscie
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param pnume     Numer podatkowy szukanej firmy
///  @returns     Zwraca szukany element typu firma
///
struct firma** znajdz_firme(struct menu** pmenu, int pnumer); // Znajdz dana firme oraz zwróæ

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprawdzanie numeru podatkowego

///
///  \brief     Sprawdza czy dany numer podatkowy znajduje sie w bazie danych firm
///  @param glowa     Referencja do glowy listy firm
///  @param pnumer     Szukany numer podatkowy
///  @returns     Zwraca true lub false, w zaleznosci czy dzialanie sie powiedzie
///

bool sprawdz_numer_firmy(struct firma** glowa, int pnumer);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Wyœwietlanie danych
///
///  \brief     Wyswietl dane firmy 
///  @param glowa     Referencja do glowy listy firm
///  @param pnumer     Numer podatkowy danej firmy
///  @returns     Nic nie zwraca
///
void dane_firmy(void** dane); // Wyœwietl dane o firmie

///
///  \brief   Wyswietl wszystkie firmy w bazie danych firm, z wyjatkiem nowo dodanej firmy
///  @param glowa     Referencja do glowy listy firm
///  @param pnumer     Numer firm, ktora wlasnie zostala dodana do bazy
///  @returns     Zwraca true lub false, w zaleznosci czy dzialanie sie powiedzie
///
bool wszystkie_firmy(struct firma* glowa, int pnumer); // Wyswietla wszystkie firmy w bazie danych

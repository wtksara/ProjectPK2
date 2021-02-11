#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "menu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Struktura, ktora zawiera szczegolowe informacje na temat osoby
struct osoba {
    /// Imie 
    char imie[20];
    /// Nazwisko
    char nazwisko[20];
    /// Numer podatkowy
    int numer;
    /// Wskaznik na poprzedni element typu umowa
    struct  osoba* poprzedni;
    /// Wskaznik na kolejny element typu umowa
    struct  osoba* nastepny;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tworzenie nowych elementów
///
///  \brief     Tworzenie nowych elementow typu osoba
///  @param glowa     Referencja do glowy listy osob
///  @param wybor     Okresla czy osoba ma byc z bazy, czy nowa
///  @param pnumer     Numer podatkowy w przypadku wyszukiwania z bazy
///  @param check     Zmienna pomocnicza w przypadku nie znalezenia danej osoby w bazie
///  @returns     Zwraca nowy element typu osoba
///
struct osoba* nowa_osoba(struct osoba** glowa, int* wybor, int* pnumer, int* check); // Utworzenie nowej osoby

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dodanie do listy

///
///  \brief     Dodanie do listy danej osoby
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param nowa     Referencja do nowo utworzonej osoby
///  @returns     Nic nie zwraca
///
void dodaj_do_listy_osob(struct menu** pmenu, struct osoba** nowa); // Dodanie elemenetu osoba do bazy osob prywatnych

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Znajdz osobe 

///
///  \brief     Znajdz osobe po numerze podatkowym w liscie
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param pnumer     Numer podatkowy szukanej osoby
///  @returns     Zwraca szukany element typu osoba
///
struct osoba** znajdz_osobe(struct menu** pmenu, int pnumer); // Znajdz dana osobe oraz zwrosc

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprawdzanie numeru podatkowego

///
///  \brief     Sprawdza czy dany numer podatkowy znajduje sie w bazie danych osob
///  @param glowa     Referencja do glowy listy osob
///  @param pnumer     Szukany numer podatkowy
///  @returns     Zwraca true lub false, w zaleznosci czy dzialanie sie powiedzie
///

bool sprawdz_numer_osoby(struct osoba** glowa, int pnumer);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Wyœwietlanie danych

///
///  \brief     Wyswietl dane osobowe 
///  @param glowa     Referencja do glowy listy osob
///  @param pnumer     Numer podatkowy danej osoby
///  @returns     Nic nie zwraca
///
void dane_osoby(void** dane); // Wyœwietl dane osobowe

///
///  \brief     Wyswietl wszystkie osoby w bazie danych osob, z wyjatkiem nowo dodanej osoby
///  @param glowa     Referencja do glowy listy osob
///  @param pnumer     Numer osoby, ktora wlasnie zostala dodana do bazy
///  @returns     Zwraca true lub false, w zaleznosci czy dzialanie sie powiedzie
///
bool wszystkie_osoby(struct osoba* glowa, int pnumer); // Wyswietla wszystkie osoby w bazie danych
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sprawdzanie.h"
#include "wczytaj.h"

///      Struktura, ktora zawiera szczegolowe informacje na temat zawartej umowy

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct umowa
{
    /// Numer indywidualny - porzadkowy
    int numer; 
    /// Zawiera informacje o dacie, godzinie wystawienia umowy
    struct tm datawystawienia; 
    /// Zawiera informacje o dacie, godzinie zakonczenia lub dokonania uslugi/zakupu
    struct tm datazakonczenia; 
    /// Umowa strony
    ///
    /// 1.Osoba prywatna - Osoba prywatna
    ///
    /// 2.Osoba prywatna - Firma
    ///
    /// 3.Firma - Osoba prywatna
    ///
    /// 4.Firma - Firma
    int rodzaj;
    /// Nabywca
    void* nabywca; 
    /// Dostawca
    void* dostawca; 
    /// Umowa sprzedazy lub uslugi
    int typ; 
    /// Na co wystawiona umowa
    char element[25];
    /// Kwota bez podatku 
    float kwotanetto; 
    /// Stawka podatku
    float stawkapodatku; 
    /// Kwota z podatkiem 
    float kwotabrutto; 
    /// Zaplacone -1  / Niezaplacona - 0
    int stan;
    /// Wskaznik na poprzedni element typu umowa
    struct umowa* poprzedni;
    /// Wskaznik na kolejny element typu umowa
    struct umowa* nastepny;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tworzenie nowych elementów
///
///  \brief     Tworzenie nowych elementow typu umowa
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @returns     Zwraca nowy element typu umowa
///
struct umowa* nowa_umowa (struct menu** pmenu); // Utworzenie nowej umowy

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rodzaje umow

///
///  \brief     Okreslanie stron umowy
///  @param rodzaj     Numer rodzaju umowy
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param nowa_umowa     Referencja do umowy,ktora aktualnie jest tworzona  
///  @returns     Zwraca true lub false, w zaleznosci czy dzialanie sie powiedzie
///
bool kto_umowa(int* rodzaj, struct menu** pmenu, struct umowa** nowa_umowa); // Us³uga pomiedzy kim a kim

///
///  \brief     Okreslenie rodzaju umowy (sprzedaz / usluga)
///  @param typ     Numer typu umowy
///  @returns     Zwraca true lub false, w zaleznosci czy dzialanie sie powiedzie
///
bool rodzaj_umowy(int* typ); // Rodzaj umowy (usluga/sprzedaz)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dodanie do listy

///
///  \brief     Dodanie do listy danej umowy
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param i     Zmienna okreslajaca, czy jest wczytywywana umowa lub recznie tworzona
///  @param buffer     Bufor do wczytywania
///  @returns     Nic nie zwraca
///
void dodaj_do_listy(struct menu** pmenu, int i, char* buffer); // Dodanie elemenetu umowy do bazy umow




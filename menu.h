#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sprawdzanie.h"
#include "wczytaj.h"
#include "osoba.h"
#include "firma.h"
#include "umowa.h"

///      Struktura, ktora zawiera wskazniki do wszystkich baz w programie
///
///      Nie ma mozliwosci edycji bazy danych osob i firm jest ona jedynie w celu ulatwienia obslugi dodawania nowych umow w przypadku powtarzajacych sie osob/firm.
///
///      W momencie usuniecia danej umowy nie jest usuwana dana osoba/firma z bazy danych.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct menu {
    /// Glowa listy zawierajacej umowy
    struct umowa* glowa; 
    /// Ogon listy zawierajacej umowy
    struct umowa* ogon;
    /// Ilosc umow w bazie
    int licznik; 
    /// Glowa listy osob prywatnych
    struct osoba* oglowa;
    /// Ogon listy osob prywatnych
    struct osoba* oogon;
    /// Glowa listy firm
    struct firma* fglowa; 
    /// Ogon listy firm
    struct firma* fogon;
};

///
///  \brief    Ustawienie wszystkich wskaznikow i zmiennych
///  @returns     Zwraca nowo utworzona strukture typu menu
///
struct menu* ustaw_menu(); // Ustawienie wszystkich wskaznikow i zmiennych

///
///  \brief    Funkcja odpowiedzialna za menu programu
///  @param data     Referencja do menu, ktore zawiera glowy wszystkich list
///  @returns     Zwraca false, w przypadku checi zakonczenia programu, w innym przypadku true
///
bool pomoc(struct menu** pmenu); // Funkcja odpowiedzialna za menu programu

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// G³owne funkcje

///
///  \brief     Znajdz umowe po numerze porzadkowym w liscie
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param wybor     W przypadku gdy wartosc rowna 1, wyswietla informacje na temat danej umowy
///  @returns     Zwraca szukany element typu umowa
///
struct umowa** znajdz_umowe (struct menu** pmenu, int wybor); // Znajdz umowy

///
///  \brief     Usuwa dana umowe z listy
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @returns     Nic nie zwraca
///
void usun_umowe(struct menu** pmenu); // Usun umowe

///
///  \brief     Ustawia stan umowy na zaplacona
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @returns     Nic nie zwraca
///
void zaplac_umowe(struct menu** pmenu); // Zaplaæ umowe

///
///  \brief      Pokazuje wszystkie umowy w bazie
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @returns     Nic nie zwraca
///
void pokaz_umowe(struct menu** pmenu); // Pokaz wszystkie umowy w bazie

///
///  \brief     Pokazuje wszystkie umowy po aktualnej dacie - historia umow.
///  \brief     Wyswietlanie zakonczonych umow, czyli te ktore zawczasu zostaly juz zaplacone, lub sa juz po dacie i zaplacone.
///  \brief     Pozwala rozniez wyswietlic te umowy, ktore sa aktualne i do zaplaty
///
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param wybor     Zmienna, ktora wybiera rodzaj wyswietlania
///  @returns     Nic nie zwraca
///

void przedawnione_umowy(struct menu** pmenu, int* wybor); // Pokaz wszystkie umowy po aktualnej dacie - historia umow
// Wyswietlanie zakonczonych umow czyli te które zawczasu zosta³y ju¿ ZAPLACONE, lub sa juz po dacie i ZAPLACONE.
// Pozwala rozniez wyswietlic te umowy, ktore sa aktualne i do zaplaty

///
///  \brief     Pokazuje wszystkie niezaplacone umowy po aktualnej dacie
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @returns     Nic nie zwraca
///
void niezaplacone_umowy(struct menu** pmenu); // Pokaz wszystkie niezaplacone umowy po aktualnej dacie. 

///
///  \brief     Zwalnia pamiec w programie
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @returns     Nic nie zwraca
///

void zwolnij_pamiec(struct menu** pmenu); // Zwalnianie pamieci w programie

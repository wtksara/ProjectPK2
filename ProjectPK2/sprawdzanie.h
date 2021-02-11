#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "wczytaj.h"
#include "umowa.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operacje dotycz¹ce popranoœci daty
///
///  \brief     Ustawianie wprowadzonej przez uzytkownika daty
///  @param czasTM     Referencja do wlasnie ustawianej daty 
///  @returns Nic nie zwraca
///
void ustaw_date(struct tm* czasTM); // Ustawianie wprowadzonej przez u¿ytkownika daty

///
///  \brief     Wyswietla wskazana date 
///  @param data     Referencja do daty 
///  @returns     Nic nie zwraca
///
void pokaz_date(struct tm* data); // Wyswietla date 

///
///  \brief     Sprawdza czy data zakonczenia nie jest przed data wystawienia
///  @param czaswystawienia     Referencja do daty wystawienia
///  @param czaszakonczenia     Referencja do daty zakonczenia
///  @param i     Zmienna informujaca, czy nalezy wyswietlic komunikat czy nie 
///  @returns     Zwraca true lub false, w zaleznosci czy data zakonczenia jest po dacie wystawienia
///

bool poprawnosc(struct tm* czaswystawienia, struct tm* czaszakonczenia, int i); // Sprawdza czy data zakonczenia nie jest przed data wystawienia

///
///  \brief     Sprawdza czy wprowadzona data jest poprawna
///  @param dzien     Referencja do wprowadzonego dnia przez uzytkownika
///  @param miesiac     Referencja do wprowadzonego miesiaca przez uzytkownika
///  @param rok     Referencja do wprowadzonego roku przez uzytkownika
///  @returns     Zwraca true lub false, w zaleznosci czy data jest poprawna 
///

bool sprawdz_date(int* dzien, int* miesiac, int* rok);

///
///  \brief     Sprawdza czy wprowadzona godzina jest poprawna
///  @param godzina     Referencja do wprowadzonej godziny przez uzytkownika
///  @param minuty     Referencja do wprowadzonych minut przez uzytkownika
///  @returns     Zwraca true lub false, w zaleznosci czy godzina jest poprawna 
///

bool sprawdz_godzine(int* godzina, int* minuty);

///
///  \brief     Sprawdza, czy wprowadzony rok jest przestepny
///  @param rok     Wprowadzony rok przez uzytkownika
///  @returns     Zwraca 1 lub 0, w zaleznosci czy rok jest przestepny czy nie
///

int przestepny(int rok); 

///
///  \brief     Sprawdza na podstawie wprowadzonych danych jaki dzien tygodnia
///  @param dzien     Wprowadzony dzien przez uzytkownika
///  @param miesiac     Wprowadzony miesiac przez uzytkownika
///  @param rok     Wprowadzony rok przez uzytkownika
///  @param dzienroku     Referencja w celu wyliczenia dnia roku
///  @returns     Zwraca numer dnia tygodnia
///

int dzienTygodnia(int dzien, int miesiac, int rok, int* dzienroku);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operacje dotycz¹ce poprawnosci wpisywanego stringa

///
///  \brief     Zamienia litery w danym slowie na duze
///  @param slowo     Referencja do danego slowa
///  @returns     Nic nie zwraca
///
void zmiana(int* slowo[]); // Zmienia litery w slowie na du¿e litery

///
///  \brief     Sprawdza czy wprowadzony napis jest zlozony tylko z liter
///  @param slowo     Referencja do danego slowa
///  @returns     Zwraca true lub false, w zaleznosci czy napis jest poprawny
///

bool sprawdz_string(char* s); // Sprawdza czy wprowadzony napis jest zlozony tylko z liter

///
///  \brief     Sprawdza czy numer podatkowy ma dlugosc 4 i czy jest zlozony z cyfer
///  @param slowo     Referencja do danej liczby
///  @returns     Zwraca true lub false, w zaleznosci czy numer podatkowy jest poprawny
///

bool sprawdz_numer_podatkowy(int* liczba); // Sprawdza czy numer podatkowy ma d³ugosc 4 i czy jest zlozony z cyfer

///
///  \brief     Zczytywanie numeru podatkowego
///  @returns     Zwraca wpisany przez uzytkownika numer podatkowy
///
char* zczytajnumer(); // Zczytywanie numeru

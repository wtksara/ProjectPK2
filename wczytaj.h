#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "menu.h"

///
///  \brief    Czyta linia po lini z pliku
///  @param input     Plik wejsciowy do odczytu 
///  @returns     Zwraca lancuch znakow
///
char* czytajlinie(FILE* input); // Czytaj linia po lini

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Zaladowanie pliku do programu

///  \brief    Laduje dana osobe z pliku do bazy osob
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param buffer     Lancuch znakowy zawierajacy dane do odczytu
///  @returns     Nic nie zwraca
///
void zaladuj__osobe(struct menu** pmenu, char* buffer); // Zaladuj osobe do programu

///  \brief    Laduje dana firme z pliku do bazy firm
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param buffer     Lancuch znakowy zawierajacy dane do odczytu
///  @returns     Nic nie zwraca
///
void zaladuj__firme(struct menu** pmenu, char* buffer); // Zaladuj firme do programu

///  \brief    Laduje dana umowe z pliku do bazy umow
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param buffer     Lancuch znakowy zawierajacy dane do odczytu
///  @returns     Zwraca nowa elemenet typu umowa
///

struct umowa* zaladuj_umowe(struct menu** pmenu, char* buffer); // Zaladuj umowe do programu

///  \brief    Zaladowanie danych z pliku do programu
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param input     Plik wejsciowy do odczytu 
///  @returns     Nic nie zwraca
///
void zaladuj(struct menu** pmenu, FILE * input); // Zaladowanie danych z pliku do programu


#pragma once
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "menu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Zapisywanie pliku

///
///  \brief    Zapisuje date do pliku
///  @param data     Referencja do danej daty 
///  @param output     Plik wyjsciowy do zapisu 
///  @returns     Nic nie zwraca
///
void zapisz_date(struct tm* pstruktura, FILE* output);// Zapis daty do pliku

///
///  \brief    Zapisuje dane z programu do pliku
///  @param pmenu     Referencja do menu, ktore zawiera glowy wszystkich list
///  @param output     Plik wyjsciowy do zapisu 
///  @returns     Nic nie zwraca
///
void zapisz(struct menu** pmenu, FILE* output); // Zapisz program do pliku
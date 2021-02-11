#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "wczytaj.h"
#include "umowa.h"
#include "sprawdzanie.h"

///  \brief    Przykladowy plik wejsciowy txt
#define WEJSCIOWY_PLIK "input.txt"
///  \brief    Przykladowy plik wyjsciowy txt
#define WYJSCIOWY_PLIK "output.txt"

// Wyœwietlanie danych
///
///  \brief     Uruchomienie programu z dwoma parametrami. Pierwszy to plik wejsciowy txt, drugi plik wyjsciowy txt.

int main(int argc, char** argv)
{
 
    setvbuf(stdout, NULL, _IONBF, 0);
    if (argc > 2) {

        FILE* INPUT;
        fopen_s(&INPUT,argv[1], "r");
        
        if (INPUT==NULL)
        {
            printf("                   NIE MOZNA OTWORZYC PLIKU WEJSCIOWEGO \n");
            return 0;
        }
        fclose(INPUT);

        FILE* OUTPUT;
        fopen_s(&OUTPUT,argv[2], "w");

        if (OUTPUT == NULL)
        {
                printf("                   NIE MOZNA OTWORZYC PLIKU WYJSCIOWEGO \n");
                return 0;
        }
        fclose(OUTPUT);

        struct menu* nowe_menu = ustaw_menu();
        INPUT = fopen(argv[1], "r");
        zaladuj(&nowe_menu, INPUT);
        fclose(INPUT);
  
        bool option = pomoc(&nowe_menu);
        while (option != false)
        {
                    option = pomoc(&nowe_menu);
        }

        OUTPUT = fopen(argv[2], "w");
        printf("                   ZAPISYWANIE DO PLIKU WYJSCIOWEGO \n");
        zapisz(&nowe_menu, OUTPUT);
        fclose(OUTPUT);
        zwolnij_pamiec(&nowe_menu);
        free(nowe_menu); 
        printf("                   KONIEC PROGRAMU \n");
       
    }
    else {
        if (argc > 1) {
            printf("                   NIE PODALES SCIEZKI DO PLIKU WEJSCIOWEGO LUB WYJSCIOWEGO \n");    
        }
        else {
            printf("                   NIE PODALES SCIEZKI DO PLIKU WEJSCIOWEGO I WYJSCIOWEGO \n");
        }
    }

   
}
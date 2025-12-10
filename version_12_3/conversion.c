#include <stdio.h>
#include <string.h>
#include "conversion.h"

// Max dlzka pre int v trojkovej sustave
#define MAX_TROJKOVE_CISLO 19 

// Prevod z trojkovej do desiatkovej sustavy
int trojkove_na_desiatkovu(const char* trojkove_cislo) {
    int dlzka = strlen(trojkove_cislo);

    // Overenie dlzky
    if (dlzka > MAX_TROJKOVE_CISLO) {
        printf("    [CHYBA] Trojkove cislo '%s' je prilis dlhe!\n", trojkove_cislo);
        return -1;
    }

    int vysledok = 0;

    // Hornerova schema: postupne nasobime vysledok 3 a pripocitavame cifry
    for (int i = 0; trojkove_cislo[i] != '\0'; i++) {
        int cifra = trojkove_cislo[i] - '0'; // Konverzia znaku na cislo
        vysledok = vysledok * 3 + cifra; // Nasobenie 3 a pridanie cifry - Hornerova schema
    }

    return vysledok;
}
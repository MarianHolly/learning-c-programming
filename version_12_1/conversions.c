#include <stdio.h>
#include <string.h>
#include "conversions.h"

/**
 * trojkova_na_desatkovu()
 *
 * IMPLEMENTÁCIA: Hornerova schéma
 *
 * Algoritmus:
 *   1. Validovať vstup
 *   2. Pre každú cifru zľava doprava:
 *      - vysledok = vysledok * 3 + (cifra - '0')
 *   3. Vrátiť vysledok
 *
 * Príklad: "2101"
 *   vysledok = 0
 *   '2': vysledok = 0*3 + 2 = 2
 *   '1': vysledok = 2*3 + 1 = 7
 *   '0': vysledok = 7*3 + 0 = 21
 *   '1': vysledok = 21*3 + 1 = 64
 *   Výsledok: 64
 */
int trojkova_na_desatkovu(const char *trojkove_cislo) {
    // Validácia vstupu
    if (trojkove_cislo == NULL || !je_platne_trojkove_cislo(trojkove_cislo)) {
        return -1;
    }

    int vysledok = 0;

    // Hornerova schéma: pre každú cifru
    for (int i = 0; trojkove_cislo[i] != '\0'; i++) {
        int cifra = trojkove_cislo[i] - '0';  // Konverzia znaku na číslo
        vysledok = vysledok * 3 + cifra;
    }

    return vysledok;
}

/**
 * desatkova_na_trojkovu()
 *
 * IMPLEMENTÁCIA: Opakované delenie modulo
 *
 * Algoritmus:
 *   1. Ošetriť špeciálny prípad (cislo == 0)
 *   2. Zbierať zvyšky pomocou modulo 3 (od konca)
 *   3. Obrátiť reťazec (lebo zbieranie je od konca)
 *   4. Ukončiť reťazec '\0'
 *
 * Príklad: 64 → "2101"
 *   64 % 3 = 1, 64 / 3 = 21   → cifra '1'
 *   21 % 3 = 0, 21 / 3 = 7    → cifra '0'
 *   7 % 3 = 1, 7 / 3 = 2      → cifra '1'
 *   2 % 3 = 2, 2 / 3 = 0      → cifra '2'
 *   Zbierané: '1', '0', '1', '2'
 *   Po obrátení: '2', '1', '0', '1' = "2101"
 */
void desatkova_na_trojkovu(int cislo, char *vysledok) {
    // Ošetriť nulu
    if (cislo == 0) {
        vysledok[0] = '0';
        vysledok[1] = '\0';
        return;
    }

    // Zbierat zvyšky (cifry budú v opačnom poradí)
    int index = 0;
    int temp = cislo;

    while (temp > 0) {
        int zvysok = temp % 3;
        vysledok[index] = '0' + zvysok;  // Konverzia čísla na znak
        temp = temp / 3;
        index++;
    }

    // Ukončiť reťazec
    vysledok[index] = '\0';

    // Obrátiť reťazec (lebo sme ho zbierali od konca)
    // Swap algoritmus: od začiatku a od konca smerom k stredu
    for (int i = 0, j = index - 1; i < j; i++, j--) {
        char temp_char = vysledok[i];
        vysledok[i] = vysledok[j];
        vysledok[j] = temp_char;
    }
}

/**
 * je_platne_trojkove_cislo()
 *
 * IMPLEMENTÁCIA: Validácia každého znaku
 *
 * Algoritmus:
 *   1. Skontrolovať či nie je reťazec prázdny
 *   2. Pre každý znak: ak je mimo '0' až '2', vrátiť 0
 *   3. Ak všetky znaky sú v poriadku, vrátiť 1
 */
int je_platne_trojkove_cislo(const char *retazec) {
    // Skontrolovať prázdny reťazec
    if (retazec == NULL || retazec[0] == '\0') {
        return 0;
    }

    // Prejsť všetky znaky
    for (int i = 0; retazec[i] != '\0'; i++) {
        char znak = retazec[i];
        // Cifra musí byť '0', '1' alebo '2'
        if (znak < '0' || znak > '2') {
            return 0;
        }
    }

    // Ak sme sa dostali sem, všetky znaky sú platné
    return 1;
}

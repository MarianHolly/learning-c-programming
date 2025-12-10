#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"
#include "matrix.h"
#include "conversion.h"

// Maximalna dlzka nazvu suboru
#define MAX_NAZOV_SUBORU 256


/*
 * =============================================================================
 * PROGRAM: Analyza stvorcovej matice v trojkovej sustave
 * =============================================================================
 *
 * Pouzivatel zadava rozmer stvorcovej matice a nazov suboru,
 * v ktorom su ulozene prvky matice v trojkovej sustave.
 * Program overi spravnost vstupov a nacita maticu do dynamicky alokovanej
 * pamate (prvky prevadza do desiatkovej sustavy).
 * Nasledne pre kazdy diagonalny prvok matice porovna jeho hodnotu
 * s hodnotou suctu ostatnych prvkov v tom istom stlpci.
 * Vysledky vypise na obrazovku v oboch sustavach.
 * Na zaver uvolni alokovanu pamat.
 *
 * =============================================================================
 */


 // Funkcia na vypis informacii o testovacich suboroch
void informacie_o_suboroch();


int main(){
    printf("=============================================================\n");
    printf("       ANALYZA STVORCOVEJ MATICE V TROJKOVEJ SUSTAVE\n");
    printf("=============================================================\n\n");


    // Premenne
    char nazov_suboru[MAX_NAZOV_SUBORU];  // Buffer pre nazov suboru
    char buffer[MAX_NAZOV_SUBORU];        // Univerzalny buffer pre fgets()
    int rozmer_matice;                     // Rozmer NxN matice
    int **p_matica = NULL;                 // Pointer na dynamicky alokovanu maticu
    size_t len;                            // Pomocna premenna pre strlen()


    // =============================================================================
    // KROK 0: Ponuka pouzivatelovi
    printf("Chcete zobrazit informacie o testovacich suboroch? (a/n): ");

    // Nacitaj odpoved pouzivatela
    if(fgets(buffer, MAX_NAZOV_SUBORU, stdin) != NULL){
        odstran_newline(buffer);

        if(buffer[0] == 'a' || buffer[0] == 'A'){
            informacie_o_suboroch();
        } else {
            printf("\n");
        }
    }


    // =============================================================================
    // KROK 1: Pouzivatelov vstup = rozmer matice
    printf("=======> Vstupy od pouzivatela\n\n");

    printf("Input 1: Zadajte rozmer matice (n pre maticu nxn): ");

    // Nacitaj cely riadok do bufferu
    fgets(buffer, 100, stdin);
    odstran_newline(buffer);

    // Kontrola ci buffer nie je prazdny
    len = strlen(buffer);
    if (len == 0) {
        printf("    [CHYBA] Prazdny vstup! Rozmer nemoze byt prazdny.\n");
        return 1;
    }

    // Konverzia retazca na cislo
    if (sscanf(buffer, "%d", &rozmer_matice) != 1) {
        printf("    [CHYBA] Vstup musi byt cele cislo (zadane: '%s')\n", buffer);
        return 1;
    }

    // Validacia rozmeru (musi byt kladne cislo)
    if (rozmer_matice <= 0) {
        printf("    [CHYBA] Rozmer musi byt kladne cislo (zadane: %d)\n",
               rozmer_matice);
        return 1;
    }

    printf("    [OK] Rozmer: %d x %d\n\n", rozmer_matice, rozmer_matice);


    // =============================================================================
    // KROK 2: Pouzivatelov vstup = nazov suboru
    printf("Input 2: Zadaj nazov suboru s maticou: ");

    // Nacitaj nazov suboru
    fgets(nazov_suboru, MAX_NAZOV_SUBORU, stdin);
    odstran_newline(nazov_suboru);

    // Kontrola ci nazov nie je prazdny
    if(strlen(nazov_suboru) == 0){
        printf("    [CHYBA] Nazov suboru nemoze byt prazdny!\n");
        return 1;
    }

    printf("    [OK] Nazov suboru: %s\n", nazov_suboru);


    // =============================================================================
    // KROK 3: Validacia vstupov
    printf("\n=======> Validacia suboru\n\n");

    printf("Validacia 1: Pocitanie prvkov v subore...\n");
    int pocet_prvkov = pocet_prvkov_v_subore(nazov_suboru);
    if (pocet_prvkov == -1){
        printf("    [CHYBA] Validacia zlyhala.\n");
        return 1;
    }
    printf("\n");

    printf("Validacia 2: Validacia rozmerov...\n");
    if(validuj_rozmer_matice(rozmer_matice, pocet_prvkov) != 0) {
        printf("    [CHYBA] Validacia zlyhala.\n");
        return 1;

    }
    printf("\n");

    printf("Validacia 3: Validacia trojkovych cisiel...\n");
    if(validuj_prvky_matice(nazov_suboru, rozmer_matice) != 0){
        printf("    [CHYBA] Validacia zlyhala.\n");
        return 1;
    }


    // =============================================================================
    // KROK 4: Alokacia a nacitanie matice
    printf("\n=======> Alokacia a nacitanie\n\n");

    printf("Proces 1: Alokacia pamate...\n");
    p_matica = alokuj_maticu(rozmer_matice);
    if (p_matica == NULL){
        return 1;
    }
    printf("\n");

    printf("Proces 2: Nacitanie a konverzia prvkov...\n");
    if(nacitaj_maticu_zo_suboru(nazov_suboru, rozmer_matice, p_matica) != 0){
        uvolni_maticu(p_matica, rozmer_matice);
        return 1;
    }


    // =============================================================================
    // KROK 5: Vypis matice v desiatkovej sustave
    printf("\n=======> Matica v desiatkovej sustave\n\n");
    vypis_maticu(p_matica, rozmer_matice);


    // =============================================================================
    // KROK 6: Analyza diagonaly
    printf("\n=======> Analyza diagonaly\n");
    analyzuj_diagonalu(p_matica, rozmer_matice);


    // =============================================================================
    // KROK 7: Uvolnenie pamate
    printf("\n=======> Uvolnenie pamate\n\n");
    uvolni_maticu(p_matica, rozmer_matice);


    printf("=============================================================\n");
    printf("                      PROGRAM UKONCENY\n");
    printf("=============================================================\n\n");
    return 0;
}

void informacie_o_suboroch(){
    // Informacia o moznych suboroch na testovanie
    printf("\n    [TESTOVACIE SUBORY]\n");
    printf("    -------------------\n");
    printf("    Funkcne testy (validne vstupy):\n");
    printf("           - matica_n1.txt => 1x1 matica\n");
    printf("           - matica_n2.txt => 2x2 matica\n");
    printf("           - matica_n3.txt => 3x3 matica\n");
    printf("           - matica_n4.txt => 4x4 matica\n");
    printf("           - matica_large.txt => 3x3 matica s velkymi cislami \n");
    printf("\n");

    printf("    Testy robustnosti (chybne vstupy):\n");
    printf("           - empty.txt => prazdny subor\n");
    printf("           - invalid_digit.txt => matica 3x3 obsahuje cifry, ktore nepatria do trojkovej sustavy\n");
    printf("           - letters.txt => matica 3x3 obsahuje pismena\n");
    printf("           - negative.txt => matica 3x3 obsahuje negativne cisla \n");
    printf("           - not_matrix.txt => subor obsahuje 11 prvkov\n");
    printf("           - too_long.txt => matica 3x3 obsahuje pridlhe cislo\n");
    printf("\n");
}

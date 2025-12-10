#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "conversion.h"

// Alokacia pamate pre stvorcovu maticu
// 1. Alokuj pole pointerov na riadky
// 2. Pre kazdy riadok alokuj pole int prvkov
int** alokuj_maticu(int rozmer_matice) {
    // Alokuje pole pointerov (jeden pointer na kazdy riadok)
    int** p_matica = malloc(rozmer_matice * sizeof(int*));

    if (p_matica == NULL) {
        printf("    [CHYBA] Nepodarilo sa alokovat pamat\n");
        return NULL;
    }

    // Alokuje pamat pre jednotlive riadky
    for (int i = 0; i < rozmer_matice; i++) {
        p_matica[i] = malloc(rozmer_matice * sizeof(int));

        if (p_matica[i] == NULL) {
            printf("    [CHYBA] Nepodarilo sa alokovat pamat pre riadok %d\n", i);

            // Uvolni uz alokovane riadky 
            for (int j = 0; j < i; j++) {
                free(p_matica[j]);
            }
            free(p_matica);

            return NULL;
        }

    }

    printf("    [OK] Matica %dx%d alokovana\n", rozmer_matice, rozmer_matice);
    return p_matica;
}


// Uvolnenie pamate alokovanej pre maticu - opacny proces k alokacii
// 1. Uvolni jednotlive riadky
// 2. Uvolni pole pointerov
void uvolni_maticu(int** p_matica, int rozmer_matice) {
    // Uvolni jednotlive riadky
    for (int i = 0; i < rozmer_matice; i++) {
        if (p_matica[i] != NULL) {
            free(p_matica[i]);
        }
    }

    // Uvolni pole pointerov
    free(p_matica);
    printf("    [OK] Pamat uvolnena\n");
};


// Nacitanie a konverzia matice zo suboru
// 1. Cita jednotlive trojkove cisla zo suboru
// 2. Konvertuje ich na desiatkove cisla pomocou funkcie trojkove_na_desiatkovu
// 3. Ulozi ich do alokovanej matice
int nacitaj_maticu_zo_suboru(const char* nazov_suboru, int rozmer_matice, int** p_matica) {
    FILE* p_subor = fopen(nazov_suboru, "r");

    if (p_subor == NULL) {
        printf("    [CHYBA] Nemam pristup k suboru '%s'.\n", nazov_suboru);
        return -1;
    }

    // Buffer pre nacitanie jedneho trojkoveho cisla
    char buffer[50];

    // Nacitanie matice po prvkoch
    for (int i = 0; i < rozmer_matice; i++) {
        for (int j = 0; j < rozmer_matice; j++) {

            if (fscanf(p_subor, "%49s", buffer) == 1) {
                // Konverzia z trojkovej do desiatkovej sustavy
                int hodnota = trojkove_na_desiatkovu(buffer);
                if (hodnota == -1) {
                    fclose(p_subor);
                    return -1;
                }
                p_matica[i][j] = hodnota;

            }
            else {
                printf("    [CHYBA] Nepodarilo sa nacitat prvok matice na pozicii [%d][%d]\n", i, j);
                fclose(p_subor);
                return -1;
            }
        }
    }

    fclose(p_subor);
    printf("    [OK] Matica nacitana a konvertovana\n");
    return 0;
};


// Vypis maticu na obrazovku
void vypis_maticu(int** p_matica, int rozmer_matice) {

    for (int i = 0; i < rozmer_matice; i++) {
        printf("   ");

        for (int j = 0; j < rozmer_matice; j++) {
            printf("%5d ", p_matica[i][j]);  // Sirka 5 znakov pre zarovnanie
        }

        printf("\n");
    }

    printf("\n");
};


// Vypocet suctu stlpca bez diagonalneho prvku
// Diagonalny prvok je na pozicii [i][i] pre stlpec index_stlpca
int sucet_stlpca_bez_diagonaly(int** p_matica, int rozmer_matice, int index_stlpca) {
    int sucet = 0;

    // Prejdi vsetky riadky v danom stlpci
    for (int i = 0; i < rozmer_matice; i++) {

        // Preskoc diagonalny prvok (riadok == stlpec)
        if (i != index_stlpca) {
            sucet += p_matica[i][index_stlpca];
        }
    }

    return sucet;
}


// Analyza kazdého prvku na hlavnej diagonale
// 1. Vypocita sucet ostatnych prvkov v tom istom stlpci (bez diagonalneho)
// 2. Urci vztah diagonalneho prvku k suctu (>, <, =)
// 3. Vypise vysledky
void analyzuj_diagonalu(int** p_matica, int rozmer_matice) {
    printf("\n================ ANALYZA DIAGONALY ================\n");
    printf("Vztah diagonalneho prvku voci suctu ostatnych prvkov v stlpci\n\n");

    // Specialny pripad matice 1x1
    if (rozmer_matice == 1) {
        printf("Specialny pripad: Matica 1x1\n");
        printf("Diagonalny prvok [0,0]: %d\n", p_matica[0][0]);
        printf("Sucet ostatnych je 0. \nIch vztah je 0 < %d\n", p_matica[0][0]);
    }
    else {
        // Standardny pripad matice nxn, n>1
        for (int i = 0; i < rozmer_matice; i++) {
            int diagonalny_prvok = p_matica[i][i];

            int sucet_stlpca = sucet_stlpca_bez_diagonaly(p_matica, rozmer_matice, i);

            // Urcenie vztahu
            const char* vztah_symbol;
            int rozdiel;

            if (diagonalny_prvok > sucet_stlpca) {
                vztah_symbol = ">";
            }
            else if (diagonalny_prvok < sucet_stlpca) {
                vztah_symbol = "<";
            }
            else {
                vztah_symbol = "=";
            }

            // Vypis
            printf("Diagonalny prvok [%d, %d]:   %d\n", i, i, diagonalny_prvok);
            printf("Sucet ostatnych prvkov:      %d\n", sucet_stlpca);
            printf("Vztah:                       %d %s %d\n\n", diagonalny_prvok, vztah_symbol, sucet_stlpca);

        }
    }

}

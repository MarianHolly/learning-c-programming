#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "conversions.h"
#include "utils.h"

int main() {
    char nazov_suboru[256];
    int n = 0;
    int **matica = NULL;

    // Privítanie
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║   ANALÝZA ŠTVORCOVEJ MATICE V TROJKOVEJ SÚSTAVE        ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");

    // Krok 1: Zistiť od užívateľa názov súboru
    printf("Zadajte názov vstupného súboru: ");
    scanf("%255s", nazov_suboru);

    // Krok 2: Načítať maticu zo súboru
    printf("\nNačítavanie matice...\n");
    int vysledok = nacitaj_maticu(nazov_suboru, &n, &matica);

    if (vysledok != 0) {
        printf("\nChyba pri načítavaní matice. Program sa ukončí.\n");
        return 1;
    }

    // Krok 3: Vypísať načítanú maticu
    vypis_maticu(matica, n);

    // Krok 4: Analýza diagonálnych prvkov
    printf("========== ANALÝZA DIAGONÁLY ==========\n\n");

    for (int i = 0; i < n; i++) {
        int hodnota_prvku = matica[i][i];
        int sucet_stlpca = vypocitaj_sucet_stlpca_bez_diagonaly(matica, n, i);

        // Konvertovať do trojkovej sústavy
        char trojkovy_prvok[256];
        char trojkovy_sucet[256];
        desatkova_na_trojkovu(hodnota_prvku, trojkovy_prvok);
        desatkova_na_trojkovu(sucet_stlpca, trojkovy_sucet);

        // Porovnať
        Vztah vztah = porovnaj(hodnota_prvku, sucet_stlpca);
        int rozdiel = (hodnota_prvku > sucet_stlpca) ? (hodnota_prvku - sucet_stlpca) : (sucet_stlpca - hodnota_prvku);

        // Vypísať výsledky
        printf("───────────────────────────────────────────\n");
        printf("Diagonálny prvok [%d,%d]:\n", i, i);
        printf("  Hodnota:                    %s₃ = %d₁₀\n", trojkovy_prvok, hodnota_prvku);
        printf("  Súčet ostatných v stĺpci:  %s₃ = %d₁₀\n", trojkovy_sucet, sucet_stlpca);
        printf("  Vzťah:                      %d %s %d (%s o %d)\n",
               hodnota_prvku,
               vztah_na_symbol(vztah),
               sucet_stlpca,
               vztah_na_retazec(vztah),
               rozdiel);
        printf("\n");
    }

    printf("==========================================\n\n");

    // Krok 5: Uvoľniť pamäť
    printf("Uvoľňovanie pamäte...\n");
    uvolni_maticu(matica, n);

    printf("Program úspešne ukončený.\n");
    return 0;
}

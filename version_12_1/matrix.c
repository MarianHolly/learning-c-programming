#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "conversions.h"

/**
 * alokuj_maticu()
 *
 * IMPLEMENTÁCIA: Dvojstupňová alokácia
 *   1. Alokovať pole n pointerov (int**)
 *   2. Pre každý pointer alokovať pole n intov
 *   3. Pri chybe uvoľniť už alokované a vrátiť NULL
 */
int** alokuj_maticu(int n) {
    // Krok 1: Alokovať pole n pointerov na int
    int **matica = (int **)malloc(n * sizeof(int *));

    if (matica == NULL) {
        printf("Chyba: Nepodarilo sa alokovať pole pointerov!\n");
        return NULL;
    }

    // Krok 2: Alokovať každý riadok
    for (int i = 0; i < n; i++) {
        matica[i] = (int *)malloc(n * sizeof(int));

        if (matica[i] == NULL) {
            printf("Chyba: Nepodarilo sa alokovať riadok %d!\n", i);

            // Rollback: uvoľniť už alokované riadky
            for (int j = 0; j < i; j++) {
                free(matica[j]);
            }
            free(matica);
            return NULL;
        }
    }

    return matica;
}

/**
 * nacitaj_maticu()
 *
 * IMPLEMENTÁCIA: Načítanie zo súboru
 *   1. Otvoriť súbor
 *   2. Načítať rozmer n
 *   3. Validovať rozmer
 *   4. Alokovať maticu
 *   5. Načítať prvky (trojková → desiatková konverzia)
 *   6. Zatvoriť súbor
 */
int nacitaj_maticu(const char *nazov_suboru, int *n, int ***matica) {
    FILE *subor = NULL;

    // Krok 1: Otvoriť súbor
    subor = fopen(nazov_suboru, "r");
    if (subor == NULL) {
        printf("Chyba: Nepodarilo sa otvoriť súbor '%s'!\n", nazov_suboru);
        return -1;
    }

    // Krok 2: Načítať rozmer n
    if (fscanf(subor, "%d", n) != 1) {
        printf("Chyba: Nepodarilo sa načítať rozmer matice!\n");
        fclose(subor);
        return -1;
    }

    // Krok 3: Validovať rozmer
    if (*n <= 0) {
        printf("Chyba: Rozmer matice musí byť kladný! (načítané: %d)\n", *n);
        fclose(subor);
        return -1;
    }

    if (*n > 1000) {  // Rozumná hranica
        printf("Chyba: Rozmer matice je príliš veľký! (max 1000, požiadavka: %d)\n", *n);
        fclose(subor);
        return -1;
    }

    printf("Načítaný rozmer matice: %d x %d\n", *n, *n);

    // Krok 4: Alokovať maticu
    *matica = alokuj_maticu(*n);
    if (*matica == NULL) {
        printf("Chyba: Nepodarilo sa alokovať maticu!\n");
        fclose(subor);
        return -1;
    }

    // Krok 5: Načítať prvky
    char buffer[256];  // Buffer na trojkové číslo
    int konverzna_chyba = 0;

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            // Načítať reťazec (trojkové číslo)
            if (fscanf(subor, "%s", buffer) != 1) {
                printf("Chyba: Nepodarilo sa načítať prvok [%d][%d]!\n", i, j);
                konverzna_chyba = 1;
                break;
            }

            // Konvertovať z trojkovej na desiatkovú
            int hodnota = trojkova_na_desatkovu(buffer);

            if (hodnota == -1) {
                printf("Chyba: Neplatné trojkové číslo '%s' na pozícii [%d][%d]!\n", buffer, i, j);
                konverzna_chyba = 1;
                break;
            }

            // Uložiť do matice
            (*matica)[i][j] = hodnota;
        }

        if (konverzna_chyba) {
            break;
        }
    }

    // Krok 6: Zatvoriť súbor
    fclose(subor);

    if (konverzna_chyba) {
        // Uvoľniť maticu ak sa niečo pokazilo
        uvolni_maticu(*matica, *n);
        return -1;
    }

    return 0;  // Úspech
}

/**
 * vypis_maticu()
 *
 * IMPLEMENTÁCIA: Prehľadný výpis s formátovaním
 */
void vypis_maticu(int **matica, int n) {
    if (matica == NULL) {
        printf("Chyba: Matica je NULL!\n");
        return;
    }

    printf("\n========== MATICA %dx%d (desiatková sústava) ==========\n", n, n);

    // Vypísať maticu s formátovaním
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%6d ", matica[i][j]);  // Zarovnať na 6 znakov
        }
        printf("\n");
    }

    printf("========================================================\n\n");
}

/**
 * vypocitaj_sucet_stlpca_bez_diagonaly()
 *
 * IMPLEMENTÁCIA: Iterácia cez stĺpec s preskočením diagonály
 */
int vypocitaj_sucet_stlpca_bez_diagonaly(int **matica, int n, int index_stlpca) {
    int sucet = 0;

    // Prejsť všetky riadky v danom stĺpci
    for (int i = 0; i < n; i++) {
        // Preskočiť diagonálny prvok
        if (i != index_stlpca) {
            sucet += matica[i][index_stlpca];
        }
    }

    return sucet;
}

/**
 * uvolni_maticu()
 *
 * IMPLEMENTÁCIA: Uvoľnenie dynamickej pamäte
 */
void uvolni_maticu(int **matica, int n) {
    if (matica == NULL) {
        return;
    }

    // Uvoľniť každý riadok
    for (int i = 0; i < n; i++) {
        if (matica[i] != NULL) {
            free(matica[i]);
        }
    }

    // Uvoľniť pole pointerov
    free(matica);
}

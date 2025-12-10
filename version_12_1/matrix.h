#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

/**
 * MODUL: matrix
 * ÚČEL: Práca so štvorcovou maticou – alokácia, načítanie, výpis, uvoľnenie
 *
 * Reprezentácia:
 *   int **matica = alokuj_maticu(n)
 *   matica[i][j] = prvok na riadku i, stĺpci j
 *
 * PAMÄŤ:
 *   - Matica je dynamicky alokovaná
 *   - Musíš ju uvoľniť volením uvolni_maticu()!
 */

/**
 * alokuj_maticu()
 *
 * ÚČEL: Dynamicky alokuje pamäť pre štvorcovú maticu n×n
 *
 * PARAMETRE:
 *   n - rozmer matice (počet riadkov = počet stĺpcov)
 *
 * NÁVRATOVÁ HODNOTA:
 *   - Pointer na alokovanú maticu (int**)
 *   - NULL ak alokácia zlyhá
 *
 * IMPLEMENTÁCIA:
 *   1. Alokovať pole n pointerov (int **)
 *   2. Pre každý pointer alokovať pole n intov
 *   3. Pri chybe uvoľniť už alokované riadky a vrátiť NULL
 *
 * PRÍKLAD:
 *   int **mat = alokuj_maticu(3);
 *   if (mat == NULL) { printf("Chyba!\n"); return 1; }
 *   mat[0][0] = 42;
 *   mat[1][2] = 15;
 */
int** alokuj_maticu(int n);

/**
 * nacitaj_maticu()
 *
 * ÚČEL: Načíta maticu zo súboru (prvky v trojkovej sústave)
 *
 * PARAMETRE:
 *   nazov_suboru - cesta k vstupnému súboru
 *   n - pointer na int, kde sa uloží rozmer matice (OUT parameter)
 *   matica - pointer na pointer, kam sa uloží alokovaná matica (OUT parameter)
 *
 * NÁVRATOVÁ HODNOTA:
 *   - 0 pri úspechu
 *   - -1 pri chybe (súbor, formát, alokácia, atď.)
 *
 * FORMÁT SÚBORU:
 *   Riadok 1: rozmer n (celé číslo)
 *   Riadky 2 až n+1: po n prvkov v trojkovej sústave (oddelené medzerami)
 *
 *   Príklad súboru (matica 3×3):
 *   ```
 *   3
 *   1 2 10
 *   20 21 22
 *   100 101 102
 *   ```
 *
 * PROCESY:
 *   1. Otvoriť súbor
 *   2. Načítať rozmer n
 *   3. Validovať rozmer (n > 0)
 *   4. Alokovať maticu
 *   5. Pre každý prvok: načítať trojkový reťazec, konvertovať, uložiť
 *   6. Zatvoriť súbor
 *   7. Vrátiť výsledok
 *
 * POZNÁMKA:
 *   - Prvky v matici sú uložené v DESIATKOVEJ sústave!
 *   - Konverzia z trojkovej na desiatkovú sa robí v tejto funkcii
 */
int nacitaj_maticu(const char *nazov_suboru, int *n, int ***matica);




/**
 * vypis_maticu()
 *
 * ÚČEL: Vypíše maticu na obrazovku v prehľadnom formáte (desiatková sústava)
 *
 * PARAMETRE:
 *   matica - pointer na maticu
 *   n - rozmer matice
 *
 * NÁVRATOVÁ HODNOTA: žiadna (void)
 *
 * FORMÁT VÝPISU:
 *   Matica 3×3 (desiatková sústava):
 *      1    2    3
 *      4    5    6
 *      7    8    9
 *
 * POZNÁMKA:
 *   - Zarovnať čísla na minimálnu šírku (napr. 5 znakov)
 *   - Výstup musí byť prehľadný
 */
void vypis_maticu(int **matica, int n);

/**
 * vypocitaj_sucet_stlpca_bez_diagonaly()
 *
 * ÚČEL: Vypočíta súčet všetkých prvkov v stĺpci OKREM diagonálneho prvku
 *
 * PARAMETRE:
 *   matica - pointer na maticu
 *   n - rozmer matice
 *   index_stlpca - index stĺpca (a zároveň index riadka diagonálneho prvku)
 *
 * NÁVRATOVÁ HODNOTA:
 *   Súčet prvkov v stĺpci okrem prvku [index_stlpca][index_stlpca]
 *
 * PRÍKLAD:
 *   Matica:       Stĺpec 1 (bez diagonály [1,1]):
 *   1 2 3              2
 *   4 5 6          +   6  = 8
 *   7 8 9
 *
 *   vypocitaj_sucet_stlpca_bez_diagonaly(matica, 3, 1) → 8
 */
int vypocitaj_sucet_stlpca_bez_diagonaly(int **matica, int n, int index_stlpca);

/**
 * uvolni_maticu()
 *
 * ÚČEL: Uvoľní dynamicky alokovanú pamäť matice
 *
 * PARAMETRE:
 *   matica - pointer na maticu
 *   n - rozmer matice
 *
 * NÁVRATOVÁ HODNOTA: žiadna (void)
 *
 * PROCESY:
 *   1. Skontroluj či matica != NULL
 *   2. Uvoľni každý riadok (free matica[i] pre i = 0 až n-1)
 *   3. Uvoľni pole pointerov (free matica)
 *
 * DÔLEŽITÉ: Bez tohto dôjde k úniku pamäte (memory leak)!
 */
void uvolni_maticu(int **matica, int n);

#endif

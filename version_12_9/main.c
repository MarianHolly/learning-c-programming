#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "binary_io.h"
#include "conversion.h"
#include "input.h"

#define MAX_FILE 256

void zobraz_menu() {
    printf("\n");
    printf("==========================================\n");
    printf("  ANALYZA MATICE - TROJKOVA SUSTAVA\n");
    printf("==========================================\n");
    printf("1. Zadat vlastnu maticu\n");
    printf("2. Nacitat BIN maticu\n");
    printf("3. Koniec\n");
    printf("==========================================\n");
    printf("Volba: ");
}

int main() {
    int volba;
    char buf[10];
    
    while (1) {
        zobraz_menu();
        
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        if (sscanf(buf, "%d", &volba) != 1) continue;
        
        if (volba == 3) {
            printf("\nKoniec programu.\n");
            break;
        }
        
        // SCENAR 1: Vlastna matica
        if (volba == 1) {
            printf("\n========== VLASTNA MATICA ==========\n");
            
            // Rozmer
            int n = nacitaj_rozmer();
            if (n < 0) continue;
            
            // Alokuj
            int **mat = alokuj_maticu(n);
            if (!mat) continue;
            
            // Nacitaj prvky
            if (nacitaj_maticu(mat, n) != 0) {
                uvolni_maticu(mat, n);
                continue;
            }
            
            // Nazov BIN suboru
            char file[MAX_FILE];
            if (nacitaj_nazov(file, MAX_FILE, "Zadajte nazov BIN suboru") != 0) {
                uvolni_maticu(mat, n);
                continue;
            }
            
            // Zapis do BIN
            if (zapis_bin(file, mat, n) != 0) {
                uvolni_maticu(mat, n);
                continue;
            }
            
            // Uvolni povodnu
            uvolni_maticu(mat, n);
            
            // Precitaj z BIN (overenie)
            int **mat2 = NULL;
            int n2;
            if (citaj_bin(file, &mat2, &n2) != 0) continue;
            
            // Vypis a analyzuj
            printf("\n========== VYSLEDKY ==========\n\n");
            vypis_maticu_dual(mat2, n2);
            analyzuj_diagonalu(mat2, n2);
            
            // Uvolni
            uvolni_maticu(mat2, n2);
        }
        
        // SCENAR 2: Nacitaj BIN
        else if (volba == 2) {
            printf("\n========== NACITANIE BIN ==========\n");
            
            // Nazov suboru
            char file[MAX_FILE];
            if (nacitaj_nazov(file, MAX_FILE, "Zadajte nazov BIN suboru") != 0) {
                continue;
            }
            
            // Citaj
            int **mat = NULL;
            int n;
            if (citaj_bin(file, &mat, &n) != 0) continue;
            
            // Vypis a analyzuj
            printf("\n========== VYSLEDKY ==========\n\n");
            vypis_maticu_dual(mat, n);
            analyzuj_diagonalu(mat, n);
            
            // Uvolni
            uvolni_maticu(mat, n);
        }
        
        else {
            printf("Neplatna volba!\n");
        }
        
        printf("\nStlacte Enter...");
        getchar();
    }
    
    return 0;
}
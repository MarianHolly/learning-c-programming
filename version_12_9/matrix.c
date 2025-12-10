#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "conversion.h"

// Alokacia matice n×n
int** alokuj_maticu(int n) {
    int **mat = malloc(n * sizeof(int*));
    if (!mat) {
        printf("Chyba: Nepodarila sa alokacia!\n");
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        mat[i] = malloc(n * sizeof(int));
        if (!mat[i]) {
            // Uvolni uz alokovane
            for (int j = 0; j < i; j++) free(mat[j]);
            free(mat);
            printf("Chyba: Nepodarila sa alokacia riadku %d!\n", i);
            return NULL;
        }
    }
    
    return mat;
}

// Uvolnenie matice
void uvolni_maticu(int **mat, int n) {
    if (!mat) return;
    for (int i = 0; i < n; i++) {
        if (mat[i]) free(mat[i]);
    }
    free(mat);
}

// Vypis len v desiatkovej
void vypis_maticu_desiat(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        printf("   ");
        for (int j = 0; j < n; j++) {
            printf("%6d ", mat[i][j]);
        }
        printf("\n");
    }
}

// Vypis v oboch sustavach
void vypis_maticu_dual(int **mat, int n) {
    printf("DESIATKOVA          TROJKOVA\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        // Desiatkova strana
        printf("   ");
        for (int j = 0; j < n; j++) {
            printf("%6d ", mat[i][j]);
        }
        
        printf("  |  ");
        
        // Trojkova strana
        for (int j = 0; j < n; j++) {
            char *tern = dec_to_tern(mat[i][j]);
            printf("%6s ", tern);
            free_tern(tern);
        }
        printf("\n");
    }
    printf("\n");
}

// Analyza diagonaly
void analyzuj_diagonalu(int **mat, int n) {
    printf("\n========== ANALYZA DIAGONALY ==========\n\n");
    
    if (n == 1) {
        printf("Matica 1x1 - diagonalny prvok je jediny.\n");
        printf("Prvok [0,0] = %d\n", mat[0][0]);
        char *tern = dec_to_tern(mat[0][0]);
        printf("V trojkovej: %s\n", tern);
        free_tern(tern);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        int diag = mat[i][i];
        int sum = 0;
        
        // Sucet stlpca bez diagonaly
        for (int r = 0; r < n; r++) {
            if (r != i) sum += mat[r][i];
        }
        
        // Vztah
        char *symbol = "=";
        if (diag > sum) symbol = ">";
        else if (diag < sum) symbol = "<";
        
        // Vypis
        char *diag_tern = dec_to_tern(diag);
        char *sum_tern = dec_to_tern(sum);
        
        printf("Pozicia [%d,%d]:\n", i, i);
        printf("  Diagonalny prvok: %d (trojk: %s)\n", diag, diag_tern);
        printf("  Sucet ostatnych:  %d (trojk: %s)\n", sum, sum_tern);
        printf("  Vztah: %d %s %d\n\n", diag, symbol, sum);
        
        free_tern(diag_tern);
        free_tern(sum_tern);
    }
}
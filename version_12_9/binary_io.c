#include <stdio.h>
#include <stdlib.h>
#include "binary_io.h"
#include "matrix.h"

// Zapis do BIN
int zapis_bin(const char *file, int **mat, int n) {
    FILE *f = fopen(file, "wb");
    if (!f) {
        printf("Chyba: Nepodarilo sa otvorit subor '%s' na zapis!\n", file);
        return -1;
    }
    
    // Zapis rozmer
    if (fwrite(&n, sizeof(int), 1, f) != 1) {
        printf("Chyba: Nepodaril sa zapis rozmeru!\n");
        fclose(f);
        return -1;
    }
    
    // Zapis maticu po riadkoch
    for (int i = 0; i < n; i++) {
        if (fwrite(mat[i], sizeof(int), n, f) != (size_t)n) {
            printf("Chyba: Nepodaril sa zapis riadku %d!\n", i);
            fclose(f);
            return -1;
        }
    }
    
    fclose(f);
    printf("Uspech: Matica zapisana do '%s'\n", file);
    return 0;
}

// Citanie z BIN
int citaj_bin(const char *file, int ***mat, int *n) {
    FILE *f = fopen(file, "rb");
    if (!f) {
        printf("Chyba: Nepodarilo sa otvorit subor '%s'!\n", file);
        return -1;
    }
    
    // Citaj rozmer
    if (fread(n, sizeof(int), 1, f) != 1) {
        printf("Chyba: Nepodarilo sa precitat rozmer!\n");
        fclose(f);
        return -1;
    }
    
    if (*n <= 0 || *n > 1000) {
        printf("Chyba: Neplatny rozmer %d!\n", *n);
        fclose(f);
        return -1;
    }
    
    // Alokuj maticu
    *mat = alokuj_maticu(*n);
    if (!*mat) {
        fclose(f);
        return -1;
    }
    
    // Citaj maticu po riadkoch
    for (int i = 0; i < *n; i++) {
        if (fread((*mat)[i], sizeof(int), *n, f) != (size_t)*n) {
            printf("Chyba: Nepodarilo sa precitat riadok %d!\n", i);
            uvolni_maticu(*mat, *n);
            fclose(f);
            return -1;
        }
    }
    
    fclose(f);
    printf("Uspech: Matica nacitana zo '%s' (rozmer %dx%d)\n", file, *n, *n);
    return 0;
}
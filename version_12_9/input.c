#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

// Helper - odstran newline
static void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';
}

// Nacitaj rozmer
int nacitaj_rozmer() {
    char buf[100];
    int n;
    
    printf("\nZadajte rozmer matice (n): ");
    
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Chyba: Nepodarilo sa nacitat vstup!\n");
        return -1;
    }
    
    trim_newline(buf);
    
    if (sscanf(buf, "%d", &n) != 1 || n <= 0) {
        printf("Chyba: Neplatny rozmer!\n");
        return -1;
    }
    
    return n;
}

// Nacitaj nazov suboru
int nacitaj_nazov(char *buf, int max, const char *prompt) {
    printf("\n%s: ", prompt);
    
    if (!fgets(buf, max, stdin)) {
        printf("Chyba: Nepodarilo sa nacitat vstup!\n");
        return -1;
    }
    
    trim_newline(buf);
    
    if (strlen(buf) == 0) {
        printf("Chyba: Prazdny nazov!\n");
        return -1;
    }
    
    return 0;
}

// Nacitaj maticu od pouzivatela
int nacitaj_maticu(int **mat, int n) {
    printf("\nZadavajte prvky matice (v desiatkovej sustave):\n");
    printf("Format: zadajte %d cisel pre kazdy riadok.\n\n", n);
    
    for (int i = 0; i < n; i++) {
        printf("Riadok %d: ", i + 1);
        
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &mat[i][j]) != 1) {
                printf("Chyba: Neplatny vstup!\n");
                // Vycisti buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                return -1;
            }
        }
    }
    
    // Vycisti buffer (zostane newline po poslednom scanf)
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("\nMatica uspesne nacitana!\n");
    return 0;
}
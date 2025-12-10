#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversion.h"

// Prevod desiatkovej na trojkovu
char* dec_to_tern(int num) {
    if (num == 0) {
        char *result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    // Buffer pre max cislo (int max ~2 miliardy = cca 20 cifier v trojkovej)
    char buffer[32];
    int idx = 0;
    int n = num;
    
    while (n > 0) {
        buffer[idx++] = '0' + (n % 3);
        n /= 3;
    }
    buffer[idx] = '\0';
    
    // Otoc retazec (lebo sme ho stavali odzadu)
    int len = idx;
    for (int i = 0; i < len / 2; i++) {
        char tmp = buffer[i];
        buffer[i] = buffer[len - 1 - i];
        buffer[len - 1 - i] = tmp;
    }
    
    // Alokuj vysledok
    char *result = malloc(len + 1);
    strcpy(result, buffer);
    return result;
}

// Uvolnenie
void free_tern(char *str) {
    if (str) free(str);
}
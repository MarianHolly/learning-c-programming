#ifndef INPUT_H
#define INPUT_H

// Nacitaj rozmer od pouzivatela
int nacitaj_rozmer();

// Nacitaj nazov suboru
int nacitaj_nazov(char *buf, int max, const char *prompt);

// Nacitaj prvky matice od pouzivatela
int nacitaj_maticu(int **mat, int n);

#endif
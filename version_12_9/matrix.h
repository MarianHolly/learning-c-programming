#ifndef MATRIX_H
#define MATRIX_H

// Alokacia a uvolnenie
int** alokuj_maticu(int n);
void uvolni_maticu(int **mat, int n);

// Vypis
void vypis_maticu_desiat(int **mat, int n);
void vypis_maticu_dual(int **mat, int n);

// Analyza
void analyzuj_diagonalu(int **mat, int n);

#endif
#ifndef BINARY_IO_H
#define BINARY_IO_H

// Zapis matice do BIN suboru
// Format: [int rozmer][int prvky...]
int zapis_bin(const char *file, int **mat, int n);

// Citanie matice z BIN suboru
// Alokuje maticu a vrati cez ***mat
int citaj_bin(const char *file, int ***mat, int *n);

#endif
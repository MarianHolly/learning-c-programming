#ifndef MATRIX_H
#define MATRIX_H

/**
 * Alokuj pamat pre stvorcovu maticu daneho rozmeru
 * Dvojstupnova alokacia (pole pointerov + jednotlive riadky)
 *
 * @param rozmer_matice - rozmer stvorcovej matice (n x n)
 * @return pointer na alokovanu maticu, NULL pri chybe
 */
int** alokuj_maticu(int rozmer_matice);

/**
 * Uvolni pamat alokovanu pre maticu
 * Najprv uvolni jednotlive riadky, potom pole pointerov
 *
 * @param p_matica - pointer na maticu
 * @param rozmer_matice - rozmer matice
 */
void uvolni_maticu(int** p_matica, int rozmer_matice);

/**
 * Konvertuj a nacita maticu zo suboru do alokovanej pamate
 * Prvky v subore su v trojkovej sustave, konvertuju sa do desiatkovej
 *
 * @param nazov_suboru - nazov suboru so vstupnou maticou
 * @param rozmer_matice - rozmer stvorcovej matice
 * @param p_matica - pointer na alokovanu maticu
 * @return 0 pri uspesnom nacitani, -1 pri chybe
 */
int nacitaj_maticu_zo_suboru(const char* nazov_suboru, int rozmer_matice, int** p_matica);

/**
 * Vypis maticu na obrazovku v desiatkovej sustave
 *
 * @param p_matica - pointer na maticu
 * @param rozmer_matice - rozmer matice
 */
void vypis_maticu(int** p_matica, int rozmer_matice);

/**
 * Vypocitaj sucet prvkov v danom stlpci okrem prvku na hlavnej diagonale
 *
 * @param p_matica - pointer na maticu
 * @param rozmer_matice - rozmer matice
 * @param index_stlpca - index stlpca, ktoreho sucet sa pocita
 * @return sucet prvkov v stlpci okrem diagonalneho prvku
 */
int sucet_stlpca_bez_diagonaly(int** p_matica, int rozmer_matice, int index_stlpca);

/**
 * Analyzuj kazdy prvok hlavnej diagonaly matice
 * Pre kazdy diagonalny prvok urci jeho vztah k suctu ostatnych prvkov v jeho stlpci
 * Vypise vysledky na obrazovku
 *
 * @param p_matica - pointer na maticu
 * @param rozmer_matice - rozmer matice
 */
void analyzuj_diagonalu(int** p_matica, int rozmer_matice);

#endif
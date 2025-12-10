#ifndef VALIDATION_H
#define VALIDATION_H

/**
 * Odstr·ni '\n' z konca reùazca (ak tam je)
 * @param retazec - reùazec, z ktorÈho sa m· odstr·niù nov˝ riadok
 */
void odstran_newline(char *retazec);

/**
 * Spocita kolko prvkov (trojkovych cisiel) je v subore
 *
 * @param nazov_suboru - nazov suboru, ktory sa ma otvorit a precitat
 * @return pocet prvkov v subore, -1 ak sa nepodarilo otvorit subor
*/
int pocet_prvkov_v_subore(const char *nazov_suboru);

/**
 * Skontroluje ci rozmer matice n zodpoveda poctu prvkov v subore (n*n)
 *
 * @param rozmer_matice - rozmer matice (n)
 * @param pocet_prvkov - pocet prvkov v subore
 * @return 0 ak validne, -1 ak chyba
*/
int validuj_rozmer_matice(int rozmer_matice, int pocet_prvkov);

/**
 * Skontroluje ci subor obsahuje len platne trojkove cisla (cifry 0,1,2)
 *
 * @param nazov_suboru - nazov suboru, ktory sa ma otvorit a precitat
 * @param rozmer_matice - rozmer stvorcovej matice (n)
 * @return 0 ak validne, -1 ak chyba
*/
int validuj_prvky_matice(const char *nazov_suboru, int rozmer_matice);

#endif

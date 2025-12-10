#ifndef CONVERSION_H
#define CONVERSION_H

/**
 * Prevod z trojkovej do desiatkovej sustavy
 * Pouziva Hornerovu schemu
 *
 * @param trojkove_cislo - retazzec reprezentujuci cislo v trojkovej sustave
 * @return cele cislo v desiatkovej sustave
*/
int trojkove_na_desiatkovu(const char *trojkove_cislo);

#endif

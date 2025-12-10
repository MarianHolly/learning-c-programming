#ifndef UTILS_H
#define UTILS_H

/**
 * MODUL: utils
 * ÚČEL: Pomocné a utility funkcie pre porovnávanie a výstup
 */

/**
 * Enum pre vzťah medzi dvoma číslami
 */
typedef enum {
    MENSI = -1,    // a < b
    ROVNY = 0,     // a == b
    VACSI = 1      // a > b
} Vztah;

/**
 * porovnaj()
 *
 * ÚČEL: Porovná dve čísla a vráti ich vzťah
 *
 * PARAMETRE:
 *   a, b - čísla na porovnanie
 *
 * NÁVRATOVÁ HODNOTA:
 *   - MENSI (-1) ak a < b
 *   - ROVNY (0) ak a == b
 *   - VACSI (1) ak a > b
 *
 * PRÍKLADY:
 *   porovnaj(5, 10)  → MENSI
 *   porovnaj(10, 10) → ROVNY
 *   porovnaj(15, 10) → VACSI
 */
Vztah porovnaj(int a, int b);

/**
 * vztah_na_symbol()
 *
 * ÚČEL: Konvertuje enum Vztah na symbol
 *
 * PARAMETRE:
 *   vztah - hodnota typu Vztah
 *
 * NÁVRATOVÁ HODNOTA:
 *   - "<" pre MENSI
 *   - "=" pre ROVNY
 *   - ">" pre VACSI
 *
 * PRÍKLADY:
 *   vztah_na_symbol(MENSI) → "<"
 *   vztah_na_symbol(ROVNY) → "="
 *   vztah_na_symbol(VACSI) → ">"
 */
const char* vztah_na_symbol(Vztah vztah);

/**
 * vztah_na_retazec()
 *
 * ÚČEL: Konvertuje enum Vztah na textový reťazec
 *
 * PARAMETRE:
 *   vztah - hodnota typu Vztah
 *
 * NÁVRATOVÁ HODNOTA:
 *   - "menší" pre MENSI
 *   - "rovný" pre ROVNY
 *   - "väčší" pre VACSI
 */
const char* vztah_na_retazec(Vztah vztah);

#endif

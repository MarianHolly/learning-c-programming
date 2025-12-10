#include <stdio.h>
#include "utils.h"

/**
 * porovnaj()
 *
 * Jednoduché porovnanie dvoch čísel
 */
Vztah porovnaj(int a, int b) {
    if (a < b) {
        return MENSI;
    } else if (a > b) {
        return VACSI;
    } else {
        return ROVNY;
    }
}

/**
 * vztah_na_symbol()
 *
 * Konverzia enum na symbol
 */
const char* vztah_na_symbol(Vztah vztah) {
    switch (vztah) {
        case MENSI:
            return "<";
        case ROVNY:
            return "=";
        case VACSI:
            return ">";
        default:
            return "?";
    }
}

/**
 * vztah_na_retazec()
 *
 * Konverzia enum na textový reťazec
 */
const char* vztah_na_retazec(Vztah vztah) {
    switch (vztah) {
        case MENSI:
            return "menší";
        case ROVNY:
            return "rovný";
        case VACSI:
            return "väčší";
        default:
            return "neznámy";
    }
}

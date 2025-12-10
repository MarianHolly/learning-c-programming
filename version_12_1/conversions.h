#ifndef CONVERSIONS_H
#define CONVERSIONS_H

/**
 * MODUL: conversions
 * ÚČEL: Konverzie medzi trojkovou a desatkovou číselnými sústavami
 *
 * Trojková sústava (base-3):
 *   - Cifry: 0, 1, 2
 *   - Príklad: "2101" = 2*3^3 + 1*3^2 + 0*3^1 + 1*3^0 = 54 + 9 + 0 + 1 = 64 (desiatková)
 *
 * Algoritmy:
 *   - Trojková → Desiatková: Hornerova schéma
 *   - Desiatková → Trojková: Opakované delenie modulo
 */

/**
 * trojkova_na_desatkovu()
 *
 * ÚČEL: Konvertuje reťazec v trojkovej sústave na celé číslo v desiatkovej
 *
 * PARAMETRE:
 *   trojkove_cislo - reťazec obsahujúci len cifry 0, 1, 2
 *                    napríklad: "2101", "10", "222"
 *
 * NÁVRATOVÁ HODNOTA:
 *   - Celé číslo v desiatkovej sústave (>= 0)
 *   - (-1) ak je reťazec neplatný (obsahuje cifru >= 3 alebo je prázdny)
 *
 * PRÍKLADY:
 *   trojkova_na_desatkovu("0")    → 0
 *   trojkova_na_desatkovu("1")    → 1
 *   trojkova_na_desatkovu("2")    → 2
 *   trojkova_na_desatkovu("10")   → 3
 *   trojkova_na_desatkovu("2101") → 64
 *   trojkova_na_desatkovu("999")  → -1 (neplatné)
 */
int trojkova_na_desatkovu(const char *trojkove_cislo);




/**
 * desatkova_na_trojkovu()
 *
 * ÚČEL: Konvertuje celé číslo v desiatkovej sústave na reťazec v trojkovej
 *
 * PARAMETRE:
 *   cislo - nezáporné celé číslo v desiatkovej sústave
 *   vysledok - buffer na uloženie výsledku v trojkovej sústave
 *              MUSÍ byť dostatočne veľký! Pre číslo do miliardy stačí 50 znakov
 *
 * NÁVRATOVÁ HODNOTA: žiadna (void)
 *
 * POZNÁMKA: Funkcii musíš sám zaručiť, že buffer je dostatočne veľký
 *           Inak dôjde k buffer overflow!
 *
 * PRÍKLADY:
 *   desatkova_na_trojkovu(0, buf)    → buf = "0"
 *   desatkova_na_trojkovu(3, buf)    → buf = "10"
 *   desatkova_na_trojkovu(64, buf)   → buf = "2101"
 */
void desatkova_na_trojkovu(int cislo, char *vysledok);

/**
 * je_platne_trojkove_cislo()
 *
 * ÚČEL: Validácia či reťazec predstavuje platné číslo v trojkovej sústave
 *
 * PARAMETRE:
 *   retazec - reťazec na kontrolu
 *
 * NÁVRATOVÁ HODNOTA:
 *   - 1 (true) ak je reťazec platné trojkové číslo
 *   - 0 (false) ak obsahuje neplatné znaky alebo je prázdny
 *
 * PRÍKLADY:
 *   je_platne_trojkove_cislo("2101")  → 1
 *   je_platne_trojkove_cislo("10")    → 1
 *   je_platne_trojkove_cislo("999")   → 0 (neplatné cifry)
 *   je_platne_trojkove_cislo("")      → 0 (prázdny)
 */
int je_platne_trojkove_cislo(const char *retazec);

#endif

#include <stdio.h>
#include <string.h>
#include "validation.h"

#define MAX_ROZMER_CISLA 50

// Odstránenie '\n' z konca reťazca (ak tam je)
void odstran_newline(char *retazec) {
    size_t len = strlen(retazec);
    if (len > 0 && retazec[len - 1] == '\n') {
        retazec[len - 1] = '\0';
    }
}


// Spocitanie poctu prvkov v subore
// Cita vsetky retazce zo suboru a pocita ich - jeden retazec = jedno trojkove cislo
int pocet_prvkov_v_subore(const char *nazov_suboru){
    FILE *p_subor = fopen(nazov_suboru, "r");

    if (p_subor == NULL) {
        printf("    [CHYBA] Nemam pristup k suboru '%s'.\n", nazov_suboru);
        return -1; // Posli naspat chybu, nepodarilo sa otvorit subor
    }

    int pocet = 0;
    char buffer[MAX_ROZMER_CISLA];  // Pomocne retazec, na nacitanie jedneho cisla v trojkovej sustave

    // Postupne citanie retazcov zo suboru a pocitanie
    while(fscanf(p_subor, "%49s", buffer) == 1){
        // ak fscanf vrati 1, podarilo sa mu nacitat retazec do buffer
        pocet ++;
    };

    fclose(p_subor);

    printf("    [DATA] Nasli sme %d prvkov v subore.\n", pocet);
    return pocet;
};


// Validacia rozmeru matice
// Porovna pocet prvkov v subore s ocakavanym poctom prvkov pre dany rozmer matice
int validuj_rozmer_matice(int rozmer_matice, int pocet_prvkov){
    int ocakavany_pocet = rozmer_matice * rozmer_matice;

    if(pocet_prvkov == ocakavany_pocet){
        printf("    [OK] Pocet prvkov matice v subore zodpoveda zadanym rozmerom matice.\n");
        return 0;
    }else {
        printf("    [CHYBA] Pocet prvkov: %d, ocakavany: %d (pre maticu %dx%d)\n", pocet_prvkov, ocakavany_pocet, rozmer_matice, rozmer_matice);
        return -1;
    }
}


// Validacia prvkov matice (trojkove cisla)
// Kontroluje ci subor obsahuje len platne trojkove cisla (cifry 0, 1, 2)
int validuj_prvky_matice(const char *nazov_suboru, int rozmer_matice){
    FILE *p_subor = fopen(nazov_suboru, "r");

    if (p_subor == NULL) {
        printf("    [CHYBA] Nemam pristup k suboru '%s'\n", nazov_suboru);
        return -1; // Nepodarilo sa otvorit subor
    }

    char buffer[MAX_ROZMER_CISLA];
    int ocakavany_pocet = rozmer_matice * rozmer_matice;
    int preskumane_prvky = 0;

    // Citanie a validacia kazdeho prvku
    while(fscanf(p_subor, "%49s", buffer) == 1) {

        // Kontrola prazdneho retazca
        if (strlen(buffer) == 0) {
            printf("    [CHYBA] Nacitane cislo v subore je prazdne.\n");
            fclose(p_subor);
            return -1;
        }

        // Validacia kazdeho znaku v retazci
        // Prejdeme kazdy znak v buffer a skontrolujeme ci je platna trojkova cifra
        for (int i=0; buffer[i] != '\0'; i++) {

            if (buffer[i] < '0' || buffer[i] > '2'){
                // Znak musi byt v rozsahu '0' az '2' - inak vratime chybu
                // Porovnavame hodnotu znaku, nie jeho ciselnú hodnotu
                // '0' = 48, '1' = 49, '2' = 50 v ASCII tabulke

                printf("    [CHYBA] Neplatny znak '%c' v cisle '%s'.\n", buffer[i], buffer);
                printf("            Trojkova sustava povoluje len cifry 0, 1, 2.\n");
                fclose(p_subor);
                return -1;
            }
        }

        preskumane_prvky++;
    }

    fclose(p_subor);

    // Posledna kontrola: pocet preskumaných prvkov = ocakavany pocet
    if (preskumane_prvky == ocakavany_pocet) {
        printf("    [OK] Vsetky prvky v subore su platne trojkove cisla\n");
        return 0;
    } else {
        printf("    [CHYBA] Pocet preskumaných prvkov (%d) neodpoveda ocakávanému počtu (%d)\n", preskumane_prvky, ocakavany_pocet);
        return -1;
    }

};

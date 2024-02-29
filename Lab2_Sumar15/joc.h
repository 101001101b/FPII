#ifndef joc_h
#define joc_h

#include <stdbool.h>
#define MIDA_TAULER 10      // Mida del tauler
#define SUMA 15             // Objectiu a sumar

typedef struct 
{
    char nom[50];   // Per desar el nom del jugador
    int torn;       // Defineix qui esta jugant: 0 - ordinador, 1 - persona
    int punts[2];   // Per desar els punts acumulats: : 0 - ordinador, 1 - persona
    int guanyador; // Per saber el guanayador: -1 no hi ha guanyador
    char tauler[MIDA_TAULER];   // Tauler de joc: 'P' persona, 'O' ordinador, '-' lliure
} joc_t;


void iniciar_joc(joc_t *j, char *argv[]);

bool hi_ha_joc(joc_t *j);

void missatge_benvinguda(joc_t *j);

void missatge_comiat(joc_t *j);

void mostrar_joc(joc_t *j);

int fer_jugada(joc_t *j);

void actualitzar_joc(joc_t *j, int posicio);

#endif /* joc_h */
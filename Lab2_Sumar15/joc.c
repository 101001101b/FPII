// Una solucio a la practiqueta del laboratori L2, que es desenvolupa en dues sessions

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "joc.h"
#define MAX 15

// Inicialitza la partida
void iniciar_joc(joc_t *j, char *argv[])
{
    srand(time(NULL));
    j->guanyador = -1;  // El joc no ha acabat
    j->torn = rand() % 2;      // Jugador inicial
    j->punts[0] = 0;    // Punts inicials de l'ordinador
    j->punts[1] = 0;    // Punts inicials de la persona
    strcpy(j->nom, argv[1]);    // Nom del jugador/a

    // Inicialitzar el tauler
    for (int i = 0; i < MIDA_TAULER; i++)
    {
        j->tauler[i] = '-';
    }
}

void missatge_benvinguda(joc_t *j)
{
    printf("Benvingut al joc, %c.\n", j->nom);
}

void mostrar_joc(joc_t *j)
{
    printf("\n");
    printf("Punts %s: %d - Punts O: %d\n", j->nom, j->punts[1], j->punts[0]);

    for (int i = 0; i < MIDA_TAULER; i++)
    {
        printf("%d\t", i + 1);
    }

    printf("\n");
    for (int i = 0; i < MIDA_TAULER; i++)
    {
        printf("%c\t", j->tauler[i]);
    }
    printf("\n");
}

// Interaccio amb usuari partida
int fer_jugada(joc_t *j)
{
    int posicio;

    switch(j->torn)
    {
        // Juga l'ordinador
        case 0 :   printf("Toca jugar a l'ordinador. ");
            posicio = rand() % 10 + 1;
            while (j->tauler[posicio-1 != '-'])
            {
                posicio = rand() % 10 + 1; //Seguim generant aleatoris fins que no troba una posició lliure
            }
            printf("%c ha triat la posicio %d\n", j->nom, posicio);
            j->torn = 1;
            break;

        // Juga la persona
        case 1 :  printf("Toca jugar a %s. Quin numero agafes?\n", j->nom);
            printf("Introdueix el numero que vols:\n");
            scanf("%d", &posicio);
            while (j->tauler[posicio-1] != '-') //mentre el jugador no tria una casella vàlida
            {
                printf("Has de triar una posició lliure!\n");
                scanf("%d", &posicio);
            }
            j->torn = 0;
            break;
    }
   return posicio;
}

//Indica si es pot seguir jugant
bool hi_ha_joc(joc_t *j)
{
    bool hi_ha_joc = true;
    /*Retornar un booleà cert si el joc segueix viu, fals si ja ha acabat */
    if ((j->punts[0] > MAX) || (j->punts[1] == MAX))
    {
        j->guanyador = 1; // Guanya la persona
        hi_ha_joc = false;
    }
    else if ((j->punts[0] == MAX) || (j->punts[1] > MAX))
    {
        j->guanyador = 0; // Guanya l'ordinador
        hi_ha_joc = false;
    }
    return hi_ha_joc;
}

// Actualitza la partida
void actualitzar_joc(joc_t *j, int posicio)
{
    //bool guanyador = false;
    if (j->torn == 0)
    {
        j->punts[1] += posicio;
        j->tauler[posicio-1]='P';
        if (hi_ha_joc(j)) j->torn=1; //si es pot seguir jugant, actualitza el torn
    }
    else
    {
        j->punts[0]+=posicio;
        j->tauler[posicio-1]='O';
        if (hi_ha_joc(j)) j->torn=0;
    }
}

void missatge_comiat(joc_t *j)
{
    if (j->guanyador == 0)
    {
        printf("Ho sento %s! Ha guanyat l'ordinador!\n", j->nom);
    }
    else
    {
        printf("Enhorabona %s! Has guanyat a l'ordinador!\n", j->nom);
    }
    printf("Fins aviat!\n");
}










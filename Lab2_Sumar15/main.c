#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <string.h>
#include <time.h>

#include "joc.h"
#define MAX 15


int main(int argc, char *argv[])
{
    joc_t joc;  // Per desar les dades de la partida

    // Si els parametres son correctes inicialitza el joc
    if (argc != 2)
    {
        printf("Has d'indicar el nom del jugador!\n");
    }
    else
    {
        iniciar_joc(&joc, argv);
        missatge_benvinguda(&joc);
        mostrar_joc(&joc);

        while (hi_ha_joc(&joc))
        {
            int pos = fer_jugada(&joc);
            actualitzar_joc(&joc, pos);
            mostrar_joc(&joc);
        }
        missatge_comiat(&joc);
    }

	return 0;
}

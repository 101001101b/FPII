#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MIDA_TAULER 10
#define SUMA 15

typedef struct
{
    char nom[50];
    int torn;
    int punts[2];
    char guanyador;
    char tauler[MIDA_TAULER];
} joc_t;

void iniciar_joc(joc_t *j, char *argv[])
{
    int i;

    srand(time(NULL));
    j->guanyador = 'X';
    j->torn = rand() % 2;
    j->punts[0] = 0;
    j->punts[1] = 0;
    strcpy(j->nom, argv[1]);


    for (i = 0; i < MIDA_TAULER; i++)
    {
        j->tauler[i] = '-';
    }
}

void missatge_benvinguda(joc_t *j)
{
    printf("Benvingut %s, que gaudeixis del  joc.",j->nom);
}

void mostrar_joc(joc_t *j)
{
    int i;
    printf("\n");
    printf("Punts P (%s) %d - Punts O (ordinador) %d\n", j->nom, j->punts[1], j->punts[0]);

    for (i = 0; i < MIDA_TAULER; i++)
    {
        printf("%d\t", i + 1);
    }

    printf("\n");
    for (i = 0; i < MIDA_TAULER; i++)
    {
        printf("%c\t", j->tauler[i]);
    }
    printf("\n");
}

int fer_jugada(joc_t *j)
{
    int posicio;

	switch(j->torn)
	{
	    case 0:
	        printf("\n7Es el torn de la maquina\n");
	        posicio = rand() % 10+1;
	        while(j->tauler[posicio-1]!='-') posicio = rand() % 10+1;
	        j->torn = 1;
	        break;
        case 1:
            printf("\nQuin numero escolleixes?\n");
            scanf("%d",&posicio);
            while(j->tauler[posicio-1]!='-')
            {
                printf("\nHas d'escollir un numero que no estigui ja seleccionat!\n");
                scanf("%d",&posicio);
            }
	        j->torn = 0;
	        break;
	}
   return posicio;
}

bool fi_joc(joc_t *j)
{
    bool fi=false;

    if (j->punts[0]>=SUMA)
    {
        if (j->punts[0]==SUMA)
        {
            fi=true;
            j->guanyador ='O';
        }
        if (j->punts[0]>SUMA)
        {
            fi=true;
            j->guanyador='P';
        }
    }
    if (j->punts[1]>=SUMA)
    {
        if (j->punts[1]==SUMA)
        {
            fi=true;
            j->guanyador='P';
        }
        if (j->punts[1]>SUMA)
        {
            fi=true;
            j->guanyador='O';
        }
    }
    return (fi);
}
void actualitzar_joc(joc_t *j, int pos)
{
	int i=0;
	i=pos-1;
	if (j->torn==0)
	{
	    j->punts[1]=j->punts[1]+pos;
        j->tauler[i]='P';
	}

	else
    {
        j->punts[0]=j->punts[0]+pos;
        j->tauler[i]='O';
    }
}
void missatge_comiat(joc_t *j)
{
    if (j->guanyador=='P') printf("EL guanyador ha sigut %s\n",j->nom);
    else printf("EL guanyador ha sigut l'ordinador\n");
    printf("Fins aviat!\n");
}
int main(int argc, char *argv[])
{
    joc_t joc;
    int pos;

    if (argc != 2)
    {
        printf("Has d'indicar el nom del jugador!\n");
    }
    else
    {
        iniciar_joc(&joc, argv);
        missatge_benvinguda(&joc);
        mostrar_joc(&joc);

        while (!fi_joc(&joc))
        {
            pos = fer_jugada(&joc);
            actualitzar_joc(&joc, pos);
            mostrar_joc(&joc);
        }
        missatge_comiat(&joc);
    }
	return 0;
}

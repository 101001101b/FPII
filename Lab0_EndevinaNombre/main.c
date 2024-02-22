#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main()
{
    srand(time(NULL));
    int max, aposta, numRand = 0;
    int intents = 10;
    bool fi_joc = false;

    printf("Introdueix un nombre del 10 al 100.\n");
    do
    {
        scanf("%d", &max);
        if (max < 10 || max > 100)
        {
            printf("Tria un numero dins el rang.\n");
        }
    }
    while (max < 10 || max > 100);

    numRand = rand() % max + 1;
    //printf("%d", numRand);

    printf("Inici del joc: Endevina el numero entre 1 i %d.\n", max);

    do {
        printf("Introdueix la teva aposta. Intents restants: %d.\n", intents);
        do
        {
            scanf("%d", &aposta);
            if (aposta < 1 || aposta > max)
            {
                printf("Tria un numero dins el rang.\n");
            }
        } while (aposta < 1 || aposta > max);

        if (aposta == numRand)
        {
            printf("Correcte! El numero es %d", numRand);
            fi_joc = true;
        }
        else if (aposta < numRand)
        {
            printf("El nombre que busques es mes petit.\n");
        }
        else
        {
            printf("El nombre que busques es mes gran.\n");
        }

        intents--;

        if (intents == 0)
        {
            printf("Has esgotat el nombre d'intents. Fi del joc.\n");
            fi_joc = true;
        }

    } while (!fi_joc);

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
 
#include "funcions.h" 

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Us: %s <id_usuari>\n", argv[0]);
        return 1;
    }
    int userId = atoi(argv[1]);
    int amistatId ,amics, numSugg;
    

    /* Comprovar que l'ID esta dins del rang */
    if (userId < 0 || userId >= MAX_USERS)
    {
        printf("ID d'usuari no valid.\n");
        return 1;
    }
    /* Carregar dades dels usuaris */
    user usuaris[MAX_USERS];
    int numUsers = carregar_usuaris("usuaris.pfb", usuaris);
    if (numUsers == -1)
    {
        printf("Error carregant els usuaris.\n");
        return 1;
    }
    /* Carregar dades de proximitat */
    int propers[MAX_USERS][MAX_USERS];
    int numPropers = carregar_propers(propers, "propers.pfb");
    if (numPropers == -1)
    {
        printf("Error carregant les dades de proximitat.\n");
        return 1;
    }

    /* Bucle principal */
    int opcio;
    do
    {
        opcio = mostrar_menu(); // Mostrar menu i obtenir opcio
        switch (opcio) {
            case 1:
                mostrar_perfil(usuaris[userId]); // Mostrar perfil de l'usuari loguejat
                break;
            case 2:
                mostrar_amistats(userId, usuaris, numUsers, propers); // Mostrar amistats de l'usuari loguejat
                break;
            case 3: {
                suggeriment *suggeriments = suggerir_amistats(userId, usuaris, numUsers, propers, &numSugg); // Passem el nombre de suggeriments per referencia perque la funcio el pugui modificar directament
                if (suggeriments == NULL) {
                    printf("No hay sugerencias de amistad disponibles.\n");
                } else {
                    /* Mostrar els suggeriments d'amistats potencials */
                    printf("Usuaris que et podrien interessar:\n");
                    for (int i = 0; i < numSugg; i++)
                    {
                        int suggId = suggeriments[i].id;
                        printf("ID: %d, Nom: %s, Distancia: %d\n", usuaris[suggId].id, usuaris[suggId].nom, suggeriments[i].distancia);
                    }
                }
                /* Demanar a l'usuari si vol afegir-ne algun */
                printf("Introduiu l'ID de l'usuari que voleu afegir com a amic (o -1 per no afegir-ne cap):");
                scanf("%d", &amistatId);
                /* Comprovar que l'id introduit esta dins del rang*/
                while (amistatId < 0 || amistatId >= MAX_USERS)
                {
                    printf("Introduiu un id valid: entre 0 i %d", MAX_USERS);
                    scanf("%d", &amistatId);
                }
                afegir_amistats(userId, amistatId, usuaris, numUsers, propers); // Afegir amistats
                /* Alliberar memoria */
                free(suggeriments);
                break;
            }
            case 4:
                printf("Sortint del programa.\n");
                break;
            default:
                printf("Selecciona una opcio valida.\n");
                break;
        }
    } while (opcio != 4);
    /* Actualitzar la matriu de proximitat abans de sortir */
    actualitzar_propers(propers, numUsers);
    return 0;
}




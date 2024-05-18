#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "funcions.h" 

#define MAX_USERS 100  // Nombre maxim d'usuaris
#define MAX_PARELLS 10   // Nombre maxim de suggeriments d'amistat a mostrar

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Us: %s <id_usuari>\n", argv[0]);
        return 1;
    }
    int userId = atoi(argv[1]);
    /* Comprovar que l'ID esta dins del rang */
    if (userId < 0 || userId >= MAX_USERS) {
        printf("ID d'usuari no valid.\n");
        return 1;
    }
    /* Carregar dades dels usuaris */
    user usuaris[MAX_USERS];
    int numUsers = carregar_usuaris("usuaris.pfb", usuaris);
    if (numUsers == -1) {
        printf("Error carregant els usuaris.\n");
        return 1;
    }
    /* Carregar dades de proximitat */
    int propers[MAX_USERS][MAX_USERS];
    int numPropers = carregar_propers(propers, "propers.pfb");
    if (numPropers == -1) {
        printf("Error carregant les dades de proximitat.\n");
        return 1;
    }
    /* Bucle principal */
    int opcio;
    do {
        opcio = mostrar_menu(); // Mostrar men� i obtenir opci�
        switch (opcio) {
            case 1:
                mostrar_perfil(usuaris[userId]); // Mostrar perfil de l'usuari loguejat
                break;
            case 2:
                mostrar_amistats(userId, usuaris, numUsers, propers); // Mostrar amistats de l'usuari loguejat
                break;
            case 3:
                afegir_amistats(userId, usuaris, numUsers, propers); // Afegir amistats
                break;
            case 4:
                printf("Sortint del programa.\n");
                break;
            default:
                printf("Selecciona una opcio valida.\n");
                break;
        }
    } while (opcio != 4);
    // Actualitzar la matriu de proximitat abans de sortir
    actualitzar_propers(propers, numUsers);
    return 0;
}




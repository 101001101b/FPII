#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcions.h" 
 
/**
 * @brief Mostra menu amb les opcions del programa
 * @return Numero de l'opcio triada
 */
int mostrar_menu() {
    printf("\nMenu:\n");
    printf("1. El meu perfil\n");
    printf("2. Les meves amistats\n");
    printf("3. Afegir amistats\n");
    printf("4. Sortir\n");
    printf("Seleccioneu una opcio: ");
    int opcio;
    scanf("%d", &opcio);
    return opcio;
}

/**
 * @brief Carrega les dades dels usuaris
 * @param filename Nom del fitxer de dades d'usuaris
 * @param usuaris Array per desar les dades dels usuaris
 * @return Nombre d'usuaris carregats
 *
*/
int carregar_usuaris(const char *filename, user usuaris[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error en obrir el fitxer %s\n", filename);
        return -1;
    }
    int numUsers;
    fscanf(file, "%d", &numUsers); // La primera linia del fitxer es el nombre d'usuaris
    /* Llegir informacio de cada usuari */
    for (int i = 0; i < numUsers; i++) {
        /*fscanf(file, "%d", &usuaris[i].id);
        fscanf(file, "%s", usuaris[i].nom);
        fscanf(file, "%s", usuaris[i].poblacio);
        fscanf(file, "%s", usuaris[i].sexe);
        fscanf(file, "%s", usuaris[i].data);*/
        fscanf(file, "%d %s %s %c %s", &usuaris[i].id, usuaris[i].nom, usuaris[i].poblacio, &usuaris[i].sexe, usuaris[i].data);
    }
    fclose(file);
    return numUsers;
}

/**
 * @brief Carrega la matriu de proximitat entre usuaris
 * @param propers Matriu de proximitat a carregar
 * @param filename Nom del fitxer de dades de proximitat
 * @return Nombre d'usuaris a la matriu
 */
int carregar_propers(int propers[MAX_USERS][MAX_USERS], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error en obrir el fitxer %s\n", filename);
        return -1;
    }
    int numUsers;
    fscanf(file, "%d", &numUsers); // Llegeix el nombre d'usuaris
    /* Llegeix la matriu */
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numUsers; j++) {
            fscanf(file, "%d", &propers[i][j]);
        }
    }
    fclose(file);
    return numUsers;
}

/**
 * @brief Actualitza la matriu d'amistats de propers.fpb
 * @param propers Matriu de proximitat actualitzada
 * @param numUsers Nombre d'usuaris
 */
void actualitzar_propers(int propers[MAX_USERS][MAX_USERS], int numUsers) {
    FILE *file = fopen("propers.fpb", "w");
    if (!file) {
        printf("Error en obrir l'arxiu propers.fpb per actualitzar.\n");
        return;
    }
    fprintf(file, "%d\n", numUsers);
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numUsers; j++) {
            fprintf(file, "%d ", propers[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

/**
 * @brief Mostra les dades de l'usuari loguejat.
 * @param usuari Usuari del qual es mostrar� el perfil.
 */
void mostrar_perfil(user usuari) {
    printf("El meu perfil:\n");
    printf("ID: %d\nNom: %s\nPoblacio: %s\nSexe: %c\nData de Naixement: %s\n",
        usuari.id, usuari.nom, usuari.poblacio, usuari.sexe, usuari.data);
}

/**
 * @brief Mostra les amistats d'un usuari
 * @param userId: id de l'usuari
 * @param usuaris: punter al llistat de tots els usuaris
 * @param numUsers: nombre d'usuaris al sistema
 * @param propers: matriu de proximitat
*/
void mostrar_amistats(int userId, user *usuaris, int numUsers, int propers[][MAX_USERS]) {
    printf("Les meves amistats:\n");
    for (int j = 0; j < numUsers; j++) {
        if (propers[userId][j] == -1) { // Si l'usuari ja es amic de l'usuari_id
            mostrar_perfil(usuaris[j]);
        }
    }
}

suggeriment* suggerir_amistats(int userId, user *usuaris, int numUsers, int propers[][MAX_USERS], int *numSugg) {
    *numSugg = 0;
    /* Comptar les suggerencies */
    for (int j = 0; j < numUsers; j++) {
        if (j != userId && propers[userId][j] > 0) {
            (*numSugg)++;
        }
    }

    if (*numSugg == 0) {
        return NULL; // Si no hi ha suggerencies, retornar null
    }

    /* Assignar memoria per a les suggerencies */
    suggeriment *suggeriments = (suggeriment *)malloc(*numSugg * sizeof(suggeriment));
    if (suggeriments == NULL) {
        printf("Error en assignar memoria.\n");
        exit(1);
    }

    int index = 0;
    for (int j = 0; j < numUsers; j++) {
        if (j != userId && propers[userId][j] > 0) {
            suggeriments[index].id = j;
            suggeriments[index].distancia = propers[userId][j];
            index++;
        }
    }

    // Ordenar sugerencias en distancia creciente
    for (int i = 0; i < *numSugg - 1; i++) {
        for (int j = i + 1; j < *numSugg; j++) {
            if (suggeriments[i].distancia > suggeriments[j].distancia) {
                // Intercambiar las datos
                int tmpId = suggeriments[i].id;
                suggeriments[i].id = suggeriments[j].id;
                suggeriments[j].id = tmpId;
                int tmpDist = suggeriments[i].distancia;
                suggeriments[i].distancia = suggeriments[j].distancia;
                suggeriments[j].distancia = tmpDist;
            }
        }
    }

    return suggeriments;
}




void afegir_amistats(int userId, int amistatId, user *usuaris, int numUsers, int propers[][MAX_USERS])
{
    /* Si l'id introduit es valid i no es el mateix usuari, s'afegeir l'amistat */
    if (amistatId >= 0 && amistatId < numUsers && amistatId != userId)
    {
        propers[userId][amistatId] = -1;
        propers[amistatId][userId] = -1;
        printf("Amistat afegida.\n");
    } else if (amistatId == -1) {
        printf("No s'ha afegit cap amistat.\n");
    } else {
        printf("Id introduit invalid.\n");
    }
}





















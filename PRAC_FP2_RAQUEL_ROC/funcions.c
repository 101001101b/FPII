#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcions.h" 

#define MAX_USERS 100  // Nombre m�xim d'usuaris
#define MAX_PARELLS 10   // Nombre m�xim de suggeriments d'amistat a mostrar

/* Estructura per a desar un usuari */
/*typedef struct {
    int id;
    char nom[50];
    char poblacio[50];
    char sexe;
    char data[11];
} user;*/

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

/**
 * @brief Suggerir amistats potencials segons proximitat
 * @param userId ID de l'usuari loguejat
 * @param usuaris Llista de tots els usuaris
 * @param numUsers Nombre d'usuaris al sistema
 * @param propers Matriu de proximitat
 */
void suggerir_amistats(int userId, user *usuaris, int numUsers, int propers[][MAX_USERS]) {
    printf("Amistats potencials:\n");
    /* Matriu d'estructures per guardar suggeriments i les seves distancies */
    struct {
        int id;
        int distancia;
    } suggeriments[MAX_PARELLS];
    int count = 0;  // Suggeriments trobats
    /* Buscar suggeriments d'amistats basats en la distancia i que no siguin amics */
    for (int j = 0; j < numUsers; j++) {
        if (j != userId && propers[userId][j] > 0) {
            suggeriments[count].id = j;
            suggeriments[count].distancia = propers[userId][j];
            count++;
        }
    }
    /* Ordenar suggeriments en distancia creixent */
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (suggeriments[i].distancia > suggeriments[j].distancia) {
                /* Intercanviar les dades */
                int tmpId = suggeriments[i].id;
                suggeriments[i].id = suggeriments[j].id;
                suggeriments[j].id = tmpId;
                int tmpDist = suggeriments[i].distancia;
                suggeriments[i].distancia = suggeriments[j].distancia;
                suggeriments[j].distancia = tmpDist;
            }
        }
    }
    /* Mostrar els suggeriments d'amistats potencials */
    for (int i = 0; i < count && i < MAX_PARELLS; i++) {
        int suggId = suggeriments[i].id;
        printf("ID: %d, Nom: %s, Distancia: %d\n", usuaris[suggId].id, usuaris[suggId].nom, suggeriments[i].distancia);
    }
    /* Demanar a l'usuari si vol afegir una amistat */
    printf("\nIntroduiu l'ID de l'usuari que voleu afegir com a amic (o -1 per no afegir cap): ");
    int id_amistat;
    scanf("%d", &id_amistat);
    if (id_amistat >= 0 && id_amistat < numUsers && propers[userId][id_amistat] > 0) {
        /* Afegir l'usuari com a amic si no ho s�n */
        propers[userId][id_amistat] = -1;
        propers[id_amistat][userId] = -1;
        printf("Amistat afegid.\n");
    } else if (id_amistat == -1) {
        printf("No s'ha afegit cap amistat.\n");
    } else {
        printf("ID d'usuari inv�lid o ja s�n amics.\n");
    }
}


/**
 * @brief Permet a l'usuari loguejat afegir amistats potencials.
 * @param userId: ID de l'usuari loguejat.
 * @param usuaris: Llista d'usuaris.
 * @param numUsers: Nombre total d'usuaris.
 * @param propers: Matriu de proximitat.
 */
void afegir_amistats(int userId, user *usuaris, int numUsers, int propers[][MAX_USERS]) {
    printf("Afegir amistats:\n");
    int suggeriments[MAX_PARELLS]; // Llista de suggeriments d'amistat
    int distancies[MAX_PARELLS];
    int count = 0;
    /* Buscar suggeriments d'amistat basats en la dist�ncia */
    for (int j = 0; j < numUsers; j++) {
        /* Nom�s considera usuaris no amics amb dist�ncia positiva */
        if (propers[userId][j] > 0) {
            suggeriments[count] = j;
            distancies[count] = propers[userId][j];
            count++;
        }
    }
    /* Ordenar suggeriments per dist�ncia creixent */
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (distancies[i] > distancies[j]) {
                /* Intercanvia els suggeriments amb les dist�ncies */
                int tmp = suggeriments[i];
                suggeriments[i] = suggeriments[j];
                suggeriments[j] = tmp;

                tmp = distancies[i];
                distancies[i] = distancies[j];
                distancies[j] = tmp;
            }
        }
    }
    /*Mostra suggeriments d'amistat */
    printf("Amistats potencials:\n");
    for (int i = 0; i < count && i < MAX_PARELLS; i++) {
        int j = suggeriments[i];
        printf("ID: %d, Nom: %s\n", usuaris[j].id, usuaris[j].nom);
    }
    /* Demanar a l'usuari si vol afegir alguna amistat */
    printf("\nIntroduiu l'ID de l'usuari que voleu afegir com a amic (introduir -1 per no afegir-ne cap): ");
    int id_amistat;
    scanf("%d", &id_amistat);
    /* Si id v�lida i no �s el mateix usuari, afegir amistat */
    if (id_amistat >= 0 && id_amistat < numUsers && id_amistat != userId) {
        propers[userId][id_amistat] = -1;
        propers[id_amistat][userId] = -1;
        printf("Amic afegit.\n");
    } else if (id_amistat == -1) {
        printf("No s'ha afegit cap amistat.\n");
    } else {
        printf("ID d'usuari inv�lid.\n");
    }
}





















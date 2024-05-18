
#ifndef USUARI_H  // Control d'inclusi� peer assegurar que el fitxer nom�s es pugui incloure una vegada
#define USUARI_H

#include <stdio.h>
 
#define MAX_USERS 100  // Nombre m�xim d'usuaris
#define MAX_PARELLS 10  // Nombre m�xim de suggeriments d'amistat a mostrar

/* Estructura per a desar un usuari */
typedef struct {
    int id;
    char nom[50];
    char poblacio[50];
    char sexe;
    char data[11];
} user;

/* Funcions */

/**
 * @brief Mostra men� amb les opcions del programa
 * @return N�mero de l'opci� triada
 */
int mostrar_menu();

/**
 * @brief Carrega les dades dels usuaris
 * @param filename Nom del fitxer de dades d'usuaris
 * @param usuaris Array per desar les dades dels usuaris
 * @return Nombre d'usuaris carregats
 */
int carregar_usuaris(const char *filename, user usuaris[]);

/**
 * @brief Carrega la matriu de proximitat entre usuaris
 * @param propers Matriu de proximitat a carregar
 * @param filename Nom del fitxer de dades de proximitat
 * @return Nombre d'usuaris a la matriu
 */
int carregar_propers(int propers[MAX_USERS][MAX_USERS], const char *filename);

/**
 * @brief Mostra les dades de l'usuari loguejat
 * @param usuari Usuari del qual es mostrar� el perfil
 */
void mostrar_perfil(user usuari);

/**
 * @brief Mostra les amistats d'un usuari
 * @param userId ID de l'usuari
 * @param usuaris Llista de tots els usuaris
 * @param numUsers Nombre d'usuaris al sistema
 * @param propers Matriu de proximitat
 */
void mostrar_amistats(int userId, user *usuaris, int numUsers, int propers[][MAX_USERS]);

/**
 * @brief Suggerir amistats basades en la proximitat
 * @param userId ID de l'usuari
 * @param usuaris Llista de tots els usuaris
 * @param numUsers Nombre d'usuaris al sistema
 * @param propers Matriu de proximitat
 */
void suggerir_amistats(int userId, user *usuaris, int numUsers, int propers[][MAX_USERS]);

/**
 * @brief Permet afegir amistats potencials per a l'usuari loguejat
 * @param userId ID de l'usuari loguejat
 * @param usuaris Llista de tots els usuaris
 * @param numUsers Nombre d'usuaris al sistema
 * @param propers Matriu de proximitat
 */
void afegir_amistats(int userId, user *usuaris, int numUsers, int propers[][MAX_USERS]);

/**
 * @brief Actualitza la matriu d'amistats de propers.fpb
 * @param propers Matriu de proximitat actualitzada
 * @param numUsers Nombre d'usuaris
 */
void actualitzar_propers(int propers[MAX_USERS][MAX_USERS], int numUsers);

#endif  // USUARI_H
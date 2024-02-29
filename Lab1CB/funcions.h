/* Fitxers de capçalera per a inclusio */

/**
 * @brief Genera un aleatori entre dos valors
 * @param min (E) Valor mínim
 * @param max (E) Valor màxim
 * @return int
 */
int generar_valor(int min, int max);

/**
 * @brief Mostra en pantalla els valors d'una taula d'enters
 * @param d (E) Taula d'enters (punter a enters)
 * @param n_files (E) Nombre de files de la taula
 * @param n_cols (E) Nombre de columnes de la taula
 */
void mostrar_dades(int *d, int n_files, int n_cols);

/**
 * @brief Desa en un fitxer de text els valors d'una taula d'enters
 * @param d (E) Taula d'enters (punter a enters)
 * @param n_files (E) Nombre de files de la taula
 * @param n_cols (E) Nombre de columnes de la taula
 * @param nom (E) El nom del fitxer
 * @return bool cert -> s'ha pogut crear el fitxer, fals -> altrament
 */
bool desar_taula_fitxer_t(int *d, int n_files, int n_cols, char nom[]);

/**
 * @brief Desa en un fitxer binari els valors d'una taula d'enters
 * @param d (E) Taula d'enters (punter a enters)
 * @param n_files (E) Nombre de files de la taula
 * @param n_cols (E) Nombre de columnes de la taula
 * @param nom (E) El nom del fitxer
 * @return bool cert -> s'ha pogut crear el fitxer, fals -> altrament
 */
bool desar_taula_fitxer_b(int *d, int nf, int nc, char nom[]);

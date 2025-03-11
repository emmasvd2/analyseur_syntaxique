#ifndef PLANIFICATEUR_H
#define PLANIFICATEUR_H

#define MAX_COMMANDE 1024
#define MAX_REPERTOIRE 1024
#define MAX_ARGS 64
#define PREFIX_CHEMIN "/usr/bin/"

/**
 * \brief Demande à l'utilisateur les paramètres nécessaires pour planifier l'exécution de la commande
 */
void demander_parametres_user();

/**
 * \brief Segmenter la commande en arguments pour execv
 */
void segmenter_commande();

/**
 * \brief Gestion du chemin de la commande
 *
 * \param path Chemin de la commande
 * \param args Arguments de la commande
 */
void gestion_chemin_commande(const char *path, char **args);

/**
 * \brief Exécute la commande
 */
void executer_commande();

/**
 * \brief Exécute la commande
 */
void lanceur();

/**
 * \brief Répète l'exécution de la commande
 *
 * \param commande Commande à exécuter
 * \param delai Délai entre chaque exécution
 * \param iterations Nombre d'itérations
 */
void repetiteur();

/**
 * \brief Planificateur
 */
void planificateur();

#endif
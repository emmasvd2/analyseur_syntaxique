#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "planificateur.h"

// Déclaration de la commande comme variable globale
char commande_user[MAX_COMMANDE];          // Commande à exécuter
char *liste_argv[MAX_ARGS];                // Tableau d'arguments pour execv
int nb_argc = 0;                           // Nombre d'arguments pour execv
int delai_user = 0;                        // Délai entre chaque exécution
int iterations_user = 0;                   // Nombre d'itérations
char repertoire_execution[MAX_REPERTOIRE]; // Répertoire d'exécution

void demander_parametres_user()
{
    printf("Entrez l'intervalle de temps entre chaque exécution: ");
    scanf("%d", &delai_user);
    while ((getchar()) != '\n')
        ; // Pour vider le tampon d'entrée standard

    printf("Entrez le nombre d'itérations: ");
    scanf("%d", &iterations_user);

    while ((getchar()) != '\n')
        ; // Pour vider le tampon d'entrée standard

    printf("Entrez le répertoire d'exécution (Appuyez sur entrée pour rester dans le répertoire courant) : ");
    fflush(stdout);

    if (fgets(repertoire_execution, sizeof(repertoire_execution), stdin) == NULL)
    {
        perror("Erreur lors de la lecture de l'entrée");
        exit(1);
    }

    // Supprimer le retour à la ligne en fin de l'entrée
    repertoire_execution[strcspn(repertoire_execution, "\n")] = 0;

    // Si l'utilisateur a laissé l'entrée vide, utiliser le répertoire courant
    if (strlen(repertoire_execution) == 0)
    {
        if (getcwd(repertoire_execution, sizeof(repertoire_execution)) == NULL)
        {
            perror("Erreur lors de l'obtention du répertoire courant");
            exit(1);
        }
    }

    // Supprimer le retour à la ligne en fin de l'entrée
    repertoire_execution[strcspn(repertoire_execution, "\n")] = 0;

    printf("Quelle commande voulez-vous exécuter ? ");
    fflush(stdout);

    if (fgets(commande_user, sizeof(commande_user), stdin) == NULL)
    {
        perror("Erreur lors de la lecture de l'entrée");
        exit(1);
    }

    // Supprimer le retour à la ligne en fin de l'entrée
    commande_user[strcspn(commande_user, "\n")] = 0;
}

void segmenter_commande()
{
    char *token = strtok(commande_user, " "); // Découper la commande en arguments
    nb_argc = 0;
    while (token != NULL && nb_argc < MAX_ARGS - 1) // Stocker les arguments dans un tableau
    {
        liste_argv[nb_argc++] = token;
        token = strtok(NULL, " ");
    }
    liste_argv[nb_argc] = NULL; // Dernier élément du tableau doit être NULL pour execv
}

void gestion_chemin_commande(const char *path, char **args)
{
    if (access(path, X_OK) == 0) // Vérifier si le chemin est correct et exécutable
    {
        execv(path, args);
        perror("execv a échoué"); // S'exécutera seulement si execv échoue
    }
    else
    {
        printf("La commande n'a pas été trouvée dans %s: %s\n", PREFIX_CHEMIN, path);
        exit(EXIT_FAILURE);
    }
}

void executer_commande()
{
    if (nb_argc == 0)
    {
        printf("Aucune commande entrée. Veuillez essayer à nouveau.\n");
    }
    else if (nb_argc == 1)
    { // Une commande simple
        char chemin_commande[MAX_COMMANDE];
        snprintf(chemin_commande, sizeof(chemin_commande), "%s%s", PREFIX_CHEMIN, liste_argv[0]);
        gestion_chemin_commande(chemin_commande, liste_argv);
    }
    else
    { // Une ligne de commande complète
        char chemin_commande[MAX_COMMANDE];
        snprintf(chemin_commande, sizeof(chemin_commande), "%s%s", PREFIX_CHEMIN, liste_argv[0]);
        liste_argv[0] = chemin_commande; // Mise à jour avec le chemin complet
        gestion_chemin_commande(chemin_commande, liste_argv);
    }
}

void lanceur()
{
    if (chdir(repertoire_execution) != 0) // Changer de répertoire d'exécution
    {
        perror("chdir");
        exit(EXIT_FAILURE);
    }
    segmenter_commande(); // Découper la commande en arguments et les stocker dans un tableau global
    executer_commande();  // Exécuter la commande en utilisant les variables globales
}

void repetiteur()
{
    int i;
    struct timespec start, end;
    long sleepTime;

    for (i = 0; i < iterations_user; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start); // Enregistrer le temps de début

        pid_t pid = fork(); // Créer un processus enfant
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Processus enfant
            lanceur();
            exit(EXIT_SUCCESS); // L'enfant doit se terminer après l'exécution de la commande
        }
        else
        {
            // Processus parent
            wait(NULL); // Attendre la fin du processus enfant

            clock_gettime(CLOCK_MONOTONIC, &end); // Enregistrer le temps de fin

            // Calculer le temps écoulé et ajuster le délai
            sleepTime = delai_user - (end.tv_sec - start.tv_sec);
            if (sleepTime < 0)
            {
                fprintf(stderr, "Avertissement: le temps d'exécution de la commande dépasse le délai prévu.\n");
                sleepTime = 0;
            }

            sleep(sleepTime); // Attendre pour le prochain lancement
        }
    }
}

void planificateur()
{
    pid_t pid = fork(); // Créer un processus enfant

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Processus fils: exécute la fonction répétiteur
        repetiteur();
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Processus parent: termine immédiatement
        printf("Le répétiteur (PID: %d) a été lancé.\n", pid);
    }
}

int main()
{
    demander_parametres_user(); // Demander à l'utilisateur le délai et le nombre d'itérations
    planificateur();            // Planifier l'exécution du répétiteur et se terminer
    return 0;                   // Le planificateur se termine, le répétiteur continue dans son processus enfant
}
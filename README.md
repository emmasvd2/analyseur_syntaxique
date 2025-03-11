# Planificateur de Tâches

## Description
Ce projet est un planificateur de tâches qui permet d'exécuter des commandes de manière différée dans le temps. Il offre la possibilité de spécifier une commande, un délai entre chaque exécution, et un nombre d'itérations.

## Fonctionnalités
- **Planification de tâches différées** : Exécute des commandes à des intervalles spécifiés.
- **Gestion des processus** : Utilise `fork()` pour créer des processus enfants et `execv()` pour exécuter des commandes.
- **Précision temporelle** : Ajuste les délais en fonction du temps réel d'exécution pour éviter la dérive du temps.
- **Tests** : Inclut des tests avec les commandes `echo` et `ls` pour vérifier le bon fonctionnement du planificateur.

## Structure du Code
Le code est structuré en plusieurs fonctions distinctes :
- `segmenter_commande()`
- `executer_commande()`
- `gestion_chemin_commande()`
- Fonctions de répétition et de planification

## Utilisation
1. **Cloner le dépôt** :
    ```bash
    git clone <URL_du_dépôt>
    cd <nom_du_dépôt>
    ```
2. **Compiler le programme** :
    ```bash
    gcc -o planificateur planificateur.c
    ```
3. **Exécuter le programme** :
    ```bash
    ./planificateur
    ```

## Tests
- **Test avec `echo`** :
    ```bash
    echo "TEST1"
    echo "TEST2"
    ```
- **Test avec `ls` dans différents répertoires** :
    ```bash
    ls archi_test
    ls archi_test2
    ```

## Équipe
- Jade Delebecque
- Emma Stievenard

## Difficultés Rencontrées
- Gestion de l'entrée des commandes utilisateur avec `fgets()`
- Segmentation des commandes en arguments pour `execv()`

## Limites du Projet
- Gestion des espaces et des guillemets dans les commandes complexes
- Risques de sécurité liés aux entrées utilisateur non vérifiées
- Répertoire préfixé par `PREFIX_CHEMIN`

## Conclusion
Ce projet a permis de développer un planificateur de tâches fonctionnel, capable de gérer plusieurs tâches simultanément sans interférence. Des améliorations sont nécessaires pour renforcer la sécurité et augmenter la flexibilité du système.

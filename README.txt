Notice d'utilisation

Ce logiciel est un planificateur de tâches qui permet d'exécuter des commandes de manière différée dans le temps, avec des exécutions répétées à intervalles réguliers.

Prérequis : Compilez le programme avec le makefile

Exécution : Pour exécuter le programme, lancez-le depuis le terminal en tapant : ./planificateur

Vous serez alors invité à entrer :

L'intervalle de temps entre chaque exécution (en secondes).
Le nombre d'itérations pour l'exécution de la commande.
Le répertoire d'exécution (appuyez sur entrée pour utiliser le répertoire courant).
La commande à exécuter.
Après avoir fourni ces informations, le programme planifiera et exécutera la commande selon les paramètres spécifiés.

Cas d'utilisation
Cas 1 : Exécution simple d'une commande

Objectif : Exécuter la commande echo "Hello World" toutes les 10 secondes, 5 fois.
Étapes :
Lancez le planificateur.
Entrez 10 pour l'intervalle de temps.
Entrez 5 pour le nombre d'itérations.
Laissez le répertoire d'exécution vide pour utiliser le répertoire courant.
Entrez echo "Hello World" comme commande.
Le planificateur exécutera la commande 5 fois à intervalles de 10 secondes.

Cas 2 : Utilisation dans un répertoire spécifique

Objectif : Lister les fichiers dans un répertoire spécifique toutes les minute, 3 fois.
Étapes :
Lancez le planificateur.
Entrez 60 pour l'intervalle de temps.
Entrez 3 pour le nombre d'itérations.
Entrez le chemin du répertoire spécifique pour l'exécution.
Entrez ls comme commande.
Le planificateur listera les fichiers dans le répertoire spécifié à intervalles d'une minute.

# Vitali Melnik

## Interface et Expérience Utilisateur
- [x] numérotation automatique des ID utilisateurs.

## Gestion des Données
- [x] Tri des résultats par titre, auteur pour l’affichage (utilisation de la fonction de tri de la STL).

## &#x2611; La fonctionnalité journal d’activités.

## &#x2611; Corriger le bug


## Question 1 : C++
J'ai utilisé la librairie `chrono` pour avoir le temps actuel.

Explication ligne par ligne:
1. `system_clock::now()` donne le **time_point**, le temps depuis 1970 pour calculer le temps actuel.
2. `to_time_t(now)` convertit le **time_point** en **time_t**
3. `localtime()` Prends notre **time_t** et redonne un **pointeur**
     - Une structure **tm** permet d'avoir des dates du calendrier.
4. `put_time()` retourne un stream formaté avec les paramètres de formatage et **localTime** qu'on pourra après convertir en String.


Avec le temps actuel j'ai pu créer un journal de logs.


```cpp
_Put_time<char> FileManager::getCurrentTime() {

    auto now = chrono::system_clock::now();

    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm* localTime = localtime(&currentTime);

    return put_time(localTime, "%Y-%m-%d %H:%M:%S");
}
```

Exemple de sortie:
```txt
2026-10-08 20:00:12 - [AJOUT LIVRE] 123|123|13|1|
```
## Question 2 : Options de développement possible
Avec des millions de livres, une excellente solution est d'utiliser une base de données comme `PostgreSQL` pour ne pas sauvegarder tous les livres en mémoire. PostgreSQL nous permettra de chercher par index. On peut appeler le client de la base de données pour ajouter, supprimer, modifier, ou lire une donnée sans à avoir utiliser la mémoire pour garder tous les données qu'on a, la base de données prends seulement la donnée nécessaire au lieu de toute la collection et on n'aura plus besoin de sauvegarder les données dans un fichier .txt.

En utilisant la bibliothèque officielle **`libpqxx`**, l'application C++ établit un pool de connexions vers la base données, les opération comme recherche par le titre ou auteur sont exécutées vis des requêtres SQL paramètrées afin d'éviter les injections SQL et optimiser les executions.

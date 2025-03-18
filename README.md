# Projet de Dessin en Mode Texte

Ce projet est une application en C permettant de dessiner des formes géométriques en mode texte. L'utilisateur peut interagir avec la console pour ajouter, afficher et manipuler différentes formes.

## Fonctionnalités

- Création d'une zone de dessin (`Area`) où les formes sont placées.
- Ajout et gestion de plusieurs formes géométriques :
  - **Point**
  - **Ligne**
  - **Carré**
  - **Rectangle**
  - **Cercle**
  - **Polygone**
- Gestion des commandes pour manipuler les formes :
  - Ajouter une forme
  - Afficher la liste des formes
  - Supprimer une forme
  - Nettoyer la zone de dessin
  - Afficher l'aide des commandes disponibles
  
## Utilisation

L'utilisateur peut saisir des commandes dans la console pour interagir avec le programme. Voici quelques commandes disponibles :

- `point x y` : Ajouter un point aux coordonnées `(x, y)`.
- `line x1 y1 x2 y2` : Ajouter une ligne entre `(x1, y1)` et `(x2, y2)`.
- `square x y length` : Ajouter un carré avec le coin supérieur gauche à `(x, y)` et de côté `length`.
- `rectangle x y width height` : Ajouter un rectangle avec le coin supérieur gauche à `(x, y)`, de largeur `width` et de hauteur `height`.
- `circle x y radius` : Ajouter un cercle centré en `(x, y)` avec un rayon de `radius`.
- `polygon x1 y1 x2 y2 ... xn yn` : Ajouter un polygone avec la liste des points donnés.
- `plot` : Afficher la zone de dessin avec toutes les formes dessinées.
- `list` : Lister toutes les formes ajoutées avec leurs informations.
- `delete id` : Supprimer une forme en fonction de son identifiant `id`.
- `erase` : Supprimer toutes les formes présentes dans la zone de dessin.
- `clear` : Nettoyer la zone de dessin sans supprimer les formes.
- `help` : Afficher la liste des commandes disponibles.
- `exit` : Quitter le programme.

## Structure du Projet

Le projet est organisé en plusieurs fichiers :

- **`main.c`** : Contient la boucle principale du programme et gère les interactions utilisateur.
- **`area.h / area.c`** : Définit la structure `Area` et les fonctions liées à la gestion de la zone de dessin.
- **`shapes.h / shapes.c`** : Définit les différentes formes géométriques et leurs fonctions associées.
- **`commandes.h / commandes.c`** : Gère les commandes utilisateur et leur exécution.

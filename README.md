# Same Gnome Game

Jeu de puzzle console en C, clone du SameGame/Same Gnome. Le joueur sélectionne des groupes de billes adjacentes de même couleur sur une grille, les supprime et marque des points.

## Règles du jeu

- Grille de **10 lignes × 15 colonnes**
- **3 couleurs** de billes : Rouge (R), Vert (V), Bleu (B)
- Sélectionner un groupe de billes adjacentes de même couleur
- Le groupe se supprime et les billes au-dessus tombent
- Les colonnes vides glissent vers la gauche
- Score : `(taille_groupe - 1)²` points par suppression
- La partie se termine quand il ne reste plus de billes ou plus de mouvements possibles

## Compilation et exécution

Aucune dépendance externe. Compilateur C requis.

```bash
# Version plateau aléatoire (3 couleurs)
gcc -o SG_alea SG_alea.c && ./SG_alea

# Version plateau par fonction mathématique
gcc -o SG_math SG_math.c -lm && ./SG_math

# Version la plus simple (toutes vertes)
gcc -o SG_3 SG_3.c && ./SG_3
```

## Fichiers du projet

| Fichier | Description |
|---------|-------------|
| `SG_3.c` | Version de base - plateau monochrome (toutes vertes) |
| `SG_4.c` | Ajout d'une bille bleue pour test |
| `SG_5.c` | Ajout d'une ligne bleue complète pour test |
| `SG_6.c` | Ajout de plusieurs lignes bleues pour test |
| `SG_7.c` | Ajout d'une colonne bleue verticale pour test |
| `SG_8.c` | Patterns de test plus complexes |
| `SG_alea.c` | Génération aléatoire du plateau (3 couleurs) |
| `SG_math.c` | Génération déterministe par fonction `sin()` |

## Fonctionnalités techniques

- **Rendu coloré** via codes d'échappement ANSI (reverse video)
- **Sélection de groupe** par flood-fill récursif
- **Gravité** : les billes s'écroulent vers le bas
- **Décalage** : les colonnes vides glissent vers la gauche
- **Validation d'entrée** : vérification des bornes et cases vides

## Structure de données

```c
typedef struct Case {
    char bille;   // 'R', 'V', 'B', 'x' (sélectionnée), 'o' (vide)
    int occupe;   // 1 = occupée, 0 = vide
} Case;

typedef struct Plateau {
    Case mat[10][15];
    int nb_occupe;  // nombre total de billes restantes
} plateau;
```

## Auteur

Projet réalisé dans le cadre d'un projet universitaire.

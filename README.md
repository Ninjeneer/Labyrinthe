## Projet réalisé dans le cadre d'un TP de l'ENSICAEN

# Compte-rendu de projet
Auteur : Loan Alouache

## Labyrinthe - Manuel utilisateur
### Démarrer le jeu
Afin de démarrer le jeu, il suffit d'entrer la commande `make run` (ou `./game` si celui-ci a déjà été généré) dans le répertoire du jeu.
Le jeu utilisant une table ASCII étendue propre aux systèmes UNIX, ainsi que des commandes systèmes, celui-ci ne peut s'exécuter que dans un environnement UNIX **sur un terminal différent de celui de CLion.**
Pour une expérience graphique plus agréable, assurez-vous de posséeder un terminal ayant une largeur plus grande que 101 caractères.

Une fois le jeu lancé, un menu apparaîtra et vous demandera de faire un choix :

 1. Créer un labyrinthe
 2. Charger un labyrinthe
 3. Jouer
 4. Tableau des scores
 5. Quitter

### 1. Créer un labyrinthe
Si c'est la première fois que vous lancez le jeu, il vous faudra tout d'abord créer un ou plusieurs labyrinthes. Il est évidemment possible d'en créer à n'importe quel moment.

Il vous sera demandé plusieurs paramètres durant sa création :

- ***Difficulté*** : F pour le mode facile, et D pour le mode difficile
La difficulté influe sur deux facteurs : dans le mode facile, il n'existe qu'un seul chemin pour sortir du labyrinthe et aucun monstre ne jalonnent ce dernier. A l'inverse, le mode difficile propose plusieurs chemins possibles, ainsi que des monstres.
- ***Largeur et Hauteur*** : ces deux paramètres représentent les dimensions souhaitées du labyrinthe. Elles doivent êtres **impaires** et **supérieures à 3**.
- ***Nom*** : ce paramètre représente le nom du labyrinthe. C'est sous ce nom qu'il sera enregistré, et c'est par celui-ci que vous pourrez le charger de nouveau.

Une fois le labyrinthe créé, il est automatiquement chargé et vous serez redirigé vers le menu. Vous pouvez dores et déjà jouer (voir 3.).

### 2.Charger un labyrinthe
Si vous possédez des labyrinthes déjà enregistrés, vous pouvez les charger et jouer dessus.
Une liste de labyrinthes déjà créés s'affichera, et vous serez invité à en choisir un en écrivant son nom **sans renseigner son extension** (.cfg).

Une fois le labyrinthe chargé, vous serez redirigé vers le menu. Vous pouvez maintenant jouer (voir 3.).

### 3. Jouer
Votre mission est de sortir du labyrinthe avec un sort le plus élevé possible. Vous démarrez tout en haut à gauche de la carte, et la sortie se trouve en bas à droite de celle-ci.

**Touches de déplacement**

| Avancer   | Aller à gauche   | Reculer  | Aller à droite |
|:---------:|:----------------:|:--------:|:--------------:|
| `Z`       | `Q`              | `S`      | `D`            |

Vous trouverez sur votre parcours des *trésors* représentés par le symbole `T` et des *pièges* représentés par le symbole `P`. Ramasser un trésor vous gratifiera de 15 points, et tomber dans un piège vous pénalisera de 10 points. 
Chaque pas que vous effectuez vous enlève un point : choisissez bien votre trajectoire !

Si vous jouez en mode difficile, vous devez également éviter les monstres qui parcourent le labyrinthe. Vous rencontrerez des ogres représentés par le caractère `O` qui se déplacent normalement, et des fantômes représentés par le caractère `F` qui peuvent traverser les mûrs. Le ratio Ogres/Fantômes est aléatoire, ainsi il est possible de tomber sur des parties remplies de fantômes ou d'ogres seulement. Si un de ces monstres vous touche, vous perdez autant de point que celui à de liberté de mouvement.

Si vous faites partie des 10 premiers à avoir jouer ce labyrinthe, ou bien des 10 plus hauts scores, il vous sera possible d'enregistrer votre score ainsi que votre pseudonyme (voir 4.).

**Récapitulatif de l'affichage**

| Caractère     | Signification   |
|:-------------:|:---------------:|
| `o`           | Joueur          |
| `█`           | Mur             |
| `T`           | Trésor          |
| `P`           | Piège           |
| `O`           | Ogre            |
| `F`           | Fantôme         |

### 4. Tableau des scores
Chaque labyrinthe possède un tableau des scores afin de sauvegarder vos meilleurs scores.
Pour ouvrir le tableau des scores, vous devez charger un labyrinthe (voir 2.), puis depuis le menu, choisir `4. Tableau des scores`.

Pour avoir l'honneur de faire partie de ce tableau des scores vous devez remplir au moins une de ces deux conditions :

 1. Faire partie des 10 premiers joueurs à jouer dans le labyrinthe
 2. Avoir un score supérieur à un ou des scores présents dans le tableau des scores

### 5. Quitter
Ferme le jeu

----

## Labyrinthe - Manuel développeur
### Compilation
Pour compiler le projet, entrez la commande suivante 

`make`

Pour compiler la suite de tests, entrez la commande suivante

`make testsuite` (l'utilisation de MinUnit créera des warnings, celui-ci étant incompatible avec les options de warning utilisés lors de la compilation)

Pour exécuter les tests unitaires, entrez la commande suivante

`make run_test`
### Tâches réalisées
- Génération d'un labyrinthe parfait de taille dynamique
- Déplacement du joueur dans celui-ci
- Enregistrement et chargement d'un labyrinthe dans des fichiers
- Placement de trésors et de pièges, gestion du score joueur et enregistrement dans des fichiers
- Différenciation mode facile/difficile, ajout de plusieurs chemins et de monstres en mode difficile
- Tests unitaires
- Saisie sécurisée (format de donnée, espaces...)
- Documentation Doxygen
- Makefile
- Déplacement des ogres en fonction d'un trésor croisé

   - Les ogres se déplacent dans leur périmètre autour de leur point d'apparition. Lorsqu'ils croisent un trésor, le centre de leur périmètre devient le trésor.
- Déplacement des monstres : paramètre d'étendue de mobilité

    - Les ogres restent dans leurs périmètres
    - Les fantômes restent dans leurs périmètres et peuvent traverser les murs

### Tâches restantes

- Déplacement des fantômes : leur comportement fonctionne parfaitement, mais il arrive que les fantômes ne bougent pas à certains tours.

### Fonctionnement des points clés

***1. Génération du labyrinthe***

La génération du labyrinthe se fait en suivant l'algorithme de fusion aléatoire des chemins. Un des problèmes qui se pose ici est le choix du mur à casser, qui se fait de manière aléatoire. En tirant aléatoirement X murs au sein d'une grille M\*N, il y a un risque de tomber plusieurs fois sur le même mur incassable et donc de réaliser plus de M\*N tirages, voire même dans le pire des cas ne jamais sortir de la boucle. Afin d'optimiser un minimum cet algorithme, j'ai décidé d'implémenter une structure de données différentes, en utilisant **une liste de murs**. A chaque fois que l'on tire un mur aléatoirement, on le retire de la liste, qu'il soit cassable ou non. Ainsi, dans le pire dans des cas, on réalise M*N tour de boucle (*Ex : labyrinthe de 301x301 généré en moins de 3s*).

***2. Mise à jour des cases***

Lorsque l'on casse un mur, il faut mettre à jour la valeur de toutes les cases communicantes. Pour cela j'ai adopté une fonction récursive, permettant ainsi de parcourir uniquement les cases qui ont besoin d'être mises à jour, et non tout le tableau à la recherche des cases adéquat.

***3. Gestion de la carte***

Pour la gestion des données du labyrinthe, j'ai utilisé une structure comportant diverses informations. Concernant la structure même du labyrinthe, j'ai volontairement décidé de ne **pas** implémenter la solution d'un tableau de structure Étiquette/Valeur mais **uniquement** un tableau de int. Ce choix vient de la volonté de ne pas vouloir mélanger la partie affichage de la partie métier. Ce choix d'implémentation me permet ainsi de **manipuler plus facilement les fichiers**, et de ne **modifier qu'une seule et unique fonction** en cas de changement graphique (changement de caractères, voire même création d'une interface graphique).

***4. Déclaration anticipée***

Durant le développement, j'ai rencontré un problème de dépendances circulaires. En effet, mon fichier `game.h` dépendait de la structure *Coordinate* présente dans le fichier `labyrinth.h`, mais ce dernier dépendant de la structure *Monster* présente dans le fichier `game.h`. Ainsi, une des solution à ce problème est la **déclaration anticipée** (*forward declaration*). Cela revient à déclarer la présence d'une structure Monster dans mon `labyrinth.h` mais sans l'initialiser et sans inclure le fichier `game.h`, qu'il faudra uniquement inclure dans le fichier `labyrinth.c`.
```C
/* Labyrinth.h */
typedef struct {  
	char *name;  
	int **matrix;  
	int nbRow;  
	int nbCol;  
	int loaded;  
	int difficulty;  
	struct Monster *monsters; /* Forward declaration */  
	int nbMonsters;  
} Map;
```
### Limitations/Bugs connus
En temps normal, les cartes ainsi que les scores sont respectivement stockés dans les dossiers `maps/` et `scores/`. Or, si ces deux dossier ne sont pas au créés au préalable, l'enregistrement et/ou la lecture des fichiers ne fonctionne pas. Il existe évidemment une fonction pour faire cela (`mkdir`) mais j'ai été limité par le réseau de l'école. En effet, lorsque le jeu est lancé par l'intermédiaire de CLion, le dossier créé appartient donc au propriétaire de CLion, qui n'est d'autre que l'utilisateur *adminlinux*. Par conséquent, il devenait impossible d'écrire et de lire dans ce dossier, ni même de le supprimer.

# Labyrinthe - Manuel développeur
## Tâches réalisées
- Génération d'un labyrinthe parfait de taille dynamique
- Déplacement du joueur dans celui-ci
- Enregistrement et chargement d'un labyrinthe dans des fichiers
- Placement de trésors et de pièges, gestion du score joueur et enregistrement dans des fichiers
- Différenciation mode facile/difficile, ajout de plusieurs chemins et de monstres en mode difficile
- Déplacement des monstres (Ogre normal, fantôme pouvant traverser les mûrs...)
- Tests unitaires
- Documentation entière Doxygen
- Manuel utilisateur

## Tâches restantes
- Déplacement des ogres en fonction d'un trésor croisé
- Déplacement des monstres : paramètre d'étendue de mobilité

## Fonctionnement des points clés

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
	int nbLig;  
	int nbCol;  
	int loaded;  
	int difficulty;  
	struct Monster *monsters; /* Forward declaration */  
	int nbMonsters;  
} Map;
```
## Limitations/Bugs connus
En temps normal, les cartes ainsi que les scores sont respectivement stockés dans les dossiers `maps/` et `scores/`. Or, si ces deux dossier ne sont pas au créés au préalable, l'enregistrement et/ou la lecture des fichiers ne fonctionne pas. Il existe évidemment une fonction pour faire cela (`mkdir`) mais j'ai été limité par le réseau de l'école. En effet, lorsque le jeu est lancé par l'intermédiaire de CLion, le dossier créé appartient donc au propriétaire de CLion, qui n'est d'autre que l'utilisateur *adminlinux*. Par conséquent, il devenait impossible d'écrire et de lire dans ce dossier, ni même de le supprimer.

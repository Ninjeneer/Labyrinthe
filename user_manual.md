# Labyrinthe - Manuel utilisateur
## Démarrer le jeu
Afin de démarrer le jeu, il suffit de lancer l'exécutable XXX via la commande `./XXXX` dans le répertoire du jeu.
Le jeu utilisant une table ASCII étendue propre aux systèmes UNIX, ainsi que des commandes systèmes, celui-ci ne peut s'exécuter que dans un environnement UNIX, différent du terminal CLion.
Pour une expérience graphique plus agréable, assurez-vous de posséeder un terminal ayant une largeur plus grande que 101 caractères.

Une fois le jeu lancé, un menu apparaîtra et vous demandera de faire un choix :

 1. Créer un labyrinthe
 2. Charger un labyrinthe
 3. Jouer
 4. Tableau des scores
 5. Quitter

## 1. Créer un labyrinthe
Si c'est la première fois que vous lancez le jeu, il vous faudra tout d'abord créer un ou plusieurs labyrinthes. Il est évidemment possible d'en créer à n'importe quel moment.

Il vous sera demandé plusieurs paramètres durant sa création :

- ***Difficulté*** : F pour le mode facile, et D pour le mode difficile
La difficulté influe sur deux facteurs : dans le mode facile, il n'existe qu'un seul chemin pour sortir du labyrinthe et aucun monstre ne jalonnent ce dernier. A l'inverse, le mode difficile propose plusieurs chemins possibles, ainsi que des monstres.
- ***Largeur et Hauteur*** : ces deux paramètres représentent les dimensions souhaitées du labyrinthe. Elles doivent êtres **impaires** et **supérieures à 3**.
- ***Nom*** : ce paramètre représente le nom du labyrinthe. C'est sous ce nom qu'il sera enregistré, et c'est par celui-ci que vous pourrez le charger de nouveau.

Une fois le labyrinthe créé, il est automatiquement chargé et vous serez redirigé vers le menu. Vous pouvez dores et déjà jouer (voir 3.).

## 2.Charger un labyrinthe
Si vous possédez des labyrinthes déjà enregistrés, vous pouvez les charger et jouer dessus.
Une liste de labyrinthes déjà créés s'affichera, et vous serez invité à en choisir un en écrivant son nom **sans renseigner son extension** (.cfg).

Une fois le labyrinthe chargé, vous serez redirigé vers le menu. Vous pouvez maintenant jouer (voir 3.).

## 3. Jouer
Votre mission est de sortir du labyrinthe avec un sort le plus élevé possible. Les murs sont représentés par le caractère `#`. Vous démarrez tout en haut à gauche de la carte, et la sortie se trouve en bas à droite de celle-ci.

**Touches de déplacement**

| Avancer   | Aller à gauche   | Reculer  | Aller à droite |
|:---------:|:----------------:|:--------:|:--------------:|
| `Z`       | `Q`              | `S`      | `D`            |

Vous trouverez sur votre parcours des *trésors* représentés par le symbole `T` et des *pièges* représentés par le symbole `P`. Ramasser un trésor vous gratifiera de 15 points, et tomber dans un piège vous pénalisera de 10 points. 
Chaque pas que vous effectuez vous enlève un point : choisissez bien votre trajectoire !

Si vous jouez en mode difficile, vous devez également éviter les monstres qui parcourent le labyrinthe. Vous rencontrerez des ogres représentés par le caractère `O` qui se déplacent normalement, et des fantômes représentés par le caractère `F` qui peuvent traverser les mûrs. Si un de ces monstres vous touche, vous perdez 20 points.

Si vous faites partie des 10 premiers à avoir jouer ce labyrinthe, ou bien des 10 plus hauts scores, il vous sera possible d'enregistrer votre score ainsi que votre pseudonyme (voir 4.).

**Récapitulatif de l'affichage**

| Caractère     | Signification   |
|:-------------:|:---------------:|
| `o`           | Joueur          |
| `#`           | Mur             |
| `T`           | Trésor          |
| `P`           | Piège           |
| `O`           | Ogre            |
| `F`           | Fantôme         |

## 4. Tableau des scores
Chaque labyrinthe possède un tableau des scores afin de sauvegarder vos meilleurs scores.
Pour ouvrir le tableau des scores, vous devez charger un labyrinthe (voir 2.), puis depuis le menu, choisir `4. Tableau des scores`.

Pour avoir l'honneur de faire partie de ce tableau des scores vous devez remplir au moins une de ces deux conditions :

 1. Faire partie des 10 premiers joueurs à jouer dans le labyrinthe
 2. Avoir un score supérieur à un ou des scores présents dans le tableau des scores

## 5. Quitter
Ferme le jeu


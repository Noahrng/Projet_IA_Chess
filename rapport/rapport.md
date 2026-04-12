---
header-includes:
  - \usepackage{graphicx}

include-before: |
  \begin{titlepage}
    \centering

    \includegraphics[width=10cm]{image/logo_upvd.png} \\[1cm]

    {\Large \textbf{Génie Logiciel -- L3 Informatique} \\[0.5cm]}
    {\Large \textbf{31 mars 2026} \\[0.5cm]}
    
    \rule{.8\linewidth}{0.5mm} \\[0.5cm]
    {\Huge \textbf{Rapport du projet : \\ IA d'Échecs}} \\[0.5cm]
    \rule{.8\linewidth}{0.5mm} \\[1.5cm]
    
    {\Large FAVRIOU Valentin \\ 
    ARANEGA Noah \\[1cm]}

    {\Large Encadrant: ANTUNES Benjamin \\[1cm]}
      
  \end{titlepage}
---

\newpage

# Introduction

Le jeu d'échecs est un des jeux les plus anciens de l'histoire qui est encore populaire de nos jours. Faisant son apparition autour du 6ème siècle après J-C, il mélange stratégie, anticipation, prise dé decisions  dans un environnement complexe et réflexion du joueur.  

Le jeu d'échecs oppose deux armées, une blanche et une noire, composées de 8 pions, 2 fous, 2 cavaliers, 2 tours, 1 reine et 1 roi sur un plateau de 8 cases par 8 cases. Le but est de mettre en échec et mat le joueur adverse, c'est-à-dire de faire en sorte que le roi soit attaqué sans que le joueur puisse le bouger ou le défendre.

Chaque pièce a des déplacements spéciaux:  
- Le **pion** peut se déplacer en avant d'une case sauf si la case est bloquée par une autre pièce. Son premier coup peut avancer de deux cases, et il ne peut manger une pièce que si elle se trouve en diagonale une case devant elle.  
- Le **fou** peut se déplacer qu'en diagonale, il ne peut pas passer à travers une pièce mais peut la manger si elle se trouve dans ses diagonales.  
- Le **cavalier** peut se déplacer en forme de L, il peut passer au dessus de n'importe quelle pièce et peut la manger si elle se trouve sur sa case de déplacement. (ex: si le cavalier se trouve en (5,5), il peut aller en (3,6), (3,4), (7,6), (7,4), (6,3), (4,3), (6,7) et (4,7).)  
- La **tour** peut se déplacer verticalement et horizontalement (dans sa colonne et sa ligne), tout comme le fou il ne peut pas passer au dessus d'une pièce mais il peut la manger si elle est sur son chemin.  
- La **reine** hérite des déplacements de la tour et du fou, elle peut se déplacer en diagonales et sur sa ligne et sa colonne.  
- Le **roi** peut bouger d'une case dans toutes les directions (nord, est, sud, ouest, nord-est, sud-est, sud-ouest et nord-ouest), mais il doit faire attention à ne pas être en échec s'il se déplace sur une de ces cases.  

Le jeu d'échecs est un jeu très complexe qui requiert beaucoup de capacités intellectuelles pour pouvoir anticiper plusieurs coups d'avances et par conséquent être fort à ce jeu. L'Intelligence Artificielle (IA) a réussi à impacter ce jeu, notamment en 1997 lorsque le superordinateur IA Deep Blue bat le champion du monde Garry Kasparov. 

Cet épisode de l'histoire des échecs nous a inspiré à recréer une IA qui soit capable de jouer aux échecs de manière autonome, en analysant la meilleure décision à prendre dans chaque position où elle se trouve.

Ce rapport présentera tout d'abord l'application que l'on a conçue, pour ensuite présenter l'architecture logicielle, suivi du diagramme des classes UML de notre projet, nous rebondirons ensuite sur les patrons de conceptions que nous avons utilisé pour notre projet, puis nous aborderons ensuite les outils logiciells utilisés, les tâches effectuées et les difficultés rencontrées.



# Présentation de l'Applicaton

# Présentation de l'architecture logicielle

L’application a été conçue selon une architecture modulaire, permettant de séparer clairement les différentes responsabilités du système. Cette organisation facilite la compréhension, la maintenance et l’évolution du code.

L’architecture repose sur plusieurs composants principaux :  
Tout d’abord, la gestion du jeu est assurée par un ensemble de classes représentant les éléments fondamentaux des échecs. La classe Piece constitue une classe de base dont héritent les différentes pièces du jeu telles que Pawn, Rook, Knight, Bishop, Queen et King. L’échiquier et les positions sont gérés à l’aide des classes Player et Coordinates, permettant de représenter l’état du jeu à tout instant.

La logique du jeu est centralisée dans la classe GameController, qui gère le déroulement d’une partie, les déplacements des pièces, ainsi que les règles du jeu (déplacements valides, échecs, captures, etc.). Cette classe joue un rôle central dans la coordination des différents composants du projet.

Le module d’intelligence artificielle est principalement composé des classes Minimax et Evaluator. La classe Minimax implémente un algorithme de recherche permettant d’explorer les coups possibles afin de déterminer le meilleur choix. Elle s’appuie sur la classe Evaluator, qui attribue un score à une position donnée en fonction de différents critères (valeur des pièces, position sur l’échiquier, etc.). Cette séparation permet de distinguer clairement la logique de recherche de celle d’évaluation.

L’interface utilisateur est divisée en deux parties : une interface graphique (GraphicDisplay) et une interface terminale (TerminalDisplay). Ces composants permettent d’interagir avec le joueur et d’afficher l’état du jeu. Des classes supplémentaires telles que Button, Shape ou TextShape sont utilisées pour gérer les éléments graphiques.

Enfin, des classes utilitaires comme MoveHistory permettent de suivre les coups joués, tandis que Player représente les joueurs et leurs pièces.

Les différents modules interagissent de manière structurée. Par exemple, l’intelligence artificielle utilise l’état du jeu fourni par GameController pour simuler des coups, tandis que l’interface récupère ces informations pour les afficher à l’utilisateur.

Cette architecture repose sur une séparation claire des responsabilités, rendant le code plus modulaire, maintenable et évolutif.

# Diagramme de classes UML

# Diagramme de séquence UML

# Patrons de Conception utilisés

Modèle-Vue-Controlleur :

Modèle
Vue
Controlleur

Memento : 
Historique des coups

# Outils logiciels utilisés

# Tableau des Tâches

# Difficultés rencontrées

# Conclusion
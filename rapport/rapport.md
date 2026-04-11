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

# Diagramme de classes UML

# Diagramme de séquence UML

# Patrons de Conception utilisés

# Outils logiciels utilisés

# Tableau des Tâches

# Difficultés rencontrées

# Conclusion
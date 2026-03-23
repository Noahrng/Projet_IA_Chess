# Projet_IA_Chess

## Description du Projet

Notre projet consiste à développer une IA capable de jouer aux échecs de manière autonome. L'objectif est de simuler un joueur qui est capable d'analyser un plateau, anticiper les coups adverses et calculer le meilleur coup possible pour prendre l'avantage sur l'adversaire.

## Prérequis Système

## Instructions d'installations détaillées

## Instructions pour lancer l'application

Dans le répertoire du projet, exécutez la commande suivante pour construire l'image docker :
docker build -t aichess .

Pour lancer l'image, exécutez les deux commandes suivantes :
```bash
xhost +local:docker
docker run -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix aichess
```
## Instructions Pour exécuter les tests


## Structure du Projet
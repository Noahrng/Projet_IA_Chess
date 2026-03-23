# Projet_IA_Chess

## Description du Projet

Notre projet consiste à développer une IA capable de jouer aux échecs de manière autonome. L'objectif est de simuler un joueur qui est capable d'analyser un plateau, anticiper les coups adverses et calculer le meilleur coup possible pour prendre l'avantage sur l'adversaire.

## Prérequis Système

Le seul prérequis système est d'avoir docker d'installé sur votre machine.

## Instructions d'installations détaillées

Dans le répertoire du projet, exécutez la commande suivante pour construire l'image docker :
```bash
docker build -t aichess .
```

## Instructions pour lancer l'application

Pour lancer l'image, exécutez les deux commandes suivantes :
```bash
xhost +local:docker
docker run -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix aichess
```
## Instructions Pour exécuter les tests

Si docker n'est pas utilisé :
```bash
./build/AICHESS
```
dans le répertoire du projet.



## Structure du Projet

.<br>
├── src/                # Code source (.cpp)<br>
├── include/            # Headers (.hpp) <br>
├── build/              # Fichiers compilés <br>
├── Dockerfile          # Configuration Docker <br>
├── Makefile            # Script de compilation <br>
└── README.md <br>
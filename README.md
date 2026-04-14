# Projet_IA_Chess

## Description du Projet

Notre projet consiste à développer une IA capable de jouer aux échecs de manière autonome. L'objectif est de simuler un joueur qui est capable d'analyser un plateau, anticiper les coups adverses et calculer le meilleur coup possible pour prendre l'avantage sur l'adversaire.

## Prérequis Système

### Avec Docker
- Docker installé sur votre machine

### Avec Guix
- Guix installé sur votre machine
- Pour installer Guix :
```bash
sudo apt install guix
```

## Instructions d'installations détaillées

### Avec Docker
```bash
docker build -t aichess .
```

### Avec Guix
```bash
guix shell --manifest=guix.scm
make clean && make
```

## Instructions pour lancer l'application

### Avec Docker
Pour lancer l'image, exécutez les deux commandes suivantes :
```bash
xhost +local:docker
docker run --rm -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix aichess
```
Si vous voulez utiliser valgrind, faites la commande suivante :
```bash
docker run --rm -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix aichess valgrind ./build/AICHESS
```
### Avec Guix
```bash
./build/AICHESS
```

## Instructions pour exécuter les tests

Si docker n'est pas utilisé :
```bash
./build/AICHESS
```
dans le répertoire du projet.



## Structure du Projet
```text
.
├── src/                # Code source (.cpp)
├── include/            # Headers (.hpp) 
├── build/              # Fichiers compilés 
├── rapport/            # Rapport du Projet
├── Dockerfile          # Configuration Docker 
├── guix.scm            # Configuration guix
├── Makefile            # Script de compilation 
└── README.md 
```
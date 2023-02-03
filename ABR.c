#include "meteo.h"


pArbre creationArbre(float a) { // Fonction qui crée et initialise un arbre.
    pArbre nouveau1 = malloc(sizeof(Arbre));
    Store *nouveau2 = malloc(sizeof(Store));
    if((nouveau1 == NULL) || (nouveau2 == NULL)) {
        exit(1);
    }
    nouveau2->donnee = a;
    nouveau1->element = nouveau2;
    nouveau1->fd = NULL;
    nouveau1->fg = NULL;
    nouveau1->equilibre = 0;
    nouveau1->hauteur = 0;
    return nouveau1;
}


pArbre creationArbreTps(time_t a) { // Création d'un arbre avec comme racine une donnée de type "time_t" représentant une date en secondes.
    pArbre nouveau1 = malloc(sizeof(Arbre));
    Store *nouveau2 = malloc(sizeof(Store));
    if((nouveau1 == NULL) || (nouveau2 == NULL)) {
        exit(1);
    }
    nouveau2->secondes = a;
    nouveau1->element = nouveau2;
    nouveau1->fd = NULL;
    nouveau1->fg = NULL;
    nouveau1->equilibre = 0;
    nouveau1->hauteur = 0;
    return nouveau1;
}


pArbre ajouterFilsGauche(pArbre a, float e) { // Fonction pour ajouter un fils gauche.
    if(!estVide(a)) {
        a->fg = creationArbre(e);
        a->fg->hauteur = hauteur(a->fg);
        a->equilibre = hauteur(a->fd) - hauteur(a->fg);
    }
    return a;
}


pArbre ajouterFilsDroit(pArbre a, float e) { // Fonction pour ajouter un fils droit.
    if(!estVide(a)) {
        a->fd = creationArbre(e);
        a->fd->hauteur = hauteur(a->fd);
        a->equilibre = hauteur(a->fd) - hauteur(a->fg);
    }
    return a;
}


pArbre insertABR(pArbre a, float e) { // Fonction pour insérer un élement de façon à ce que l'arbre soit un ABR.
    pArbre temp = NULL;
    if(estVide(a)) {
        return creationArbre(e);
    }
    else if(a->element->donnee == e) {
        return a;
    }
    else if(e < a->element->donnee) {
        temp = insertABR(a->fg, e);
        a->fg = temp;
    }
    else if(e > a->element->donnee) {
        temp = insertABR(a->fd, e);
        a->fd = temp;
    }
}


int estVide(pArbre a) { // Vérifie si le noeud est vide ou pas.
    if(a == NULL) {
        return 1;
    }
    return 0;
}


int existeFilsGauche(pArbre a) { // Vérifie s'il existe un fils gauche au noeud.
    if((a != NULL) && (a->fg != NULL)) {
        return 1;
    }
    return 0;
}


int existeFilsDroit(pArbre a) { // Vérifie s'il existe un fils droit au noeud.
    if((a != NULL) && (a->fd != NULL)) {
        return 1;
    }
    return 0;
}


void verification_fichier(FILE *fichier) { // Vérifie qu'il n'y a pas de problème lors de l'ouverture du fichier.
    if (fichier == NULL) {
        printf("\nProblème lors de l'ouverture d'un fichier !\n");
        printf("Code d'erreur : %d\n", errno);
        printf("Message d'erreur : %s\n", strerror(errno));
        exit(1);
    }
}


void traiterTP1(pArbre a) { // affiche dans un fichier les stations avec leur températures moyennes, maximales et mimnimales.
    if(!estVide(a)) {
        FILE *fichier = NULL;
        fichier = fopen("donneesTriees.dat", "a");
        verification_fichier(fichier);
        fprintf(fichier, "%d %f %f %f\n", a->element->idStation, a->element->moyenne, a->element->maximum, a->element->minimum);
        fclose(fichier);
    }
}


void traiterTP2(pArbre a) { // affiche dans un fichier la date et la température associée.
    if(!estVide(a)) {
        FILE *fichier = NULL;
        fichier = fopen("donneesTriees.dat", "a");
        verification_fichier(fichier);
        fprintf(fichier, "%s %f\n", a->element->date, a->element->moyenne);
        fclose(fichier);
    }
}


void traiterH(pArbre a) { // Affiche dans un fichier l'altitude avec la longitude et la latitude correspondant des stations.
    if(!estVide(a)) {
        FILE *fichier = NULL;
        fichier = fopen("donneesTriees.dat", "a");
        verification_fichier(fichier);
        fprintf(fichier, "%f %f %f\n", a->element->donnee, a->element->donnee1, a->element->donnee2);
        fclose(fichier);
    }
}


void traiterW(pArbre a) { // Affiche dans un fichier l'identifiant des stations, leur latitude et leur longitude ainsi que la direction et la vitesse des vents pour chaque station.
    if(!estVide(a)) {
        FILE *fichier = NULL;
        fichier = fopen("donneesTriees.dat", "a");
        verification_fichier(fichier);
        fprintf(fichier, "%d %f %f %f %f\n", a->element->idStation, a->element->donnee1, a->element->donnee2, a->element->moyenne, a->element->moyenne2);
        fclose(fichier);
    }
}


void traiter1M(pArbre a) { // Affiche dans un fichier l'humidité maximale avec la longitude et la latitude correspondant à la station associée.
    if(!estVide(a)) {
        FILE *fichier = NULL;
        fichier = fopen("donneesTriees.dat", "a");
        verification_fichier(fichier);
        fprintf(fichier, "%f %f %f\n", a->element->maximum, a->element->donnee1, a->element->donnee2);
        fclose(fichier);
    }
}
#include "meteo.h"


Chainon* creationChainon(pArbre a) { // Fonction qui crée et initialise un chainon.
    Chainon *nouveau = malloc(sizeof(Chainon));
    if(nouveau == NULL) {
        exit(1);
    }
    nouveau->elmt = a;
    nouveau->suivant = NULL;
    return nouveau;
}


FileDyn* creationFileDyn() { // Fonction qui crée et initialise une file.
    FileDyn *file = malloc(sizeof(FileDyn));
    if(file == NULL) {
        exit(1);
    }
    file->tete = NULL;
    file->queue = NULL;
    return file;
}


FileDyn* enfile(FileDyn *file, pArbre a) { // Fonction qui enfile des chainons dans une file.
    if(!estVide(a)) {
        Chainon *nouveau = creationChainon(a);
        if(file->queue == NULL) { // Si la file est vide.
            file->tete = nouveau;
            file->queue = nouveau;
            file->tete->suivant = nouveau;
        }
        else {
            file->queue->suivant = nouveau;
            file->queue = nouveau;
        }
    }
    return file;
}


FileDyn* defile(FileDyn *file, pArbre *a) { // Fonction qui retire des chainons dans une file.
    if(file->tete != NULL) {
        Chainon *p = file->tete;
        *a = p->elmt;
        if(file->tete->suivant != NULL) { // Si il reste encore au moins un élément dans la file.
            file->tete = p->suivant;
        }
        else { // Si il ne reste plus d'élément dans la file.
            file->tete = NULL;
            file->queue = NULL;
        }
        free(p);
    }
    return file;
}


float max(float a, float b) { // Fonction qui renvoie le maximum entre 2 floats.
    return(a <= b ? b : a);
}


float min1(float a, float b) { // Fonction qui renvoie le minimum entre 2 floats.
    return(a <= b ? a : b);
}

float min2(float a, float b, float c){ // Fonction qui renvoie le minimum entre 3 floats.
    if(a <= b && a <= c) {
        return a;
    }
    else if(b <= a && b <= c) {
        return b;
    }
    else {
        return c;
    }
}

int hauteur(pArbre a) { // Renvoie la hauteur d'un arbre.
    if(estVide(a)) {
        return -1;
    }
    return 1 + max(hauteur(a->fg), hauteur(a->fd)); 
}


pArbre rotationGauche(pArbre a) { // Effectue la rotation gauche pour que l'arbre reste un avl en cas de problème d'équilibre.
    pArbre pivot;
    int eq_a, eq_p;

    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min2(eq_a-2, eq_a+eq_p-2, eq_p-1);
    a = pivot;
    return a;
}


pArbre rotationDroite(pArbre a) { // Effectue la rotation droite pour que l'arbre reste un avl en cas de problème d'équilibre.
    pArbre pivot;
    int eq_a, eq_p;

    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) + 1;
    pivot->equilibre = min2(eq_a+2, eq_a+eq_p+2, eq_p+1);
    a = pivot;
    return a;
}


pArbre doubleRotationGauche(pArbre a) { // Effectue la double rotation gauche pour que l'arbre reste un avl en cas de problème d'équilibre.
    rotationDroite(a->fd);
    return rotationGauche(a);
}


pArbre doubleRotationDroite(pArbre a) { // Effectue la double rotation droite pour que l'arbre reste un avl en cas de problème d'équilibre.
    rotationGauche(a->fg);
    return rotationDroite(a);
}


pArbre equilibrerAVL(pArbre a) { // Permet d'équilibrer l'AVL.
    if(a->equilibre >= 2) { // Sous-arbre droit plus profond
        if(a->fd->equilibre >= 0) {
            return rotationGauche(a);
        }
        else {
            return doubleRotationGauche(a);
        }
    }
    else if(a->equilibre <= -2) { // Sous-arbre gauche plus profond
        if(a->fg->equilibre <= 0) {
            return rotationDroite(a);
        }
        else {
            return doubleRotationDroite(a);
        }
    }
    return a;
}


time_t date_en_secondes(const char *date) { // Converti la date en seconde afin de manipuler des entiers pour la suite.
    int annee, mois, jour, heure, minute, seconde, tz_heures, tz_minutes;
    sscanf(date, "%d-%d-%dT%d:%d:%d%d:%d", &annee, &mois, &jour, &heure, &minute, &seconde, &tz_heures, &tz_minutes);
    struct tm tm = {
        .tm_year = annee - 1900,
        .tm_mon = mois - 1,
        .tm_mday = jour,
        .tm_hour = heure,
        .tm_min = minute,
        .tm_sec = seconde,
        .tm_isdst = 0
    };
    
    return mktime(&tm) - tz_heures * 3600 - tz_minutes * 60;
}


pArbre insertionAVLTP1(pArbre a, int station, float donnee, int *h) { // Tri les données pour les modes -t1 et -p1 + fait la moyenne, le minimum et le maximum des températures par station.
    if(estVide(a)) {
        *h = 1;
        a = creationArbre(donnee);
        a->element->maximum = donnee;
        a->element->minimum = donnee;
        a->element->total += donnee;
        a->element->compte += 1;
        a->element->moyenne = a->element->total/a->element->compte;
        a->element->idStation = station;
    }
    else if(station < a->element->idStation) {
        a->fg = insertionAVLTP1(a->fg, station ,donnee, h);
        *h = -*h;
    }
    else if(station > a->element->idStation) {
        a->fd = insertionAVLTP1(a->fd, station, donnee, h);
    }
    else {
        a->element->maximum = max(donnee, a->element->maximum);
        a->element->minimum = min1(donnee, a->element->minimum);
        a->element->compte += 1;
        a->element->total += donnee;
        a->element->moyenne = a->element->total/a->element->compte;
        *h = 0;
    }
    if(*h != 0) {
        a->equilibre = a->equilibre + *h;
        if(a->equilibre == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}


pArbre insertionAVLTP2(pArbre a, char *date, time_t secondes, float donnee, int *h) { // Tri les données pour les modes -t2 et -p2 + fait la moyenne des températures selon la date.
    if(estVide(a)) {
        *h = 1;
        a = creationArbreTps(secondes);
        a->element->total = donnee;
        a->element->compte = 1;
        a->element->moyenne = donnee;
        a->element->date = date;
        //a->element->date[strlen(a->element->date)] = '\0';
    }
    else if(secondes < a->element->secondes) {
        a->fg = insertionAVLTP2(a->fg, date, secondes, donnee, h);
        *h = -*h;
    }
    else if(secondes > a->element->secondes) {
        a->fd = insertionAVLTP2(a->fd, date, secondes, donnee, h);
    }
    else {
        a->element->total += donnee;
        a->element->compte += 1;
        a->element->moyenne = a->element->total/a->element->compte;
        *h = 0;
    }
    if(*h != 0) {
        a->equilibre = a->equilibre + *h;
        if(a->equilibre == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}


pArbre insertionAVLH(pArbre a, float donnee, float donnee1, float donnee2, int *h) { // Tri les données pour le mode -h.
    if(estVide(a)) {
        *h = 1;
        a = creationArbre(donnee);
        a->element->donnee1 = donnee1;
        a->element->donnee2 = donnee2;
    }
    else if(donnee < a->element->donnee) {
        a->fg = insertionAVLH(a->fg, donnee, donnee1, donnee2, h);
        *h = -*h;
    }
    else if(donnee > a->element->donnee) {
        a->fd = insertionAVLH(a->fd, donnee, donnee1, donnee2, h);
    }
    if(*h != 0) {
        a->equilibre = a->equilibre + *h;
        if(a->equilibre == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}


pArbre insertionAVLW(pArbre a, int station, float donnee1, float donnee2, float donnee, float donnee3, int *h) { // Tri les données pour le mode -w + fait la moyenne des directions et vitesses des vents.
    if(estVide(a)) {
        *h = 1;
        a = creationArbre(donnee);
        a->element->idStation = station;
        a->element->total += donnee;
        a->element->compte += 1;
        a->element->moyenne = a->element->total/a->element->compte;
        a->element->total2 += donnee3;
        a->element->compte2 += 1;
        a->element->moyenne2 = a->element->total2/a->element->compte2;
        a->element->donnee1 = donnee1;
        a->element->donnee2 = donnee2;
    }
    else if(station < a->element->idStation) {
        a->fg = insertionAVLW(a->fg, station ,donnee1, donnee2, donnee, donnee3, h);
        *h = -*h;
    }
    else if(station > a->element->idStation) {
        a->fd = insertionAVLW(a->fd, station, donnee1, donnee2, donnee, donnee3, h);
    }
    else {
        a->element->compte += 1;
        a->element->total += donnee;
        a->element->moyenne = a->element->total/a->element->compte;
        a->element->compte2 += 1;
        a->element->total2 += donnee3;
        a->element->moyenne2 = a->element->total2/a->element->compte2;
        *h = 0;
    }
    if(*h != 0) {
        a->equilibre = a->equilibre + *h;
        if(a->equilibre == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}



pArbre insertionAVL1M(pArbre a, int station, float donnee, float donnee1, float donnee2, int *h) { // Tri les données pour le mode -m et donne l'humidité maximale par station.
    if(estVide(a)) {
        *h = 1;
        a = creationArbre(donnee);
        a->element->donnee1 = donnee1;
        a->element->donnee2 = donnee2;
        a->element->maximum = donnee;
        a->element->idStation = station;
    }
    else if(station < a->element->idStation) {
        a->fg = insertionAVL1M(a->fg, station, donnee, donnee1, donnee2, h);
        *h = -*h;
    }
    else if(station > a->element->idStation) {
        a->fd = insertionAVL1M(a->fd, station, donnee, donnee1, donnee2, h);
    }
    else {
        a->element->maximum = max(donnee, a->element->maximum);
        *h = 0;
    }
    if(*h != 0) {
        a->equilibre = a->equilibre + *h;
        if(a->equilibre == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}


void parcoursInfixeNormalTP1(pArbre a) { // parcours l'AVL des modes -t1 et -p1 pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeNormalTP1(a->fg);
        traiterTP1(a);
        parcoursInfixeNormalTP1(a->fd);
    }
}


void parcoursInfixeInverseTP1(pArbre a) { // parcours l'AVL dans le sens inverse des modes -t1 et -p1 pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeInverseTP1(a->fd);
        traiterTP1(a);
        parcoursInfixeInverseTP1(a->fg);
    }
}

void parcoursInfixeNormalTP2(pArbre a) { // parcours l'AVL des modes -t2 et -p2 pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeNormalTP2(a->fg);
        traiterTP2(a);
        parcoursInfixeNormalTP2(a->fd);
    }
}


void parcoursInfixeInverseTP2(pArbre a) { // parcours l'AVL dans le sens inverse des modes -t2 et -p2 pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeInverseTP2(a->fd);
        traiterTP2(a);
        parcoursInfixeInverseTP2(a->fg);
    }
}


void parcoursInfixeNormalH(pArbre a) { // parcours l'AVL du mode -h pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeNormalH(a->fg);
        traiterH(a);
        parcoursInfixeNormalH(a->fd);
    }
}


void parcoursInfixeInverseH(pArbre a) { // parcours l'AVL dans le sens inverse du mode -h pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeInverseH(a->fd);
        traiterH(a);
        parcoursInfixeInverseH(a->fg);
    }
}


void parcoursInfixeNormal1M(pArbre a) { // parcours l'AVL du mode -m pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeNormal1M(a->fg);
        traiter1M(a);
        parcoursInfixeNormal1M(a->fd);
    }
}


void parcoursInfixeInverse1M(pArbre a) { // parcours l'AVL dans le sens inverse du mode -m pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeInverse1M(a->fd);
        traiter1M(a);
        parcoursInfixeInverse1M(a->fg);
    }
}


void parcoursInfixeNormalW(pArbre a) { // parcours l'AVL du mode -w pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeNormalW(a->fg);
        traiterW(a);
        parcoursInfixeNormalW(a->fd);
    }
}


void parcoursInfixeInverseW(pArbre a) { // parcours l'AVL dans le sens inverse du mode -w pour afficher les données triées (grâce à la fonction traiter).
    if(!estVide(a)) {
        parcoursInfixeInverseW(a->fd);
        traiterW(a);
        parcoursInfixeInverseW(a->fg);
    }
}


pArbre creationAVL(char *argv[]) { // Crée un AVL en fonction de l'option et du mode à partir des données du fichier .txt extrait grâce au script shell.
    FILE *f = NULL;
    f = fopen(argv[1],"r");
    verification_fichier(f);

    pArbre a;

    int station;
    time_t secondes; // Utilisée pour stocker une date en secondes.
    float donnee;
    float donnee1;
    float donnee2;
    float donnee3;
    char date[30];

    int r;
    int h;

    if(((strcmp(argv[4], "t") == 0) && (strcmp(argv[5], "2") == 0)) || ((strcmp(argv[4], "p") == 0) && (strcmp(argv[5], "2") == 0))) {
        r = fscanf(f, "%d %s %f", &station, date, &donnee);
        secondes = date_en_secondes(date);
        a = creationArbreTps(secondes);
        a->element->total = donnee;
        a->element->compte = 1;
        a->element->moyenne = donnee;
        a->element->date = date;
        //a->element->date[strlen(a->element->date)] = '\0';
    }
    else if(strcmp(argv[4], "h") == 0) {
        r = fscanf(f, "%f %f %f", &donnee, &donnee1, &donnee2);
        a = creationArbre(donnee);
        a->element->donnee1 = donnee1;
        a->element->donnee2 = donnee2;
    }
    else if(strcmp(argv[4], "m") == 0) {
        r = fscanf(f, "%d %f %f %f", &station, &donnee, &donnee1, &donnee2);
        a = creationArbre(donnee);
        a->element->donnee1 = donnee1;
        a->element->donnee2 = donnee2;
        a->element->idStation = station;
    }
    else if(strcmp(argv[4], "w") == 0) {
        r = fscanf(f, "%d %f %f %f %f", &station, &donnee1, &donnee2, &donnee, &donnee3);
        a = creationArbre(donnee);
        a->element->donnee1 = donnee1;
        a->element->donnee2 = donnee2;
        a->element->idStation = station;
        a->element->donnee3 = donnee3;
        a->element->moyenne = donnee;
        a->element->compte = 1;
        a->element->total = donnee;
        a->element->moyenne2 = donnee3;
        a->element->compte2 = 1;
        a->element->total2 = donnee3;
    }
    else {
        r = fscanf(f, "%d %f", &station, &donnee);
        a = creationArbre(donnee);
        a->element->idStation = station;
    }


    while(r != EOF) {
        if(((strcmp(argv[4], "t") == 0) && (strcmp(argv[5], "2") == 0)) || ((strcmp(argv[4], "p") == 0) && (strcmp(argv[5], "2") == 0))) {
            r = fscanf(f, "%d %s %f", &station, date, &donnee);
            secondes = date_en_secondes(date);
            insertionAVLTP2(a, date, secondes, donnee, &h);
        }
        else if(strcmp(argv[4], "h") == 0) {
            r = fscanf(f, "%f %f %f", &donnee, &donnee1, &donnee2);
            insertionAVLH(a, donnee, donnee1, donnee2, &h);
        }
        else if(strcmp(argv[4], "m") == 0) {
            r = fscanf(f, "%d %f %f %f", &station, &donnee, &donnee1, &donnee2);
            insertionAVL1M(a, station, donnee, donnee1, donnee2, &h);
        }
        else if(strcmp(argv[4], "w") == 0){
            r = fscanf(f, "%d %f %f %f %f", &station, &donnee1, &donnee2, &donnee, &donnee3);
            insertionAVLW(a, station, donnee1, donnee2, donnee, donnee3, &h);
        }
        else {
            r = fscanf(f, "%d %f", &station, &donnee);
            insertionAVLTP1(a, station, donnee, &h);
        }
    }

    fclose(f);
    
    return a;
}
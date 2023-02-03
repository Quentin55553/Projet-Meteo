#include "meteo.h"


Liste_Chainee* creationListe_Chainee(float a) {
    Liste_Chainee *nouveau = malloc(sizeof(Liste_Chainee));
    if(nouveau == NULL) {
        exit(1);
    }
    nouveau->elmt = a;
    nouveau->suivant = NULL;
    return nouveau;
}


Liste_Chainee* insertDebut(Liste_Chainee *pliste, float a) {
    Liste_Chainee *nouveau = creationListe_Chainee(a);
    nouveau->suivant = pliste;
    pliste = nouveau;
    return pliste;
}


Liste_Chainee* insertFin(Liste_Chainee *pliste, float a) {
    Liste_Chainee *nouveau = creationListe_Chainee(a);
    Liste_Chainee *p = pliste;
    while(p->suivant != NULL) {
        p = p->suivant;
    }
    p->suivant = nouveau;
    return pliste;
}


Liste_Chainee* insertCroissant(Liste_Chainee *pliste, float a) {
    Liste_Chainee *nouveau = creationListe_Chainee(a);
    Liste_Chainee *p = pliste; // On crée une autre variable pour ne pas perdre le début de pliste

    if (p == NULL) {
        p = nouveau;
        return pliste; // Que l'on retourne "p" ou "pliste", cela revient au même
    }
    if (nouveau->elmt < pliste->elmt) {
        pliste = insertDebut(pliste, nouveau->elmt);
        return pliste;
    }

    while(p->suivant != NULL && p->suivant->elmt < nouveau->elmt) {
        p = p->suivant;
    }
    if (p->suivant == NULL) {
        pliste = insertFin(pliste, nouveau->elmt);
    }
    else {
        nouveau->suivant = p->suivant;
        p->suivant = nouveau;
    }
    return pliste;
}


Liste_Chainee* inverseListe(Liste_Chainee *pliste1, Liste_Chainee *pliste2) {
    Liste_Chainee *p = pliste1;
    while(p != NULL) {
        pliste2 = insertDebut(pliste2, p->elmt);
        p = p->suivant;
    }
    return pliste2;
}


void afficheListe(Liste_Chainee *pliste) {
    Liste_Chainee *p = pliste;
    while(p != NULL) {
        if (p->suivant == NULL) {
            printf("(%f)\n", p->elmt);
        }
        else {
            printf("(%f) -> ", p->elmt);
        }
        p = p->suivant;
    }
}
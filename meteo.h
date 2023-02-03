#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>


typedef struct store {
    float donnee;
    float donnee1;
    float donnee2;
    float donnee3;
    time_t secondes;
    int idStation;
    float minimum;
    float maximum;
    float moyenne; // stock la valeur de la moyenne
    float moyenne2; // stock la valeur de la moyenne
    float total; // sert à calculer les moyennes
    float total2; // sert à calculer les moyennes
    int compte; // sert à calculer les moyennes
    int compte2; // sert à calculer les moyennes
    char *date;
}Store;


typedef struct arbre {
    Store *element;
    struct arbre *fg;
    struct arbre *fd;
    int equilibre;
    int hauteur;
}Arbre;

typedef Arbre *pArbre;


typedef struct chainon {
    pArbre elmt;
    struct chainon *suivant;
}Chainon;


typedef struct fileDyn {
    Chainon *tete;
    Chainon *queue;
}FileDyn;


typedef struct liste_chainee {
    float elmt;
    struct liste_chainee *suivant;
}Liste_Chainee;


time_t date_en_secondes(const char *date);

Chainon* creationChainon(pArbre a);

FileDyn* creationFileDyn();

FileDyn* enfile(FileDyn *file, pArbre a);

FileDyn* defile(FileDyn *file, pArbre *a);

Liste_Chainee* creationListe_Chainee(float a);

Liste_Chainee* inverseListe(Liste_Chainee *pliste1, Liste_Chainee *pliste2);

Liste_Chainee* insertCroissant(Liste_Chainee *pliste, float a);

Liste_Chainee* insertFin(Liste_Chainee *pliste, float a);

Liste_Chainee* insertDebut(Liste_Chainee *pliste, float a);

pArbre creationArbre(float a);

pArbre creationArbreTps(time_t a);

pArbre creationAVL(char *argv[]);

pArbre insertABR(pArbre a, float e);

pArbre ajouterFilsGauche(pArbre a, float e);

pArbre ajouterFilsDroit(pArbre a, float e);

pArbre rotationGauche(pArbre a);

pArbre rotationDroite(pArbre a);

pArbre doubleRotationDroite(pArbre a);

pArbre doubleRotationGauche(pArbre a);

pArbre equilibrerAVL(pArbre a);

pArbre insertionAVLTP1(pArbre a, int station, float donnee, int *h);

pArbre insertionAVLTP2(pArbre a, char *date, time_t secondes, float donnee, int *h);

pArbre insertionAVLH(pArbre a, float donnee, float donnee1, float donnee2, int *h);

pArbre insertionAVL1M(pArbre a, int station, float donnee, float donnee1, float donnee2, int *h);

pArbre insertionAVLW(pArbre a, int station, float donnee1, float donnee2, float donnee, float donnee3, int *h);

pArbre ordonnerAVL2M(pArbre a, pArbre b, int *h);

float max(float a,float b);

float min1(float a, float b);

float min2(float a, float b, float c);

int estVide(pArbre a);

int hauteur(pArbre a);

int existeFilsDroit(pArbre a);

int existeFilsGauche(pArbre a);

void verification_fichier(FILE *fichier);

void traiterTP1(pArbre a);

void traiterTP2(pArbre a);

void traiterH(pArbre a);

void traiter1M(pArbre a);

void traiterW(pArbre a);

void afficheListe(Liste_Chainee* pliste);

void parcoursInfixeNormalTP1(pArbre a);

void parcoursInfixeInverseTP1(pArbre a);

void parcoursInfixeNormalTP2(pArbre a);

void parcoursInfixeInverseTP2(pArbre a);

void parcoursInfixeNormalH(pArbre a);

void parcoursInfixeInverseH(pArbre a);

void parcoursInfixeNormal1M(pArbre a);

void parcoursInfixeInverse1M(pArbre a);

void parcoursInfixeNormalW(pArbre a);

void parcoursInfixeInverseW(pArbre a);
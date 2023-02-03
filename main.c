#include "meteo.h"


int main(int argc, char *argv[]) { // argc : entier représentant le nombre d'arguments passés en paramètre | argv : tableau de chaînes de caractères qui contient les arguments.    
    if((strcmp(argv[2], "--avl") == 0)) { // Si la méthode de tris saisie par l'utilisateur est --avl
        pArbre a = creationAVL(argv);

        if(strcmp(argv[4], "h") == 0) { // Si l'option choisie est -h.
            if(strcmp(argv[3], "-r") == 0) { // Si l'utilisateur veut un classement des données dans le sens inverse que celui prévu.
                parcoursInfixeNormalH(a);
            }
            else {
                parcoursInfixeInverseH(a);
            }
        }
        else if(strcmp(argv[4], "m") == 0) { // Si l'option choisie est -m.
            int h;
            
            if(strcmp(argv[3], "-r") == 0) { // Si l'utilisateur veut un classement des données dans le sens inverse que celui prévu.
                parcoursInfixeNormal1M(a);
            }
            else {
                parcoursInfixeInverse1M(a);
            }
        }
        else if(((strcmp(argv[4], "t") == 0) && (strcmp(argv[5], "2") == 0)) || ((strcmp(argv[4], "p") == 0) && (strcmp(argv[5], "2") == 0))) { // Si l'option choisie est -t2 ou -p2.
            if(strcmp(argv[3], "-r") == 0) { // Si l'utilisateur veut un classement des données dans le sens inverse que celui prévu.
                parcoursInfixeInverseTP2(a);
            }
            else {
                parcoursInfixeNormalTP2(a);
            }
        }
        else if(strcmp(argv[4], "w") == 0) { // Si l'option choisie est -w.
            if(strcmp(argv[3], "-r") == 0) { // Si l'utilisateur veut un classement des données dans le sens inverse que celui prévu.
                parcoursInfixeInverseW(a);
            }
            else {
                parcoursInfixeNormalW(a);
            }
        }
        else { // Sinon (c'est à dire si l'option choisie est t1 ou p1).
            if(strcmp(argv[3], "-r") == 0) { // Si l'utilisateur veut un classement des données dans le sens inverse que celui prévu.
                parcoursInfixeInverseTP1(a);
            }
            else {
                parcoursInfixeNormalTP1(a);
            }
        }

        return 0;
    }

    else if(strcmp(argv[2], "--abr") == 0) { // Si la méthode de tri est --ABR (ne fonctionne pas par manque de temps).
        return 0;
    }
    else if(strcmp(argv[2], "--chaine") == 0) { // Si la méthode de tri est --chaine (ne fonctionne pas par manque de temps).
        return 0;
    }

    return 1;
}
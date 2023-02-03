Tout d'abord, le programme est séparé en 7 fichiers (Makefile non compris) ainsi qu'un fichier comprenant toutes les données météorologique,un pdf sur notre organisation et un fichier help.txt.

Ce programme permet d'afficher des graphiques en fonction des données demandées dans la commande écrite dans le terminal.

Le script shell compile et execute les fichiers ".c" à l'aide du Makefile.
Il n'y a qu'à écrire la commande : "bash script_meteo.sh <options> <arguments> -f meteo_filtered_data_v1.csv" (l'ordre n'a pas d'importance après "bash script_meteo.sh", cependant -f doit-être avant le nom du fichier).

Les options mises à votre disposition sont :

Les options -t et -p qui doivent être accompagnées d’un mode: -t<mode> , -p<mode>.
Pour ces 2 options, il faut indiquer la valeur du<mode> :
1  :   produit en sortie les températures (ou pressions) minimales, maximales et moyennes par station dans l’ordre croissant du numéro de station.
2  :   produit en sortie les températures (ou pressions) moyennes par date/heure, triées dans l’ordre chronologique. La moyenne se fait sur toutes les stations.


L’option -w : produit en sortie l’orientation moyenne et la vitesse moyenne desvents pour chaque station. Quand on parle de moyenne, il s’agira defaire la somme pour chaque composante du vecteur, et d’en faire la moyenne une fois tous les vecteurs traités.   
On aura donc unemoyenne sur l’axe X et une moyenne sur l’axe Y : les 2 résultats fournissant le module et l’orientation moyens demandés. Les données seront triées par identifiant croissant de la station.

L’option -h : produit en sortie l’altitude pour chaque station. Les altitudes seront triées par ordre décroissant.

L’option -m : produit en sortie l’humidité maximale pour chaque station. Les valeurs d’humidités seront triées par ordre décroissant.


Vous pouvez également saisir des options de tris. Une seule de ces options peut être activée à la fois.
Si aucune option de tri n’est activée, par défaut le tri se fera à l’aide d’un AVL qui sera la plus efficace.
--avl: tri effectué à l’aide d’une structure de type AVL.

IMPORTANT : Il faut rentrer au moins une option pour que le programme s'exécute. Cependant, il est possible d'en mettre plusieurs. Vous pouvez également utiliser une option de limitation géographique.

Afin de mieux comprendre comment executé le scipt, la fonction --help peut être utilisée.

L'ensemble du programme a été conçu par Quentin FILLION et Axel COTTRANT.

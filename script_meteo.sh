#!/bin/bash

Couleur_OFF='\033[0m'    # Réinitialisation des couleurs
Rouge='\033[0;31m'       # Rouge
Vert='\033[0;32m'        # Vert
Jaune='\033[0;33m'       # Jaune
Violet='\033[0;35m'      # Violet
Orange='\e[38;5;208m'    # Orange
Noir='\033[0;30m'        # Noir
Bleu='\033[0;34m'        # Bleu
Cyan='\033[0;36m'        # Cyan
Blanc='\033[0;37m'       # Blanc

MEF_OFF='\e[0m'          # Réinitialisation de la mise en forme du texte
Gras='\e[1m'             # Texte en gras
Italique='\e[3m'         # Texte en italique
Souligne='\e[4m'         # Texte souligné


function _help() { # Fonction permettant de fournir de l'aide à l'utilisateur quand l'option --help est exécutée avec la commande.
	echo -e "\n${Jaune}La commande '${Violet}--help${Jaune}' a été saisie${Couleur_OFF}"
	echo -e "\n${Gras}${Souligne}Aide à l'utilisation du script :${MEF_OFF}\n"
	if (! cat help.txt); then
		echo -e "\n${Rouge}L'aide n'a pas pu être affichée, il manque le fichier 'help.txt'.${Couleur_OFF}"
		exit 1
	fi
	echo -e "\n"
	exit 1
}


function extraire() { # Fonction permettant l'extraction des informations du jeu de données météorologiques en fonction des arguments/options passés par l'utilisateur.
	if [ "$limitation_geographique" == "-F" ]; then
		tail -n+2 meteo_filtered_data_v1.csv | tr ',' ';' | awk -F ";" '{if(($10 >= 40.60 && $10 <= 51.18) && ($11 >= -6.82 && $11 <= 12.06)) {print $0}}' > tmp.csv

	elif [ "$limitation_geographique" == "-G" ]; then
		tail -n+2 meteo_filtered_data_v1.csv | tr ',' ';' | awk -F ";" '{if($10 > 1.55 && $10 < 6.66 && $11 > -55.14 && $11 < -50.55) {print $0}}' > tmp.csv

	elif [ "$limitation_geographique" == "-S" ]; then
		tail -n+2 meteo_filtered_data_v1.csv | tr ',' ';' | awk -F ";" '{if($10 > 46.65 && $10 < 47.24 && $11 > -56.64 && $11 < -55.91) {print $0}}' > tmp.csv

	elif [ "$limitation_geographique" == "-A" ]; then
		tail -n+2 meteo_filtered_data_v1.csv | tr ',' ';' | awk -F ";" '{if($10 > 12.65 && $10 < 19.33 && $11 > -65.70 && $11 < -58.89) {print $0}}' > tmp.csv

	elif [ "$limitation_geographique" == "-O" ]; then
		tail -n+2 meteo_filtered_data_v1.csv | tr ',' ';' | awk -F ";" '{if(($10 > -13.09 && $10 < -12.55 && $11 > 44.88 && $11 < 45.35) || ($10 > -21.83 && $10 < -20.37 && $11 > 54.51 && $11 < 56.24)) {print $0}}' > tmp.csv

	elif [ "$limitation_geographique" == "-Q" ]; then
		tail -n+2 meteo_filtered_data_v1.csv | tr ',' ';' | awk -F ";" '{if(($10 > -84.43 && $10 < -33.16 && $11 > 31.03 && $11 < 149.4656) || ($10 > -23.02 && $10 < -15.90 && $11 > 38.97 && $11 < 43.16) || ($10 > -16.35 && $10 < -10.75 && $11 > 46.21 && $11 < 55)) {print $0}}' > tmp.csv

	fi
	
	if [ "$opt" == "t" ]; then
		if [ $a -eq 1 ]; then
			if [ "$limitation_geographique" == "NULL" ]; then
				awk -F ";" 'NR > 1 && $11 != "" {print $1 " " $11}' meteo_filtered_data_v1.csv > temperatures.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : ID station, température.
			else
				awk -F ";" '$12 != "" {print $1 " " $12}' tmp.csv > temperatures.txt
			fi	

			./exec temperatures.txt $methode_tri $ordre_tri $opt $a
			gnuplot -c t1-p1-mode.gnu "Températures" "Grahique-t1.png"
					
		elif [ $a -eq 2 ]; then
			if [ "$limitation_geographique" == "NULL" ]; then
				awk -F ";" 'NR > 1 && $11 != "" {print $1 " " $2 " " $11}' meteo_filtered_data_v1.csv > temperatures.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : ID station, Date, température.
			else
				awk -F ";" '$12 != "" {print $1 " " $2 " " $12}' tmp.csv > temperatures.txt
			fi	
			
			./exec temperatures.txt $methode_tri $ordre_tri $opt $a
			gnuplot -c t2-p2-mode.gnu "Températures" "Grahique-t2.png"

		else # Sinon le mode est forcément 3
			if [ "$limitation_geographique" == "NULL" ]; then
				awk -F ";" 'NR > 1 && $11 != "" {print $1 " " $2 " " $11}' meteo_filtered_data_v1.csv > temperatures.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : ID station, date, température.
			else
				awk -F ";" '$12 != "" {print $1 " " $2 " " $12}' tmp.csv > temperatures.txt
			fi	
			
			./exec temperatures.txt $methode_tri $ordre_tri $opt $a
		fi

	elif [ "$opt" == "p" ]; then
		if [ $b -eq 1 ]; then
			if [ "$limitation_geographique" == "NULL" ]; then
				awk -F ";" 'NR > 1 && $7 != "" {print $1 " " $7}' meteo_filtered_data_v1.csv > pression.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : ID station, pression station.
			else
				awk -F ";" '$7 != "" {print $1 " " $7}' tmp.csv > pression.txt
			fi	
			
			./exec pression.txt $methode_tri $ordre_tri $opt $b
			gnuplot -c t1-p1-mode.gnu "Pressions" "Grahique-p1.png"
	
		elif [ $b -eq 2 ]; then
			if [ "$limitation_geographique" == "NULL" ]; then
				awk -F ";" 'NR > 1 && $7 != "" {print $2 " " $7}' meteo_filtered_data_v1.csv > pression.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : Date, pression station.
			else
				awk -F ";" '$7 != "" {print $2 " " $7}' tmp.csv > pression.txt
			fi	
			
			./exec pression.txt $methode_tri $ordre_tri $opt $b
			gnuplot -c t2-p2-mode.gnu "Pressions" "Grahique-p2.png"

		else
			if [ "$limitation_geographique" == "NULL" ]; then
				awk -F ";" 'NR > 1 && $7 != "" {print $1 " " $2 " " $7}' meteo_filtered_data_v1.csv > pression.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : ID station, date, pression station.
			else
				awk -F ";" '$7 != "" {print $1 " " $2 " " $7}' tmp.csv > pression.txt
			fi	
			
			./exec pression.txt $methode_tri $ordre_tri $opt $b
		fi
		
	elif [ "$opt" == "w" ]; then
		if [ "$limitation_geographique" == "NULL" ]; then
			awk -F ";" 'NR > 1 && $5 != "" && $4 != "" {print $1 " " $10 " " $4 " " $5}' meteo_filtered_data_v1.csv | awk -F "," '{print $1 " " $2 " " $3 " " $4 " " $5}' > coordinates_wind_direction_speed.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : ID station, Latitude, longitude, direction, vitesse.
		else
			awk -F ";" '$5 != "" && $4 != "" {print $1 " " $10 " " $11 " " $4 " " $5}' tmp.csv > coordinates_wind_direction_speed.txt
		fi	
		
		./exec coordinates_wind_direction_speed.txt $methode_tri $ordre_tri $opt
		gnuplot w-mode.gnu
	
	elif [ "$opt" == "h" ]; then
		if [ "$limitation_geographique" == "NULL" ]; then
			awk -F ";" 'NR > 1 && $14 != "" {print $14 " " $10}' meteo_filtered_data_v1.csv | awk -F "," '{print $14 " " $1 " " $2}' > altitude.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : Altitude, latitude, longitude.
		else
			awk -F ";" '$14 != "" {print $14 " " $10 " " $11}' tmp.csv > altitude.txt
		fi	
		
		./exec altitude.txt $methode_tri $ordre_tri $opt
		gnuplot -c h-m-mode.gnu "altitude" "Carte-h.png"
		
	elif [ "$opt" == "m" ]; then	
		if [ "$limitation_geographique" == "NULL" ]; then
			awk -F ";" 'NR > 1 && $6 != "" {print $1 " " $6 " " $10}' meteo_filtered_data_v1.csv | awk -F "," '{print $1 " " $6 " " $2 " " $3}' > humidity.txt # LES COLONNES SÉLECTIONNÉES SONT DANS L'ORDRE : ID Station, Humidité, latitude, longitude.
		else
			awk -F ";" '$6 != "" {print $1 " " $6 " " $10 " " $11}' tmp.csv > humidity.txt
		fi	
		
		./exec humidity.txt $methode_tri $ordre_tri $opt
		gnuplot -c h-m-mode.gnu "humidité" "Carte-m.png"
		
	fi

	rm -f donneesTriees.dat
	rm -f tmp.csv
}


function verifier_commande() { # Fonction permettant de vérifier si la commande rentrée par l'utilisateur est correcte et ne peut pas de faire 'bugger' le programme.
	echo "Vérification des arguments et options.."
	param_possible=("-r" "--abr" "--avl" "--chaine" "-F" "-G" "-S" "-A" "-O" "-Q" "-f" "-t" "-p" "-w" "-m" "-h") # Liste des arguments/options possibles.
	pos=1
	fichier_trouve=n
	re='^[0-9]+$' # Permet de vérifier à l'aide d'une égalité si une variable est un nombre.
	
	for arg; do # Avec cette boucle, on cherche à savoir si il y a le jeu de données .CSV de fourni ou l'option '--help'.
	    if [ $arg == "--help" ]; then
	    	_help
	    fi
	    
	    if [ -f $arg ] && [ "$(md5sum $arg | cut -d' ' -f1)" == "61495c4101e2012a06f2ec524d9bcae8" ]; then # Vérifie à l'aide des sommes de contrôle si l'argumentest le jeu de données météorologiques avec lequel le programme doit fonctionner.
		if [ $fichier_trouve == 'o' ]; then # Si le fichier a déjà été trouvé auparavant, cela veut dire qu'on l'a 2 fois.
			echo -e "\n${Rouge}Attention, vous ne pouvez entrer '${Violet}$arg${Rouge}' qu'une seule fois !${Couleur_OFF}"
			exit 1
		fi
		fichier_trouve=o
		param_possible+=("${*: pos:1}") # Insère le nom de fichier en .CSV dans la liste des paramètres autorisés.
	    fi
	    
	    if [ $fichier_trouve == 'n' ]; then
	    	let pos++
    	    fi
	done
	
	if [ "$fichier_trouve" == "n" ]; then # Si le jeu de données n'a pas été fourni, on affiche un message d'erreur.
		echo -e "\n${Rouge}Attention, il faut obligatoirement :\n- Le jeu de données météorologiques fourni au format CSV, qui doit être enregistré au même endroit que le programme et précedé de : ${Violet}-f${Couleur_OFF}"
		exit 1
	fi

	# ----------------------------------------------------------------------------------------------------------------------------------------------------------

	if [ "${*: pos-1:1}" != "-f" ]; then # Vérifie qu'il y a bien "-f" avant le fichier CSV.
		echo -e "\n${Rouge}Attention, il faut précisément écrire avant le fichier au format CSV fourni : ${Violet}-f${Couleur_OFF}"
		exit 1
	fi
	
	# ----------------------------------------------------------------------------------------------------------------------------------------------------------

	IFS=' ' read -r -a input <<< "$@" # Crée une liste 'input' contenant de façon isolée tous les arguments/options rentrés par l'utilisateur.
	opt_standard=n # Permet de vérifier que l'on a au moins une option standard (t, p, w, m, h)
	limitation_geographique=NULL # Permet à la fois de vérifier que l'on a uniquement une seule option de limitation géographique et de savoir si on en a une.
	opt_tri=n
	methode_tri=--avl
	ordre_tri=NULL
	for parametre in ${input[*]}; do # Les deux boucles permettent de vérifier que tous les paramètres passés sont autorisés (contenus dans : 'param_possible').		
		existe_opt=n # Permet de vérifier que toutes les options passées existent.
		for para_dispo in ${param_possible[*]}; do
			optionsm=$(echo $parametre | grep -o '.*[^0-9]') # L'option sans le mode, si il y en a un.
			if [ "$optionsm" == "$para_dispo" ]; then
				if [ "$optionsm" == "-t" ] || [ "$optionsm" == "-p" ]; then
					mode=$(echo $parametre | grep -o '[!^0-9].*') # Le mode sans l'option.
					if [[ ! $mode =~ $re ]] || [ $mode -lt 1 ] || [ $mode -gt 3 ]; then
						echo -e "\n${Rouge}Attention, le mode accompagnant l'option ${Violet}$optionsm ${Rouge}doit obligatoirement être un entier compris entre 1 et 3 inclus.${Couleur_OFF}"
					   	exit 1
					fi
					opt_standard=o
				fi
				if [ "$optionsm" == "-w" ] || [ "$optionsm" == "-m" ] || [ "$optionsm" == "-h" ]; then
					opt_standard=o
				fi
				if [ "$optionsm" == "-r" ]; then
					if [ "$ordre_tri" == "-r" ]; then
						echo -e "\n${Rouge}Attention, vous avez spécifié plus d'une fois l'ordre de tri inversé (${Violet}-r${Rouge}).${Couleur_OFF}"
						exit 1
					fi
					ordre_tri=-r
				fi
				existe_opt=o
				break
			fi
		done
		
		if [ "$existe_opt" == "n" ]; then # Si une option inexistante a été fournie.
			echo -e "\n${Rouge}L'option ${Violet}$parametre ${Rouge}n'est pas supportée.\nVoir le fichier 'readme.txt' ou exécutez le script en utilisant la commande '${Violet}--help${Rouge}' pour plus d'informations.${Couleur_OFF}"
			exit 1
		fi

		for para_dispo in ${param_possible[*]:4:6}; do
			if [ "$parametre" == "$para_dispo" ]; then
				if [ "$limitation_geographique" != "NULL" ]; then
					echo -e "\n${Rouge}Attention, il ne peut y avoir qu'une option de limitation géographique maximum.${Couleur_OFF}"
					exit 1
				fi
				limitation_geographique=$parametre
			fi
		done

		for para_dispo in ${param_possible[*]:1:3}; do
			if [ "$parametre" == "$para_dispo" ]; then
				if [ "$opt_tri" == "o" ]; then
					echo -e "\n${Rouge}Attention, il ne peut y avoir qu'une option de méthode de tri.${Couleur_OFF}"
					exit 1
				fi
				methode_tri=$parametre
				opt_tri=o
			fi
		done
	done
	
	if [ $opt_standard == "n" ]; then # Si un mauvais jeu de données ou un nombre insuffisant de paramètres a été fourni, on affiche un message d'erreur.
		echo -e "\n${Rouge}Attention, il faut obligatoirement :\n- Au moins une option (${Violet}-t${Rouge}, ${Violet}-p${Rouge}, ${Violet}-w${Rouge}, ${Violet}-m ${Rouge}ou/et ${Violet}-h${Rouge})${Couleur_OFF}"
		exit 1
	fi
	echo -e "${Vert}Arguments et options corrects${Couleur_OFF}"
}


function main() {
	verifier_commande $@

	echo -e "\nCommande en cours d'exécution.."
	
	echo -e "Compilation des script.."
	if (! make -s exec); then
		echo -e "\n${Rouge}La compilation des programmes en langage C n'a pas pu s'effectuer.\nFaites attention à bien avoir tous les fichiers fournis.${Couleur_OFF}"
		exit 1
	fi
	echo -e "${Vert}Compilation réussie${Couleur_OFF}"
	
	rm -f donneesTriees.dat
	while getopts "f:t:p:m h w -abr -avl -chaine F G S A O Q" opt; do # getopts regarde les options derrière les tirets et opt les valeurs de t, p, w, m ou h.
		case $opt in
			t) a=$OPTARG
			   extraire $opt $methode_tri $limitation_geographique $ordre_tri $a
			;;	
			
			p) b=$OPTARG
		   	   extraire $opt $methode_tri $limitation_geographique $ordre_tri $b
			;;	

			w) extraire $opt $methode_tri $limitation_geographique $ordre_tri
			;;

			m) extraire $opt $methode_tri $limitation_geographique $ordre_tri
			;;

			h) extraire $opt $methode_tri $limitation_geographique $ordre_tri
			;;
		esac
	done


	echo -e "\n${Vert}Commande exécutée avec succès !${Couleur_OFF}\n"
	make -s clean
	exit 0
}

# Amorçage du script avec les options/arguments rentrés
main $@

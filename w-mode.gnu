#!/usr/local/bin/gnuplot -persist


set xlabel "longitude (Ouest-Est)"
set ylabel "lattitude (Nord-Sud)"
set style fill solid 1.0
set palette defined (0 "#9bf6ff", 1/3 "#bdb2ff", 1 "#ffadad")
set title "Diagramme de type vecteurs associé à l'orientation et la vitesse des vents des stations"
set term png
set output "Diagramme-w"
plot "donneesTriees.dat" using 3:2:(($4*pi)/180):5 with vectors head filled
     #"" using 1:2 with linespoints lc rgb "green" ps 2
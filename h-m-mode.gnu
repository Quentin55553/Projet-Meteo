#!/usr/local/bin/gnuplot -persist

VAL1 = ARG1
VAL2 = ARG2



set view map
set pm3d interpolate 3,3
set ticslevel 0
set dgrid3d 100,100,7
set xlabel "Latitude (Sud-Nord)"
set ylabel "Longitude (Ouest-Est)"
set zlabel VAL1
set xrange [-66.663170:50.136002]
set yrange [-62.852165:140.001007]
set title "Carte interpolée et colorée de l'".VAL1." des stations"
set term png
set output VAL2
splot "donneesTriees.dat" using 2:3:1 with pm3d
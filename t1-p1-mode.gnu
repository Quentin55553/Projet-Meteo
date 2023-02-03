#!/usr/local/bin/gnuplot -persist

VAL1 = ARG1
VAL2 = ARG2

set xlabel "Identifiant de station"
set ylabel VAL1
set xrange [7005:89642]
set style fill solid 1.0
set palette defined (0 "#9bf6ff", 1/3 "#bdb2ff", 1 "#ffadad")
set title VAL1." par station"
set term png
set output VAL2
plot "donneesTriees.dat" using 1:3:4 with filledcurves lc "#c8b6ff",\
     "donneesTriees.dat" using 1:2  with lines title VAL1." moyennes",\
     "donneesTriees.dat" using 1:3  with lines title VAL1." maximum",\
     "donneesTriees.dat" using 1:4  with lines title VAL1." minimum"
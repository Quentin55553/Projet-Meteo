#!/usr/local/bin/gnuplot -persist

VAL1 = ARG1
VAL2 = ARG2

set xlabel "Dates des mesures (en secondes)"
set ylabel VAL1." moyennes"
set xrange [1262300400:1664557200]
set style fill solid 1.0
set palette defined (0 "#9bf6ff", 1/3 "#bdb2ff")
set title "Moyennes des ".VAL1." selon la date"
set term png
set output VAL2
plot "donneesTriees.dat" using 1:2 smooth acsplines title VAL1." moyennes"

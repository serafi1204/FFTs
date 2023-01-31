scale = 500.0

set term png
set terminal pngcairo size 4*scale, 5*scale fontscale 2 linewidth 4 pointscale 4
set output 'rectangle.png'

set multiplot layout 3, 2 title "< rectangle >"  font ", 20"
set grid

set key font ",10"
set tics font ",10"
set xlab font ",10"
set key left top

set xlab "t (time domain)"
plot "rectangle.txt" u (column(1)):(column(2)) with lines title "time domain" lc 2

set xlab "w (freq domain)"
plot "rectangle.txt" u (column(1)):(column(3)) with lines title "DFT" lc 2
plot "rectangle.txt" u (column(1)):(column(3)) with lines title "DFT" lc 7, "rectangle.txt" u (column(1)):(column(4)) with lines title "FFT.CT.radix2" lc 2
plot "rectangle.txt" u (column(1)):(column(3)) with lines title "DFT" lc 7, "rectangle.txt" u (column(1)):(column(5)) with lines title "FFT.CT.radix4" lc 2

set xrange [-100:100]
plot "rectangle.txt" u (column(1)):(column(3)) with lines title "DFT" lc 7, "rectangle.txt" u (column(1)):(column(4)) with lines title "FFT.CT.radix2" lc 2
plot "rectangle.txt" u (column(1)):(column(3)) with lines title "DFT" lc 7, "rectangle.txt" u (column(1)):(column(5)) with lines title "FFT.CT.radix4" lc 2

unset multiplot
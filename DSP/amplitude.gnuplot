
set terminal pdf monochrome
set output "amplitude.pdf"
set termoption dash
set grid
set xlabel "Ω"
set xrange [0:pi]
set xtics font "," ("0" 0,"π/4" pi/4,"π/2" pi/2,"3π/4" 3*pi/4,"π" pi) set ylabel "|H(Ω)|"
i = {0.0, 1.0}
set dummy w
H(w) = (1 + exp(-i*w))/2
plot abs(H(w)) lw 4 notitle
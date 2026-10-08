set xlabel "Number of Inputs"
set ylabel "Number of Comparisons"
set title "Comparisons"
plot "output.txt" using 1:2 with linespoints title "bubble", "output.txt" using 1:4 with linespoints title "merge", "output.txt" using 1:6 with linespoints title "quick1", "output.txt" using 1:8 with linespoints title "quick3", "output.txt" using 1:10 with linespoints title "quickM"

pause -1 "Press Enter to see Time graph"

set ylabel "Time (seconds)"
set title "Time Taken"
plot "output.txt" using 1:3 with linespoints title "bubble", "output.txt" using 1:5 with linespoints title "merge", "output.txt" using 1:7 with linespoints title "quick1", "output.txt" using 1:9 with linespoints title "quick3", "output.txt" using 1:11 with linespoints title "quickM"

C++
make

The program is run like:

./submission smallInput.txt output.txt fibSmall.txt fiboutput.txt

The first argument is the input file for the 0/1 knapsack program like program 4

The second argument is the output file for the 0/1 knapsack algorithm.
Each line corresponds to a different implementation.
The output is as follows: size of n, number of subproblems, answer, time in milliseconds

The third argument is the input file for the fibonacci algorithm.
The file should consist of line delimited numbers.

The fourth argument is the output file for the fibonacci algorithm.
The output is as follows: number in fibonacci sequence (n), answer, time in milliseconds

*NOTE*
For large 0/1 knapsack inputs (largeInput.txt) and (fibLarge.txt) both recursive algorithms WILL TIME OUT!!!
This is intended and we comment out the lines which call these recursive algorithms when we generated our results for larger inputs.

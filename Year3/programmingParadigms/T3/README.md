
# Task 3 (Z3): University Modules Allocation

The Computer Science department has a number of modules, $m_i$, that must be taught,
and a few lecturers, $\ell_j$, who may deliver them. 

- Each module must be delivered by *exactly one* lecturer.
- No lecturer should need to teach more than $k$ modules at the same time, for some fixed value of $k$.
- No module should be taught by a lecturer with expertise 1 or less.

Each lecturer has been invited to rate their expertise on the modules on a linear 0 to 5 scale (with 5 being most expert).

The following table shows an example of expertise weighting of 6 lecturers' for 20 modules:

$$\begin{array}{|l|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|}
\hline
 & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 10 & 11 & 12 & 13 & 14 & 15 & 16 & 17 & 18 & 19 & 20\\
\hline\hline
\ell_{1} &  5  &  4  &  1  &  2  &  0  &  5  &  0  &  5  &  2  &  3  &  4  &  0  &  2  &  3  &  2  &  4  &  5  &  1  &  4  &  3  \\
\ell_{2} &  3  &  4  &  2  &  0  &  4  &  0  &  0  &  5  &  3  &  5  &  5  &  5  &  0  &  4  &  3  &  2  &  1  &  5  &  2  &  5  \\
\ell_{3} &  0  &  1  &  4  &  1  &  1  &  1  &  4  &  3  &  0  &  0  &  2  &  4  &  3  &  0  &  2  &  4  &  2  &  5  &  0  &  4  \\
\ell_{4} &  2  &  4  &  1  &  4  &  4  &  4  &  2  &  3  &  0  &  4  &  3  &  2  &  4  &  1  &  2  &  1  &  1  &  1  &  0  &  4  \\
\ell_{5} &  5  &  2  &  3  &  0  &  0  &  5  &  1  &  1  &  0  &  0  &  5  &  4  &  5  &  3  &  5  &  4  &  2  &  4  &  1  &  1  \\
\ell_{6} &  5  &  4  &  3  &  4  &  2  &  3  &  3  &  5  &  5  &  5  &  2  &  0  &  2  &  4  &  0  &  3  &  4  &  5  &  2  &  1  \\
\hline
\end{array}$$

We would like to allocate modules to lecturers to **maximise expertise**.

Use Python and Z3 to identify an allocation of modules to lecturers that has the maximum possible expertise, for any given set of modules, lecturers and $k$.

Your solution should be in a single Python script, named `allocations.py`,
which when executed prints the answer to the terminal. (Both the *lecturer-modules allocations* and resulting *total expertise used*).


## Rules

- You are allowed to make use of functions from the Python standard library or the Z3
module (the version installed on Codio).
  Make sure your code contains the necessary import statements.
- You are not allowed to make use of functions from outside the standard library other than from the Z3 module.
  Your code will be marked by the installation of Python3 on Codio with no additional installs made.
- The code you write must be your own.
  You can look at the 6008CEM Codio guide or the textbooks recommended on Talis for help.
- List any external resources used to help you complete your work as comments in your code. (URLs, etc.)

## Marking Guidance

| | |
|--------:|:-----------------------|
|10 marks:| Z3 code to find a feasible solution.|
|10 marks:| Z3 code to find an optimal solution.|
| 5 marks:| Documentation (function encapsulation, docstrings, and comments)|
| 5 marks:| Effective use of GitHub.       |

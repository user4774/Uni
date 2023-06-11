
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

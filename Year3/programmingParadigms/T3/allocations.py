from z3 import *
from random import randint, seed
from pprint import pprint
import time


seed(10753424)  # set the seed to your Student ID

def get_preferences(nm: int, nl: int):
    return [[randint(0,5) for i in range(nm)] for j in range(nl)]  # nl x nm matrix

if __name__=='__main__':
    s = Optimize()  # Optimize instead of Solver to use maximize function to maximize expertise
    k = 4   # number of modules a lecturer can teach
    nm = 20 # number of modules
    nl = 6  # number of lecturers
    preferences = get_preferences(nm, nl)
    pprint(preferences)
    allocations = [[Int("x_%s_%s" % (i+1, j+1)) for i in range(nm) ] for j in range(nl)] # creates 2d vector of Ints for lecturers for each module

    # allocate lecturer to module if their expertise is greater than one, otherwise set allocation slot to 0 to indicate as not allocated
    allocate_expertise = [Or(If(preferences[j][i] > 1, allocations[j][i] == preferences[j][i], allocations[j][i] == 0), allocations[j][i] == 0) for i in range(nm) for j in range(nl)]
    
    # PbEq and PbLe found from https://stackoverflow.com/questions/43081929/k-out-of-n-constraint-in-z3py
    for i in range(nm):
      s.add(PbEq([(allocations[j][i] > 0, 1) for j in range(nl)], 1))   # allocate lecturer only if no other lecturers have been assigned to module (all others are 0)

    for i in range(nl):
      s.add(PbLe([(allocations[i][j] > 0, 1) for j in range(nm)], k))   # allocate lecturer only if they have less than or equal to k modules already

    conditions = allocate_expertise

    s.maximize(Sum([allocations[j][i] for i in range(nm) for j in range(nl)]))  # try maximize the sum of all allocation expertise values

    s.add(conditions) # add conditions to solver
    print("Finding Solution")
    t1=time.perf_counter()
    foundSol = s.check()  # sat when solution found
    t2=time.perf_counter()
    print("Solver finished in: " + str(t2-t1))

    if foundSol == sat:
      m = s.model()   # model solution
      ans = [[m.evaluate(allocations[j][i]) for i in range(nm)] for j in range(nl)]   # use ecaluate to add solution values to ans as 2d vector
      pprint(ans)   # print results
      expertise = 0   # variable to display total expertise
      for i in ans:
        for j in i:
          expertise += j.as_long()    # convert result back to format that python understands and add to expertise
      print(expertise)

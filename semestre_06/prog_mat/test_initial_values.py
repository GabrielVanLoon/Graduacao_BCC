from __future__ import print_function
from ortools.linear_solver import pywraplp


def main():
    # Create the mip solver with the SCIP backend.
    solver = pywraplp.Solver.CreateSolver('SCIP')

    infinity = solver.infinity()
    # x and y are integer non-negative variables.
    x = []
    for i in range(0,100):
        x.append(solver.IntVar(0, 1, "x{}".format(i)))

    const = []
    for i in range(0,5):
        const.append(solver.Constraint(-solver.infinity(),20))
        for j in range(0,20):
            const[i].SetCoefficient(x[i*20+j], (-1**j)*j)


    # Objective function: 3x + 4y.
    objective = solver.Objective()
    for i in range(0,100):
         objective.SetCoefficient(x[i],(-1**j)*5*i)
    objective.SetMaximization()

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print('Solution:')
        print('Objective value =', solver.Objective().Value())
    else:
        print('The problem does not have an optimal solution.')

    print('\nAdvanced usage:')
    print('Problem solved in %f milliseconds' % solver.wall_time())
    print('Problem solved in %d iterations' % solver.iterations())
    print('Problem solved in %d branch-and-bound nodes' % solver.nodes())


if __name__ == '__main__':
    main()
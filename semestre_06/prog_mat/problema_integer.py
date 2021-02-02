from __future__ import print_function
from ortools.linear_solver import pywraplp


def main():
    # Create the mip solver with the SCIP backend.
    solver = pywraplp.Solver.CreateSolver('SCIP')

    infinity = solver.infinity()
    # x and y are integer non-negative variables.
    x1 = solver.IntVar(0, solver.infinity(), 'x1')
    x2 = solver.IntVar(0, solver.infinity(), 'x2')
    x3 = solver.IntVar(0, 1, 'x3')
    x4 = solver.IntVar(0, 1, 'x4')

    # Constraint 0: 4x1 + 5x2 + 33 + x4 <= 10. 
    constraint0 = solver.Constraint(-solver.infinity(), 10)
    constraint0.SetCoefficient(x1, 4)
    constraint0.SetCoefficient(x2, 5)
    constraint0.SetCoefficient(x3, 3)
    constraint0.SetCoefficient(x4, 1)


    # Objective function: 3x + 4y.
    objective = solver.Objective()
    objective.SetCoefficient(x1, 10)
    objective.SetCoefficient(x2, 12)
    objective.SetCoefficient(x3, 7)
    objective.SetCoefficient(x4, 1.5)
    objective.SetMaximization()

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print('Solution:')
        print('Objective value =', solver.Objective().Value())
        print('x1 = ', x1.solution_value())
        print('x2 = ', x2.solution_value())
        print('x3 = ', x3.solution_value())
        print('x4 = ', x4.solution_value())
    else:
        print('The problem does not have an optimal solution.')

    print('\nAdvanced usage:')
    print('Problem solved in %f milliseconds' % solver.wall_time())
    print('Problem solved in %d iterations' % solver.iterations())
    print('Problem solved in %d branch-and-bound nodes' % solver.nodes())


if __name__ == '__main__':
    main()
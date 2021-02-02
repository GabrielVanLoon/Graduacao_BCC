from __future__ import print_function
from ortools.linear_solver import pywraplp



def LinearProgrammingExample():
    """Linear programming sample."""
    # Instantiate a Glop solver, naming it LinearExample.
    solver = pywraplp.Solver.CreateSolver('GLOP')

    # Create the two variables and let them take on any non-negative value.
    # x1 = solver.NumVar(0, solver.infinity(), 'x1')
    # x2 = solver.NumVar(0, solver.infinity(), 'x2')
    # x3 = solver.NumVar(0, 1, 'x3')
    # x4 = solver.NumVar(0, 1, 'x4')
    x1 = solver.NumVar(0, 1, 'x1')
    x2 = solver.NumVar(1, 1, 'x2')
    x3 = solver.NumVar(1, 1, 'x3')
    x4 = solver.NumVar(0, 1, 'x4')

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

    # Solve the system.
    solver.Solve()
    opt_solution = 10*x1.solution_value() + 12*x2.solution_value() + 7*x3.solution_value() + 1.5*x4.solution_value()
    print('Number of variables =', solver.NumVariables())
    print('Number of constraints =', solver.NumConstraints())
    # The value of each variable in the solution.
    print('Solution:')
    print('x1 = ', x1.solution_value())
    print('x2 = ', x2.solution_value())
    print('x3 = ', x3.solution_value())
    print('x4 = ', x4.solution_value())
    # The objective value of the solution.
    print('Optimal objective value =', opt_solution)


LinearProgrammingExample()
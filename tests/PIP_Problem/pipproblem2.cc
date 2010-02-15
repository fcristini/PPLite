/* Test the PIP_Problem class
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The PPL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include "ppl_test.hh"

namespace {

bool
test01() {
  Variable A(0);
  Variable B(1);
  Variable P(2);
  Variable Q(3);
  Variables_Set params(P, Q);

  Constraint_System cs;
  cs.insert(A + B >= 0);
  cs.insert(A - B <= P);
  cs.insert(3*A - 2*B == 5*Q);

  PIP_Problem pip(cs.space_dimension(), cs.begin(), cs.end(), params);

  bool ok = (pip.space_dimension() == 4);

  pip.add_space_dimensions_and_embed(2, 2);
  ok &= (pip.space_dimension() == 8);
  params.insert(Variable(6));
  params.insert(Variable(7));
  ok &= (pip.parameter_space_dimensions() == params);

  for (PIP_Problem::const_iterator i = pip.constraints_begin(),
         i_end = pip.constraints_end(); i != i_end; ++i)
    print_constraint(*i);

  return ok;
}

bool
test02() {
  PIP_Problem pip_1(2);
  PIP_Problem pip_2(2);
  pip_2 = pip_1;

  Variables_Set params(Variable(1));
  pip_2.add_to_parameter_space_dimensions(params);

  std::swap(pip_1, pip_2);

  bool ok = (pip_1.space_dimension() == 2
             && pip_2.space_dimension() == 2
             && pip_1.parameter_space_dimensions() == params
             && pip_2.parameter_space_dimensions() == Variables_Set());

  return ok;
}

bool
test03() {
  PIP_Problem pip;
  PIP_Problem::Control_Parameter_Value cp;

  cp = pip.get_control_parameter(PIP_Problem::CUTTING_STRATEGY);
  bool ok = (cp == PIP_Problem::CUTTING_STRATEGY_FIRST);

  pip.set_control_parameter(PIP_Problem::CUTTING_STRATEGY_DEEPEST);
  cp = pip.get_control_parameter(PIP_Problem::CUTTING_STRATEGY);
  ok &= (cp == PIP_Problem::CUTTING_STRATEGY_DEEPEST);

  PIP_Problem pip_copy(pip);
  cp = pip_copy.get_control_parameter(PIP_Problem::CUTTING_STRATEGY);
  ok &= (cp == PIP_Problem::CUTTING_STRATEGY_DEEPEST);

  return ok;
}

bool
test04() {
  PIP_Problem pip(6);
  Variables_Set params(Variable(3), Variable(5));
  pip.add_to_parameter_space_dimensions(params);

  bool ok = (pip.get_big_parameter_dimension() == not_a_dimension());

  pip.set_big_parameter_dimension(3);
  ok &= (pip.get_big_parameter_dimension() == 3);

  pip.set_big_parameter_dimension(5);
  ok &= (pip.get_big_parameter_dimension() == 5);

  return ok;
}

bool
test05() {
  PIP_Problem pip(1);
  bool ok = (pip.solve() == OPTIMIZED_PIP_PROBLEM);
  // Solving again a problem already optimized.
  ok &= (pip.solve() == OPTIMIZED_PIP_PROBLEM);

  return ok;
}

bool
test06() {
  Variable X(0);
  PIP_Problem pip(1);
  pip.add_constraint(X == -X);
  pip.add_constraint(X >= 1);

  bool ok = (pip.solve() == UNFEASIBLE_PIP_PROBLEM);
  // Solving again a problem already detected to be unfeasible.
  ok &= (pip.solve() == UNFEASIBLE_PIP_PROBLEM);

  return ok;
}

bool
test07() {
  Variable X(0);
  PIP_Problem pip(1);
  pip.add_constraint(X == -X);
  bool ok = (pip.solve() == OPTIMIZED_PIP_PROBLEM);

  // Incrementally adding a constraint.
  pip.add_constraint(X >= 1);
  // Solving a problem that was optimized and now is unfeasible.
  ok &= (pip.solve() == UNFEASIBLE_PIP_PROBLEM);

  return ok;
}

bool
test08() {
  Variable X(0);
  Variable Y(1);
  Variable Z(2);

  Constraint_System cs;
  cs.insert(X == 2);
  cs.insert(Y < 1);
  cs.insert(Z == 7);

  Variables_Set params(Y, Z);

  PIP_Problem pip(cs.space_dimension(), cs.begin(), cs.end(), params);

  bool ok = (pip.solve() == OPTIMIZED_PIP_PROBLEM);

  return ok;
}

bool
test09() {
  Variable X(0);
  Variable Y(1);
  Variable Z(2);

  PIP_Problem pip(3);
  pip.add_constraint(X == 2);
  pip.add_constraint(Y < 1);
  pip.add_constraint(Z == 7);

  bool ok = (pip.solve() == OPTIMIZED_PIP_PROBLEM);

  return ok;
}

bool
test10() {
  Variable A(0);
  Constraint_System cs;
  cs.insert(A >= 5);

  PIP_Problem pip1(3, cs.begin(), cs.end(), Variables_Set());
  bool ok = (pip1.solve() == OPTIMIZED_PIP_PROBLEM);

  return ok;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
  DO_TEST(test06);
  DO_TEST(test07);
  DO_TEST(test08);
  DO_TEST(test09);
  DO_TEST(test10);
END_MAIN
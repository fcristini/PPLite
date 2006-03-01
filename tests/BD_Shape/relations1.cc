/* Test BD_Shape::relation_with().
   Copyright (C) 2001-2006 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
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

  TBD_Shape bd(2, EMPTY);

  Poly_Con_Relation rel = bd.relation_with(A >= 0);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(A >= 0) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_included()
    && Poly_Con_Relation::is_disjoint();

  return rel == known_result;
}

bool
test02() {
  // Variable x(0);
  Variable y(1);

  TBD_Shape bd(2);
  bd.add_constraint(y <= -1);

  Constraint c(y >= 0);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_disjoint();

  return rel == known_result;
}

bool
test03() {
  // Variable x(0);
  Variable y(1);
  // Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(y <= 1);

  Constraint c(y >= 0);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::strictly_intersects();

  return rel == known_result;
}

bool
test04() {
  // Variable x(0);
  // Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(z >= 1);

  Constraint c(z >= 0);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_included();

  return rel == known_result;
}

bool
test05() {
  Variable x(0);
  // Variable y(1);

  TBD_Shape bd(2);
  bd.add_constraint(x == 1);

  Constraint c(x >= 1);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_included();

  return rel == known_result;
}

bool
test06() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x == 1);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(x == 1);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_included();

  return rel == known_result;
}

bool
test07() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x >= 3);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(x == 2);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_disjoint();

  return rel == known_result;
}

bool
test08() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x <= 3);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(x == 2);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::strictly_intersects();

  return rel == known_result;
}

bool
test09() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x <= 3);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(-x >= 2);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::strictly_intersects();

  return rel == known_result;
}

bool
test10() {
  // The zero-dim universe BDS.
  TBD_Shape bd(0);
  Poly_Con_Relation rel = bd.relation_with(Linear_Expression(0) >= 0);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(0 >= 0) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_included()
    && Poly_Con_Relation::saturates();

  return rel == known_result;
}

bool
test11() {
  // The zero-dim universe BDS.
  TBD_Shape bd(0);
  Poly_Con_Relation rel = bd.relation_with(Linear_Expression(0) >= 1);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(0 >= 1) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_disjoint();

  return rel == known_result;
}

bool
test12() {
  // The zero-dim universe BDS.
  TBD_Shape bd;
  Poly_Con_Relation rel = bd.relation_with(Linear_Expression(1) >= 0);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(1 >= 0) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_included();

  return rel == known_result;
}

bool
test13() {
  Variable x(0);
  // Variable y(1);

  TBD_Shape bd(2);
  bd.add_constraint(x == 1);

  Constraint c(x > 1);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_disjoint();

  return rel == known_result;
}

bool
test14() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);
  bd.add_constraint(x == 1);
  bd.add_constraint(y <= 0);
  bd.add_constraint(z >= 2);

  Constraint c(x > 1);
  Poly_Con_Relation rel = bd.relation_with(c);

  print_constraints(bd, "--- bd ---");
  print_constraint(c, "--- c ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(c) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::saturates()
    && Poly_Con_Relation::is_disjoint();

  return rel == known_result;
}

bool
test15() {
  Variable x(0);
  Variable y(1);

  TBD_Shape bd(2);
  bd.add_constraint(x == 0);
  bd.add_constraint(y >= 1);

  Poly_Con_Relation rel = bd.relation_with(-y >= -1);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(-y >= -1) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::strictly_intersects();

  return rel == known_result;
}

bool
test16() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);

  bd.add_constraint(x - y <= 2);
  bd.add_constraint(x - z >= -1);
  bd.add_constraint(y <= 3);

  Poly_Con_Relation rel = bd.relation_with(y > 3);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(y > 3) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_disjoint();

  return rel == known_result;
}

bool
test17() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd(3);

  bd.add_constraint(x - y <= 2);
  bd.add_constraint(x - z >= -1);
  bd.add_constraint(y <= 3);

  Poly_Con_Relation rel = bd.relation_with(-y >= -4);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(1 >= 0) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_included();

  return rel == known_result;
}

bool
test18() {
  Variable A(0);

  TBD_Shape bd(1);
  bd.add_constraint(A <= 0);
  bd.add_constraint(A >= -2);

  Poly_Con_Relation rel = bd.relation_with(Linear_Expression(0) >= -1);

  print_constraints(bd, "--- bd ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(0 >= -1) == " << rel << endl;

  Poly_Con_Relation known_result = Poly_Con_Relation::is_included();

  return rel == known_result;
}

bool
test19() {
  // We verify that a generator is not subsumed by an empty BDS.
  Variable x(0);

  TBD_Shape bd(2, EMPTY);

  Generator g = point(x);
  Poly_Gen_Relation rel = bd.relation_with(g);

  print_constraints(bd, "--- bd ---");
  print_generator(g, "--- g ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(v(A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  return rel == known_result;
}

bool
test20() {
  // We verify that a zero-dimensional generator is subsumed
  // by a zero-dimensional, universal BDS.
  TBD_Shape bd;

  Generator g = point();
  Poly_Gen_Relation rel = bd.relation_with(g);

  print_constraints(bd, "--- bd ---");
  print_generator(g, "--- g ---");
  using namespace IO_Operators;
  nout << "bd.relation_with(v()) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::subsumes();

  return rel == known_result;
}

} // namespace

BEGIN_MAIN
  NEW_TEST(test01);
  NEW_TEST(test02);
  NEW_TEST(test03);
  NEW_TEST(test04);
  NEW_TEST(test05);
  NEW_TEST(test06);
  NEW_TEST(test07);
  NEW_TEST(test08);
  NEW_TEST(test09);
  NEW_TEST(test10);
  NEW_TEST(test11);
  NEW_TEST(test12);
  NEW_TEST(test13);
  NEW_TEST(test14);
  NEW_TEST(test15);
  NEW_TEST(test16);
  NEW_TEST(test17);
  NEW_TEST(test18);
  NEW_TEST(test19);
  NEW_TEST(test20);
END_MAIN

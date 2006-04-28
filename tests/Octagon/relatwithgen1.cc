/* Test Octagonal_Shape::relation_with(g): we verify that a generator
   is not subsumed by an empty octagon.
   Copyright (C) 2001-2004 Roberto Bagnara <bagnara@cs.unipr.it>

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
  Variable x(0);

  TOctagonal_Shape oct(2, EMPTY);

  print_constraints(oct, "--- oct ---");

  Generator g = point(x);

  print_generator(g, "--- g ---");

  Poly_Gen_Relation rel = oct.relation_with(g);

  using namespace IO_Operators;
  nout << "oct.relation_with(v(A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  bool ok = (rel == known_result);

  return ok;
}

bool
test02() {
  TOctagonal_Shape oct;
  print_constraints(oct, "--- oct ---");

  Generator g = point();

  print_generator(g, "--- g ---");

  Poly_Gen_Relation rel = oct.relation_with(g);

  using namespace IO_Operators;
  nout << "oct.relation_with(v()) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::subsumes();

  bool ok = (rel == known_result);

  return ok;
}

bool
test03() {
  Variable A(0);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A == 0);

  print_constraints(oct, "--- oct ---");

  Poly_Gen_Relation rel = oct.relation_with(point(2*A));

  using namespace IO_Operators;
  nout << "oct.relation_with(point(2*A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  bool ok = (rel == known_result);

  return ok;
}

bool
test04() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A + B >= 0);
  oct.add_constraint(B >= 0);

  print_constraints(oct, "*** oct ***");

  Poly_Gen_Relation rel1 = oct.relation_with(point(B));

  using namespace IO_Operators;
  nout << "oct.relation_with(point(B)) == " << rel1 << endl;

  Poly_Gen_Relation rel2 = oct.relation_with(point(-B));

  nout << "oct.relation_with(point(-B)) == " << rel2 << endl;

  Poly_Gen_Relation known_result1 = Poly_Gen_Relation::subsumes();
  Poly_Gen_Relation known_result2 = Poly_Gen_Relation::nothing();

  bool ok = (rel1 == known_result1 && rel2 == known_result2);

  return ok;
}

bool
test05() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A >= 0);
  oct.add_constraint(B == 1);
  print_constraints(oct, "*** oct ***");

  Poly_Gen_Relation rel = oct.relation_with(ray(-A));

  using namespace IO_Operators;
  nout << "oct.relation_with(ray(-A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  bool ok = (rel == known_result);

  return ok;
}

bool
test06() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A <= 0);
  oct.add_constraint(B == 1);
  print_constraints(oct, "*** oct ***");

  Poly_Gen_Relation rel = oct.relation_with(ray(-A));

  using namespace IO_Operators;
  nout << "oct.relation_with(ray(-A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::subsumes();

  bool ok = (rel == known_result);

  return ok;
}

bool
test07() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A >= 0);
  oct.add_constraint(B >= -1);

  print_constraints(oct, "*** oct ***");

  Poly_Gen_Relation rel = oct.relation_with(line(A));

  using namespace IO_Operators;
  nout << "oct.relation_with(line(A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  bool ok = (rel == known_result);

  return ok;
}

bool
test08() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A == 0);
  oct.add_constraint(B >= -1);
  print_constraints(oct, "*** oct ***");

  Poly_Gen_Relation rel = oct.relation_with(line(-A));

  using namespace IO_Operators;
  nout << "oct.relation_with(line(A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  bool ok = (rel == known_result);

  return ok;
}

bool
test09() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct	(2);
  oct.add_constraint(A <= 0);
  oct.add_constraint(B == 2);

  print_constraints(oct	, "*** oct	 ***");

  Poly_Gen_Relation rel = oct.relation_with(closure_point(A));

  using namespace IO_Operators;
  nout << "oct.relation_with(line(A)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  bool ok = (rel == known_result);

  return ok;
}

bool
test10() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A >= 2);
  oct.add_constraint(A + B <= 3);

  print_constraints(oct, "*** oct ***");

  Poly_Gen_Relation rel = oct.relation_with(ray(A + B));

  using namespace IO_Operators;
  nout << "oct.relation_with(ray(A + B)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::nothing();

  bool ok = (rel == known_result);

  return ok;
}

bool
test11() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A >= 2);
  oct.add_constraint(A + B <= 3);
  oct.add_constraint(A - B >= 0);

  print_constraints(oct, "*** oct ***");

  Poly_Gen_Relation rel = oct.relation_with(ray(-2*B));

  using namespace IO_Operators;
  nout << "oct.relation_with(ray(-2*B)) == " << rel << endl;

  Poly_Gen_Relation known_result = Poly_Gen_Relation::subsumes();

  bool ok = (rel == known_result);

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
  DO_TEST(test11);
END_MAIN

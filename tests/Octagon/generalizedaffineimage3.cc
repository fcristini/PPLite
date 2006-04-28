/* Test Octagonal_Shape::generalized_affine_image().
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
  Variable x(0);
  Variable y(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(x <= 4);
  oct.add_constraint(x >= -6);
  oct.add_constraint(y == 0);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(2);
  known_result.add_constraint(x <= 4);
  known_result.add_constraint(x >= -6);
  known_result.add_constraint(y <= 1);

  oct.generalized_affine_image(y, LESS_THAN_OR_EQUAL, -y + 1);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(y, "
                         "LESS_THAN_OR_EQUAL, -y + 1) ***");

  return ok;
}

bool
test02() {
  Variable x(0);
  Variable y(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(x <= 4);
  oct.add_constraint(x >= -6);
  oct.add_constraint(y == 0);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(2);
  known_result.add_constraint(x >= -7);
  known_result.add_constraint(y == 0);

  oct.generalized_affine_image(x, GREATER_THAN_OR_EQUAL, -x - 3);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct,
		    "*** oct.generalized_affine_image(x, "
		    "GREATER_THAN_OR_EQUAL, -x - 3) ***");

  return ok;
}

bool
test03() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A >= 0);
  oct.add_constraint(B <= 1);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(2);
  known_result.add_constraint(A >= 0);
  known_result.add_constraint(B <= 2);

  oct.generalized_affine_image(B, LESS_THAN_OR_EQUAL, 3*B + 1, 2);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(B, "
                         "LESS_THAN_OR_EQUAL, 3*B + 1, 2) ***");

  return ok;
}

bool
test04() {
  Variable A(0);
  Variable B(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A == 0);
  oct.add_constraint(B >= 1);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(2);
  known_result.add_constraint(A == 0);
  known_result.add_constraint(B >= -1);

  oct.generalized_affine_image(B, GREATER_THAN_OR_EQUAL, B - 2);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(B, "
		    "GREATER_THAN_OR_EQUAL, B - 2) ***");

  return ok;
}

bool
test05() {
  Variable A(0);
  Variable B(1);
  Linear_Expression expr(2*A + 3);

  TOctagonal_Shape oct(2);
  oct.add_constraint(B <= 1);
  oct.add_constraint(A + B == 0);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(2);
  known_result.add_constraint(2*A >= 1);
  known_result.add_constraint(B <= 1);
  known_result.add_constraint(2*(-A - B) <= -3);

  oct.generalized_affine_image(A, GREATER_THAN_OR_EQUAL, 2*A + 3, 2);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(A, "
		    "GREATER_THAN_OR_EQUAL, 2*A + 3, 2) ***");

  return ok;
}

bool
test06() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TOctagonal_Shape oct(3);
  oct.add_constraint(A - B == 0);
  oct.add_constraint(B <= 1);
  oct.add_constraint(C + A <= 2);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(3);
  known_result.add_constraint(A - B == 0);
  known_result.add_constraint(B <= 1);
  known_result.add_constraint(A + B <= 2);
  known_result.add_constraint(A <= 1);

  oct.generalized_affine_image(C, LESS_THAN_OR_EQUAL, 2*C + 1, 5);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(C, "
                         "LESS_THAN_OR_EQUAL, 2*C + 1, 5) ***");

  return ok;
}

bool
test07() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TOctagonal_Shape oct(3);
  oct.add_constraint(A - B == 0);
  oct.add_constraint(B <= 1);
  oct.add_constraint(C + A <= 2);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(oct);
  known_result.affine_image(C, 5*C - 3, 4);

  oct.generalized_affine_image(C, EQUAL, 5*C - 3, 4);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(C, "
		    "EQUAL, 5*C - 3, 4) ***");

  return ok;
}

bool
test08() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TOctagonal_Shape oct(3);
  oct.add_constraint(A - B == 0);
  oct.add_constraint(B <= 1);
  oct.add_constraint(C + A <= 2);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(3);
  known_result.add_constraint(B >= -1);
  known_result.add_constraint(C + A <= 2);
  known_result.add_constraint(A <= 1);

  oct.generalized_affine_image(B, GREATER_THAN_OR_EQUAL, -B - 2, 3);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(B, "
                         "GREATER_THAN_OR_EQUAL, -B - 2, 3) ***");

  return ok;
}

bool
test09() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TOctagonal_Shape oct(3);
  oct.add_constraint(A - B == 0);
  oct.add_constraint(B <= 1);
  oct.add_constraint(C + A <= 2);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(3);
  known_result.add_constraint(A <= 1);
  known_result.add_constraint(C + A <= 2);

  oct.generalized_affine_image(B, LESS_THAN_OR_EQUAL, 4*A - 2*C + 3, -3);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(B, "
                         "LESS_THAN_OR_EQUAL, 4*A - 2*C + 3, -3) ***");

  return ok;
}

bool
test10() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TOctagonal_Shape oct(3);
  oct.add_constraint(A - B == 0);
  oct.add_constraint(B <= 1);
  oct.add_constraint(C + A <=2);

  print_constraints(oct, "*** oct ***");

  Octagonal_Shape<mpq_class> known_result(oct);
  known_result.affine_image(B, 2*A - 4*B + C + 3, 3);

  oct.generalized_affine_image(B, EQUAL, 2*A - 4*B + C + 3, 3);

  bool ok = (Octagonal_Shape<mpq_class>(oct) == known_result);

  print_constraints(oct, "*** oct.generalized_affine_image(B, "
		         "EQUAL, 2*A - 4*B + C + 3, 3) ***");

  return ok;
}

bool
test11() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TOctagonal_Shape oct(3);
  oct.add_constraint(x + y >= 0);
  oct.add_constraint(y >= 0);
  oct.add_constraint(z <= 2);
  oct.add_constraint(z - x >= 9);

  try {
    // This is an invalid use of the function
    // Octagonal_Shape::generalized_affine_image(v, e, d): it is illegal applying
    // the function with a linear expression with the denominator equal to
    // zero.
    Coefficient d = 0;
    oct.generalized_affine_image(y, LESS_THAN_OR_EQUAL, y + 1, d);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl;
  }
  catch (...) {
    return false;
  }
  return true;
}

bool
test12() {
  Variable x(0);
  Variable y(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(x >= y);

  try {
    // This is an incorrect use of the function
    // Octagonal_Shape::generalized_affine_image(v, r, expr, d): it is illegal
    // to use a strict relation symbol.
    oct.generalized_affine_image(x, LESS_THAN, x + 1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl;
  }
  catch (...) {
    return false;
  }
  return true;
}

bool
test13() {
  Variable x(0);
  Variable y(1);

  TOctagonal_Shape oct(2);
  oct.add_constraint(x >= y);

  try {
    // This is an incorrect use of the function
    // Octagonal_Shape::generalized_affine_image(v, r, expr, d): it is illegal
    // to use a strict relation symbol.
    oct.generalized_affine_image(x, GREATER_THAN, x + 1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl;
  }
  catch (...) {
    return false;
  }
  return true;
}

bool
test14() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TOctagonal_Shape oct(2);
  oct.add_constraint(x >= y);

  try {
    // This is an incorrect use of the function
    // Octagonal_Shape::generalized_affine_image(v, r, expr, d): it is illegal
    // to apply to a expression which space dimension is
    // greather than the octagon's space dimension.
    oct.generalized_affine_image(y, GREATER_THAN_OR_EQUAL, z);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl;
  }
  catch (...) {
    return false;
  }
  return true;
}

bool
test15() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A >= 0);

  try {
    // This is an incorrect use of function
    // Octagonal_Shape::generalized_affine_image(lhs, r, rhs):
    // it is illegal to use a variable in the `rhs' expression that
    // does not appear in the octagon.
    oct.generalized_affine_image(A + B, GREATER_THAN_OR_EQUAL, B + C);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl;
  }
  catch (...) {
    return false;
  }
  return true;
}

bool
test16() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TOctagonal_Shape oct(2);
  oct.add_constraint(A >= 1);

  try {
    // This is an incorrect use of function
    // Octagonal_Shape::generalized_affine_image(lhs, r, rhs):
    // it is illegal to use a variable in the `lhs' expression that
    // does not appear in the octagon.
    oct.generalized_affine_image(B + C, LESS_THAN_OR_EQUAL, A + 1);
  }
  catch (invalid_argument& e) {
    nout << "invalid_argument: " << e.what() << endl;
  }
  catch (...) {
    return false;
  }
  return true;
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
  DO_TEST(test12);
  DO_TEST(test13);
  DO_TEST(test14);
  DO_TEST(test15);
  DO_TEST(test16);
END_MAIN

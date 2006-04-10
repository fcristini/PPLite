/* Test Octagon::affine_dimension().
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

  TOctagon oct1(3);

  oct1.add_constraint(x <= 2);
  oct1.add_constraint(x - y == 3);
  oct1.add_constraint(y <= 2);

  TOctagon oct2(2);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  dimension_type affine_dim1 = oct1.affine_dimension();
  dimension_type affine_dim2 = oct2.affine_dimension();

  nout << endl
       << "The affine dimension of a system of `oct1' "
       << endl
       << affine_dim1
       << endl;

  nout << endl
       << "The affine dimension of a system of `oct2' "
       << endl
       << affine_dim2
       << endl;

  bool ok = (affine_dim1 == affine_dim2);

  return ok;
}

bool
test02() {
  Variable A(0);
  Variable B(1);
  Variable C(2);
  Variable D(3);
  Variable E(4);

  TOctagon oct1(5);

  oct1.add_constraint(A <= 5);
  oct1.add_constraint(A - B == 3);
  oct1.add_constraint(C <= 2);
  oct1.add_constraint(E - D == 2);

  TOctagon oct2(4);

  oct2.add_constraint(A <= 1);
  oct2.add_constraint(A - D == 8);
  oct2.add_constraint(B <= 7);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  dimension_type affine_dim1 = oct1.affine_dimension();
  dimension_type affine_dim2 = oct2.affine_dimension();

  nout << endl
       << "The affine dimension of a system of `oct1' "
       << endl
       << affine_dim1
       << endl;

  nout << endl
       << "The affine dimension of a system of `oct2' "
       << endl
       << affine_dim2
       << endl;

  bool ok = (affine_dim1 == affine_dim2);

  return ok;
}

bool
test03() {
  Variable A(0);
  Variable B(1);
  Variable C(2);
  Variable D(3);
  Variable E(4);

  TOctagon oct1(5);

  oct1.add_constraint(A == 5);
  oct1.add_constraint(A - B == 3);
  oct1.add_constraint(C <= 2);
  oct1.add_constraint(E - D == 2);

  TOctagon oct2(5);

  oct2.add_constraint(A == 1);
  oct2.add_constraint(E == 1);
  oct2.add_constraint(A - D == 8);
  oct2.add_constraint(B <= 7);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  dimension_type affine_dim1 = oct1.affine_dimension();
  dimension_type affine_dim2 = oct2.affine_dimension();

  nout << endl
       << "The affine dimension of a system of `oct1' "
       << endl
       << affine_dim1
       << endl;

  nout << endl
       << "The affine dimension of a system of `oct2' "
       << endl
       << affine_dim2
       << endl;

  bool ok = (affine_dim1 == affine_dim2);

  return ok;
}

bool
test04() {
  Variable A(0);
  Variable B(1);

  TOctagon oct1(2);

  oct1.add_constraint(A <= 3);
  oct1.add_constraint(B - A <= -5);
  oct1.add_constraint(-B <= 2);

  TOctagon oct2(2);

  oct2.add_constraint(A == 0);
  oct2.add_constraint(B == 2);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  dimension_type affine_dim1 = oct1.affine_dimension();
  dimension_type affine_dim2 = oct2.affine_dimension();

  nout << endl
       << "The affine dimension of a system of `oct1' "
       << endl
       << affine_dim1
       << endl;

  nout << endl
       << "The affine dimension of a system of `oct2' "
       << endl
       << affine_dim2
       << endl;

  bool ok = (affine_dim1 == affine_dim2);

  return ok;
}

bool
test05() {
  Variable A(0);
  Variable B(1);

  TOctagon oct1(2, EMPTY);

  TOctagon oct2(7);

  oct2.add_constraint(A <= 1);
  oct2.add_constraint(B == 2);
  oct2.add_constraint(B - A <= -6);

  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");

  dimension_type affine_dim1 = oct1.affine_dimension();
  dimension_type affine_dim2 = oct2.affine_dimension();

  nout << endl
       << "The affine dimension of a system of `oct1' "
       << endl
       << affine_dim1
       << endl;

  nout << endl
       << "The affine dimension of a system of `oct2' "
       << endl
       << affine_dim2
       << endl;

  bool ok = (affine_dim1 == affine_dim2);

  return ok;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
END_MAIN


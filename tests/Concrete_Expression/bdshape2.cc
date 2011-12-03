/* Test BD_Shape::refine_wiht_linear_form_inequaity on interval linear forms.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)

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
site: http://bugseng.com/products/ppl/ . */

#include "ppl_test.hh"

namespace {

// Tests trivial cases.
bool
test01() {
  Variable A(0);
  FP_BD_Shape bd1(0);
  bool ok1 = false;
  FP_Linear_Form l1(A);
  FP_Linear_Form l2;

  try{
    bd1.refine_with_linear_form_inequality(l1,l2);
    std::cout <<"no eccezione" <<std::endl;
  }
  catch(std::invalid_argument e) {
    ok1 = true;
  }


  bool ok2 = false;
  try{
    bd1.refine_with_linear_form_inequality(l2,l1);
    std::cout <<"no eccezione" <<std::endl;
  }
  catch(std::invalid_argument e){
    FP_BD_Shape bd2(1);
    bd2.refine_with_linear_form_inequality(l1, l1);
    bd2.refine_with_linear_form_inequality(-l1, l1);
    bd2.refine_with_linear_form_inequality(l1, -l1);
    FP_Interval tmp(0);
    l1 -= A;
    l1 += tmp;
    l2 += tmp;
    bd2.refine_with_linear_form_inequality(l1, l2);
    ok2 = true;
  }

  return ok1 && ok2;
}

// Tests [-1, 2] <= [-4, -1] + A and [-4, -1] + A <= [-1, 2].
bool
test02() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(-1);
  tmp.join_assign(2);
  FP_Linear_Form l1(tmp);
  FP_Linear_Form l2(A);
  tmp.lower() = -4;
  tmp.upper() = -1;
  l2 += tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [-1, 2] <= [-4, -1] + A ***");

  known_result.add_constraint(-A <= 0);
  print_constraints(known_result, "*** known_result1 ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [-4, -1] + A <= [-1, 2] ***");

  known_result.add_constraint(A <= 6);
  print_constraints(known_result, "*** known_result2 ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;

}

// Tests [3.5, 6] <= [-2.5, 0] - A and [-2.5, 0] - A <= [3.5, 6].
bool
test03() {
  Variable A(0);
  Variable B(1);

  FP_Octagonal_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_Octagonal_Shape known_result(bd1);
  FP_Interval tmp(3.5);
  tmp.join_assign(6);
  FP_Linear_Form l1(tmp);
  FP_Linear_Form l2(-A);
  tmp.lower() = -2.5;
  tmp.upper() = 0;
  l2 += tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [3.5, 6] <= [-2.5, 0] - A ***");

  known_result.add_constraint(2*A <= -7);
  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [-2.5, 0] - A <= [3.5, 6] ***");

  known_result.add_constraint(2*(-A) <= 17);
  print_constraints(known_result, "*** known_result2 ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;

}

// Tests [-0.5, 1] + A <= [2.5, 5] + B and [2.5, 5] + B <= [-0.5, 1] + A.
bool
test04() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(-0.5);
  tmp.join_assign(1);
  FP_Linear_Form l1(A);
  l1 += tmp;
  FP_Linear_Form l2(B);
  tmp.lower() = 2.5;
  tmp.upper() = 5;
  l2 += tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [-0.5, 1] + A <= [2.5, 5] + B ***");

  known_result.add_constraint(2*A - 2*B <= 11);
  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [2.5, 5] + B <= [-0.5, 1] + A ***");

  known_result.add_constraint((2*B) - (2*A) <= -3);
  print_constraints(known_result, "*** known_result2 ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;

}

// Tests [1, 3] + A <= [4, 4] - B and [4, 4] - B <= [1, 3] + A.
bool
test05() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(4);
  FP_Linear_Form l2(-B);
  l2 += tmp;
  FP_Linear_Form l1(A);
  tmp.lower() = 1;
  tmp.upper() = 3;
  l1 += tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [1, 3] + A <= [4, 4] - B ***");

  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [4, 4] - B <= [1, 3] + A ***");

  known_result.add_constraint(-A <= 1);
  known_result.add_constraint(-B <= 1);
  print_constraints(known_result, "*** known_result2 ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;

}

// Tests [1, 4] - A <= [-2, -2] + B and [-2, -2] + B <= [1, 4] - A.
bool
test06() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(-2);
  FP_Linear_Form l2(B);
  l2 += tmp;
  FP_Linear_Form l1(-A);
  tmp.lower() = 1;
  tmp.upper() = 4;
  l1 += tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [1, 4] - A <= [-2, -2] + B ***");

  known_result.add_constraint(-A <= -1);
  known_result.add_constraint(-B <= -1);
  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [-2, -2] + B <= [1, 4] - A ***");

  print_constraints(known_result, "*** known_result2 ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;

}

// Tests [-3, -0.5] - A <= [-2, -1] - B and [-2, -1] - B <= [-3, -0.5] - A.
bool
test07() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(-2);
  tmp.join_assign(-1);
  FP_Linear_Form l2(-B);
  l2 += tmp;
  FP_Linear_Form l1(-A);
  tmp.lower() = -3;
  tmp.upper() = -0.5;
  l1 += tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [-3, -0.5] - A <= [-2, -1] - B ***");

  known_result.add_constraint(B - A <= 2);
  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [-2, -1] - B <= [-3, -0.5] - A ***");

  known_result.add_constraint(-2*B + 2*A <= 3);
  print_constraints(known_result, "*** known_result2 ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;

}

// Tests [1, 3] * B <= [-1.5, 0] * A.
bool
test08() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(3);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(1);
  tmp.join_assign(3);
  FP_Linear_Form l1(B);
  l1 *= tmp;
  FP_Linear_Form l2(A);
  tmp.lower() = -1.5;
  tmp.upper() = 0;
  l2 *= tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [1, 3] * B <= [-1.5, 0] * A ***");

  print_constraints(known_result, "*** known_result ***");

  bool ok = (bd1 == known_result);

  return ok;
}

// Tests [0.25, 0.5] * A + [-2, -1] * B <= [-7, -2]
// and   [-7, -2] <= [0.25, 0.5] * A + [-2, -1] * B.
bool
test09() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);

  FP_Interval tmp(-7);
  tmp.join_assign(-2);
  FP_Linear_Form l2(tmp);
  FP_Linear_Form l1(A);
  tmp.lower() = 0.25;
  tmp.upper() = 0.5;
  l1 *= tmp;
  tmp.lower() = -2;
  tmp.upper() = -1;
  l1 += tmp * FP_Linear_Form(B);
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [0.25, 0.5]*A + [-2, -1]*B <= [-7, -2] ***");

  known_result.add_constraint(-2*B + 2*A <= 3);
  known_result.add_constraint(2*A <= 7);
  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [-7, -2] <= [0.25, 0.5]*A + [-2, -1]*B ***");

  print_constraints(known_result, "*** known_result2 ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;
}

// Tests [-5, -1] * A <= [2, 3] * B + [0.5, 1].
bool
test10() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(2);
  tmp.join_assign(3);
  FP_Linear_Form l2(B);
  l2 *= tmp;
  tmp.lower() = 0.5;
  tmp.upper() = 1;
  l2 += tmp;
  FP_Linear_Form l1(A);
  tmp.lower() = -5;
  tmp.upper() = -1;
  l1 *= tmp;
  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** [-5, -1] * A <= [2, 3] * B + [0.5, 1] ***");

  known_result.add_constraint(B - A <= 17);
  known_result.add_constraint(-B + A <= 17);
  known_result.add_constraint(A <= 19);
  known_result.add_constraint(-A <= 15);
  print_constraints(known_result, "*** known_result ***");

  bool ok = (bd1 == known_result);

  return ok;
}

// Tests Octagonal_Shape<T>::refine_fp_interval_abstract_store.
bool
test11() {
  Variable A(0);
  Variable B(1);
  FP_Interval_Abstract_Store store(2);
  FP_Interval tmp(-2.5);
  tmp.join_assign(3.5);
  store.set_interval(A, tmp);
  tmp.lower() = -4;
  tmp.upper() = 4;
  store.set_interval(B, tmp);
  BD_Shape<ANALYZER_FP_FORMAT> bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(B <= 2);
  bd1.add_constraint(-A <= 3);
  bd1.add_constraint(2*(-B) <= 3);
  bd1.refine_fp_interval_abstract_store(store);

  tmp = store.get_interval(A);
  nout << "*** store.get_interval(A) ***" << endl
       << tmp << endl;

  FP_Interval known_result1(-2.5);
  known_result1.join_assign(2);
  nout << "*** known_result1 ***" << endl
       << known_result1 << endl;

  bool ok1 = (tmp == known_result1);

  tmp = store.get_interval(B);
  nout << "*** store.get_interval(B) ***" << endl
       << tmp << endl;

  FP_Interval known_result2(-1.5);
  known_result2.join_assign(2);
  nout << "*** known_result2 ***" << endl
       << known_result2 << endl;

  bool ok2 = (tmp == known_result2);

  return ok1 && ok2;
}

// Tests - A <= [-1, 0] and [0, 1] <= A.
bool
test12() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(0);
  tmp.join_assign(-1);
  FP_Linear_Form l2(tmp);
  FP_Linear_Form l1(-A);

  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** - A <= [-1, 0]  ***");

  known_result.add_constraint( - A <= 0);
  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** [0, 1] <= - A  ***");
  known_result.add_constraint( A <= 1);
  print_constraints(known_result, "*** known_result ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;
}

// Tests  A <= - B + [-1, 0] and - B + [-1, 0] <= A.
bool
test13() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(0);
  tmp.join_assign(-1);
  FP_Linear_Form l2(-B);
  FP_Linear_Form l1(A);
   l2 += tmp;

  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** A <= - B + [-1, 0]  ***");

  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** - B + [-1, 0] <= A  ***");
  known_result.add_constraint(-A <= 3);
  known_result.add_constraint(-B <= 3);

  print_constraints(known_result, "*** known_result ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;
}

// Tests  A <= - A + [-1, 0] and - A + [0, 1] <= A.
bool
test14() {
  Variable A(0);
  Variable B(1);

  FP_BD_Shape bd1(2);
  bd1.add_constraint(A <= 2);
  bd1.add_constraint(A - B <= 3);
  bd1.add_constraint(B <= 2);
  FP_BD_Shape known_result(bd1);
  FP_Interval tmp(0);
  tmp.join_assign(-1);
  FP_Linear_Form l2(-A);
  FP_Linear_Form l1(A);
  l2 += tmp;

  bd1.refine_with_linear_form_inequality(l1, l2);
  print_constraints(bd1, "*** A <= - A + [-1, 0]  ***");

  known_result.add_constraint(2*A <= 0);
  print_constraints(known_result, "*** known_result ***");

  bool ok1 = (bd1 == known_result);

  bd1.refine_with_linear_form_inequality(l2, l1);
  print_constraints(bd1, "*** - A + [0, 1] <= A  ***");

  known_result.add_constraint(2*(-A) <= 1);
  print_constraints(known_result, "*** known_result ***");

  bool ok2 = (bd1 == known_result);

  return ok1 && ok2;
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
END_MAIN

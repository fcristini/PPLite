/* Testing linearization algorithm ad its related functions.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or moDif_FP_Expressiony it 
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
#include "C_Expr.defs.hh"
#include "linearize_integer.hh"
#include <vector>

namespace {

class Test_Oracle : public Oracle<C_Expr,Intero_Interval> {
public:
  Test_Oracle() : int_store(0) {}
  Test_Oracle(Integer_Interval_Abstract_Store init) : int_store(init) {}
  bool get_interval(dimension_type dim, Intero_Interval& result) const {
    result = int_store.get_interval(Variable(dim));
    return true;
  }
  bool get_fp_constant_value(const Floating_Point_Constant<C_Expr>&,
                             Intero_Interval&) const {
    return false;
  }
  bool get_int_constant_value(const Int_Constant<C_Expr>& expr,
                     Intero_Interval& result) const {
    result = expr.value;
    return true;
  }
  bool get_integer_expr_value(const Concrete_Expression<C_Expr>&,
                              Intero_Interval&) const {
    return false;
  }
  bool get_associated_dimensions(
       const Approximable_Reference<C_Expr>& expr,
       std::set<dimension_type>& result) const {
    result = expr.dimensions;
    return true;
  }
  
  Integer_Interval_Abstract_Store int_store;
};

using namespace Parma_Polyhedra_Library::IO_Operators;

Concrete_Expression_Type Integer_Type =
  Concrete_Expression_Type::bounded_integer(BITS_32, SIGNED_2_COMPLEMENT, 
                     OVERFLOW_IMPOSSIBLE);

typedef Integer_Interval Int_Interval;

/*
  Tests linearization 3*B + [2, 2147483639] op B + [1, 16] 
  with op content {|, & , ^ , << , >> }
*/
bool
test01(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
   
  Intero_Interval a(2147483636);
  a.join_assign(7);
  
  Intero_Interval b(3);
  
  Intero_Interval inh_term(2);
  inh_term.join_assign(3);
  
  Intero_Interval a1(12);
  a1.join_assign(5);
  
  Intero_Interval b1(1);
  b1.join_assign(7);
  
  Intero_Interval inh_term1(1);
  inh_term1.join_assign(4);
  Approximable_Reference<C_Expr> var0(Integer_Type, 
               Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
               Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff_a(Integer_Type, a);
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeff_inh_term(Integer_Type, inh_term);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_b1(Integer_Type, b1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> term_a(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a);
  Binary_Operator<C_Expr> term_b(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum_a_b(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a, &term_b);
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term,&sum_a_b);
  Binary_Operator<C_Expr> term_a1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a1);
  Binary_Operator<C_Expr> sum_a1_b1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a1, &var1);
  Binary_Operator<C_Expr> expr2(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &sum_a1_b1);

  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &expr2);
  Integer_Linear_Form result_or, result_and,result_xor, result_lshift,
               result_rshift;

  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_or = Integer_Linear_Form(tmp);
  known_result_or *= a;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  known_result_or += lb;
  known_result_or += inh_term;
  Integer_Linear_Form known_result = Integer_Linear_Form(tmp);
  known_result *= a1;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  known_result += lb1;
  known_result += inh_term1;
  
  Integer_Linear_Form known_result_and, known_result_xor, known_result_lshift,
                      known_result_rshift;
  known_result_and = known_result_or;
  known_result_xor = known_result_or;
  known_result_lshift = known_result_or;
  known_result_rshift = known_result_or;
  
  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << known_result << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= known_result;
  nout << known_result_or << std::endl;
   
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << known_result << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= known_result;
  nout << known_result_and << std::endl; 

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << known_result << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= known_result;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(),
            result_lshift);
  nout << "*** " << known_result_lshift << " << " << known_result << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << known_result;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
            result_rshift);
  nout << "*** " << known_result_rshift << " >> " << known_result << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> known_result;
  nout << known_result_rshift << std::endl;


  bool ok = (result_or == known_result_or) && 
            (result_and == known_result_and) &&
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
  return ok;

}

/*
  Tests linearization A + 3*B + [2, 3] op B + [1, 9] 
  with op content {|, & , ^ , << , >> }
*/
bool
test02(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  
  Intero_Interval b(3);
  
  Intero_Interval inh_term(2);
  inh_term.join_assign(3);
  
  Intero_Interval a1(3);
  a1.join_assign(5);
  
  Intero_Interval inh_term1(1);
  inh_term1.join_assign(4);
  Approximable_Reference<C_Expr> var0(Integer_Type, 
                                 Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
                                 Int_Interval(mpz_class(0)), 1);
  
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeff_inh_term(Integer_Type, inh_term);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> term_b(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum_a_b(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &var0, &term_b);
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term,&sum_a_b);
  Binary_Operator<C_Expr> term_a1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a1);
  Binary_Operator<C_Expr> sum_a1_b1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a1, &var1);
  Binary_Operator<C_Expr> expr2(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &sum_a1_b1);

  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &expr2);
  Integer_Linear_Form result_and,result_or, result_xor, result_lshift,
                result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_and = Integer_Linear_Form(A);
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  known_result_and += lb;
  known_result_and += inh_term;
  Integer_Linear_Form known_result = Integer_Linear_Form(tmp);
  known_result *= a1;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  known_result += lb1;
  known_result += inh_term1;
  
  Integer_Linear_Form known_result_or, known_result_xor, known_result_lshift, 
                      known_result_rshift;
  known_result_or = known_result_and;
  known_result_xor = known_result_and;
  known_result_lshift = known_result_and;
  known_result_rshift = known_result_and;
  
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << known_result << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= known_result;
  nout << known_result_and << std::endl;

  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << known_result << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= known_result;
  nout << known_result_or << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << known_result << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= known_result;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
            result_lshift);
  nout << "*** " << known_result_lshift << " << " << known_result << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << known_result;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
            result_rshift);
  nout << "*** " << known_result_rshift << " >> " << known_result << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> known_result;
  nout << known_result_rshift << std::endl;

  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) && 
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
  return ok;
}

/*
  Tests linearization -A + -3*B + [-3, -2] op -B + [-4, -1] 
  with op content {|, & , ^ , << , >> }
*/
bool
test03(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  
  Intero_Interval a(-1);  
  Intero_Interval b(-3);
  
  Intero_Interval inh_term(-2);
  inh_term.join_assign(-3);
  
  Intero_Interval a1(-3);
  a1.join_assign(-5);
  Intero_Interval b1(-1);  
  Intero_Interval inh_term1(-1);
  inh_term1.join_assign(-4);
  Approximable_Reference<C_Expr> var0(Integer_Type, 
               Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
               Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff_a(Integer_Type, a);  
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeff_inh_term(Integer_Type, inh_term);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_b1(Integer_Type, b1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> term_a(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a);
  Binary_Operator<C_Expr> term_b(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum_a_b(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a, &term_b);
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term,&sum_a_b);
  Binary_Operator<C_Expr> term_b1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b1);
  Binary_Operator<C_Expr> expr2(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &term_b1);

  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &expr2);
  Integer_Linear_Form result_and, result_or, result_xor, result_lshift,
               result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_and = Integer_Linear_Form(A);
  known_result_and *= a;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  known_result_and += lb;
  known_result_and += inh_term;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  lb1 *= b1;
  lb1 += inh_term1;
  
  Integer_Linear_Form known_result_or, known_result_xor, known_result_lshift, 
                      known_result_rshift;
  known_result_or = known_result_and;
  known_result_xor = known_result_and;
  known_result_lshift = known_result_and;
  known_result_rshift = known_result_and;
  
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << lb1 << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= lb1;
  nout << known_result_and << std::endl;

  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << lb1 << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= lb1;
  nout << known_result_or << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << lb1 << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= lb1;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_lshift);
  nout << "*** " << known_result_lshift << " << " << lb1 << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << lb1;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_rshift);
  nout << "*** " << known_result_rshift << " >> " << lb1 << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> lb1;
  nout << known_result_rshift << std::endl;

  
  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) &&
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
  return ok;
}

/*
  Tests linearization -A + -3*B + [-3, -2] op B + [1, 4] 
  with op content {|, & , ^ , << , >> }
*/
bool
test04(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  
  Intero_Interval a(-1);  
  Intero_Interval b(-3);
  
  Intero_Interval inh_term(-2);
  inh_term.join_assign(-3);
  
  Intero_Interval a1(-3);
  a1.join_assign(-5);
  Intero_Interval b1(1);  
  Intero_Interval inh_term1(1);
  inh_term1.join_assign(4);
  Approximable_Reference<C_Expr> var0(Integer_Type, 
              Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
              Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff_a(Integer_Type, a);  
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeff_inh_term(Integer_Type, inh_term);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_b1(Integer_Type, b1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> term_a(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a);
  Binary_Operator<C_Expr> term_b(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum_a_b(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a, &term_b);
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term,&sum_a_b);
  Binary_Operator<C_Expr> term_b1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b1);
  Binary_Operator<C_Expr> expr2(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &term_b1);

  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &expr2);
  Integer_Linear_Form result_and ,result_or, result_xor, result_lshift, 
                result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_and = Integer_Linear_Form(A);
  known_result_and *= a;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  known_result_and += lb;
  known_result_and += inh_term;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  lb1 *= b1;
  lb1 += inh_term1;
  
  Integer_Linear_Form known_result_or, known_result_xor, known_result_lshift, 
                      known_result_rshift;
  known_result_or = known_result_and;
  known_result_xor = known_result_and;
  known_result_lshift = known_result_and;
  known_result_rshift = known_result_and;
  
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << lb1 << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= lb1;
  nout << known_result_and << std::endl;

  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << lb1 << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= lb1;
  nout << known_result_or << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << lb1 << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= lb1;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_lshift);
  nout << "*** " << known_result_lshift << " << " << lb1 << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << lb1;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_rshift);
  nout << "*** " << known_result_rshift << " >> " << lb1 << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> lb1;
  nout << known_result_rshift << std::endl;

  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) && 
            (result_xor == known_result_xor) && 
            (result_lshift== known_result_lshift) &&
            (result_rshift == known_result_rshift);
  return ok;
}

/*
  Tests linearization A + 3*B + [2, 3] op -B + [-4, -1] 
  with op content {|, & , ^ , << , >> }
*/
bool
test05(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  
  Intero_Interval a(1);  
  Intero_Interval b(3);
  
  Intero_Interval inh_term(2);
  inh_term.join_assign(3);
  
  Intero_Interval a1(-3);
  a1.join_assign(-5);
  Intero_Interval b1(-1);  
  Intero_Interval inh_term1(-1);
  inh_term1.join_assign(-4);

  Approximable_Reference<C_Expr> var0(Integer_Type, 
              Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
              Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff_a(Integer_Type, a);  
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeff_inh_term(Integer_Type, inh_term);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_b1(Integer_Type, b1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> term_a(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a);
  Binary_Operator<C_Expr> term_b(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum_a_b(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a, &term_b);
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term,&sum_a_b);
  Binary_Operator<C_Expr> term_b1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b1);
  Binary_Operator<C_Expr> expr2(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &term_b1);

  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &expr2);
  Integer_Linear_Form result_and, result_or, result_xor, result_lshift, 
                result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_and = Integer_Linear_Form(A);
  known_result_and *= a;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  known_result_and += lb;
  known_result_and += inh_term;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  lb1 *= b1;
  lb1 += inh_term1;
  
  Integer_Linear_Form  known_result_or, known_result_xor, known_result_lshift,
                       known_result_rshift;
  known_result_or = known_result_and;
  known_result_xor = known_result_and;
  known_result_lshift = known_result_and;
  known_result_rshift = known_result_and;
  
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << lb1 << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= lb1;
  nout << known_result_and << std::endl;


  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << lb1 << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= lb1;
  nout << known_result_or << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << lb1 << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= lb1;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
           result_lshift);
  nout << "*** " << known_result_lshift << " << " << lb1 << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << lb1;
  nout << known_result_lshift << std::endl;
  
  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_rshift);
  nout << "*** " << known_result_rshift << " >> " << lb1 << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> lb1;
  nout << known_result_rshift << std::endl;

  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) && 
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
  return ok;
}


/*
  Tests linearization A op A with op content {|, & , ^ , << , >> }
*/
bool
test06(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(1));
  oracle.int_store.set_interval(Variable(0), tmp);
  
  Approximable_Reference<C_Expr> var0(Integer_Type, 
              Int_Interval(mpz_class(0)), 0);

  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &var0, &var0);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &var0, &var0);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &var0, &var0);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &var0, &var0);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &var0, &var0);
  Integer_Linear_Form result_and, result_or, result_xor, result_lshift, 
               result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_and = Integer_Linear_Form(A);
  
  Integer_Linear_Form known_result = known_result_and;
  
  Integer_Linear_Form known_result_or, known_result_xor, known_result_lshift, 
                      known_result_rshift;
  known_result_or = known_result;
  known_result_xor = known_result;
  known_result_lshift = known_result;
  known_result_rshift = known_result;
  
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << known_result << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= known_result;
  nout << known_result_and << std::endl;

  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << known_result << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= known_result;
  nout << known_result_or << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << known_result << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= known_result;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
            result_lshift);
  nout << "*** " << known_result_lshift << " << " << known_result << " ***" << std::endl
         << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << known_result;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
            result_rshift);
  nout << "*** " << known_result_rshift << " >> " << known_result << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> known_result;
  nout << known_result_rshift << std::endl;
 
  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) && 
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
 
  return ok;
}

/*
  Tests linearization A + 3 op B with op content {|, & , ^ , << , >> }
*/
bool 
test07(){
  Intero_Interval tmp(1);
  Intero_Interval tmp1(5);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  Approximable_Reference<C_Expr> var0(Integer_Type, 
              Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
              Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff(Integer_Type, Intero_Interval(3));
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &var0, &coeff);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &var1);
  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &var1);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &var1);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &var1);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &var1);
  Integer_Linear_Form result_and, result_or, result_xor, result_lshift, 
               result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_or = Integer_Linear_Form(A);
  known_result_or += Intero_Interval(3);
  Integer_Linear_Form known_result_and = known_result_or;
  Integer_Linear_Form known_result_xor = known_result_or;
  Integer_Linear_Form known_result_lshift = known_result_or;
  Integer_Linear_Form known_result_rshift = known_result_or;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  
  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << lb << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= lb;
  nout << known_result_or << std::endl;
  
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << lb << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= lb;
  nout << known_result_and << std::endl;


  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << lb << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= lb;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
            result_lshift);
  nout << "*** " << known_result_lshift << " << " << lb << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << lb;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
            result_rshift);
  nout << "*** " << known_result_rshift << " >> " << lb << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> lb;
  nout << known_result_rshift << std::endl;

  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) && 
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
  
  return ok;
}

/*
  Tests linearization -3*B + [-2147483641, -2] op -B + [-9, -1] 
  with op content {|, & , ^ , << , >> }
*/
bool
test08(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  
  Intero_Interval a(-2147483638);
  a.join_assign(-7);
  
  Intero_Interval b(-3);
  
  Intero_Interval inh_term(-2);
  inh_term.join_assign(-3);
  
  Intero_Interval a1(-3);
  a1.join_assign(-5);
  
  Intero_Interval b1(-1);
  
  Intero_Interval inh_term1(-1);
  inh_term1.join_assign(-4);
  
  Approximable_Reference<C_Expr> var0(Integer_Type, 
              Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
              Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff_a(Integer_Type, a);
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeff_inh_term(Integer_Type, inh_term);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_b1(Integer_Type, b1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> term_a(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a);
  Binary_Operator<C_Expr> term_b(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum_a_b(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a, &term_b);
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term,&sum_a_b);
  Binary_Operator<C_Expr> term_a1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a1);
  Binary_Operator<C_Expr> term_b1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b1);
  Binary_Operator<C_Expr> sum_a1_b1(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a1, &term_b1);
  Binary_Operator<C_Expr> expr2(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &sum_a1_b1);

  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &expr2);
  Integer_Linear_Form result_or, result_and, result_xor, result_lshift, 
                result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_or = Integer_Linear_Form(tmp);
  known_result_or *= a;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  known_result_or += lb;
  known_result_or += inh_term;
  
  Integer_Linear_Form known_result = Integer_Linear_Form(tmp);
  known_result *= a1;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  lb1 *= b1;
  known_result += lb1;
  known_result += inh_term1;
  Integer_Linear_Form known_result_and, known_result_xor, known_result_lshift,
                      known_result_rshift;
  known_result_and = known_result_or;
  known_result_xor = known_result_or;
  known_result_lshift = known_result_or;
  known_result_rshift = known_result_or;
  
  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << known_result << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= known_result;
  nout << known_result_or << std::endl;

  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << known_result << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= known_result;
  nout << known_result_and << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << known_result << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= known_result;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
           result_lshift);
  nout << "*** " << known_result_lshift << " << " << known_result << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << known_result;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
           result_rshift);
  nout << "*** " << known_result_rshift << " >> " << known_result << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> known_result;
  nout << known_result_rshift << std::endl;

  bool ok = (result_or == known_result_or) && 
            (result_and == known_result_and) && 
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
  return ok;
}

/*
  Tests linearization A + 12*B + [2, 3] op -2147483638*B + [-4, -1] 
  with op content {|, & , ^ , << , >> }
*/
bool
test09(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  
  Intero_Interval a(1);  
  Intero_Interval b(12);
  
  Intero_Interval num(-4);
  num.join_assign(-6);
  
  Intero_Interval den(2);
  
  Intero_Interval a1(-3);
  a1.join_assign(-2147483638);
  Intero_Interval b1(-2147483638);  
  Intero_Interval inh_term1(-1);
  inh_term1.join_assign(-4);
  Approximable_Reference<C_Expr> var0(Integer_Type, 
              Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
               Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff_a(Integer_Type, a);  
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeffnum(Integer_Type, num);
  Int_Constant<C_Expr> coeffden(Integer_Type, den);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_b1(Integer_Type, b1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> term_a(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a);
  Binary_Operator<C_Expr> term_b(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum_a_b(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &term_a, &term_b);
  Binary_Operator<C_Expr> div(Integer_Type, Binary_Operator<C_Expr>::DIV,
                              &coeffnum, &coeffden);
  Binary_Operator<C_Expr> expr1(Integer_Type, Binary_Operator<C_Expr>::SUB,
                              &sum_a_b,&div);
  Binary_Operator<C_Expr> term_b1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b1);
  Binary_Operator<C_Expr> expr2(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &term_b1);

  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &expr1, &expr2);
  
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &expr1, &expr2);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &expr1, &expr2);
  Integer_Linear_Form result_and, result_or, result_xor, result_lshift, 
                result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_and = Integer_Linear_Form(A);
  known_result_and *= a;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  num /= den;
  known_result_and += lb;
  known_result_and -= num;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  lb1 *= b1;
  lb1 += inh_term1;
  
  Integer_Linear_Form known_result_or, known_result_xor, known_result_lshift, 
                      known_result_rshift;
  known_result_or = known_result_and;
  known_result_xor = known_result_and;
  known_result_lshift = known_result_and;
  known_result_rshift = known_result_and;
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << lb1 << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= lb1;
  nout << known_result_and << std::endl;


  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << lb1 << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= lb1;
  nout << known_result_or << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor);
  nout << "*** " << known_result_xor << " ^ " << lb1 << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= lb1;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_lshift);
  nout << "*** " << known_result_lshift << " << " << lb1 << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << lb1;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_rshift);
  nout << "*** " << known_result_rshift << " >> " << lb1 << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> lb1;
  nout << known_result_rshift << std::endl;

  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) && 
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
  return ok;
}


/* 
  Tests linearization -A + -12*B + [-3, -2] op 2147483638*B + [1, 4] 
  with op content {|, & , ^ , << , >> }
*/
bool
test10(){
  Intero_Interval tmp(0);
  tmp.join_assign(1);
  Intero_Interval tmp1(2);
  tmp1.join_assign(3);
  Test_Oracle oracle(Integer_Interval_Abstract_Store(2));
  oracle.int_store.set_interval(Variable(0), tmp);
  oracle.int_store.set_interval(Variable(1), tmp1);
  
  Intero_Interval a(-1);  
  Intero_Interval b(-12);
  
  Intero_Interval num(4);
  num.join_assign(6);
  
  Intero_Interval den(2);
  
  Intero_Interval a1(3);
  a1.join_assign(2147483638);
  Intero_Interval b1(2147483638);  
  Intero_Interval inh_term1(1);
  inh_term1.join_assign(4);
  Approximable_Reference<C_Expr> var0(Integer_Type, 
              Int_Interval(mpz_class(0)), 0);
  Approximable_Reference<C_Expr> var1(Integer_Type, 
              Int_Interval(mpz_class(0)), 1);
  Int_Constant<C_Expr> coeff_a(Integer_Type, a);  
  Int_Constant<C_Expr> coeff_b(Integer_Type, b);
  Int_Constant<C_Expr> coeffnum(Integer_Type, num);
  Int_Constant<C_Expr> coeffden(Integer_Type, den);
  Int_Constant<C_Expr> coeff_a1(Integer_Type, a1);
  Int_Constant<C_Expr> coeff_b1(Integer_Type, b1);
  Int_Constant<C_Expr> coeff_inh_term1(Integer_Type, inh_term1);
  Binary_Operator<C_Expr> mul1(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var0, &coeff_a);
  Binary_Operator<C_Expr> mul2(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b);
  Binary_Operator<C_Expr> sum3(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &mul1, &mul2);
  Binary_Operator<C_Expr> div(Integer_Type, Binary_Operator<C_Expr>::DIV,
                              &coeffnum, &coeffden);
  Binary_Operator<C_Expr> sub4(Integer_Type, Binary_Operator<C_Expr>::SUB,
                              &sum3,&div);
  Binary_Operator<C_Expr> mul6(Integer_Type, Binary_Operator<C_Expr>::MUL,
                              &var1, &coeff_b1);
  Binary_Operator<C_Expr> sum8(Integer_Type, Binary_Operator<C_Expr>::ADD,
                              &coeff_inh_term1, &mul6);

  Binary_Operator<C_Expr> band(Integer_Type, Binary_Operator<C_Expr>::BAND,
                              &sub4, &sum8);
  Binary_Operator<C_Expr> bor(Integer_Type, Binary_Operator<C_Expr>::BOR,
                              &sub4, &sum8);
  
  Binary_Operator<C_Expr> bxor(Integer_Type, Binary_Operator<C_Expr>::BXOR,
                              &sub4, &sum8);
  Binary_Operator<C_Expr> lshift(Integer_Type, Binary_Operator<C_Expr>::LSHIFT,
                              &sub4, &sum8);
  Binary_Operator<C_Expr> rshift(Integer_Type, Binary_Operator<C_Expr>::RSHIFT,
                              &sub4, &sum8);
  Integer_Linear_Form result_and, result_or, result_xor, result_lshift, 
                result_rshift;
  Variable A(0);
  Variable B(1);
  Integer_Linear_Form known_result_and = Integer_Linear_Form(A);
  known_result_and *= a;
  Integer_Linear_Form lb = Integer_Linear_Form(B);
  lb *= b;
  num /= den;
  known_result_and += lb;
  known_result_and -= num;
  Integer_Linear_Form lb1 = Integer_Linear_Form(B);
  lb1 *= b1;
  lb1 += inh_term1;
  
  Integer_Linear_Form known_result_or, known_result_xor, known_result_lshift,
                      known_result_rshift;
  known_result_or = known_result_and;
  known_result_xor = known_result_and;
  known_result_lshift = known_result_and;
  known_result_rshift = known_result_and;
  linearize_int(band, oracle, Integer_Linear_Form_Abstract_Store(), result_and);
  nout << "*** " << known_result_and << " & " << lb1 << " ***" << std::endl
       << "*** known_result_and ***" << std::endl;
  known_result_and &= lb1;
  nout << known_result_and << std::endl;

  linearize_int(bor, oracle, Integer_Linear_Form_Abstract_Store(), result_or);
  nout << "*** " << known_result_or << " | " << lb1 << " ***" << std::endl
       << "*** known_result_or ***" << std::endl;
  known_result_or |= lb1;
  nout << known_result_or << std::endl;

  linearize_int(bxor, oracle, Integer_Linear_Form_Abstract_Store(), result_xor); 
  nout << "*** " << known_result_xor << " ^ " << lb1 << " ***" << std::endl
       << "*** known_result_xor ***" << std::endl;
  known_result_xor ^= lb1;
  nout << known_result_xor << std::endl;

  linearize_int(lshift, oracle, Integer_Linear_Form_Abstract_Store(), 
           result_lshift);
  nout << "*** " << known_result_lshift << " << " << lb1 << " ***" << std::endl
       << "*** known_result_lshift ***" << std::endl;
  known_result_lshift << lb1;
  nout << known_result_lshift << std::endl;

  linearize_int(rshift, oracle, Integer_Linear_Form_Abstract_Store(), 
               result_rshift);
  nout << "*** " << known_result_rshift << " >> " << lb1 << " ***" << std::endl
       << "*** known_result_rshift ***" << std::endl;
  known_result_rshift >> lb1;
  nout << known_result_rshift << std::endl;

  
  bool ok = (result_and == known_result_and) && 
            (result_or == known_result_or) &&
            (result_xor == known_result_xor) && 
            (result_lshift == known_result_lshift) && 
            (result_rshift == known_result_rshift);
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

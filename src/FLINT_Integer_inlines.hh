/* FLINT_Integer class implementation: inline functions.
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2016 BUGSENG srl (http://bugseng.com)

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

#ifndef PPL_FLINT_Integer_inlines_hh
#define PPL_FLINT_Integer_inlines_hh 1

#include "assertions.hh"

namespace Parma_Polyhedra_Library {

inline void
neg_assign(FLINT_Integer& x) {
  fmpz_neg(x.get_fmpz_t(), x.get_fmpz_t());
}

inline void
neg_assign(FLINT_Integer& x, const FLINT_Integer& y) {
  fmpz_neg(x.get_fmpz_t(), y.get_fmpz_t());
}

inline void
abs_assign(FLINT_Integer& x) {
  fmpz_abs(x.get_fmpz_t(), x.get_fmpz_t());
}

inline void
abs_assign(FLINT_Integer& x, const FLINT_Integer& y) {
  fmpz_abs(x.get_fmpz_t(), y.get_fmpz_t());
}

inline void
gcd_assign(FLINT_Integer& x, const FLINT_Integer& y, const FLINT_Integer& z) {
  fmpz_gcd(x.get_fmpz_t(), y.get_fmpz_t(), z.get_fmpz_t());
}

inline void
rem_assign(FLINT_Integer& x, const FLINT_Integer& y, const FLINT_Integer& z) {
  fmpz_tdiv_q(x.get_fmpz_t(), y.get_fmpz_t(), z.get_fmpz_t());
}

inline void
gcdext_assign(FLINT_Integer& x, FLINT_Integer& s, FLINT_Integer& t,
              const FLINT_Integer& y, const FLINT_Integer& z) {
  fmpz_xgcd (x.get_fmpz_t(),
             s.get_fmpz_t(), t.get_fmpz_t(),
             y.get_fmpz_t(), z.get_fmpz_t());
}

inline void
lcm_assign(FLINT_Integer& x, const FLINT_Integer& y, const FLINT_Integer& z) {
  fmpz_lcm(x.get_fmpz_t(), y.get_fmpz_t(), z.get_fmpz_t());
}

inline void
add_mul_assign(FLINT_Integer& x, const FLINT_Integer& y, const FLINT_Integer& z) {
  fmpz_addmul(x.get_fmpz_t(), y.get_fmpz_t(), z.get_fmpz_t());
}

inline void
sub_mul_assign(FLINT_Integer& x, const FLINT_Integer& y, const FLINT_Integer& z) {
  fmpz_submul(x.get_fmpz_t(), y.get_fmpz_t(), z.get_fmpz_t());
}

inline void
mul_2exp_assign(FLINT_Integer& x, const FLINT_Integer& y, const unsigned int exp) {
  fmpz_mul_2exp(x.get_fmpz_t(), y.get_fmpz_t(), exp);
}

inline void
div_2exp_assign(FLINT_Integer& x, const FLINT_Integer& y, const unsigned int exp) {
  fmpz_tdiv_q_2exp(x.get_fmpz_t(), y.get_fmpz_t(), exp);
}

inline void
exact_div_assign(FLINT_Integer& x, const FLINT_Integer& y, const FLINT_Integer& z) {
  PPL_ASSERT(y % z == 0);
  fmpz_divexact(x.get_fmpz_t(), y.get_fmpz_t(), z.get_fmpz_t());
}

inline void
sqrt_assign(FLINT_Integer& x, const FLINT_Integer& y) {
  fmpz_sqrt(x.get_fmpz_t(), y.get_fmpz_t());
}

inline int
cmp(const FLINT_Integer& x, const FLINT_Integer& y) {
  return fmpz_cmp(x.get_fmpz_t(), y.get_fmpz_t());
}

inline const fmpz_class&
raw_value(const FLINT_Integer& x) {
  return x;
}

inline fmpz_class&
raw_value(FLINT_Integer& x) {
  return x;
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_FLINT_Integer_inlines_hh)

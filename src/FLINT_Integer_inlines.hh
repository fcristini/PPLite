/* GMP_Integer class implementation: inline functions.
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
neg_assign(flint_mpz_class& x) {
  x = -x;
}

inline void
neg_assign(flint_mpz_class& x, const flint_mpz_class& y) {
  x = -y;
}

inline void
abs_assign(flint_mpz_class& x) {
  x = x.getAbs();
}

inline void
abs_assign(flint_mpz_class& x, const flint_mpz_class& y) {
  x = y.getAbs();
}

inline void
gcd_assign(flint_mpz_class& x, const flint_mpz_class& y, const flint_mpz_class& z) {
  x = x.getGCD(y, z);
}

inline void
rem_assign(flint_mpz_class& x, const flint_mpz_class& y, const flint_mpz_class& z) {
  fmpz_fdiv_r(x.mp, y.mp, z.mp);
}

inline void
gcdext_assign(flint_mpz_class& x, flint_mpz_class& s, flint_mpz_class& t,
              const flint_mpz_class& y, const flint_mpz_class& z) {
  fmpz_xgcd(x.mp,
            s.mp, t.mp,
            y.mp, z.mp);
}

inline void
lcm_assign(flint_mpz_class& x, const flint_mpz_class& y, const flint_mpz_class& z) {
  x = x.getLCM(y, z);
}

inline void
add_mul_assign(flint_mpz_class& x, const flint_mpz_class& y, const flint_mpz_class& z) {
  fmpz_addmul(x.mp, y.mp, z.mp);
}

inline void
sub_mul_assign(flint_mpz_class& x, const flint_mpz_class& y, const flint_mpz_class& z) {
  fmpz_submul(x.mp, y.mp, z.mp);
}

inline void
mul_2exp_assign(flint_mpz_class& x, const flint_mpz_class& y, const unsigned int exp) {
  fmpz_mul_2exp(x.mp, y.mp, exp);
}

inline void
div_2exp_assign(flint_mpz_class& x, const flint_mpz_class& y, const unsigned int exp) {
  fmpz_tdiv_q_2exp(x.mp, y.mp, exp);
}

inline void
exact_div_assign(flint_mpz_class& x, const flint_mpz_class& y, const flint_mpz_class& z) {
  PPL_ASSERT(y % z == 0);
  fmpz_divexact(x.mp, y.mp, z.mp);
  ///x = y / z;
}

//////inline void
//////sqrt_assign(GMP_Integer& x, const GMP_Integer& y) {
//////  mpz_sqrt(x.get_mpz_t(), y.get_mpz_t());
//////}

inline int
cmp(const flint_mpz_class& x, const flint_mpz_class& y) {
  return fmpz_cmp(x.mp, y.mp);
}

//////inline const mpz_class&
//////raw_value(const GMP_Integer& x) {
//////  return x;
//////}
//////
//////inline mpz_class&
//////raw_value(GMP_Integer& x) {
//////  return x;
//////}

inline int sgn(const flint_mpz_class& x) {
  return fmpz_sgn(x.mp);
  ///return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

inline void swap(flint_mpz_class & x, flint_mpz_class & y) {
  fmpz_swap(x.mp, y.mp);
}


} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_GMP_Integer_inlines_hh)

/* GMP_Integer class declaration.
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

#ifndef PPL_GMP_Integer_defs_hh
#define PPL_GMP_Integer_defs_hh 1

#include "globals_types.hh"
#include <cstddef>

namespace Parma_Polyhedra_Library {

//! \name Accessor Functions
//@{

//! Returns a const reference to the underlying integer value.
/*! \relates GMP_Integer */
///const mpz_class& raw_value(const GMP_Integer& x);

//! Returns a reference to the underlying integer value.
/*! \relates GMP_Integer */
////mpz_class& raw_value(GMP_Integer& x);

//@} // Accessor Functions

//! \name Arithmetic Operators
//@{

//! Assigns to \p x its negation.
/*! \relates flint_mpz_class */
void neg_assign(flint_mpz_class& x);

//! Assigns to \p x the negation of \p y.
/*! \relates flint_mpz_class */
void neg_assign(flint_mpz_class& x, const flint_mpz_class& y);

//! Assigns to \p x its absolute value.
/*! \relates flint_mpz_class */
void abs_assign(flint_mpz_class& x);

//! Assigns to \p x the absolute value of \p y.
/*! \relates flint_mpz_class */
void abs_assign(flint_mpz_class& x, const flint_mpz_class& y);

//! Assigns to \p x the remainder of the division of \p y by \p z.
/*! \relates flint_mpz_class */
void rem_assign(flint_mpz_class& x,
                const flint_mpz_class& y, const flint_mpz_class& z);

//! Assigns to \p x the greatest common divisor of \p y and \p z.
/*! \relates flint_mpz_class */
void gcd_assign(flint_mpz_class& x,
                const flint_mpz_class& y, const flint_mpz_class& z);

//! Extended GCD.
/*! \relates flint_mpz_class
  Assigns to \p x the greatest common divisor of \p y and \p z, and to
  \p s and \p t the values such that \p y * \p s + \p z * \p t = \p x.
*/
void gcdext_assign(flint_mpz_class& x, flint_mpz_class& s, flint_mpz_class& t,
                   const flint_mpz_class& y, const flint_mpz_class& z);

//! Assigns to \p x the least common multiple of \p y and \p z.
/*! \relates flint_mpz_class */
void lcm_assign(flint_mpz_class& x,
                const flint_mpz_class& y, const flint_mpz_class& z);

//! Assigns to \p x the value <CODE>x + y * z</CODE>.
/*! \relates flint_mpz_class */
void add_mul_assign(flint_mpz_class& x,
                    const flint_mpz_class& y, const flint_mpz_class& z);

//! Assigns to \p x the value <CODE>x - y * z</CODE>.
/*! \relates flint_mpz_class */
void sub_mul_assign(flint_mpz_class& x,
                    const flint_mpz_class& y, const flint_mpz_class& z);

//! Assigns to \p x the value \f$ y \cdot 2^\mathtt{exp} \f$.
/*! \relates flint_mpz_class */
void mul_2exp_assign(flint_mpz_class& x, const flint_mpz_class& y, unsigned int exp);

//! Assigns to \p x the value \f$ y / 2^\mathtt{exp} \f$.
/*! \relates flint_mpz_class */
void div_2exp_assign(flint_mpz_class& x, const flint_mpz_class& y, unsigned int exp);

/*! \brief
  If \p z divides \p y, assigns to \p x the quotient of the integer
  division of \p y and \p z.

  \relates flint_mpz_class
  The behavior is undefined if \p z does not divide \p y.
*/
void exact_div_assign(flint_mpz_class& x,
                      const flint_mpz_class& y, const flint_mpz_class& z);

//! Assigns to \p x the integer square root of \p y.
/*! \relates GMP_Integer */
///void sqrt_assign(GMP_Integer& x, const GMP_Integer& y);

/*! \brief
  Returns a negative, zero or positive value depending on whether
  \p x is lower than, equal to or greater than \p y, respectively.

  \relates flint_mpz_class
*/
int cmp(const flint_mpz_class& x, const flint_mpz_class& y);

/*! \brief
  Returns a negative, zero or positive value depending on whether
  \p x is lower than, equal to or greater than 0, respectively.

  \relates flint_mpz_class
*/
int sgn(const flint_mpz_class& x);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Swaps \p x with \p y.
/*! \relates flint_mpz_class */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
void swap(flint_mpz_class & x, flint_mpz_class & y);

//@} // Arithmetic Operators

} // namespace Parma_Polyhedra_Library

#ifndef FABIO_NO_INLINES
#include "FLINT_Integer_inlines.hh"
#endif

#endif // !defined(PPL_GMP_Integer_defs_hh)

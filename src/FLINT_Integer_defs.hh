/* FLINT_Integer class declaration.
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

#ifndef PPL_FLINT_Integer_defs_hh
#define PPL_FLINT_Integer_defs_hh 1

#include "FLINT_Integer_types.hh"
#include "globals_types.hh"
#include <cstddef>

namespace Parma_Polyhedra_Library {

//! \name Accessor Functions
//@{

//! Returns a const reference to the underlying integer value.
/*! \relates FLINT_Integer */
const mpz_class& raw_value(const FLINT_Integer& x);

//! Returns a reference to the underlying integer value.
/*! \relates FLINT_Integer */
mpz_class& raw_value(FLINT_Integer& x);

//@} // Accessor Functions

//! \name Arithmetic Operators
//@{

//! Assigns to \p x its negation.
/*! \relates FLINT_Integer */
void neg_assign(FLINT_Integer& x);

//! Assigns to \p x the negation of \p y.
/*! \relates FLINT_Integer */
void neg_assign(FLINT_Integer& x, const FLINT_Integer& y);

//! Assigns to \p x its absolute value.
/*! \relates FLINT_Integer */
void abs_assign(FLINT_Integer& x);

//! Assigns to \p x the absolute value of \p y.
/*! \relates FLINT_Integer */
void abs_assign(FLINT_Integer& x, const FLINT_Integer& y);

//! Assigns to \p x the remainder of the division of \p y by \p z.
/*! \relates FLINT_Integer */
void rem_assign(FLINT_Integer& x,
                const FLINT_Integer& y, const FLINT_Integer& z);

//! Assigns to \p x the greatest common divisor of \p y and \p z.
/*! \relates FLINT_Integer */
void gcd_assign(FLINT_Integer& x,
                const FLINT_Integer& y, const FLINT_Integer& z);

//! Extended GCD.
/*! \relates FLINT_Integer
  Assigns to \p x the greatest common divisor of \p y and \p z, and to
  \p s and \p t the values such that \p y * \p s + \p z * \p t = \p x.
*/
void gcdext_assign(FLINT_Integer& x, FLINT_Integer& s, FLINT_Integer& t,
                   const FLINT_Integer& y, const FLINT_Integer& z);

//! Assigns to \p x the least common multiple of \p y and \p z.
/*! \relates FLINT_Integer */
void lcm_assign(FLINT_Integer& x,
                const FLINT_Integer& y, const FLINT_Integer& z);

//! Assigns to \p x the value <CODE>x + y * z</CODE>.
/*! \relates FLINT_Integer */
void add_mul_assign(FLINT_Integer& x,
                    const FLINT_Integer& y, const FLINT_Integer& z);

//! Assigns to \p x the value <CODE>x - y * z</CODE>.
/*! \relates FLINT_Integer */
void sub_mul_assign(FLINT_Integer& x,
                    const FLINT_Integer& y, const FLINT_Integer& z);

//! Assigns to \p x the value \f$ y \cdot 2^\mathtt{exp} \f$.
/*! \relates FLINT_Integer */
void mul_2exp_assign(FLINT_Integer& x, const FLINT_Integer& y, unsigned int exp);

//! Assigns to \p x the value \f$ y / 2^\mathtt{exp} \f$.
/*! \relates FLINT_Integer */
void div_2exp_assign(FLINT_Integer& x, const FLINT_Integer& y, unsigned int exp);

/*! \brief
  If \p z divides \p y, assigns to \p x the quotient of the integer
  division of \p y and \p z.

  \relates FLINT_Integer
  The behavior is undefined if \p z does not divide \p y.
*/
void exact_div_assign(FLINT_Integer& x,
                      const FLINT_Integer& y, const FLINT_Integer& z);

//! Assigns to \p x the integer square root of \p y.
/*! \relates FLINT_Integer */
void sqrt_assign(FLINT_Integer& x, const FLINT_Integer& y);

/*! \brief
  Returns a negative, zero or positive value depending on whether
  \p x is lower than, equal to or greater than \p y, respectively.

  \relates FLINT_Integer
*/
int cmp(const FLINT_Integer& x, const FLINT_Integer& y);

//@} // Arithmetic Operators

} // namespace Parma_Polyhedra_Library

#include "FLINT_Integer_inlines.hh"

#endif // !defined(PPL_FLINT_Integer_defs_hh)

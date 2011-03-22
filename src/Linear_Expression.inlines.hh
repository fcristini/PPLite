/* Linear_Expression class implementation: inline functions.
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
site: http://www.cs.unipr.it/ppl/ . */

#ifndef PPL_Linear_Expression_inlines_hh
#define PPL_Linear_Expression_inlines_hh 1

#include "Variable.defs.hh"
#include "Coefficient.defs.hh"
#include <stdexcept>

namespace Parma_Polyhedra_Library {

inline dimension_type
Linear_Expression::max_space_dimension() {
  return Linear_Row::max_space_dimension();
}

inline
Linear_Expression::Linear_Expression()
  : row(1, Linear_Row::Flags()) {
}

inline
Linear_Expression::Linear_Expression(dimension_type sz, bool)
  : row(sz, Linear_Row::Flags()) {
}

inline
Linear_Expression::Linear_Expression(const Linear_Expression& e)
  : row(e.row) {
}

inline
Linear_Expression::~Linear_Expression() {
}

inline
Linear_Expression::Linear_Expression(const Linear_Expression& e,
				     dimension_type sz)
  : row(e.row, sz, sz) {
}

inline
Linear_Expression::Linear_Expression(Coefficient_traits::const_reference n)
  : row(1, Linear_Row::Flags()) {
  row[0] = n;
}

inline Linear_Row&
Linear_Expression::get_row() {
  return row;
}

inline const Linear_Row&
Linear_Expression::get_row() const {
  return row;
}

inline dimension_type
Linear_Expression::space_dimension() const {
  return row.size() - 1;
}

inline void
Linear_Expression::set_space_dimension(dimension_type n) {
  row.resize(n + 1);
}

inline Coefficient_traits::const_reference
Linear_Expression::coefficient(Variable v) const {
  if (v.space_dimension() > space_dimension())
    return Coefficient_zero();
  return row.coefficient(v.id());
}

inline Coefficient_traits::const_reference
Linear_Expression::inhomogeneous_term() const {
  return row.inhomogeneous_term();
}

inline bool
Linear_Expression::is_zero() const {
  return row.is_zero();
}

inline bool
Linear_Expression::all_homogeneous_terms_are_zero() const {
  return row.all_homogeneous_terms_are_zero();
}

inline const Linear_Expression&
Linear_Expression::zero() {
  PPL_ASSERT(zero_p != 0);
  return *zero_p;
}

inline memory_size_type
Linear_Expression::external_memory_in_bytes() const {
  return row.external_memory_in_bytes();
}

inline memory_size_type
Linear_Expression::total_memory_in_bytes() const {
  return external_memory_in_bytes() + sizeof(*this);
}

/*! \relates Linear_Expression */
inline Linear_Expression
operator+(const Linear_Expression& e) {
  return e;
}

/*! \relates Linear_Expression */
inline Linear_Expression
operator+(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  return n + e;
}

/*! \relates Linear_Expression */
inline Linear_Expression
operator+(const Linear_Expression& e, const Variable v) {
  return v + e;
}

/*! \relates Linear_Expression */
inline Linear_Expression
operator-(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  return -n + e;
}

/*! \relates Linear_Expression */
inline Linear_Expression
operator-(const Variable v, const Variable w) {
  return Linear_Expression(v, w);
}

/*! \relates Linear_Expression */
inline Linear_Expression
operator*(const Linear_Expression& e, Coefficient_traits::const_reference n) {
  return n * e;
}

/*! \relates Linear_Expression */
inline Linear_Expression&
operator+=(Linear_Expression& e, Coefficient_traits::const_reference n) {
  e.row[0] += n;
  return e;
}

/*! \relates Linear_Expression */
inline Linear_Expression&
operator-=(Linear_Expression& e, Coefficient_traits::const_reference n) {
  e.row[0] -= n;
  return e;
}

inline void
Linear_Expression::swap(Linear_Expression& y) {
  row.swap(y.row);
}

inline void
Linear_Expression::ascii_dump(std::ostream& s) const {
  row.ascii_dump(s);
}

inline bool
Linear_Expression::ascii_load(std::istream& s) {
  return row.ascii_load(s);
}

} // namespace Parma_Polyhedra_Library


namespace std {

/*! \relates Parma_Polyhedra_Library::Linear_Expression */
inline void
swap(Parma_Polyhedra_Library::Linear_Expression& x,
     Parma_Polyhedra_Library::Linear_Expression& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Linear_Expression_inlines_hh)

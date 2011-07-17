/* Cast_Floating_Point_Expression class implementation: inline functions.
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

#ifndef PPL_Cast_Floating_Point_Expression_inlines_hh
#define PPL_Cast_Floating_Point_Expression_inlines_hh 1

#include "globals.defs.hh"

namespace Parma_Polyhedra_Library {

template <typename FP_Interval_Type, typename FP_Format>
inline
Cast_Floating_Point_Expression<FP_Interval_Type, FP_Format>::
Cast_Floating_Point_Expression(
Floating_Point_Expression<FP_Interval_Type, FP_Format>* const e)
  : expr(e) {
  assert(e != 0);
}

template <typename FP_Interval_Type, typename FP_Format>
inline
Cast_Floating_Point_Expression<FP_Interval_Type, FP_Format>::
~Cast_Floating_Point_Expression() {
  delete expr;
}

template <typename FP_Interval_Type, typename FP_Format>
inline void
Cast_Floating_Point_Expression<FP_Interval_Type, FP_Format>::swap(
	 Cast_Floating_Point_Expression& y) {
  std::swap(expr, y.expr);
}

} // namespace Parma_Polyhedra_Library

namespace std {

/*! \relates Parma_Polyhedra_Library::Cast_Floating_Point_Expression */
template <typename FP_Interval_Type, typename FP_Format>
inline void
swap(Parma_Polyhedra_Library::Cast_Floating_Point_Expression<
                              FP_Interval_Type, FP_Format>& x,
     Parma_Polyhedra_Library::Cast_Floating_Point_Expression<
                              FP_Interval_Type, FP_Format>& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Cast_Floating_Point_Expression_inlines_hh)
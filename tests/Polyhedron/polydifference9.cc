/* Test Polyhedra_Powerset<PH>::poly_difference_assign().
   Copyright (C) 2001-2005 Roberto Bagnara <bagnara@cs.unipr.it>

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

using namespace std;
using namespace Parma_Polyhedra_Library;
using namespace Parma_Polyhedra_Library::IO_Operators;

#ifndef NOISY 
#define NOISY 0
#endif

namespace {

Variable x(0);
Variable y(1);

C_Polyhedron
rectangle(int lx, int ly, int dx, int dy) {
  C_Polyhedron ph(2, EMPTY);
  ph.add_generator(point((lx+0*dx)*x + (ly+0*dy)*y));
  ph.add_generator(point((lx+1*dx)*x + (ly+0*dy)*y));
  ph.add_generator(point((lx+1*dx)*x + (ly+1*dy)*y));
  ph.add_generator(point((lx+0*dx)*x + (ly+1*dy)*y));
  return ph;
}

} // namespace

int main() TRY {
  set_handlers();

  Polyhedra_Powerset<C_Polyhedron> cross(2, EMPTY);
  cross.add_disjunct(rectangle(0, 3, 9, 3));
  cross.add_disjunct(rectangle(3, 0, 3, 9));

#if NOISY
  cout << "cross = " << cross << endl;
#endif

  Polyhedra_Powerset<C_Polyhedron> squares(2, EMPTY);
  squares.add_disjunct(rectangle(1, 4, 1, 1));
  squares.add_disjunct(rectangle(4, 4, 1, 1));
  squares.add_disjunct(rectangle(7, 4, 1, 1));
  squares.add_disjunct(rectangle(4, 1, 1, 1));
  squares.add_disjunct(rectangle(4, 7, 1, 1));

#if NOISY
  cout << "squares = " << squares << endl;
#endif

  Polyhedra_Powerset<C_Polyhedron> difference = cross;
  difference.poly_difference_assign(squares);

#if NOISY
  cout << "cross - squares = " << difference << endl;
#endif

  Polyhedra_Powerset<C_Polyhedron> intersection = difference;
  intersection.meet_assign(squares);

#if NOISY
  cout << "(cross - squares) inters squares = " << intersection << endl;
#endif

  // When using Polyhedra_Powerset<NNC_Polyhedron>, intersection will be
  // empty.  When using Polyhedra_Powerset<C_Polyhedron>,
  // intersection will consist of objects of affine dimension at most 1.
  for (Polyhedra_Powerset<C_Polyhedron>::const_iterator
	 i = intersection.begin(), in_end = intersection.end();
       i != in_end; ++i)
    if (i->element().affine_dimension() > 1) {
#if NOISY
      cout << "intersection contains " << i->element() << "," << endl
	   << "which is of affine dimension greater than 1" << endl;
#endif
      return 1;
    }

  Polyhedra_Powerset<C_Polyhedron> re_union = difference;
  re_union.upper_bound_assign(squares);
#if NOISY
  cout << "(cross - squares) union squares = " << re_union << endl;
#endif

  re_union.pairwise_reduce();

#if NOISY
  cout << "<Above union pairwise reduced>  = " << re_union << endl;
#endif

  if (!re_union.geometrically_equals(cross)) {
#if NOISY
    cout << "Union does not give back the original!" << endl;
#endif
    return 1;
  }

  return 0;
}
CATCH

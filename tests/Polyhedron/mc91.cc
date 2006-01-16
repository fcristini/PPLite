/* Test the constraint systems' constructions with McCarthy's 91 function.
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

using namespace Parma_Polyhedra_Library::IO_Operators;

typedef Polyhedra_Powerset<C_Polyhedron> PCS;

int
main() TRY {
  set_handlers();

  Variable x(0);
  Variable y(1);

  C_Polyhedron ph1(2);
  ph1.add_constraint(x <= 101);
  ph1.add_constraint(y == 91);

  C_Polyhedron ph2(2);
  ph2.add_constraint(x >= 102);
  ph2.add_constraint(y == x-10);

  PCS p1(2, EMPTY);
  p1.add_disjunct(ph1);

  nout << p1 << endl;

  PCS p2(2, EMPTY);
  p2.add_disjunct(ph2);

  nout << p2 << endl;

  p1.upper_bound_assign(p2);

  nout << p1 << endl;

  p1.meet_assign(p2);

  nout << p1 << endl;

  C_Polyhedron top(2);
  C_Polyhedron y_91(2);

  y_91.add_constraint(y == 91);

  return 0;
}
CATCH

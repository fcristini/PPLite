/* Test BD_Shape::limited_CH78_extrapolation_assign().
   Copyright (C) 2001-2003 Roberto Bagnara <bagnara@cs.unipr.it>

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
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include "ppl_test.hh"

using namespace std;
using namespace Parma_Polyhedra_Library;

#ifndef NOISY
#define NOISY 0
#endif

int
main() TRY {
  Variable x(0);
  Variable y(1);

  Constraint_System cs1;
  cs1.insert(x >= 0);
  cs1.insert(x <= 1);
  cs1.insert(y >= 0);
  cs1.insert(x - y >= 0);

  TBD_Shape bd1(cs1);

#if NOISY
  print_constraints(bd1, "*** bd1 ****");
#endif

  Constraint_System cs2;
  cs2.insert(x >= 0);
  cs2.insert(x <= 2);
  cs2.insert(y >= 0);
  cs2.insert(x - y >= 0);

  TBD_Shape bd2(cs2);

#if NOISY
  print_constraints(bd2, "*** bd2 ****");
#endif

  Constraint_System cs;
  cs.insert(x >= 0);
  cs.insert(y >= 0);
  cs.insert(x <= 5);
  cs.insert(y <= 5);

#if NOISY
  print_constraints(cs, "*** cs ****");
#endif

  TBD_Shape computed_result = bd2;
  computed_result.limited_CH78_extrapolation_assign(bd1, cs);

  TBD_Shape known_result(2);
  known_result.add_constraint(y >= 0);
  known_result.add_constraint(x <= 5);
  known_result.add_constraint(y - x <= 0);
  known_result.add_constraint(x >= 0);

#if NOISY
  print_constraints(computed_result,
		    "*** bd1.limited_CH78_extrapolation_assign(bd2) ***");
#endif

  return (computed_result == known_result) ? 0 : 1;
}
CATCH

/* Test Octagon::poly_hull_assign().
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
  Variable x1(0);
  Variable x2(1);

  TOctagon oct1(2);
  TOctagon oct2(2);
  TOctagon known_result(2);

  oct1.add_constraint(x1 >= 1);
  oct1.add_constraint(x1 - x2 <= 3);

  oct2.add_constraint(x2 <= 1);
  oct2.add_constraint(x1 - x2 <= 2);

#if NOISY
  print_constraints(oct1, "*** oct1 ***");
  print_constraints(oct2, "*** oct2 ***");
#endif

  oct1.poly_hull_assign(oct2);

#if NOISY
  print_constraints(oct1, "*** oct1.poly_hull_assign(oct2) ***");
#endif

  known_result.add_constraint(x1 - x2 <= 3);

  int retval = (oct1 == known_result) ? 0 : 1;

  return retval;
}
CATCH

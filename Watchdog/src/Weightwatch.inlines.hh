/* Weightwatch and associated classes' implementation: inline functions.
   Copyright (C) 2001-2009 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Watchdog Library (PWL).

The PWL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The PWL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#ifndef PWL_Weightwatch_inlines_hh
#define PWL_Weightwatch_inlines_hh 1

#include <stdexcept>

#include "Handler.defs.hh"

namespace Parma_Watchdog_Library {

template <typename Flag_Base, typename Flag>
Weightwatch::Weightwatch(int units, const Flag_Base* volatile& holder, Flag& flag)
  : expired(false),
    handler(*new Handler_Flag<Flag_Base, Flag>(holder, flag)) {
  if (units <= 0)
    throw std::invalid_argument("Weightwatch constructor called with a"
				" non-positive weight");
  pending_position = new_weight_threshold(units, handler, expired);
}

inline
Weightwatch::Weightwatch(int units, void (*function)())
  : expired(false), handler(*new Handler_Function(function)) {
  if (units <= 0)
    throw std::invalid_argument("Weightwatch constructor called with a"
				" non-positive weight");
  pending_position = new_weight_threshold(units, handler, expired);
}

inline void
Weightwatch::add(unsigned int units, unsigned int iterations) {
  if (weight_so_far == 0)
    return;
  weight_so_far += (Weight)units * iterations;
}

inline void
Weightwatch::check() {
  if (weight_so_far == 0)
    return;
  WW_Pending_List::Iterator i = pending.begin();
  assert(i != pending.end());
  while (weight_so_far >= i->deadline()) {
    i->handler().act();
    i->expired_flag() = true;
    i = pending.erase(i);
    if (i == pending.end())
      weight_so_far = 0;
  }
}

} // namespace Parma_Watchdog_Library

#endif // !defined(PWL_Weightwatch_inlines_hh)

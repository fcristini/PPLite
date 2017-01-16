/* Functions for compatibility between PPL and PPLite */

#ifndef PPL_Checked_Compat_defs_hh
#define PPL_Checked_Compat_defs_hh 1

#define FABIO_NO_ASSERTS_HH

#include "Result_defs.hh"

#define FABIO_NO_INLINES

#include "Rounding_Dir_defs.hh"
#include "GMP_Integer_types.hh"

#undef FABIO_NO_INLINES
#undef FABIO_NO_ASSERTS_HH

namespace Parma_Polyhedra_Library {

template <typename To, typename From> inline
Result assign_r(To & to, From from, Rounding_Dir rd);

template <typename To, typename Num, typename Den> inline
Result div_assign_r(To & to, Num num, Den den, Rounding_Dir rd);

template <typename To, typename Num, typename Pow> inline
Result div_2exp_assign_r(To & to, Num num, Pow pow, Rounding_Dir rd);

template <typename To, typename Fac1, typename Fac2> inline
Result mul_assign_r(To & to, Fac1 fac1, Fac2 fac2, Rounding_Dir rd);

} // namespace Parma_Polyhedra_Library

#include "Checked_Compat_inlines.hh"

#endif // !defined(PPL_Checked_Compat_defs_hh)

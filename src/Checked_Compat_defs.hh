
#ifndef PPL_Checked_Compat_defs_hh
#define PPL_Checked_Compat_defs_hh 1

#define FABIO_NO_ASSERTS_HH

#include <Result_defs.hh>

#define FABIO_NO_INLINES

#include <Rounding_Dir_defs.hh>
#include <GMP_Integer_types.hh>

#undef FABIO_NO_INLINES
#undef FABIO_NO_ASSERTS_HH

namespace Parma_Polyhedra_Library {

template <typename To, typename From> inline
Parma_Polyhedra_Library::Result assign_r(To to, From from, Parma_Polyhedra_Library::Rounding_Dir rd);
/*
template <>
Parma_Polyhedra_Library::Result assign_r<unsigned int, Parma_Polyhedra_Library::GMP_Integer>(unsigned int to, Parma_Polyhedra_Library::GMP_Integer from, Parma_Polyhedra_Library::Rounding_Dir rd);
*/
template <typename To, typename Num, typename Den> inline
Parma_Polyhedra_Library::Result div_assign_r(To to, Num num, Den den, Parma_Polyhedra_Library::Rounding_Dir rd);

template <typename To, typename Num, typename Pow> inline
Parma_Polyhedra_Library::Result div_2exp_assign_r(To to, Num num, Pow pow, Parma_Polyhedra_Library::Rounding_Dir rd);

template <typename To, typename Fac1, typename Fac2> inline
Parma_Polyhedra_Library::Result mul_assign_r(To to, Fac1 fac1, Fac2 fac2, Parma_Polyhedra_Library::Rounding_Dir rd);

/////#define assign_r(to, from, rd) (V_EQ,to=from)
/////#define div_assign_r(to, n, d, rd) (V_EQ,to=n/d)
/////#define div_2exp_assign_r(to, n, power, rd) (V_EQ,to=n>>power)
/////#define mul_assign_r(to, f1, f2, rd) (V_EQ,to=f1*f2)

} // namespace Parma_Polyhedra_Library

#include "Checked_Compat_inlines.hh"

#endif // !defined(PPL_Checked_Compat_defs_hh)

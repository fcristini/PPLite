
#include "ppl-config.h"

namespace Parma_Polyhedra_Library {

template <typename To, typename From>
inline
Parma_Polyhedra_Library::Result assign_r(To to, From from, Parma_Polyhedra_Library::Rounding_Dir rd)
{
    to = from;
    return Parma_Polyhedra_Library::Result::V_EQ;
}

template <>
inline
Parma_Polyhedra_Library::Result assign_r<unsigned int, Parma_Polyhedra_Library::GMP_Integer>(unsigned int to, Parma_Polyhedra_Library::GMP_Integer from, Parma_Polyhedra_Library::Rounding_Dir rd)
{
    to = from.get_ui();
    return Parma_Polyhedra_Library::Result::V_EQ;
}

template <typename To, typename Num, typename Den>
inline
Parma_Polyhedra_Library::Result div_assign_r(To to, Num num, Den den, Parma_Polyhedra_Library::Rounding_Dir rd)
{
    to = num / den;
    return Parma_Polyhedra_Library::Result::V_EQ;
}

template <typename To, typename Num, typename Pow>
inline
Parma_Polyhedra_Library::Result div_2exp_assign_r(To to, Num num, Pow pow, Parma_Polyhedra_Library::Rounding_Dir rd)
{
    to = num >> pow;
    return Parma_Polyhedra_Library::Result::V_EQ;
}

template <typename To, typename Fac1, typename Fac2>
inline
Parma_Polyhedra_Library::Result mul_assign_r(To to, Fac1 fac1, Fac2 fac2, Parma_Polyhedra_Library::Rounding_Dir rd)
{
    to = fac1 * fac2;
    return Parma_Polyhedra_Library::Result::V_EQ;
}

} // namespace Parma_Polyhedra_Library


#ifndef PPL_Checked_Compat_inlines_hh
#define PPL_Checked_Compat_inlines_hh 1

namespace Parma_Polyhedra_Library {

template <typename To, typename From>
inline
Result assign_r(To & to, From from, Rounding_Dir)
{
    to = from;
    return V_EQ;
}

template <>
inline
Result assign_r<unsigned int, GMP_Integer>(unsigned int & to, GMP_Integer from, Rounding_Dir)
{
    to = from.get_ui();
    return V_EQ;
}

template <>
inline
Result assign_r<unsigned int, flint_mpz_class>(unsigned int & to, flint_mpz_class from, Rounding_Dir)
{
    to = from.get_ui();
    return V_EQ;
}

template <>
inline
Result assign_r<GMP_Integer, flint_mpz_class>(GMP_Integer & to, flint_mpz_class from, Rounding_Dir)
{
    to = from.get_str();
    return V_EQ;
}

template <>
inline
Result assign_r<flint_mpz_class, GMP_Integer>(flint_mpz_class & to, GMP_Integer from, Rounding_Dir)
{
    to = from.get_str();
    return V_EQ;
}

template <>
inline
Result assign_r<flint_mpz_class, mpq_class>(flint_mpz_class & to, mpq_class from, Rounding_Dir)
{
    to = from.get_str();
    return V_EQ;
}

template <typename To, typename Num, typename Den>
inline
Result div_assign_r(To & to, Num num, Den den, Rounding_Dir)
{
    to = num / den;
    return V_EQ;
}

template <typename To, typename Num, typename Pow>
inline
Result div_2exp_assign_r(To & to, Num num, Pow pow, Rounding_Dir)
{
    to = num >> pow;
    return V_EQ;
}

template <typename To, typename Fac1, typename Fac2>
inline
Result mul_assign_r(To & to, Fac1 fac1, Fac2 fac2, Rounding_Dir)
{
    to = fac1 * fac2;
    return V_EQ;
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Checked_Compat_inlines_hh)

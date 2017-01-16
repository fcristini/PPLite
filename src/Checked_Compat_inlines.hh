
#ifndef PPL_Checked_Compat_inlines_hh
#define PPL_Checked_Compat_inlines_hh 1

namespace Parma_Polyhedra_Library {

template <typename To, typename From>
inline
Result assign_r(To & to, From from, Rounding_Dir)
{
    /////std::cout << "Passed in assign_r" << std::endl;
    to = from;
    return Result::V_EQ;
}

template <>
inline
Result assign_r<unsigned int, GMP_Integer>(unsigned int & to, GMP_Integer from, Rounding_Dir)
{
    /////std::cout << "Passed in assign_r(GMP)" << std::endl;
    to = from.get_ui();
    return Result::V_EQ;
}

template <typename To, typename Num, typename Den>
inline
Result div_assign_r(To & to, Num num, Den den, Rounding_Dir)
{
    /////std::cout << "Passed in div_assign_r" << std::endl;
    to = num / den;
    return Result::V_EQ;
}

template <typename To, typename Num, typename Pow>
inline
Result div_2exp_assign_r(To & to, Num num, Pow pow, Rounding_Dir)
{
    /////std::cout << "Passed in div_2exp_assign_r" << std::endl;
    to = num >> pow;
    return Result::V_EQ;
}

template <typename To, typename Fac1, typename Fac2>
inline
Result mul_assign_r(To & to, Fac1 fac1, Fac2 fac2, Rounding_Dir)
{
    /////std::cout << "Passed in mul_assign_r" << std::endl;
    to = fac1 * fac2;
    return Result::V_EQ;
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Checked_Compat_inlines_hh)

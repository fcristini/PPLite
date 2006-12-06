/* Checked extended arithmetic functions.
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

namespace Parma_Polyhedra_Library {

namespace Checked {

template <typename T>
inline bool
handle_ext_natively(const T&) {
  return false;
}
inline bool
handle_ext_natively(const float&) {
  return true;
}
inline bool
handle_ext_natively(const double&) {
  return true;
}
inline bool
handle_ext_natively(const long double&) {
  return true;
}

template <typename Policy, typename Type>
inline bool
ext_to_handle(const Type& x) {
  return !handle_ext_natively(x)
    && (Policy::has_infinity || Policy::has_nan);
}

template <typename Policy, typename Type>
inline Result
sgn_ext(const Type& x) {
  if (!ext_to_handle<Policy>(x))
    goto native;
  if (is_nan<Policy>(x))
    return VC_NAN;
  else if (is_minf<Policy>(x))
    return V_LT;
  else if (is_pinf<Policy>(x))
    return V_GT;
  else {
  native:
    return sgn<Policy>(x);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
construct_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return construct<To_Policy, void>(to, NOT_A_NUMBER, dir);
  else if (is_minf<From_Policy>(x))
    return construct<To_Policy, void>(to, MINUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return construct<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return construct<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
assign_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return assign<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
neg_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
  else {
  native:
    return neg<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
floor_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return floor<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
ceil_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return ceil<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
trunc_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return trunc<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
abs_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x) || is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return abs<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
add_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (!ext_to_handle<From1_Policy>(x) && !ext_to_handle<From2_Policy>(y))
    goto native;
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From1_Policy>(x)) {
    if (CHECK_P(To_Policy::check_inf_add_inf, is_pinf<From2_Policy>(y)))
      goto inf_add_inf;
    else
      goto minf;
  }
  else if (is_pinf<From1_Policy>(x)) {
    if (CHECK_P(To_Policy::check_inf_add_inf, is_minf<From2_Policy>(y))) {
    inf_add_inf:
      return set_special<To_Policy>(to, V_INF_ADD_INF);
    }
    else
      goto pinf;
  }
  else {
    if (is_minf<From2_Policy>(y)) {
    minf:
      return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
    }
    else if (is_pinf<From2_Policy>(y)) {
    pinf:
      return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
    }
    else {
    native:
      return add<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
    }
  }
}

template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
sub_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (!ext_to_handle<From1_Policy>(x) && !ext_to_handle<From2_Policy>(y))
    goto native;
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From1_Policy>(x)) {
    if (CHECK_P(To_Policy::check_inf_sub_inf, is_minf<From2_Policy>(y)))
      goto inf_sub_inf;
    else
      goto minf;
  }
  else if (is_pinf<From1_Policy>(x)) {
    if (CHECK_P(To_Policy::check_inf_sub_inf, is_pinf<From2_Policy>(y))) {
    inf_sub_inf:
      return set_special<To_Policy>(to, V_INF_SUB_INF);
    }
    else
      goto pinf;
  }
  else {
    if (is_pinf<From2_Policy>(y)) {
    minf:
      return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
    }
    else if (is_minf<From2_Policy>(y)) {
    pinf:
      return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
    }
    else {
    native:
      return sub<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
    }
  }
}

template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
mul_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (!ext_to_handle<From1_Policy>(x) && !ext_to_handle<From2_Policy>(y))
    goto native;
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  if (is_minf<From1_Policy>(x)) {
    switch (sgn_ext<From2_Policy>(y)) {
    case V_LT:
      goto pinf;
    case V_GT:
      goto minf;
    default:
      goto inf_mul_zero;
    }
  }
  else if (is_pinf<From1_Policy>(x)) {
    switch (sgn_ext<From2_Policy>(y)) {
    case V_LT:
      goto minf;
    case V_GT:
      goto pinf;
    default:
      goto inf_mul_zero;
    }
  }
  else {
    if (is_minf<From2_Policy>(y)) {
      switch (sgn<From1_Policy>(x)) {
      case V_LT:
	goto pinf;
      case V_GT:
	goto minf;
      default:
	goto inf_mul_zero;
      }
    }
    else if (is_pinf<From2_Policy>(y)) {
      switch (sgn<From1_Policy>(x)) {
      case V_LT:
      minf:
	return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
      case V_GT:
      pinf:
	return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
      default:
      inf_mul_zero:
	assert(To_Policy::check_inf_mul_zero);
	return set_special<To_Policy>(to, V_INF_MUL_ZERO);
      }
    }
    else {
    native:
      return mul<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
    }
  }
}


template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
add_mul_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (!ext_to_handle<To_Policy>(to)
      && !ext_to_handle<From1_Policy>(x) && !ext_to_handle<From2_Policy>(y))
    goto native;
  if (is_nan<To_Policy>(to)
      || is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  if (is_minf<From1_Policy>(x)) {
    switch (sgn_ext<From2_Policy>(y)) {
    case V_LT:
      goto a_pinf;
    case V_GT:
      goto a_minf;
    default:
      goto inf_mul_zero;
    }
  }
  else if (is_pinf<From1_Policy>(x)) {
    switch (sgn_ext<From2_Policy>(y)) {
    case V_LT:
      goto a_minf;
    case V_GT:
      goto a_pinf;
    default:
      goto inf_mul_zero;
    }
  }
  else {
    if (is_minf<From2_Policy>(y)) {
      switch (sgn<From1_Policy>(x)) {
      case V_LT:
	goto a_pinf;
      case V_GT:
	goto a_minf;
      default:
	goto inf_mul_zero;
      }
    }
    else if (is_pinf<From2_Policy>(y)) {
      switch (sgn<From1_Policy>(x)) {
      case V_LT:
      a_minf:
	if (CHECK_P(To_Policy::check_inf_add_inf, is_pinf<To_Policy>(to)))
	  goto inf_add_inf;
	else
	  goto minf;
      case V_GT:
      a_pinf:
	if (CHECK_P(To_Policy::check_inf_add_inf, is_minf<To_Policy>(to))) {
	inf_add_inf:
	  return set_special<To_Policy>(to, V_INF_ADD_INF);
	}
	else
	  goto pinf;
      default:
      inf_mul_zero:
	assert(To_Policy::check_inf_mul_zero);
	return set_special<To_Policy>(to, V_INF_MUL_ZERO);
      }
    }
    else {
      if (is_minf<To_Policy>(to)) {
      minf:
	return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
      }
      if (is_pinf<To_Policy>(to)) {
      pinf:
	return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
      }
    native:
      return add_mul<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
    }
  }
}

template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
sub_mul_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (!ext_to_handle<To_Policy>(to)
      && !ext_to_handle<From1_Policy>(x) && !ext_to_handle<From2_Policy>(y))
    goto native;
  if (is_nan<To_Policy>(to)
      || is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  if (is_minf<From1_Policy>(x)) {
    switch (sgn_ext<From2_Policy>(y)) {
    case V_LT:
      goto a_pinf;
    case V_GT:
      goto a_minf;
    default:
      goto inf_mul_zero;
    }
  }
  else if (is_pinf<From1_Policy>(x)) {
    switch (sgn_ext<From2_Policy>(y)) {
    case V_LT:
      goto a_minf;
    case V_GT:
      goto a_pinf;
    default:
      goto inf_mul_zero;
    }
  }
  else {
    if (is_minf<From2_Policy>(y)) {
      switch (sgn<From1_Policy>(x)) {
      case V_LT:
	goto a_pinf;
      case V_GT:
	goto a_minf;
      default:
	goto inf_mul_zero;
      }
    }
    else if (is_pinf<From2_Policy>(y)) {
      switch (sgn<From1_Policy>(x)) {
      case V_LT:
      a_minf:
	if (CHECK_P(To_Policy::check_inf_sub_inf, is_minf<To_Policy>(to)))
	  goto inf_sub_inf;
	else
	  goto pinf;
      case V_GT:
      a_pinf:
	if (CHECK_P(To_Policy::check_inf_sub_inf, is_pinf<To_Policy>(to))) {
	inf_sub_inf:
	  return set_special<To_Policy>(to, V_INF_SUB_INF);
	}
	else
	  goto minf;
      default:
      inf_mul_zero:
	assert(To_Policy::check_inf_mul_zero);
	return set_special<To_Policy>(to, V_INF_MUL_ZERO);
      }
    }
    else {
      if (is_minf<To_Policy>(to)) {
      minf:
	return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
      }
      if (is_pinf<To_Policy>(to)) {
      pinf:
	return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
      }
    native:
      return sub_mul<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
    }
  }
}

template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
div_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (!ext_to_handle<From1_Policy>(x) && !ext_to_handle<From2_Policy>(y))
    goto native;
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  if (is_minf<From1_Policy>(x)) {
    if (CHECK_P(To_Policy::check_inf_div_inf, is_minf<From2_Policy>(y)
		|| is_pinf<From2_Policy>(y)))
      goto inf_div_inf;
    else {
      switch (sgn<From2_Policy>(y)) {
      case V_LT:
	goto pinf;
      case V_GT:
	goto minf;
      default:
	goto div_zero;
      }
    }
  }
  else if (is_pinf<From1_Policy>(x)) {
    if (CHECK_P(To_Policy::check_inf_div_inf, is_minf<From2_Policy>(y)
		|| is_pinf<From2_Policy>(y))) {
    inf_div_inf:
      return set_special<To_Policy>(to, V_INF_DIV_INF);
    }
    else {
      switch (sgn<From2_Policy>(y)) {
      case V_LT:
      minf:
	return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
      case V_GT:
      pinf:
	return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
      default:
      div_zero:
	assert(To_Policy::check_div_zero);
	return set_special<To_Policy>(to, V_DIV_ZERO);
      }
    }
  }
  else {
    if (is_minf<From2_Policy>(y) || is_pinf<From2_Policy>(y)) {
      to = 0;
      return V_EQ;
    }
    else {
    native:
      return div<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
    }
  }
}


template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
rem_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (!ext_to_handle<From1_Policy>(x) && !ext_to_handle<From2_Policy>(y))
    goto native;
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  else if (CHECK_P(To_Policy::check_inf_mod, is_minf<From1_Policy>(x)
		   || is_pinf<From1_Policy>(x)))
    return set_special<To_Policy>(to, V_INF_MOD);
  else {
    if (is_minf<From1_Policy>(y) || is_pinf<From2_Policy>(y)) {
      to = x;
      return V_EQ;
    }
    else {
    native:
      return rem<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
    }
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
mul2exp_ext(To& to, const From& x, int exp, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return mul2exp<To_Policy, From_Policy>(to, x, exp, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
div2exp_ext(To& to, const From& x, int exp, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return assign<To_Policy, void>(to, MINUS_INFINITY, dir);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return div2exp<To_Policy, From_Policy>(to, x, exp, dir);
  }
}

template <typename To_Policy, typename From_Policy,
	  typename To, typename From>
inline Result
sqrt_ext(To& to, const From& x, Rounding_Dir dir) {
  if (!ext_to_handle<From_Policy>(x))
    goto native;
  if (is_nan<From_Policy>(x))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From_Policy>(x))
    return set_special<To_Policy>(to, V_SQRT_NEG);
  else if (is_pinf<From_Policy>(x))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else {
  native:
    return sqrt<To_Policy, From_Policy>(to, x, dir);
  }
}

template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
gcd_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From1_Policy>(x) || is_pinf<From1_Policy>(x))
    return abs_ext<To_Policy, From2_Policy>(to, y, dir);
  else if (is_minf<From2_Policy>(y) || is_pinf<From2_Policy>(y))
    return abs_ext<To_Policy, From1_Policy>(to, x, dir);
  else
    return gcd<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
}

template <typename To1_Policy, typename From1_Policy, typename From2_Policy,
	  typename To2_Policy, typename To3_Policy,
	  typename To1, typename From1, typename From2, typename To2, typename To3>
inline Result
gcdext_ext(To1& to, const From1& x, const From2& y,
	   To2& s, To3& t, Rounding_Dir dir) {
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To1_Policy>(to, VC_NAN);
  else if (is_minf<From1_Policy>(x) || is_pinf<From1_Policy>(x)) {
    s = 0;
    t = y > 0 ? -1 : 1;
    return abs_ext<To1_Policy, From2_Policy>(to, y, dir);
  }
  else if (is_minf<From2_Policy>(y) || is_pinf<From2_Policy>(y)) {
    s = x > 0 ? -1 : 1;
    t = 0;
    return abs_ext<To1_Policy, From1_Policy>(to, x, dir);
  }
  else
    return gcdext<To1_Policy, From1_Policy, From2_Policy, To2_Policy, To3_Policy>(to, x, y, s, t, dir);
}

template <typename To_Policy, typename From1_Policy, typename From2_Policy,
	  typename To, typename From1, typename From2>
inline Result
lcm_ext(To& to, const From1& x, const From2& y, Rounding_Dir dir) {
  if (is_nan<From1_Policy>(x) || is_nan<From2_Policy>(y))
    return set_special<To_Policy>(to, VC_NAN);
  else if (is_minf<From1_Policy>(x) || is_pinf<From1_Policy>(x)
	   || is_minf<From2_Policy>(y) || is_pinf<From2_Policy>(y))
    return assign<To_Policy, void>(to, PLUS_INFINITY, dir);
  else
    return lcm<To_Policy, From1_Policy, From2_Policy>(to, x, y, dir);
}

template <typename Policy1, typename Policy2,
	  typename Type1, typename Type2>
inline Result
cmp_ext(const Type1& x, const Type2& y) {
  if (!ext_to_handle<Policy1>(x) && !ext_to_handle<Policy2>(y))
    goto native;
  if (is_nan<Policy1>(x) || is_nan<Policy2>(y))
    return V_UNORD_COMP;
  else if (is_minf<Policy1>(x))
    return is_minf<Policy2>(y) ? V_EQ : V_LT;
  else if (is_pinf<Policy1>(x))
    return is_pinf<Policy2>(y) ? V_EQ : V_GT;
  else {
    if (is_minf<Policy2>(y))
      return V_GT;
    if (is_pinf<Policy2>(y))
      return V_LT;
  native:
    return cmp<Policy1, Policy2>(x, y);
  }
}

template <typename Policy1, typename Policy2,
	  typename Type1, typename Type2>
inline bool
lt_ext(const Type1& x, const Type2& y) {
  if (!ext_to_handle<Policy1>(x) && !ext_to_handle<Policy2>(y))
    goto native;
  if (is_nan<Policy1>(x) || is_nan<Policy2>(y))
    return false;
  if (is_pinf<Policy1>(x) || is_minf<Policy2>(y))
    return false;
  if (is_minf<Policy1>(x) || is_pinf<Policy2>(y))
    return true;
 native:
  return lt<Policy1, Policy2>(x, y);
}

template <typename Policy1, typename Policy2,
	  typename Type1, typename Type2>
inline bool
gt_ext(const Type1& x, const Type2& y) {
  return lt_ext<Policy1, Policy2>(y, x);
}

template <typename Policy1, typename Policy2,
	  typename Type1, typename Type2>
inline bool
le_ext(const Type1& x, const Type2& y) {
  if (!ext_to_handle<Policy1>(x) && !ext_to_handle<Policy2>(y))
    goto native;
  if (is_nan<Policy1>(x) || is_nan<Policy2>(y))
    return false;
  if (is_minf<Policy1>(x) || is_pinf<Policy2>(y))
    return true;
  if (is_pinf<Policy1>(x) || is_minf<Policy2>(y))
    return false;
 native:
  return le<Policy1, Policy2>(x, y);
}

template <typename Policy1, typename Policy2,
	  typename Type1, typename Type2>
inline bool
ge_ext(const Type1& x, const Type2& y) {
  return le_ext<Policy1, Policy2>(y, x);
}

template <typename Policy1, typename Policy2,
	  typename Type1, typename Type2>
inline bool
eq_ext(const Type1& x, const Type2& y) {
  if (!ext_to_handle<Policy1>(x) && !ext_to_handle<Policy2>(y))
    goto native;
  if (is_nan<Policy1>(x) || is_nan<Policy2>(y))
    return false;
  if (is_minf<Policy1>(x))
    return is_minf<Policy2>(y);
  if (is_pinf<Policy1>(x))
    return is_pinf<Policy2>(y);
  else if (is_minf<Policy2>(y) || is_pinf<Policy2>(y))
    return false;
 native:
  return eq<Policy1, Policy2>(x, y);
}

template <typename Policy1, typename Policy2,
	  typename Type1, typename Type2>
inline bool
ne_ext(const Type1& x, const Type2& y) {
  return !eq_ext<Policy1, Policy2>(x, y);
}

inline std::ostream&
operator<<(std::ostream& os, const Not_A_Number&) {
  os << "nan";
  return os;
}

inline std::ostream&
operator<<(std::ostream& os, const Minus_Infinity&) {
  os << "-inf";
  return os;
}

inline std::ostream&
operator<<(std::ostream& os, const Plus_Infinity&) {
  os << "+inf";
  return os;
}

template <typename Policy, typename Type>
inline Result
output_ext(std::ostream& os, const Type& x,
	   const Numeric_Format& format, Rounding_Dir dir) {
  if (!ext_to_handle<Policy>(x))
    goto native;
  if (is_nan<Policy>(x)) {
    os << NOT_A_NUMBER;
    return VC_NAN;
  }
  if (is_minf<Policy>(x)) {
    os << MINUS_INFINITY;
    return V_EQ;
  }
  if (is_pinf<Policy>(x)) {
    os << PLUS_INFINITY;
    return V_EQ;
  }
 native:
  return output<Policy>(os, x, format, dir);
}

template <typename To_Policy, typename To>
inline Result
input_ext(To& to, std::istream& is, Rounding_Dir dir) {
  return input<To_Policy>(to, is, dir);
}

} // namespace Checked

} // namespace Parma_Polyhedra_Library

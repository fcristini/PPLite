/* Constraint class implementation (non-inline functions).
   Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2011 BUGSENG srl (http://bugseng.com)

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
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

#include <ppl-config.h>

#include "Constraint.defs.hh"
#include "Variable.defs.hh"
#include "Variables_Set.defs.hh"
#include "Congruence.defs.hh"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace PPL = Parma_Polyhedra_Library;

void
PPL::Constraint::throw_invalid_argument(const char* method,
					const char* message) const {
  std::ostringstream s;
  s << "PPL::Constraint::" << method << ":" << std::endl
    << message;
  throw std::invalid_argument(s.str());
}

void
PPL::Constraint::throw_dimension_incompatible(const char* method,
					      const char* name_var,
					      const Variable v) const {
  std::ostringstream s;
  s << "PPL::Constraint::" << method << ":" << std::endl
    << "this->space_dimension() == " << space_dimension() << ", "
    << name_var << ".space_dimension() == " << v.space_dimension() << ".";
  throw std::invalid_argument(s.str());
}

PPL::Constraint
PPL::Constraint::construct_epsilon_geq_zero() {
  Linear_Expression e = Variable(0);
  return Constraint(e, NONSTRICT_INEQUALITY, NOT_NECESSARILY_CLOSED);
}

PPL::Constraint::Constraint(const Congruence& cg)
  : Linear_Row(cg.is_equality()
	       // Size includes extra column for the inhomogeneous term.
	       ? cg.space_dimension() + 1
	       : (throw_invalid_argument("Constraint(cg)",
					 "congruence cg must be an equality."),
		  0),
	       // Capacity also includes a column for the epsilon coefficient.
	       compute_capacity(cg.space_dimension() + 2, Dense_Row::max_size())),
	       flags_(NECESSARILY_CLOSED, LINE_OR_EQUALITY) {
  Constraint& c = *this;
  // Copy coefficients and inhomogeneous term.
  for (dimension_type i = cg.space_dimension(); i-- > 0; )
    c.get_row()[i + 1] = cg.coefficient(Variable(i));
  c.get_row()[0] = cg.inhomogeneous_term();
  // Enforce normalization.
  strong_normalize();
  
  PPL_ASSERT(OK());
}

PPL::Constraint::Constraint(const Congruence& cg,
			    dimension_type sz,
			    dimension_type capacity)
  : Linear_Row(cg.is_equality()
	       ? sz
	       : (throw_invalid_argument("Constraint(cg, sz, c)",
					 "congruence cg must be an equality."),
		  0),
	       capacity),
	       flags_(NECESSARILY_CLOSED, LINE_OR_EQUALITY) {
  Constraint& c = *this;
  // Copy coefficients.
  PPL_ASSERT(sz > 0);
  --sz;
  while (sz-- > 0)
    c.get_row()[sz + 1] = cg.coefficient(Variable(sz));
  c.get_row()[0] = cg.inhomogeneous_term();
  
  PPL_ASSERT(OK());
}

void
PPL::Constraint::swap_space_dimensions(Variable v1, Variable v2) {
  PPL_ASSERT(v1.space_dimension() <= space_dimension());
  PPL_ASSERT(v2.space_dimension() <= space_dimension());
  swap(v1.space_dimension(), v2.space_dimension());
  // *this is still normalized but it may not be strongly normalized.
  sign_normalize();
  PPL_ASSERT(OK());
}

bool
PPL::Constraint::remove_space_dimensions(const Variables_Set& vars) {
  PPL_ASSERT(vars.space_dimension() <= space_dimension());
  // For each variable to be removed, replace the corresponding coefficient
  // by shifting left the coefficient to the right that will be kept.
  Variables_Set::const_iterator vsi = vars.begin();
  Variables_Set::const_iterator vsi_end = vars.end();
  dimension_type dst_col = *vsi+1;
  dimension_type src_col = dst_col + 1;
  for (++vsi; vsi != vsi_end; ++vsi) {
    const dimension_type vsi_col = *vsi+1;
    // Move all columns in between to the left.
    while (src_col < vsi_col)
      std::swap(get_row()[dst_col++], get_row()[src_col++]);
    ++src_col;
  }
  // Move any remaining columns.
  const dimension_type sz = get_row().size();
  while (src_col < sz)
    std::swap(get_row()[dst_col++], get_row()[src_col++]);

  // The number of remaining coefficients is `dst_col'.
  get_row().resize(dst_col);

  PPL_ASSERT(OK());
  return true;
}

void
PPL::Constraint
::permute_space_dimensions(const std::vector<Variable>& cycle) {
  const dimension_type n = cycle.size();
  if (n < 2)
    // No-op. No need to call sign_normalize().
    return;

  if (n == 2) {
    get_row().swap(cycle[0].space_dimension(), cycle[1].space_dimension());
  } else {
    PPL_DIRTY_TEMP_COEFFICIENT(tmp);
    tmp = get_row()[cycle.back().space_dimension()];
    for (dimension_type i = n - 1; i-- > 0; )
     get_row().swap(cycle[i + 1].space_dimension(),
                    cycle[i].space_dimension());
    if (tmp == 0)
      get_row().reset(cycle[0].space_dimension());
    else
      std::swap(tmp, get_row()[cycle[0].space_dimension()]);
  }
  // *this is still normalized but may be not strongly normalized: sign
  // normalization is necessary.
  sign_normalize();
  PPL_ASSERT(OK());
}

bool
PPL::Constraint::is_tautological() const {
  PPL_ASSERT(get_row().size() > 0);
  const Constraint& x = *this;
  if (x.all_homogeneous_terms_are_zero())
    if (is_equality())
      return x.get_row()[0] == 0;
    else
      // Non-strict inequality constraint.
      return x.get_row()[0] >= 0;
  else
    // There is a non-zero homogeneous coefficient.
    if (is_necessarily_closed())
      return false;
    else {
      // The constraint is NOT necessarily closed.
      const dimension_type eps_index = get_row().size() - 1;
      const int eps_sign = sgn(x.get_row()[eps_index]);
      if (eps_sign > 0)
	// We have found the constraint epsilon >= 0.
	return true;
      if (eps_sign == 0)
	// One of the `true' dimensions has a non-zero coefficient.
	return false;
      else {
	// Here the epsilon coefficient is negative: strict inequality.
	if (x.get_row()[0] <= 0)
	  // A strict inequality such as `lhs - k > 0',
	  // where k is a non negative integer, cannot be trivially true.
	  return false;
	// Checking for another non-zero coefficient.
	for (dimension_type i = eps_index; --i > 0; )
	  if (x.get_row()[i] != 0)
	    return false;
	// We have the inequality `k > 0',
	// where k is a positive integer.
	return true;
      }
    }
}

bool
PPL::Constraint::is_inconsistent() const {
  PPL_ASSERT(get_row().size() > 0);
  const Constraint& x = *this;
  if (x.all_homogeneous_terms_are_zero())
    // The inhomogeneous term is the only non-zero coefficient.
    if (is_equality())
      return x.get_row()[0] != 0;
    else
      // Non-strict inequality constraint.
      return x.get_row()[0] < 0;
  else
    // There is a non-zero homogeneous coefficient.
    if (is_necessarily_closed())
      return false;
    else {
      // The constraint is NOT necessarily closed.
      const dimension_type eps_index = get_row().size() - 1;
      if (x.get_row()[eps_index] >= 0)
	// If positive, we have found the constraint epsilon >= 0.
	// If zero, one of the `true' dimensions has a non-zero coefficient.
	// In both cases, it is not trivially false.
	return false;
      else {
	// Here the epsilon coefficient is negative: strict inequality.
	if (x.get_row()[0] > 0)
	  // A strict inequality such as `lhs + k > 0',
	  // where k is a positive integer, cannot be trivially false.
	  return false;
	// Checking for another non-zero coefficient.
	for (dimension_type i = eps_index; --i > 0; )
	  if (x.get_row()[i] != 0)
	    return false;
	// We have the inequality `k > 0',
	// where k is zero or a negative integer.
	return true;
      }
    }
}

void
PPL::Constraint::linear_combine(const Constraint& y,
                                const dimension_type k) {
  Constraint& x = *this;
  // We can combine only vector of the same dimension.
  PPL_ASSERT(x.get_row().size() == y.get_row().size());
  PPL_ASSERT(y.get_row()[k] != 0 && x.get_row()[k] != 0);
  // Let g be the GCD between `x[k]' and `y[k]'.
  // For each i the following computes
  //   x[i] = x[i]*y[k]/g - y[i]*x[k]/g.
  PPL_DIRTY_TEMP_COEFFICIENT(normalized_x_k);
  PPL_DIRTY_TEMP_COEFFICIENT(normalized_y_k);
  normalize2(x.get_row()[k], y.get_row()[k], normalized_x_k, normalized_y_k);
  for (dimension_type i = get_row().size(); i-- > 0; )
    if (i != k) {
      Coefficient& x_i = x.get_row()[i];
      x_i *= normalized_y_k;
      sub_mul_assign(x_i, y.get_row()[i], normalized_x_k);
    }
  x.get_row()[k] = 0;
  x.strong_normalize();
}

/*! \relates Parma_Polyhedra_Library::Constraint */
int
PPL::compare(const Constraint& x, const Constraint& y) {
  const bool x_is_line_or_equality = x.is_line_or_equality();
  const bool y_is_line_or_equality = y.is_line_or_equality();
  if (x_is_line_or_equality != y_is_line_or_equality)
    // Equalities (lines) precede inequalities (ray/point).
    return y_is_line_or_equality ? 2 : -2;

  // Compare all the coefficients of the row starting from position 1.
  const dimension_type xsz = x.get_row().size();
  const dimension_type ysz = y.get_row().size();
  const dimension_type min_sz = std::min(xsz, ysz);
  dimension_type i;
  for (i = 1; i < min_sz; ++i)
    if (const int comp = cmp(x.get_row()[i], y.get_row()[i]))
      // There is at least a different coefficient.
      return (comp > 0) ? 2 : -2;

  // Handle the case where `x' and `y' are of different size.
  if (xsz != ysz) {
    for( ; i < xsz; ++i)
      if (const int sign = sgn(x.get_row()[i]))
        return (sign > 0) ? 2 : -2;
    for( ; i < ysz; ++i)
      if (const int sign = sgn(y.get_row()[i]))
        return (sign < 0) ? 2 : -2;
  }

  // If all the coefficients in `x' equal all the coefficients in `y'
  // (starting from position 1) we compare coefficients in position 0,
  // i.e., inhomogeneous terms.
  if (const int comp = cmp(x.get_row()[0], y.get_row()[0]))
    return (comp > 0) ? 1 : -1;

  // `x' and `y' are equal.
  return 0;
}

bool
PPL::Constraint::is_equivalent_to(const Constraint& y) const {
  const Constraint& x = *this;
  const dimension_type x_space_dim = x.space_dimension();
  if (x_space_dim != y.space_dimension())
    return false;

  const Type x_type = x.type();
  if (x_type != y.type()) {
    // Check for special cases.
    if (x.is_tautological())
      return y.is_tautological();
    else
      return x.is_inconsistent() && y.is_inconsistent();
  }

  if (x_type == STRICT_INEQUALITY) {
    // Due to the presence of epsilon-coefficients, syntactically
    // different strict inequalities may actually encode the same
    // topologically open half-space.
    // First, drop the epsilon-coefficient ...
    Linear_Expression x_expr(x);
    Linear_Expression y_expr(y);
    // ... then, re-normalize ...
    x_expr.get_row().normalize();
    y_expr.get_row().normalize();
    // ... and finally check for syntactic equality.
    for (dimension_type i = x_space_dim + 1; i-- > 0; )
      if (x_expr.get_row()[i] != y_expr.get_row()[i])
	return false;
    return true;
  }

  // `x' and 'y' are of the same type and they are not strict inequalities;
  // thus, the epsilon-coefficient, if present, is zero.
  // It is sufficient to check for syntactic equality.
  for (dimension_type i = x_space_dim + 1; i-- > 0; )
    if (x.get_row()[i] != y.get_row()[i])
      return false;
  return true;
}

bool
PPL::Constraint::is_equal_to(const Constraint& y) const {
  return static_cast<const Linear_Expression&>(*this)
         .is_equal_to(static_cast<const Linear_Row&>(y))
         && flags_ == y.flags_;
}

void
PPL::Constraint::sign_normalize() {
  if (is_line_or_equality()) {
    Constraint& x = *this;
    const dimension_type sz = x.get_row().size();
    // `first_non_zero' indicates the index of the first
    // coefficient of the row different from zero, disregarding
    // the very first coefficient (inhomogeneous term / divisor).
    dimension_type first_non_zero;
    for (first_non_zero = 1; first_non_zero < sz; ++first_non_zero)
      if (x.get_row()[first_non_zero] != 0)
        break;
    if (first_non_zero < sz)
      // If the first non-zero coefficient of the row is negative,
      // we negate the entire row.
      if (x.get_row()[first_non_zero] < 0) {
        for (dimension_type j = first_non_zero; j < sz; ++j)
          neg_assign(x.get_row()[j]);
        // Also negate the first coefficient.
        neg_assign(x.get_row()[0]);
      }
  }
}

bool
PPL::Constraint::check_strong_normalized() const {
  Constraint tmp = *this;
  tmp.strong_normalize();
  return compare(*this, tmp) == 0;
}

const PPL::Constraint* PPL::Constraint::zero_dim_false_p = 0;
const PPL::Constraint* PPL::Constraint::zero_dim_positivity_p = 0;
const PPL::Constraint* PPL::Constraint::epsilon_geq_zero_p = 0;
const PPL::Constraint* PPL::Constraint::epsilon_leq_one_p = 0;

void
PPL::Constraint::initialize() {
  PPL_ASSERT(zero_dim_false_p == 0);
  zero_dim_false_p
    = new Constraint(Linear_Expression::zero() == Coefficient_one());

  PPL_ASSERT(zero_dim_positivity_p == 0);
  zero_dim_positivity_p
    = new Constraint(Linear_Expression::zero() <= Coefficient_one());

  PPL_ASSERT(epsilon_geq_zero_p == 0);
  epsilon_geq_zero_p
    = new Constraint(construct_epsilon_geq_zero());

  PPL_ASSERT(epsilon_leq_one_p == 0);
  epsilon_leq_one_p
    = new Constraint(Linear_Expression::zero() < Coefficient_one());
}

void
PPL::Constraint::finalize() {
  PPL_ASSERT(zero_dim_false_p != 0);
  delete zero_dim_false_p;
  zero_dim_false_p = 0;

  PPL_ASSERT(zero_dim_positivity_p != 0);
  delete zero_dim_positivity_p;
  zero_dim_positivity_p = 0;

  PPL_ASSERT(epsilon_geq_zero_p != 0);
  delete epsilon_geq_zero_p;
  epsilon_geq_zero_p = 0;

  PPL_ASSERT(epsilon_leq_one_p != 0);
  delete epsilon_leq_one_p;
  epsilon_leq_one_p = 0;
}

void
PPL::Constraint::ascii_dump(std::ostream& s) const {
  s << "size " << get_row().size() << " ";
  for (dimension_type j = 0; j < get_row().size(); ++j)
    s << get_row()[j] << ' ';
  switch (type()) {
  case Constraint::EQUALITY:
    s << "=";
    break;
  case Constraint::NONSTRICT_INEQUALITY:
    s << ">=";
    break;
  case Constraint::STRICT_INEQUALITY:
    s << ">";
    break;
  }
  s << " ";
  if (topology() == NECESSARILY_CLOSED)
    s << "(C)";
  else
    s << "(NNC)";

  s << "\n";
}

bool
PPL::Constraint::ascii_load(std::istream& s) {
  std::string str;
  std::string str2;

  if (!(s >> str))
    return false;
  if (str != "size")
    return false;

  dimension_type new_size;
  if (!(s >> new_size))
    return false;

  get_row().resize(new_size);

  for (dimension_type j = 0; j < new_size; ++j)
    if (!(s >> get_row()[j]))
      return false;

  if (!(s >> str))
    return false;
  if (str == "=")
    set_is_equality();
  else if (str == ">=" || str == ">")
    set_is_inequality();
  else
    return false;

  if (!(s >> str2))
    return false;
  if (str2 == "(NNC)") {
    // TODO: Avoid the mark_as_*() methods if possible.
    if (topology() == NECESSARILY_CLOSED)
      mark_as_not_necessarily_closed();
  } else
    if (str2 == "(C)") {
      // TODO: Avoid the mark_as_*() methods if possible.
      if (topology() == NOT_NECESSARILY_CLOSED)
        mark_as_necessarily_closed();
    } else
      return false;

  // Checking for equality of actual and declared types.
  switch (type()) {
  case EQUALITY:
    if (str != "=")
      return false;
    break;
  case NONSTRICT_INEQUALITY:
    if (str != ">=")
      return false;
    break;
  case STRICT_INEQUALITY:
    if (str != ">")
      return false;
    break;
  }

  return true;
}

/*! \relates Parma_Polyhedra_Library::Constraint */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Constraint& c) {
  const dimension_type num_variables = c.space_dimension();
  PPL_DIRTY_TEMP_COEFFICIENT(cv);
  bool first = true;
  for (dimension_type v = 0; v < num_variables; ++v) {
    cv = c.coefficient(Variable(v));
    if (cv != 0) {
      if (!first) {
	if (cv > 0)
	  s << " + ";
	else {
	  s << " - ";
	  neg_assign(cv);
	}
      }
      else
	first = false;
      if (cv == -1)
	s << "-";
      else if (cv != 1)
	s << cv << "*";
      s << PPL::Variable(v);
    }
  }
  if (first)
    s << Coefficient_zero();
  const char* relation_symbol = 0;
  switch (c.type()) {
  case Constraint::EQUALITY:
    relation_symbol = " = ";
    break;
  case Constraint::NONSTRICT_INEQUALITY:
    relation_symbol = " >= ";
    break;
  case Constraint::STRICT_INEQUALITY:
    relation_symbol = " > ";
    break;
  }
  s << relation_symbol << -c.inhomogeneous_term();
  return s;
}

/*! \relates Parma_Polyhedra_Library::Constraint */
std::ostream&
PPL::IO_Operators::operator<<(std::ostream& s, const Constraint::Type& t) {
  const char* n = 0;
  switch (t) {
  case Constraint::EQUALITY:
    n = "EQUALITY";
    break;
  case Constraint::NONSTRICT_INEQUALITY:
    n = "NONSTRICT_INEQUALITY";
    break;
  case Constraint::STRICT_INEQUALITY:
    n = "STRICT_INEQUALITY";
    break;
  }
  s << n;
  return s;
}

PPL_OUTPUT_DEFINITIONS(Constraint)

namespace {

// These are the keywords that indicate the individual assertions.
const char* rpi_valid = "RPI_V";
const char* is_rpi = "RPI";
const char* nnc_valid = "NNC_V";
const char* is_nnc = "NNC";
const char* bit_names[] = {rpi_valid, is_rpi, nnc_valid, is_nnc};

} // namespace

void
PPL::Constraint::Flags::ascii_dump(std::ostream& s) const {
  s << (test_bits(1 << Flags::rpi_validity_bit) ? '+' : '-')
    << rpi_valid << ' '
    << (test_bits(1 << Flags::rpi_bit) ? '+' : '-')
    << is_rpi << ' '
    << ' '
    << (test_bits(1 << Flags::nnc_validity_bit) ? '+' : '-')
    << nnc_valid << ' '
    << (test_bits(1 << Flags::nnc_bit) ? '+' : '-')
    << is_nnc;
}

PPL_OUTPUT_DEFINITIONS_ASCII_ONLY(Constraint::Flags)

bool
PPL::Constraint::Flags::ascii_load(std::istream& s) {
  std::string str;
  // Assume that the bits are used in sequence.
  reset_bits(std::numeric_limits<base_type>::max());
  for (unsigned int bit = 0;
       bit < (sizeof(bit_names) / sizeof(char*));
       ++bit) {
    if (!(s >> str))
      return false;
    if (str[0] == '+')
      set_bits(1 << bit);
    else if (str[0] != '-')
      return false;
    if (str.compare(1, strlen(bit_names[bit]), bit_names[bit]) != 0)
      return false;
  }
  return true;
}

bool
PPL::Constraint::OK() const {
  // Check the underlying Linear_Row object.
  if (!Linear_Row::OK())
    return false;

  // Topology consistency checks.
  const dimension_type min_size = is_necessarily_closed() ? 1 : 2;
  if (get_row().size() < min_size) {
#ifndef NDEBUG
    std::cerr << "Constraint has fewer coefficients than the minimum "
	      << "allowed by its topology:"
	      << std::endl
	      << "size is " << get_row().size()
	      << ", minimum is " << min_size << "."
	      << std::endl;
#endif
    return false;
  }

  if (is_equality() && !is_necessarily_closed()
      && get_row()[get_row().size() - 1] != 0) {
#ifndef NDEBUG
    std::cerr << "Illegal constraint: an equality cannot be strict."
	      << std::endl;
#endif
    return false;
  }

  // Normalization check.
  Constraint tmp = *this;
  tmp.strong_normalize();
  if (tmp != *this) {
#ifndef NDEBUG
    std::cerr << "Constraint is not strongly normalized as it should be."
	      << std::endl;
#endif
    return false;
  }

  // All tests passed.
  return true;
}

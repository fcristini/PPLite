/* Linear_Expression class declaration.
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

#ifndef PPL_Linear_Expression_defs_hh
#define PPL_Linear_Expression_defs_hh 1

#include "Linear_Expression.types.hh"

#include "Linear_Expression_Impl.defs.hh"

#include "Constraint.types.hh"
#include "Generator.types.hh"
#include "Grid_Generator.types.hh"
#include "Congruence.types.hh"
#include "Generator.types.hh"
#include "Constraint.types.hh"
#include "Constraint_System.types.hh"
#include "Coefficient.types.hh"
#include "Polyhedron.types.hh"
#include "Linear_System.types.hh"
#include "Grid.types.hh"

namespace Parma_Polyhedra_Library {
// Put them in the namespace here to declare them friend later.

//! Returns the linear expression \p e1 + \p e2.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p v + \p w.
/*! \relates Linear_Expression */
Linear_Expression
operator+(Variable v, Variable w);

//! Returns the linear expression \p v + \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator+(Variable v, const Linear_Expression& e);

//! Returns the linear expression \p e + \p v.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e, Variable v);

//! Returns the linear expression \p n + \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator+(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the linear expression \p e + \p n.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator+(const Linear_Expression& e);

//! Returns the linear expression - \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e);

//! Returns the linear expression \p e1 - \p e2.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p v - \p w.
/*! \relates Linear_Expression */
Linear_Expression
operator-(Variable v, Variable w);

//! Returns the linear expression \p v - \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator-(Variable v, const Linear_Expression& e);

//! Returns the linear expression \p e - \p v.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e, Variable v);

//! Returns the linear expression \p n - \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator-(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the linear expression \p e - \p n.
/*! \relates Linear_Expression */
Linear_Expression
operator-(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p n * \p e.
/*! \relates Linear_Expression */
Linear_Expression
operator*(Coefficient_traits::const_reference n, const Linear_Expression& e);

//! Returns the linear expression \p e * \p n.
/*! \relates Linear_Expression */
Linear_Expression
operator*(const Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p e1 + \p e2 and assigns it to \p e1.
/*! \relates Linear_Expression */
Linear_Expression&
operator+=(Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p e + \p v and assigns it to \p e.
/*! \relates Linear_Expression
  \exception std::length_error
  Thrown if the space dimension of \p v exceeds
  <CODE>Linear_Expression::max_space_dimension()</CODE>.
 */
Linear_Expression&
operator+=(Linear_Expression& e, Variable v);

//! Returns the linear expression \p e + \p n and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
operator+=(Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p e1 - \p e2 and assigns it to \p e1.
/*! \relates Linear_Expression */
Linear_Expression&
operator-=(Linear_Expression& e1, const Linear_Expression& e2);

//! Returns the linear expression \p e - \p v and assigns it to \p e.
/*! \relates Linear_Expression
  \exception std::length_error
  Thrown if the space dimension of \p v exceeds
  <CODE>Linear_Expression::max_space_dimension()</CODE>.
 */
Linear_Expression&
operator-=(Linear_Expression& e, Variable v);

//! Returns the linear expression \p e - \p n and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
operator-=(Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p n * \p e and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
operator*=(Linear_Expression& e, Coefficient_traits::const_reference n);

//! Returns the linear expression \p n / \p e and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
operator/=(Linear_Expression& e, Coefficient_traits::const_reference n);

void
neg_assign(Linear_Expression& e);

//! Returns the linear expression \p e + \p n * \p v and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
add_mul_assign(Linear_Expression& e,
               Coefficient_traits::const_reference n, Variable v);

//! Sums \p e2 multiplied by \p factor into \p e1.
void add_mul_assign(Linear_Expression& e1,
                    Coefficient_traits::const_reference factor,
                    const Linear_Expression& e2);

//! Subtracts \p e2 multiplied by \p factor from \p e1.
void sub_mul_assign(Linear_Expression& e1,
                    Coefficient_traits::const_reference factor,
                    const Linear_Expression& e2);

//! Returns the linear expression \p e - \p n * \p v and assigns it to \p e.
/*! \relates Linear_Expression */
Linear_Expression&
sub_mul_assign(Linear_Expression& e,
               Coefficient_traits::const_reference n, Variable v);

// TODO: this documentation breaks encapsulation, improve it.
//! Executes <CODE>x[i] -= n*y[i]</CODE> for all \p i in [start,end).
/*! \relates Linear_Expression */
Linear_Expression&
sub_mul_assign(Linear_Expression& x, Coefficient_traits::const_reference n,
               const Linear_Expression& y, dimension_type start, dimension_type end);

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! The basic comparison function.
/*! \relates Linear_Expression
 
  \returns -1 or -2 if x is less than y, 0 if they are equal and 1 or 2 is y
           is greater. The absolute value of the result is 1 if the difference
           is only in the inhomogeneous terms, 2 otherwise

  The order is a lexicographic. It starts comparing the variables' coefficient,
  starting from Variable(0), and at the end it compares the inhomogeneous
  terms.
*/
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
int compare(const Linear_Expression& x, const Linear_Expression& y);

namespace IO_Operators {

//! Output operator.
/*! \relates Parma_Polyhedra_Library::Linear_Expression */
std::ostream& operator<<(std::ostream& s, const Linear_Expression& e);

} // namespace IO_Operators

} // namespace Parma_Polyhedra_Library


namespace std {

//! Specializes <CODE>std::swap</CODE>.
/*! \relates Parma_Polyhedra_Library::Linear_Expression */
void swap(Parma_Polyhedra_Library::Linear_Expression& x,
	  Parma_Polyhedra_Library::Linear_Expression& y);

} // namespace std

//! A linear expression.
/*! \ingroup PPL_CXX_interface
  An object of the class Linear_Expression represents the linear expression
  \f[
    \sum_{i=0}^{n-1} a_i x_i + b
  \f]
  where \f$n\f$ is the dimension of the vector space,
  each \f$a_i\f$ is the integer coefficient
  of the \f$i\f$-th variable \f$x_i\f$
  and \f$b\f$ is the integer for the inhomogeneous term.

  \par How to build a linear expression.

  Linear expressions are the basic blocks for defining
  both constraints (i.e., linear equalities or inequalities)
  and generators (i.e., lines, rays, points and closure points).
  A full set of functions is defined to provide a convenient interface
  for building complex linear expressions starting from simpler ones
  and from objects of the classes Variable and Coefficient:
  available operators include unary negation,
  binary addition and subtraction,
  as well as multiplication by a Coefficient.
  The space dimension of a linear expression is defined as the maximum
  space dimension of the arguments used to build it:
  in particular, the space dimension of a Variable <CODE>x</CODE>
  is defined as <CODE>x.id()+1</CODE>,
  whereas all the objects of the class Coefficient have space dimension zero.

  \par Example
  The following code builds the linear expression \f$4x - 2y - z + 14\f$,
  having space dimension \f$3\f$:
  \code
  Linear_Expression e = 4*x - 2*y - z + 14;
  \endcode
  Another way to build the same linear expression is:
  \code
  Linear_Expression e1 = 4*x;
  Linear_Expression e2 = 2*y;
  Linear_Expression e3 = z;
  Linear_Expression e = Linear_Expression(14);
  e += e1 - e2 - e3;
  \endcode
  Note that \p e1, \p e2 and \p e3 have space dimension 1, 2 and 3,
  respectively; also, in the fourth line of code, \p e is created
  with space dimension zero and then extended to space dimension 3
  in the fifth line.
*/
class Parma_Polyhedra_Library::Linear_Expression {
public:
  //! Default constructor: returns a copy of Linear_Expression::zero().
  Linear_Expression();

  //! Ordinary copy constructor.
  Linear_Expression(const Linear_Expression& e);

  Linear_Expression& operator=(const Linear_Expression& e);

  //! Destructor.
  ~Linear_Expression();

  /*! \brief
    Builds the linear expression corresponding
    to the inhomogeneous term \p n.
  */
  explicit Linear_Expression(Coefficient_traits::const_reference n);

  //! Builds the linear expression corresponding to the variable \p v.
  /*!
    \exception std::length_error
    Thrown if the space dimension of \p v exceeds
    <CODE>Linear_Expression::max_space_dimension()</CODE>.
  */
  Linear_Expression(Variable v);

  //! Builds the linear expression corresponding to constraint \p c.
  /*!
    Given the constraint
    \f$c = \bigl(\sum_{i=0}^{n-1} a_i x_i + b \relsym 0\bigr)\f$,
    where \f$\mathord{\relsym} \in \{ =, \geq, > \}\f$,
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i + b\f$.
    If \p c is an inequality (resp., equality) constraint, then
    the built linear expression is unique up to a positive
    (resp., non-zero) factor.
  */
  explicit Linear_Expression(const Constraint& c);

  /*! \brief
    Builds the linear expression corresponding to generator \p g
    (for points and closure points, the divisor is not copied).

    Given the generator
    \f$g = (\frac{a_0}{d}, \ldots, \frac{a_{n-1}}{d})^\transpose\f$
    (where, for lines and rays, we have \f$d = 1\f$),
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i\f$.
    The inhomogeneous term of the linear expression will always be 0.
    If \p g is a ray, point or closure point (resp., a line), then
    the linear expression is unique up to a positive
    (resp., non-zero) factor.
  */
  explicit Linear_Expression(const Generator& g);

  /*! \brief
    Builds the linear expression corresponding to grid generator \p g
    (for points, parameters and lines the divisor is not copied).

    Given the grid generator
    \f$g = (\frac{a_0}{d}, \ldots, \frac{a_{n-1}}{d})^\transpose\f$
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i\f$.
    The inhomogeneous term of the linear expression is always 0.
  */
  explicit Linear_Expression(const Grid_Generator& g);

  //! Builds the linear expression corresponding to congruence \p cg.
  /*!
    Given the congruence
    \f$cg = \bigl(\sum_{i=0}^{n-1} a_i x_i + b = 0 \pmod{m}\bigr)\f$,
    this builds the linear expression \f$\sum_{i=0}^{n-1} a_i x_i + b\f$.
  */
  explicit Linear_Expression(const Congruence& cg);

  //! Returns the maximum space dimension a Linear_Expression can handle.
  static dimension_type max_space_dimension();

  //! Returns the dimension of the vector space enclosing \p *this.
  dimension_type space_dimension() const;

  //! Sets the dimension of the vector space enclosing \p *this to \p n .
  void set_space_dimension(dimension_type n);

  //! Returns the coefficient of \p v in \p *this.
  Coefficient_traits::const_reference coefficient(Variable v) const;

  //! Sets the coefficient of \p v in \p *this to \p n.
  void set_coefficient(Variable v,
                       Coefficient_traits::const_reference n);

  //! Returns the inhomogeneous term of \p *this.
  Coefficient_traits::const_reference inhomogeneous_term() const;

  //! Sets the inhomogeneous term of \p *this to \p n.
  void set_inhomogeneous_term(Coefficient_traits::const_reference n);

  //! Linearly combines \p *this with \p y so that the coefficient of \p v
  //! is 0.
  /*!
    \param y
    The expression that will be combined with \p *this object;

    \param v
    The variable whose coefficient has to become \f$0\f$.

    Computes a linear combination of \p *this and \p y having
    the coefficient of variable \p v equal to \f$0\f$. Then it assigns
    the resulting expression to \p *this.

    \p *this and \p y must have the same space dimension.
  */
  void linear_combine(const Linear_Expression& y, Variable v);

  //! Equivalent to <CODE>*this = *this * c1 + y * c2</CODE>, but assumes that
  //! \p *this and \p y have the same space dimension.
  void linear_combine(const Linear_Expression& y,
                      Coefficient_traits::const_reference c1,
                      Coefficient_traits::const_reference c2);

  //! Swaps the coefficients of the variables \p v1 and \p v2 .
  void swap_space_dimensions(Variable v1, Variable v2);

  //! Removes all the specified dimensions from the expression.
  /*!
    The space dimension of the variable with the highest space
    dimension in \p vars must be at most the space dimension
    of \p this.
  */
  void remove_space_dimensions(const Variables_Set& vars);

  //! Shift by \p n positions the coefficients of variables, starting from
  //! the coefficient of \p v. This increases the space dimension by \p n.
  void shift_space_dimensions(Variable v, dimension_type n);

  //! Permutes the space dimensions of the expression.
  /*!
    \param cycle
    A vector representing a cycle of the permutation according to which the
    space dimensions must be rearranged.

    The \p cycle vector represents a cycle of a permutation of space
    dimensions.
    For example, the permutation
    \f$ \{ x_1 \mapsto x_2, x_2 \mapsto x_3, x_3 \mapsto x_1 \}\f$ can be
    represented by the vector containing \f$ x_1, x_2, x_3 \f$.
  */
  void permute_space_dimensions(const std::vector<Variable>& cycle);
  
  //! Returns <CODE>true</CODE> if and only if \p *this is \f$0\f$.
  bool is_zero() const;

  /*! \brief
    Returns <CODE>true</CODE> if and only if all the homogeneous
    terms of \p *this are \f$0\f$.
  */
  bool all_homogeneous_terms_are_zero() const;

  //! Initializes the class.
  static void initialize();

  //! Finalizes the class.
  static void finalize();

  //! Returns the (zero-dimension space) constant 0.
  static const Linear_Expression& zero();

  /*! \brief
    Returns a lower bound to the total size in bytes of the memory
    occupied by \p *this.
  */
  memory_size_type total_memory_in_bytes() const;

  //! Returns the size in bytes of the memory managed by \p *this.
  memory_size_type external_memory_in_bytes() const;

  PPL_OUTPUT_DECLARATIONS

  /*! \brief
    Loads from \p s an ASCII representation (as produced by
    ascii_dump(std::ostream&) const) and sets \p *this accordingly.
    Returns <CODE>true</CODE> if successful, <CODE>false</CODE> otherwise.
  */
  bool ascii_load(std::istream& s);

  //! Swaps \p *this with \p y.
  void swap(Linear_Expression& y);

  // TODO: Make this private.
  //! Copy constructor with a specified space dimension.
  Linear_Expression(const Linear_Expression& e, dimension_type sz);

  //! Returns \p true if *this is equal to \p x.
  //! Note that (*this == x) has a completely different meaning.
  bool is_equal_to(const Linear_Expression& x) const;

  //! Normalizes the modulo of the coefficients and of the inhomogeneous term
  //! so that they are mutually prime.
  /*!
    Computes the Greatest Common Divisor (GCD) among the coefficients
    and the inhomogeneous term and normalizes them by the GCD itself.
  */
  void normalize();

  //! Ensures that the first nonzero homogeneous coefficient is positive,
  //! by negating the row if necessary.
  void sign_normalize();

  /*! \brief
    Negates the elements from index \p first (included)
    to index \p last (excluded).
  */
  void negate(dimension_type first, dimension_type last);

  /*! \brief
    Returns <CODE>true</CODE> if the coefficient of each variable in
    \p vars[i] is \f$0\f$.
  */
  bool all_zeroes(const Variables_Set& vars) const;

private:
  /*! \brief
    Holds (between class initialization and finalization) a pointer to
    the (zero-dimension space) constant 0.
  */
  static const Linear_Expression* zero_p;

  Linear_Expression_Impl* impl;

  //! Implementation sizing constructor.
  /*!
    The bool parameter is just to avoid problems with
    the constructor Linear_Expression(Coefficient_traits::const_reference n).
  */
  Linear_Expression(dimension_type sz, bool);

  Coefficient& operator[](dimension_type i);
  const Coefficient& operator[](dimension_type i) const;
  //! Equivalent to the const version of operator[].
  const Coefficient& get(dimension_type i) const;

  /*! \brief
    Returns <CODE>true</CODE> if (*this)[i] is \f$0\f$, for each i in
    [start, end).
  */
  bool all_zeroes(dimension_type start, dimension_type end) const;

  /*! \brief
    Returns the gcd of the nonzero coefficients in [start,end). If all the
    coefficients in this range are 0 returns 0.
  */
  Coefficient gcd(dimension_type start, dimension_type end) const;

  void exact_div_assign(Coefficient_traits::const_reference c,
                        dimension_type start, dimension_type end);
  
  //! Linearly combines \p *this with \p y so that the coefficient of \p v
  //! is 0.
  /*!
    \param y
    The expression that will be combined with \p *this object;

    \param i
    The index of the coefficient that has to become \f$0\f$.

    Computes a linear combination of \p *this and \p y having
    the i-th coefficient equal to \f$0\f$. Then it assigns
    the resulting expression to \p *this.

    \p *this and \p y must have the same space dimension.
  */
  void linear_combine(const Linear_Expression& y, dimension_type i);

  //! Equivalent to <CODE>(*this)[i] = (*this)[i] * c1 + y[i] * c2</CODE>,
  //! for each i in [start, end).
  void linear_combine(const Linear_Expression& y,
                      Coefficient_traits::const_reference c1,
                      Coefficient_traits::const_reference c2,
                      dimension_type start, dimension_type end);

  //! Modify `new_ray' according to the evolution of `x_g' with
  //! respect to `y_g'. This method is a code fragment used by Polyhedron.
  //! Read the method implementation for more details.
  void modify_according_to_evolution(const Linear_Expression& x,
                                     const Linear_Expression& y);

  //! Returns the index of the last nonzero element, or 0 if there are no
  //! nonzero elements.
  dimension_type last_nonzero() const;

  /*! \brief
    Returns <CODE>true</CODE> if each coefficient in [start,end) is *not* in
    \f$0\f$, disregarding coefficients of variables in \p vars.
  */
  bool all_zeroes_except(const Variables_Set& vars, dimension_type start, dimension_type end) const;

  friend class Linear_Expression_Impl;

  // NOTE: The following classes are friends of Linear_Expression in order
  // to access its private methods.
  // Since they are *not* friend of Linear_Expression_Impl, they can only
  // access its public methods so they cannot break the class invariant of
  // Linear_Expression_Impl.
  friend class Grid;
  friend class Congruence;
  friend class Polyhedron;
  friend class PIP_Tree_Node;
  friend class Grid_Generator;
  friend class Generator;
  friend class Constraint;
  friend class Constraint_System;
  template <typename T>
  friend class Linear_System;

  friend Linear_Expression
  operator+(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression
  operator+(Coefficient_traits::const_reference n, const Linear_Expression& e);
  friend Linear_Expression
  operator+(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Linear_Expression
  operator+(Variable v, const Linear_Expression& e);
  friend Linear_Expression
  operator+(Variable v, Variable w);

  friend Linear_Expression
  operator-(const Linear_Expression& e);

  friend Linear_Expression
  operator-(const Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression
  operator-(Variable v, Variable w);
  friend Linear_Expression
  operator-(Coefficient_traits::const_reference n, const Linear_Expression& e);
  friend Linear_Expression
  operator-(const Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Linear_Expression
  operator-(Variable v, const Linear_Expression& e);
  friend Linear_Expression
  operator-(const Linear_Expression& e, Variable v);

  friend Linear_Expression
  operator*(Coefficient_traits::const_reference n, const Linear_Expression& e);
  friend Linear_Expression
  operator*(const Linear_Expression& e, Coefficient_traits::const_reference n);

  friend Linear_Expression&
  operator+=(Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression&
  operator+=(Linear_Expression& e, Variable v);
  friend Linear_Expression&
  operator+=(Linear_Expression& e, Coefficient_traits::const_reference n);

  friend Linear_Expression&
  operator-=(Linear_Expression& e1, const Linear_Expression& e2);
  friend Linear_Expression&
  operator-=(Linear_Expression& e, Variable v);
  friend Linear_Expression&
  operator-=(Linear_Expression& e, Coefficient_traits::const_reference n);

  friend Linear_Expression&
  operator*=(Linear_Expression& e, Coefficient_traits::const_reference n);
  friend Linear_Expression&
  operator/=(Linear_Expression& e, Coefficient_traits::const_reference n);

  friend void
  neg_assign(Linear_Expression& e);

  friend Linear_Expression&
  add_mul_assign(Linear_Expression& e,
                 Coefficient_traits::const_reference n, Variable v);
  friend Linear_Expression&
  sub_mul_assign(Linear_Expression& e,
                 Coefficient_traits::const_reference n, Variable v);

  friend void
  add_mul_assign(Linear_Expression& e1,
                 Coefficient_traits::const_reference factor,
                 const Linear_Expression& e2);
  friend void
  sub_mul_assign(Linear_Expression& e1,
                 Coefficient_traits::const_reference factor,
                 const Linear_Expression& e2);

  friend Linear_Expression&
  sub_mul_assign(Linear_Expression& x, Coefficient_traits::const_reference n,
                 const Linear_Expression& y, dimension_type start, dimension_type end);

  friend int
  compare(const Linear_Expression& x, const Linear_Expression& y);

  friend std::ostream&
  Parma_Polyhedra_Library::IO_Operators
  ::operator<<(std::ostream& s, const Linear_Expression& e);
};

#include "Linear_Expression.inlines.hh"

#endif // !defined(PPL_Linear_Expression_defs_hh)

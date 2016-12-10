/* Copyright (C) 2001-2010 Roberto Bagnara <bagnara@cs.unipr.it>
   Copyright (C) 2010-2016 BUGSENG srl (http://bugseng.com)

This file is free software; as a special exception the author gives
unlimited permission to copy and/or distribute it, with or without
modifications, as long as this notice is preserved.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. */

#ifndef PPL_FLINT_Integer_types_hh
#define PPL_FLINT_Integer_types_hh 1

#include "Coefficient_traits_template.hh"
//#include "mp_std_bits_defs.hh"
#include <fmpz_class.hh>

namespace Parma_Polyhedra_Library {

/*! \class Parma_Polyhedra_Library::FLINT_Integer
  \brief
  Unbounded integers as provided by the GMP library.

  \ingroup PPL_CXX_interface
  FLINT_Integer is an alias for the <CODE>mpz_class</CODE> type
  defined in the C++ interface of the GMP library.
  For more information, see <CODE>http://gmplib.org/</CODE>
*/
typedef fmpz_class FLINT_Integer;

#ifdef PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS
//! Coefficient traits specialization for unbounded integers.
/*! \ingroup PPL_CXX_interface */
#endif // defined(PPL_DOXYGEN_INCLUDE_IMPLEMENTATION_DETAILS)
template <>
struct Coefficient_traits_template<FLINT_Integer> {
  //! The type used for references to const unbounded integers.
  typedef const FLINT_Integer& const_reference;
};

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_FLINT_Integer_types_hh)

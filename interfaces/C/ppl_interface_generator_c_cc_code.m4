dnl  -*- C++ -*-
m4_divert(-1)

dnl This m4 file contains the code for generating ppl_c.cc.

dnl Copyright (C) 2001-2008 Roberto Bagnara <bagnara@cs.unipr.it>
dnl
dnl This file is part of the Parma Polyhedra Library (PPL).
dnl
dnl The PPL is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation; either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl The PPL is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
dnl
dnl For the most up-to-date information see the Parma Polyhedra Library
dnl site: http://www.cs.unipr.it/ppl/ .

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_space_dimension
(ppl_@CLASS@_t* pph,
 ppl_dimension_type d,
 int empty) try {
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(d, empty ? EMPTY : UNIVERSE));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_@FRIEND@
(ppl_@CLASS@_t* pph,
 ppl_const_@ALT_FRIEND@_t ph) try {
  const @CPPX_FRIEND@& phh
    = *static_cast<const @CPPX_FRIEND@*>(to_const(ph));
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(phh));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@BUILD_REPRESENT@s_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_@UBUILD_REPRESENT@_System
(ppl_@CLASS@_t* pph, ppl_const_@UBUILD_REPRESENT@_System_t cs) try {
  const @UBUILD_REPRESENT@_System& ccs = *to_const(cs);
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(ccs));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_recycle_@BUILD_REPRESENT@s_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_recycle_@UBUILD_REPRESENT@_System
(ppl_@CLASS@_t* pph, ppl_@UBUILD_REPRESENT@_System_t cs) try {
  @UBUILD_REPRESENT@_System& ccs = *to_nonconst(cs);
  *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(ccs@RECYCLE@));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_new_@TOPOLOGY@@CLASS@_from_@BOX@_code',
`int
ppl_new_@TOPOLOGY@@CLASS@_from_@BOX@
(ppl_@CLASS@_t* pph,
 ppl_dimension_type (*space_dimension)(void),
 int (*is_empty)(void),
 int (*get_lower_bound)(ppl_dimension_type k, int closed,
			ppl_Coefficient_t n,
			ppl_Coefficient_t d),
 int (*get_upper_bound)(ppl_dimension_type k, int closed,
			ppl_Coefficient_t n,
			ppl_Coefficient_t d)) try {
  dimension_type space_dim = space_dimension();
  if (is_empty())
    *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(space_dim, EMPTY));
  else {
    *pph = to_nonconst(new @TOPOLOGY@@CPP_CLASS@(space_dim, UNIVERSE));
    // Initialization is just to avoid compilation warnings.
    bool closed = false;
    TEMP_INTEGER(n);
    TEMP_INTEGER(d);
    for (dimension_type k = space_dim; k-- > 0; ) {
      if (get_lower_bound(k, closed, to_nonconst(&n), to_nonconst(&d))) {
        if (closed)
          to_nonconst(*pph)->add_constraint(d*Variable(k) >= n);
        else
          to_nonconst(*pph)->add_constraint(d*Variable(k) > n);
      }
      if (get_upper_bound(k, closed, to_nonconst(&n), to_nonconst(&d))) {
        if (closed)
          to_nonconst(*pph)->add_constraint(d*Variable(k) <= n);
        else
          to_nonconst(*pph)->add_constraint(d*Variable(k) < n);
      }
    }
  }
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_delete_@CLASS@_code',
`int
ppl_delete_@CLASS@(ppl_const_@CLASS@_t ph) try {
  delete to_const(ph);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_assign_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@_code',
`int
ppl_assign_@TOPOLOGY@@CLASS@_from_@TOPOLOGY@@CLASS@
(ppl_@CLASS@_t dst,
 ppl_const_@CLASS@_t src) try {
  const @TOPOLOGY@@CPP_CLASS@& ssrc
    = *static_cast<const @TOPOLOGY@@CPP_CLASS@*>(to_const(src));
  @TOPOLOGY@@CPP_CLASS@& ddst
    = *static_cast<@TOPOLOGY@@CPP_CLASS@*>(to_nonconst(dst));
  ddst = ssrc;
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@DIMENSION@_code',
`int
ppl_@CLASS@_@DIMENSION@
(ppl_const_@CLASS@_t ph,
 ppl_dimension_type* m) try {
  *m = to_const(ph)->@DIMENSION@();
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@GET_REPRESENT@s_code',
`int
ppl_@CLASS@_@GET_REPRESENT@s
(ppl_const_@CLASS@_t ph,
 ppl_const_@UGET_REPRESENT@_System_t* pcs) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const @UGET_REPRESENT@_System& cs = pph.@GET_REPRESENT@s();
  *pcs = to_const(&cs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_minimized_@GET_REPRESENT@s_code',
`int
ppl_@CLASS@_minimized_@GET_REPRESENT@s
(ppl_const_@CLASS@_t ph,
 ppl_const_@UGET_REPRESENT@_System_t* pcs) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const @UGET_REPRESENT@_System& cs = pph.minimized_@GET_REPRESENT@s();
  *pcs = to_const(&cs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_relation_with_@RELATION_REPRESENT@_code',
`int
ppl_@CLASS@_relation_with_@URELATION_REPRESENT@
(ppl_const_@CLASS@_t ph,
 ppl_const_@URELATION_REPRESENT@_t c) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const @URELATION_REPRESENT@& cc = *to_const(c);
  return pph.relation_with(cc).get_flags();
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@HAS_PROPERTY@_code',
`int
ppl_@CLASS@_@HAS_PROPERTY@(ppl_const_@CLASS@_t ph) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  return pph.@HAS_PROPERTY@() ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounds_from_@ABOVEBELOW@_code',
`int
ppl_@CLASS@_bounds_from_@ABOVEBELOW@
(ppl_const_@CLASS@_t ph,
 ppl_const_Linear_Expression_t le) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const Linear_Expression& lle = *to_const(le);
  return pph.bounds_from_@ABOVEBELOW@(lle) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@MAXMIN@_code',
`int
ppl_@CLASS@_@MAXMIN@
(ppl_const_@CLASS@_t ph,
 ppl_const_Linear_Expression_t le,
 ppl_Coefficient_t sup_n,
 ppl_Coefficient_t sup_d,
 int* poptimum,
 ppl_Generator_t point) try {
  const @CPP_CLASS@& pph = *to_const(ph);
  const Linear_Expression& lle = *to_const(le);
  Coefficient& ssup_n = *to_nonconst(sup_n);
  Coefficient& ssup_d = *to_nonconst(sup_d);
  Generator& ppoint = *to_nonconst(point);
  bool optimum;
  bool ok = pph.@MAXMIN@(lle, ssup_n, ssup_d, optimum, ppoint);
  if (ok)
    *poptimum = optimum ? 1 : 0;
  return ok ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@COMPARISON@_@CLASS@_code',
`int
ppl_@CLASS@_@COMPARISON@_@CLASS@
(ppl_const_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  const @CPP_CLASS@& xx = *to_const(x);
  const @CPP_CLASS@& yy = *to_const(y);
  return xx.@COMPARISON@(yy) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_equals_@CLASS@_code',
`int
ppl_@CLASS@_equals_@CLASS@
(ppl_const_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  const @CPP_CLASS@& xx = *to_const(x);
  const @CPP_CLASS@& yy = *to_const(y);
  return (xx == yy) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_OK_code',
`int
ppl_@CLASS@_OK(ppl_const_@CLASS@_t ph) try {
  return to_const(ph)->OK() ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@SIMPLIFY@_code',
`int
ppl_@CLASS@_@SIMPLIFY@(ppl_@CLASS@_t ph) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.@SIMPLIFY@();
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@BINOP@_code',
`int
ppl_@CLASS@_@BINOP@
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  xx.@BINOP@(yy);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@BINMINOP@_code',
`int
ppl_@CLASS@_@BINMINOP@
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  return xx.@BINMINOP@(yy) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_t c) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@& cc = *to_const(c);
  pph.add_@ADD_REPRESENT@(cc);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@_and_minimize_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@_and_minimize
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_t c) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@& cc = *to_const(c);
  return pph.add_@ADD_REPRESENT@_and_minimize(cc) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@s_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@s
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@_System& ccs = *to_const(cs);
  pph.add_@ADD_REPRESENT@s(ccs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_@ADD_REPRESENT@s_and_minimize_code',
`int
ppl_@CLASS@_add_@ADD_REPRESENT@s_and_minimize
(ppl_@CLASS@_t ph,
 ppl_const_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const @UADD_REPRESENT@_System& ccs = *to_const(cs);
  return pph.add_@ADD_REPRESENT@s_and_minimize(ccs) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s_code',
`int
ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s
(ppl_@CLASS@_t ph,
 ppl_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  @UADD_REPRESENT@_System& ccs = *to_nonconst(cs);
  pph.add_recycled_@ADD_REPRESENT@s(ccs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s_and_minimize_code',
`int
ppl_@CLASS@_add_recycled_@ADD_REPRESENT@s_and_minimize
(ppl_@CLASS@_t ph,
 ppl_@UADD_REPRESENT@_System_t cs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  @UADD_REPRESENT@_System& ccs = *to_nonconst(cs);
  return pph.add_recycled_@ADD_REPRESENT@s_and_minimize(ccs) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@AFFIMAGE@_code',
`int
ppl_@CLASS@_@AFFIMAGE@
(ppl_@CLASS@_t ph,
 ppl_dimension_type var,
 ppl_const_Linear_Expression_t le,
 ppl_const_Coefficient_t d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& lle = *to_const(le);
  const Coefficient& dd = *to_const(d);
  pph.@AFFIMAGE@(Variable(var), lle, dd);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounded_@AFFIMAGE@_code',
`int
ppl_@CLASS@_bounded_@AFFIMAGE@
(ppl_@CLASS@_t ph,
 ppl_dimension_type var,
 ppl_const_Linear_Expression_t lb,
 ppl_const_Linear_Expression_t ub,
 ppl_const_Coefficient_t d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& llb = *to_const(lb);
  const Linear_Expression& uub = *to_const(ub);
  const Coefficient& dd = *to_const(d);
  pph.bounded_@AFFIMAGE@(Variable(var), llb, uub, dd);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_code',
`int
ppl_@CLASS@_generalized_@AFFIMAGE@
(ppl_@CLASS@_t ph,
 ppl_dimension_type var,
 enum ppl_enum_Constraint_Type relsym,
 ppl_const_Linear_Expression_t le,
 ppl_const_Coefficient_t d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& lle = *to_const(le);
  const Coefficient& dd = *to_const(d);
  pph.generalized_@AFFIMAGE@
    (Variable(var), relation_symbol(relsym), lle, dd);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_code',
`int
ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs
(ppl_@CLASS@_t ph,
 ppl_const_Linear_Expression_t lhs,
 enum ppl_enum_Constraint_Type relsym,
 ppl_const_Linear_Expression_t rhs) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& llhs = *to_const(lhs);
  const Linear_Expression& rrhs = *to_const(rhs);
  pph.generalized_@AFFIMAGE@(llhs, relation_symbol(relsym), rrhs);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_with_congruence_code',
`int
ppl_@CLASS@_generalized_@AFFIMAGE@_with_congruence
(ppl_@CLASS@_t ph,
 ppl_dimension_type var,
 enum ppl_enum_Constraint_Type relsym,
 ppl_const_Linear_Expression_t le,
 ppl_const_Coefficient_t d,
 ppl_const_Coefficient_t m) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& lle = *to_const(le);
  const Coefficient& dd = *to_const(d);
  const Coefficient& mm = *to_const(m);
  pph.generalized_@AFFIMAGE@
    (Variable(var), relation_symbol(relsym), lle, dd, mm);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_with_congruence_code',
`int
ppl_@CLASS@_generalized_@AFFIMAGE@_lhs_rhs_with_congruence
(ppl_@CLASS@_t ph,
 ppl_const_Linear_Expression_t lhs,
 enum ppl_enum_Constraint_Type relsym,
 ppl_const_Linear_Expression_t rhs,
 ppl_const_Coefficient_t m) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  const Linear_Expression& llhs = *to_const(lhs);
  const Linear_Expression& rrhs = *to_const(rhs);
  const Coefficient& mm = *to_const(m);
  pph.generalized_@AFFIMAGE@(llhs, relation_symbol(relsym), rrhs, mm);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens_code',
`int
ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 unsigned* tp) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  xx.@WIDEN@_widening_assign(yy, tp);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@WIDEN@_widening_assign_code',
`int
ppl_@CLASS@_@WIDEN@_widening_assign
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y) try {
  return ppl_@CLASS@_@WIDEN@_widening_assign_with_tokens(x, y, 0);
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_with_tokens_code',
`int
ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_with_tokens
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs,
 unsigned* tp) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  const @UCONSTRAINER@_System& ccs = *to_const(cs);
  xx.@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign(yy, ccs, tp);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_code',
`int
ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs) try {
  return
    ppl_@CLASS@_@LIMITEDBOUNDED@_@WIDENEXPN@_extrapolation_assign_with_tokens
      (x, y, cs, 0);
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_with_tokens_code',
`int
ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_with_tokens
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs,
 unsigned* tp) try {
  @CPP_CLASS@& xx = *to_nonconst(x);
  const @CPP_CLASS@& yy = *to_const(y);
  const @UCONSTRAINER@_System& ccs = *to_const(cs);
  xx.bounded_@WIDENEXPN@_extrapolation_assign(yy, ccs, tp);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_code',
`int
ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign
(ppl_@CLASS@_t x,
 ppl_const_@CLASS@_t y,
 ppl_const_@UCONSTRAINER@_System_t cs) try {
  return
    ppl_@CLASS@_bounded_@WIDENEXPN@_extrapolation_assign_with_tokens
      (x, y, cs, 0);
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_space_dimensions_@EMBEDPROJECT@_code',
`int
ppl_@CLASS@_add_space_dimensions_@EMBEDPROJECT@
(ppl_@CLASS@_t ph,
 ppl_dimension_type d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.add_space_dimensions_@EMBEDPROJECT@(d);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_remove_space_dimensions_code',
`int
ppl_@CLASS@_remove_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type ds[],
 size_t n) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  Variables_Set to_be_removed;
  for (ppl_dimension_type i = n; i-- > 0; )
    to_be_removed.insert(ds[i]);
  pph.remove_space_dimensions(to_be_removed);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_remove_higher_space_dimensions_code',
`int
ppl_@CLASS@_remove_higher_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.remove_higher_space_dimensions(d);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_map_space_dimensions_code',
`int
ppl_@CLASS@_map_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type maps[],
 size_t n) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  PIFunc pifunc(maps, n);
  pph.map_space_dimensions(pifunc);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_expand_space_dimension_code',
`int
ppl_@CLASS@_expand_space_dimension
(ppl_@CLASS@_t ph,
 ppl_dimension_type d,
 ppl_dimension_type m) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  pph.expand_space_dimension(Variable(d), m);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_fold_space_dimensions_code',
`int
ppl_@CLASS@_fold_space_dimensions
(ppl_@CLASS@_t ph,
 ppl_dimension_type ds[],
 size_t n,
 ppl_dimension_type d) try {
  @CPP_CLASS@& pph = *to_nonconst(ph);
  Variables_Set to_be_folded;
  for (ppl_dimension_type i = n; i-- > 0; )
    to_be_folded.insert(ds[i]);
  pph.fold_space_dimensions(to_be_folded, Variable(d));
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@MEMBYTES@_code',
`int
ppl_@CLASS@_@MEMBYTES@
(ppl_const_@CLASS@_t ps,
 size_t* sz) try {
  *sz = to_const(ps)->@MEMBYTES@();
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_iterator_equals_iterator_code',
`dnl

typedef @CPP_CLASS@::iterator
        @CLASS@_iterator;
typedef @CPP_CLASS@::const_iterator
        @CLASS@_const_iterator;

DECLARE_CONVERSIONS(@CLASS@_iterator,
                    @CLASS@_iterator)
DECLARE_CONVERSIONS(@CLASS@_const_iterator,
                    @CLASS@_const_iterator)


int
ppl_@CLASS@_iterator_equal_test
(ppl_const_@CLASS@_iterator_t x,
 ppl_const_@CLASS@_iterator_t y) try {
  return (*to_const(x) == *to_const(y)) ? 1 : 0;
}
CATCH_ALL

int
ppl_@CLASS@_const_iterator_equal_test
(ppl_const_@CLASS@_const_iterator_t x,
 ppl_const_@CLASS@_const_iterator_t y) try {
  return (*to_const(x) == *to_const(y)) ? 1 : 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@BEGINEND@_iterator_code',
`dnl
int
ppl_@CLASS@_@BEGINEND@
(ppl_@CLASS@_t ps,
 ppl_@CLASS@_iterator_t psit) try {
  @CPP_CLASS@::iterator& ppsit = *to_nonconst(psit);
  ppsit = to_nonconst(ps)->@BEGINEND@();
  return 0;
}
CATCH_ALL

int
ppl_@CLASS@_const_@BEGINEND@
(ppl_const_@CLASS@_t ps,
 ppl_@CLASS@_const_iterator_t psit) try {
  @CPP_CLASS@::const_iterator& ppsit = *to_nonconst(psit);
  ppsit = to_const(ps)->@BEGINEND@();
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_delete_iterator_code',
`dnl
int
ppl_delete_@CLASS@_iterator
(ppl_const_@CLASS@_iterator_t it)
  try {
  delete to_const(it);
  return 0;
}
CATCH_ALL

int
ppl_delete_@CLASS@_const_iterator
(ppl_const_@CLASS@_const_iterator_t it)
  try {
  delete to_const(it);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_@INCDEC@_iterator_code',
`dnl
int
ppl_@CLASS@_iterator_@INCDEC@
(ppl_@CLASS@_iterator_t it)
  try {
    @CPP_CLASS@::iterator& iit = *to_nonconst(it);
    @CPPX_INCDEC@iit;
    return 0;
}
CATCH_ALL

int
ppl_@CLASS@_const_iterator_@INCDEC@
(ppl_@CLASS@_const_iterator_t it)
  try {
    @CPP_CLASS@::const_iterator& iit = *to_nonconst(it);
    @CPPX_INCDEC@iit;
    return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_drop_disjunct_code',
`dnl
int
ppl_@CLASS@_drop_disjunct
(ppl_@CLASS@_t ps,
 ppl_const_@CLASS@_iterator_t cit,
 ppl_@CLASS@_iterator_t it) try {
  @CPP_CLASS@& pps = *to_nonconst(ps);
  const @CPP_CLASS@::iterator& ccit = *to_const(cit);
  @CPP_CLASS@::iterator& iit = *to_nonconst(it);
  iit = pps.drop_disjunct(ccit);
  return 0;
}
CATCH_ALL

int
ppl_@CLASS@_drop_disjuncts
(ppl_@CLASS@_t ps,
 ppl_const_@CLASS@_iterator_t first,
 ppl_const_@CLASS@_iterator_t last) try {
  @CPP_CLASS@& pps = *to_nonconst(ps);
  const @CPP_CLASS@::iterator& ffirst = *to_const(first);
  const @CPP_CLASS@::iterator& llast = *to_const(last);
  pps.drop_disjuncts(ffirst, llast);
  return 0;
}
CATCH_ALL

')

m4_define(`ppl_@CLASS@_add_disjunct_code',
`dnl
int
ppl_@CLASS@_add_disjunct
(ppl_@CLASS@_t ps,
 ppl_const_@DISJUNCT@_t d) try {
  @CPP_CLASS@& pps = *to_nonconst(ps);
  const @CLASSTOPOLOGY@@CPP_DISJUNCT@& dd
     = *static_cast<const @CLASSTOPOLOGY@@CPP_DISJUNCT@*>(to_const(d));
  pps.add_disjunct(dd);
  return 0;
}
CATCH_ALL

')

m4_divert`'dnl

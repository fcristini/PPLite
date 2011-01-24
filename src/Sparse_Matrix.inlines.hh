/* Sparse_Matrix class implementation: inline functions.
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

#ifndef PPL_Sparse_Matrix_inlines_hh
#define PPL_Sparse_Matrix_inlines_hh 1

namespace Parma_Polyhedra_Library {

inline dimension_type
Sparse_Matrix::max_num_rows() {
  return std::vector<Sparse_Row>().max_size();
}

inline dimension_type
Sparse_Matrix::max_num_columns() {
  return Sparse_Row::max_size();
}

inline void
Sparse_Matrix::swap(Sparse_Matrix& x) {
  std::swap(rows, x.rows);
  std::swap(num_columns_, x.num_columns_);
}

inline dimension_type
Sparse_Matrix::num_rows() const {
  return rows.size();
}

inline dimension_type
Sparse_Matrix::num_columns() const {
  return num_columns_;
}

inline bool
Sparse_Matrix::has_no_rows() const {
  return num_rows() == 0;
}

inline void
Sparse_Matrix::resize(dimension_type n, Flags row_flags) {
  resize(n, n, row_flags);
}

inline void
Sparse_Matrix::resize_no_copy(dimension_type new_n_rows,
                              dimension_type new_n_columns,
                              Flags row_flags) {
  clear();
  resize(new_n_rows, new_n_columns, row_flags);
}

inline void
Sparse_Matrix::add_zero_rows_and_columns(dimension_type n,
                                         dimension_type m,
                                         Flags row_flags) {
  resize(num_rows() + n, num_columns() + m, row_flags);
}

inline void
Sparse_Matrix::add_zero_rows(dimension_type n, Flags row_flags) {
  resize(num_rows() + n, num_columns(), row_flags);
}

inline void
Sparse_Matrix::add_row(const Sparse_Row& x) {
  Sparse_Row row(x);
  add_zero_rows(1, Flags());
  // Now x may have been invalidated, if it was a row of this matrix.
  rows.back().swap(row);
  PPL_ASSERT(OK());
}

inline void
Sparse_Matrix::add_recycled_row(Sparse_Row& x) {
  add_zero_rows(1, Flags());
  rows.back().swap(x);
  PPL_ASSERT(OK());
}

inline void
Sparse_Matrix::remove_trailing_rows(dimension_type n) {
  resize(num_rows() - n, num_columns());
}

inline void
Sparse_Matrix::add_zero_columns(dimension_type n) {
  resize(num_rows(), num_columns() + n);
}

inline void
Sparse_Matrix::remove_trailing_columns(dimension_type n) {
  PPL_ASSERT(n <= num_columns());
  resize(num_rows(), num_columns() - n);
}

inline void
Sparse_Matrix::clear() {
  resize(0, 0);
}

inline Sparse_Matrix::iterator
Sparse_Matrix::begin() {
  return rows.begin();
}

inline Sparse_Matrix::iterator
Sparse_Matrix::end() {
  return rows.end();
}

inline Sparse_Matrix::const_iterator
Sparse_Matrix::begin() const {
  return rows.begin();
}

inline Sparse_Matrix::const_iterator
Sparse_Matrix::end() const {
  return rows.end();
}

inline Sparse_Row&
Sparse_Matrix::operator[](dimension_type i) {
  PPL_ASSERT(i < rows.size());
  return rows[i];
}

inline const Sparse_Row&
Sparse_Matrix::operator[](dimension_type i) const {
  PPL_ASSERT(i < rows.size());
  return rows[i];
}

inline memory_size_type
Sparse_Matrix::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

} // namespace Parma_Polyhedra_Library

namespace std {

inline void
swap(Parma_Polyhedra_Library::Sparse_Matrix& x,
     Parma_Polyhedra_Library::Sparse_Matrix& y) {
  x.swap(y);
}

} // namespace std

#endif // !defined(PPL_Sparse_Matrix_inlines_hh)

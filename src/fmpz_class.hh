
#ifndef PPL_fmpz_class_hh
#define PPL_fmpz_class_hh 1

#include "flint/flint.h"
#include "flint/fmpz.h"

/* Test for gcc >= maj.min, as per __GNUC_PREREQ in glibc */
#if defined (__GNUC__) && defined (__GNUC_MINOR__)
#define __PPLFlintXX_GNUC_PREREQ(maj, min) \
  ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define __PPLFlintXX_GNUC_PREREQ(maj, min)  0
#endif

// wrapper for gcc's __builtin_constant_p
// __builtin_constant_p has been in gcc since forever,
// but g++-3.4 miscompiles it.
#if __PPLFlintXX_GNUC_PREREQ(4, 2)
#define __PPLFlintXX_CONSTANT(X) __builtin_constant_p(X)
#else
#define __PPLFlintXX_CONSTANT(X) false
#endif
#define __PPLFlintXX_CONSTANT_TRUE(X) (__PPLFlintXX_CONSTANT(X) && (X))

// Use C++11 features
#if __cplusplus >= 201103L
#define __PPLFlintXX_USE_CXX11 1
#else
#define __PPLFlintXX_USE_CXX11 0
#endif

#define __PPLFlintXX_NOTHROW 1

#if __PPLFlintXX_USE_CXX11
#define __PPLFlintXX_NOEXCEPT noexcept
#include <type_traits> // for common_type
#else
#define __PPLFlintXX_NOEXCEPT
#endif

// macro per dichiarazione operatori tra tipi interi C++ e tipo intero flint
#define __PPLFlintXXP_DECLARE_COMPOUND_OPERATOR(fun)                         \
  template <class T, class U>                                         \
  __flint_expr<value_type, value_type> & fun(const __flint_expr<T, U> &);

#define __PPLFlintXXN_DECLARE_COMPOUND_OPERATOR(fun) \
  __flint_expr & fun(signed char);              \
  __flint_expr & fun(unsigned char);            \
  __flint_expr & fun(signed int);               \
  __flint_expr & fun(unsigned int);             \
  __flint_expr & fun(signed short int);         \
  __flint_expr & fun(unsigned short int);       \
  __flint_expr & fun(signed long int);          \
  __flint_expr & fun(unsigned long int);        \
  __flint_expr & fun(float);                    \
  __flint_expr & fun(double);                   \
  /* __flint_expr & fun(long double); */

#define __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(fun) \
__PPLFlintXXP_DECLARE_COMPOUND_OPERATOR(fun)        \
__PPLFlintXXN_DECLARE_COMPOUND_OPERATOR(fun)

#define __PPLFlintXX_DECLARE_COMPOUND_OPERATOR_UI(fun) \
  __flint_expr & fun(mp_bitcnt_t);

#define __PPLFlintXX_DECLARE_INCREMENT_OPERATOR(fun) \
  inline __flint_expr & fun();                  \
  inline __flint_expr fun(int);

// costruttore da tipo di intero C++ a tipo intero flint
#define __PPLFlintXX_DEFINE_ARITHMETIC_CONSTRUCTORS		\
  __flint_expr(signed char c) { init_si(c); }		\
  __flint_expr(unsigned char c) { init_ui(c); }		\
  __flint_expr(signed int i) { init_si(i); }		\
  __flint_expr(unsigned int i) { init_ui(i); }		\
  __flint_expr(signed short int s) { init_si(s); }	\
  __flint_expr(unsigned short int s) { init_ui(s); }	\
  __flint_expr(signed long int l) { init_si(l); }		\
  __flint_expr(unsigned long int l) { init_ui(l); }	\
  __flint_expr(float f) { init_d(f); }			\
  __flint_expr(double d) { init_d(d); }

// assegnamento da tipo intero C++ a tipo intero flint
#define __PPLFlintXX_DEFINE_ARITHMETIC_ASSIGNMENTS		\
  __flint_expr & operator=(signed char c) { assign_si(c); return *this; } \
  __flint_expr & operator=(unsigned char c) { assign_ui(c); return *this; } \
  __flint_expr & operator=(signed int i) { assign_si(i); return *this; } \
  __flint_expr & operator=(unsigned int i) { assign_ui(i); return *this; } \
  __flint_expr & operator=(signed short int s) { assign_si(s); return *this; } \
  __flint_expr & operator=(unsigned short int s) { assign_ui(s); return *this; } \
  __flint_expr & operator=(signed long int l) { assign_si(l); return *this; } \
  __flint_expr & operator=(unsigned long int l) { assign_ui(l); return *this; } \
  __flint_expr & operator=(float f) { assign_d(f); return *this; } \
  __flint_expr & operator=(double d) { assign_d(d); return *this; }

// general expression template class
template <class T, class U>
class __flint_expr;

/**************** fmpz_class -- wrapper for fmpz_t ****************/

template <>
class __flint_expr<fmpz_t, fmpz_t>
{
private:
  typedef fmpz_t value_type;
  value_type mp;

  // Helper functions used for all arithmetic types
  void assign_ui(unsigned long l)
  {
    ///OLD if (__PPLFlintXX_CONSTANT_TRUE(l == 0))
    ///OLD   mp->_mp_size = 0;
    ///OLD else
      fmpz_set_ui(mp, l);
  }
  void assign_si(signed long l)
  {
    if (__PPLFlintXX_CONSTANT_TRUE(l >= 0))
      assign_ui(l);
    else if (__PPLFlintXX_CONSTANT_TRUE(l <= 0))
      {
	assign_ui(-static_cast<unsigned long>(l));
	fmpz_neg(mp, mp);
      }
    else
      fmpz_set_si(mp, l);
  }
  void assign_d (double d)
  {
    fmpz_set_d (mp, d);
  }

  void init_ui(unsigned long l)
  {
    if (__PPLFlintXX_CONSTANT_TRUE(l == 0)) {
      fmpz_init(mp);
    }
    else {
      fmpz_init(mp);
      fmpz_set_ui(mp, l);
    }
  }
  void init_si(signed long l)
  {
    if (__PPLFlintXX_CONSTANT_TRUE(l >= 0)){
      init_ui(l);
    }
    else if (__PPLFlintXX_CONSTANT_TRUE(l <= 0)) {
      init_ui(-static_cast<unsigned long>(l));
      fmpz_neg(mp, mp);
    }
    else {
      fmpz_init(mp);
      fmpz_set_si(mp, l);
    }
  }
  void init_d (double d)
  {
    fmpz_init(mp);
    fmpz_set_d (mp, d);
  }

public:
  mp_bitcnt_t get_prec() const { return mpf_get_default_prec(); }

  // constructors and destructor
  __flint_expr() { fmpz_init(mp); }

  __flint_expr(const __flint_expr &z) { 
    fmpz_init(mp); 
    fmpz_set(mp, z.mp); 
  }
#if __PPLFlintXX_USE_CXX11
  __flint_expr(__flint_expr &&z)
  { *mp = *z.mp; fmpz_init(z.mp); }
#endif
  template <class T>
  __flint_expr(const __flint_expr<fmpz_t, T> &expr)
  { fmpz_init(mp); __flint_set_expr(mp, expr); }
  template <class T, class U>
  explicit __flint_expr(const __flint_expr<T, U> &expr)
  { fmpz_init(mp); __flint_set_expr(mp, expr); }

  __PPLFlintXX_DEFINE_ARITHMETIC_CONSTRUCTORS

  explicit __flint_expr(const char *s, int base = 0)
  #if __PPLFlintXX_NOTHROW == 0
    __PPLFlintXX_NOEXCEPT
  #endif
  {
    fmpz_init (mp);
    #if __PPLFlintXX_NOTHROW == 0
      if (fmpz_set_str (mp, s, base) != 0) {
        fmpz_clear (mp);
        throw std::invalid_argument ("fmpz_set_str");
      }
    #else
      fmpz_set_str (mp, s, base);
    #endif
  }
  explicit __flint_expr(const std::string &s, int base = 0)
  #if __PPLFlintXX_NOTHROW == 0
    __PPLFlintXX_NOEXCEPT
  #endif
  {
    fmpz_init (mp);
    #if __PPLFlintXX_NOTHROW == 0
      if (fmpz_set_str(mp, s.c_str(), base) != 0)
        {
          fmpz_clear (mp);
          throw std::invalid_argument ("fmpz_set_str");
        }
    #else
      fmpz_set_str(mp, s.c_str(), base);
    #endif
  }

  //OLD explicit __flint_expr(fmpz_srcptr z) { fmpz_init_set(mp, z); }
  ///explicit __flint_expr(fmpz z) {
  ///  fmpz_init(mp);
  ///  fmpz_set(mp, z);
  ///}

  ~__flint_expr() { fmpz_clear(mp); }

  void swap(__flint_expr& z) __PPLFlintXX_NOEXCEPT { std::swap(*mp, *z.mp); }

  // assignment operators
  __flint_expr & operator=(const __flint_expr &z)
  { fmpz_set(mp, z.mp); return *this; }
#if __PPLFlintXX_USE_CXX11
  __flint_expr & operator=(__flint_expr &&z) noexcept
  { swap(z); return *this; }
#endif
  template <class T, class U>
  __flint_expr<value_type, value_type> & operator=(const __flint_expr<T, U> &expr)
  { __flint_set_expr(mp, expr); return *this; }

  __PPLFlintXX_DEFINE_ARITHMETIC_ASSIGNMENTS

  __flint_expr & operator=(const char *s) 
  #if __PPLFlintXX_NOTHROW == 0
    __PPLFlintXX_NOEXCEPT
  #endif
  {
    #if __PPLFlintXX_NOTHROW == 0
      if (fmpz_set_str (mp, s, 0) != 0)
        throw std::invalid_argument ("fmpz_set_str");
    #else
      fmpz_set_str (mp, s, 0);
    #endif
    return *this;
  }
  __flint_expr & operator=(const std::string &s)
  #if __PPLFlintXX_NOTHROW == 0
    __PPLFlintXX_NOEXCEPT
  #endif
  {
    #if __PPLFlintXX_NOTHROW == 0
      if (fmpz_set_str(mp, s.c_str(), 0) != 0)
        throw std::invalid_argument ("fmpz_set_str");
    #else
      fmpz_set_str(mp, s.c_str(), 0);
    #endif
    return *this;
  }

  // string input/output functions
  int set_str(const char *s, int base)
  { return fmpz_set_str(mp, s, base); }
  int set_str(const std::string &s, int base)
  { return fmpz_set_str(mp, s.c_str(), base); }
  std::string get_str(int base = 10) const
  {
    __gmp_alloc_cstring temp(fmpz_get_str(0, base, mp));
    return std::string(temp.str);
  }

  // conversion functions
  ///OLD fmpz_srcptr __get_mp() const { return mp; }
  ///OLD fmpz_ptr __get_mp() { return mp; }
  ///OLD fmpz_srcptr get_fmpz_t() const { return mp; }
  ///OLD fmpz_ptr get_fmpz_t() { return mp; }
  const fmpz * __get_mp() const { return mp; }
  fmpz * __get_mp() { return mp; }
  const fmpz * get_fmpz_t() const { return mp; }
  fmpz * get_fmpz_t() { return mp; }

  signed long int get_si() const { return fmpz_get_si(mp); }
  unsigned long int get_ui() const { return fmpz_get_ui(mp); }
  double get_d() const { return fmpz_get_d(mp); }

  // bool fits_schar_p() const { return fmpz_fits_schar_p(mp); }
  // bool fits_uchar_p() const { return fmpz_fits_uchar_p(mp); }
  bool fits_sint_p() const { return fmpz_fits_si/*nt_p*/(mp); }
  /*bool fits_uint_p() const { return fmpz_fits_uint_p(mp); }
  bool fits_sshort_p() const { return fmpz_fits_sshort_p(mp); }
  bool fits_ushort_p() const { return fmpz_fits_ushort_p(mp); }
  bool fits_slong_p() const { return fmpz_fits_slong_p(mp); }
  bool fits_ulong_p() const { return fmpz_fits_ulong_p(mp); }*/
  // bool fits_float_p() const { return fmpz_fits_float_p(mp); }
  // bool fits_double_p() const { return fmpz_fits_double_p(mp); }
  // bool fits_ldouble_p() const { return fmpz_fits_ldouble_p(mp); }

#if __PPLFlintXX_USE_CXX11
  ///OLD explicit operator bool() const { return mp->_mp_size != 0; }
#endif

  // member operators
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator+=)
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator-=)
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator*=)
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator/=)
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator%=)

  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator&=)
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator|=)
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR(operator^=)

  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR_UI(operator<<=)
  __PPLFlintXX_DECLARE_COMPOUND_OPERATOR_UI(operator>>=)

  __PPLFlintXX_DECLARE_INCREMENT_OPERATOR(operator++)
  __PPLFlintXX_DECLARE_INCREMENT_OPERATOR(operator--)
};

typedef __flint_expr<fmpz_t, fmpz_t> fmpz_class;

/**************** Functions for type conversion ****************/
// ATTENZIONE ai tipi: mpz sono stati convertiti in fmpz, ma gli altri
// della gmp per ora rimangono tali

inline void __flint_set_expr(fmpz * z, const fmpz_class &w)
///OLD inline void __flint_set_expr(fmpz_ptr z, const fmpz_class &w)
{
  fmpz_set(z, w.get_fmpz_t());
}

template <class T>
inline void __flint_set_expr(fmpz * z, const __flint_expr<fmpz_t, T> &expr)
///OLD inline void __flint_set_expr(fmpz_ptr z, const __flint_expr<fmpz_t, T> &expr)
{
  expr.eval(z);
}
/*
template <class T>
inline void __flint_set_expr(fmpz * z, const __flint_expr<mpq_t, T> &expr)
///OLD inline void __flint_set_expr(fmpz_ptr z, const __flint_expr<mpq_t, T> &expr)
{
  mpq_class const& temp(expr);
  fmpz_set_q(z, temp.get_mpq_t());
}

template <class T>
inline void __flint_set_expr(fmpz * z, const __flint_expr<mpf_t, T> &expr)
///OLD inline void __flint_set_expr(fmpz_ptr z, const __flint_expr<mpf_t, T> &expr)
{
  mpf_class const& temp(expr);
  fmpz_set_f(z, temp.get_mpf_t());
}

inline void __flint_set_expr(mpq_ptr q, const fmpz_class &z)
{
  mpq_set_z(q, z.get_fmpz_t());
}

template <class T>
inline void __flint_set_expr(mpq_ptr q, const __flint_expr<fmpz_t, T> &expr)
{
  __flint_set_expr(mpq_numref(q), expr);
  fmpz_set_ui(mpq_denref(q), 1);
}

inline void __flint_set_expr(mpq_ptr q, const mpq_class &r)
{
  mpq_set(q, r.get_mpq_t());
}

template <class T>
inline void __flint_set_expr(mpq_ptr q, const __flint_expr<mpq_t, T> &expr)
{
  expr.eval(q);
}

template <class T>
inline void __flint_set_expr(mpq_ptr q, const __flint_expr<mpf_t, T> &expr)
{
  mpf_class const& temp(expr);
  mpq_set_f(q, temp.get_mpf_t());
}

template <class T>
inline void __flint_set_expr(mpf_ptr f, const __flint_expr<fmpz_t, T> &expr)
{
  fmpz_class const& temp(expr);
  mpf_set_z(f, temp.get_fmpz_t());
}

template <class T>
inline void __flint_set_expr(mpf_ptr f, const __flint_expr<mpq_t, T> &expr)
{
  mpq_class const& temp(expr);
  mpf_set_q(f, temp.get_mpq_t());
}

inline void __flint_set_expr(mpf_ptr f, const mpf_class &g)
{
  mpf_set(f, g.get_mpf_t());
}

template <class T>
inline void __flint_set_expr(mpf_ptr f, const __flint_expr<mpf_t, T> &expr)
{
  expr.eval(f);
}
*/
#endif // !defined(PPL_fmpz_class_hh)

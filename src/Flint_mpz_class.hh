// a lot of help for operators in 
// http://en.cppreference.com/w/cpp/language/operators

#ifndef flint_mpz_class_hh
#define flint_mpz_class_hh 1

///#include <stdexcept>
#include <iostream>
#include <string>
#include <gmpxx.h>
#include <flint/fmpz.h>

#define __PPLITE_CONSTANT(X) __builtin_constant_p(X)
#define __PPLITE_CONSTANT_TRUE(X) (__PPLITE_CONSTANT(X) && (X))

class flint_mpz_class
{
public:
  // Costruttori e distruttori
  flint_mpz_class() {
    fmpz_init(mp);
  }
  flint_mpz_class(signed int l) { 
    init_si(l);
  }
  flint_mpz_class(unsigned int l) { 
    init_ui(l);
  }
  flint_mpz_class(signed long l) { 
    init_si(l);
  }
  flint_mpz_class(unsigned long l) { 
    init_ui(l);
  }
  flint_mpz_class(double d) { 
    init_d(d);
  }
  flint_mpz_class(const flint_mpz_class &z) { 
    fmpz_init(mp);
    fmpz_set(mp, z.mp);
  }
#if __cplusplus >= 201103L
  flint_mpz_class(flint_mpz_class &&z) {
    *mp = *z.mp;
    fmpz_init(z.mp);
  }
#endif
  flint_mpz_class(const mpz_class &z) { 
    *this = z.get_str(); 
  }

  explicit flint_mpz_class(const char *s, int base = 0)
  {
    fmpz_init(mp);
    if (set_str(s, base) != 0) {
      fmpz_clear (mp);
      ///throw std::invalid_argument ("fmpz_set_str");
    }
  }
  explicit flint_mpz_class(const std::string &s, int base = 0)
  {
    fmpz_init(mp);
    if (set_str(s.c_str(), base) != 0) {
      fmpz_clear (mp);
      ///throw std::invalid_argument ("fmpz_set_str");
    }
  }

  ~flint_mpz_class() { fmpz_clear(mp); }

public:
  fmpz_t mp;

  // Inizializzazione
  void init_ui(unsigned long l) {
      fmpz_init(mp);
      fmpz_set_ui(mp, l);
  }
  void init_si(signed long l) {
    if (__PPLITE_CONSTANT_TRUE(l >= 0)) {
      init_ui(l);
    }
    else if (__PPLITE_CONSTANT_TRUE(l <= 0)) {
      init_ui(-static_cast<unsigned long>(l));
      fmpz_neg(mp, mp);
    }
    else {
      fmpz_init(mp);
      fmpz_set_si(mp, l);
    }
  }
  void init_d (double d) {
    fmpz_init (mp);
    fmpz_set_d (mp, d);
  }

  // Assegnamento
  void assign_ui(unsigned long l) {
      fmpz_set_ui(mp, l);
  }
  void assign_si(signed long l) {
    if (__PPLITE_CONSTANT_TRUE(l >= 0)) {
      assign_ui(l);
    }
    else if (__PPLITE_CONSTANT_TRUE(l <= 0)) {
      assign_ui(-static_cast<unsigned long>(l));
      fmpz_neg(mp, mp);
    }
    else {
      fmpz_set_si(mp, l);
    }
  }
  void assign_d (double d) {
    fmpz_set_d (mp, d);
  }

public:
  void swap(flint_mpz_class& z) { std::swap(*mp, *z.mp); }

  // assignment operators
  flint_mpz_class & operator=(const flint_mpz_class &z) { fmpz_set(mp, z.mp); return *this; }
#if __cplusplus >= 201103L
  flint_mpz_class & operator=(flint_mpz_class &&z) noexcept { swap(z); return *this; }
#endif
  flint_mpz_class & operator=(int l) { assign_si(l); return *this; }
  flint_mpz_class & operator=(signed long l) { assign_si(l); return *this; }
  flint_mpz_class & operator=(unsigned long l) { assign_ui(l); return *this; }
  flint_mpz_class & operator=(double d) { assign_d(d); return *this; }
  flint_mpz_class & operator=(const mpz_class & z) { *this = z.get_str(); return *this; }
  flint_mpz_class & operator=(const mpq_class & z) { *this = z.get_str(); return *this; }
  flint_mpz_class & operator=(const char *s) {
    if (set_str (s, 0) != 0) {
      ///throw std::invalid_argument ("fmpz_set_str");
    }
    return *this;
  }
  flint_mpz_class & operator=(const std::string &s) {
    if (set_str(s.c_str(), 0) != 0) {
      ///throw std::invalid_argument ("fmpz_set_str");
    }
    return *this;
  }

  // string input/output functions
  int set_str(const char *s, int base)
  { return fmpz_set_str(mp, s, base); }
  int set_str(const std::string &s, int base)
  { return fmpz_set_str(mp, s.c_str(), base); }
  std::string get_str(int base = 10) const
  {
    ///__gmp_alloc_cstring temp(fmpz_get_str(0, base, mp));
    return std::string(fmpz_get_str(0, base, mp));
  }

  signed long int get_si() const { return fmpz_get_si(mp); }
  unsigned long int get_ui() const { return fmpz_get_ui(mp); }
  double get_d() const { return fmpz_get_d(mp); }
  
/*
#if __GMPXX_USE_CXX11
  explicit operator bool() const { return mp->_mp_size != 0; }
#endif*/

  // Comparison
  inline bool operator==(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) == 0; }
  inline bool operator==(signed int rhs)             const { return fmpz_cmp_si(mp,rhs) == 0; }
  inline bool operator==(unsigned int rhs)           const { return fmpz_cmp_ui(mp,rhs) == 0; }
  inline bool operator==(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) == 0; }
  inline bool operator==(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) == 0; }
  ///inline bool operator==(double rhs)                 const { return fmpz_cmp (mp,rhs) == 0; }
  inline bool operator!=(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) != 0; }
  inline bool operator!=(signed int rhs)             const { return fmpz_cmp_si(mp,rhs) != 0; }
  inline bool operator!=(unsigned int rhs)           const { return fmpz_cmp_ui(mp,rhs) != 0; }
  inline bool operator!=(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) != 0; }
  inline bool operator!=(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) != 0; }
  ///inline bool operator!=(double rhs)                 const { return fmpz_cmp (mp,rhs) != 0; }
  inline bool operator< (const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) <  0; }
  inline bool operator< (signed int rhs)             const { return fmpz_cmp_si(mp,rhs) <  0; }
  inline bool operator< (unsigned int rhs)           const { return fmpz_cmp_ui(mp,rhs) <  0; }
  inline bool operator< (signed long rhs)            const { return fmpz_cmp_si(mp,rhs) <  0; }
  inline bool operator< (unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) <  0; }
  ///inline bool operator< (double rhs)                 const { return fmpz_cmp (mp,rhs) <  0; }
  inline bool operator> (const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) >  0; }
  inline bool operator> (signed int rhs)             const { return fmpz_cmp_si(mp,rhs) >  0; }
  inline bool operator> (unsigned int rhs)           const { return fmpz_cmp_ui(mp,rhs) >  0; }
  inline bool operator> (signed long rhs)            const { return fmpz_cmp_si(mp,rhs) >  0; }
  inline bool operator> (unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) >  0; }
  ///inline bool operator> (double rhs)                 const { return fmpz_cmp (mp,rhs) >  0; }
  inline bool operator<=(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) <= 0; }
  inline bool operator<=(signed int rhs)             const { return fmpz_cmp_si(mp,rhs) <= 0; }
  inline bool operator<=(unsigned int rhs)           const { return fmpz_cmp_ui(mp,rhs) <= 0; }
  inline bool operator<=(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) <= 0; }
  inline bool operator<=(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) <= 0; }
  ///inline bool operator<=(double rhs)                 const { return fmpz_cmp (mp,rhs) <= 0; }
  inline bool operator>=(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) >= 0; }
  inline bool operator>=(signed int rhs)             const { return fmpz_cmp_si(mp,rhs) >= 0; }
  inline bool operator>=(unsigned int rhs)           const { return fmpz_cmp_ui(mp,rhs) >= 0; }
  inline bool operator>=(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) >= 0; }
  inline bool operator>=(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) >= 0; }
  ///inline bool operator>=(double rhs)                 const { return fmpz_cmp (mp,rhs) >= 0; }

  // bitwise operators
  inline flint_mpz_class& operator>>(unsigned int exp) {  
      fmpz_tdiv_q_2exp(this->mp, this->mp, exp);
      return *this;
  }

  // iostreams
  inline std::ostream& operator<<(std::ostream& os) {  
      os << get_str();  
      return os;  
  }
  inline friend std::ostream& operator<<(std::ostream& os, const flint_mpz_class & rhs) {  
      os << rhs.get_str();  
      return os;  
  }
  inline std::istream& operator>>(std::istream& is) {  
      std::string s;
      is >> s;
      *this = s;
      return is;  
  }
  inline friend std::istream& operator>>(std::istream& is, flint_mpz_class & rhs) {  
      std::string s;
      is >> s;
      rhs = s;  
      return is;  
  }

  // Arithmetic negation
  flint_mpz_class operator-() const {
    flint_mpz_class ret;
    fmpz_neg(ret.mp, this->mp);
    return ret;
  }

  friend flint_mpz_class operator+(signed   int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator+(unsigned int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator-(signed   int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator-(unsigned int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator*(signed   int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator*(unsigned int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator/(signed   int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator/(unsigned int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator%(signed   int  lhs, const flint_mpz_class& rhs);
  friend flint_mpz_class operator%(unsigned int  lhs, const flint_mpz_class& rhs);

  // New arithmetic sum implementation
  flint_mpz_class & operator+=(const flint_mpz_class& rhs) { fmpz_add(this->mp, this->mp, rhs.mp); return *this; }
  flint_mpz_class & operator+=(signed   int  rhs) {
    rhs >= 0 ? fmpz_add_ui(this->mp, this->mp, rhs) : fmpz_sub_ui(this->mp, this->mp, -rhs);
    return *this;
  }
  flint_mpz_class & operator+=(unsigned int  rhs) { fmpz_add_ui(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator+=(signed   long rhs) { 
    rhs >= 0 ? fmpz_add_ui(this->mp, this->mp, rhs) : fmpz_sub_ui(this->mp, this->mp, -rhs);
    return *this;
  }
  flint_mpz_class & operator+=(unsigned long rhs) { fmpz_add_ui(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator++() { fmpz_add_ui(this->mp, this->mp, 1); return *this; }
  const flint_mpz_class operator++(int) { flint_mpz_class temp(*this); fmpz_add_ui(this->mp, this->mp, 1); return temp; }
  friend flint_mpz_class operator+(flint_mpz_class lhs, const flint_mpz_class& rhs) { return (lhs += rhs); }

  // New arithmetic subtraction implementation
  flint_mpz_class & operator-=(const flint_mpz_class& rhs) { fmpz_sub(this->mp, this->mp, rhs.mp); return *this; }
  flint_mpz_class & operator-=(signed   int  rhs) {
    rhs >= 0 ? fmpz_sub_ui(this->mp, this->mp, rhs) : fmpz_add_ui(this->mp, this->mp, -rhs);
    return *this;
  }
  flint_mpz_class & operator-=(unsigned int  rhs) { fmpz_sub_ui(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator-=(signed   long rhs) { 
    rhs >= 0 ? fmpz_sub_ui(this->mp, this->mp, rhs) : fmpz_add_ui(this->mp, this->mp, -rhs);
    return *this;
  }
  flint_mpz_class & operator-=(unsigned long rhs) { fmpz_sub_ui(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator--() { fmpz_sub_ui(this->mp, this->mp, 1); return *this; }
  const flint_mpz_class operator--(int) { flint_mpz_class temp(*this); fmpz_sub_ui(this->mp, this->mp, 1); return temp; }
  friend flint_mpz_class operator-(flint_mpz_class lhs, const flint_mpz_class& rhs) { return (lhs -= rhs); }

  // New arithmetic multiplication implementation
  flint_mpz_class & operator*=(const flint_mpz_class& rhs) { fmpz_mul(this->mp, this->mp, rhs.mp); return *this; }
  flint_mpz_class & operator*=(signed   int  rhs) { fmpz_mul_si(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator*=(unsigned int  rhs) { fmpz_mul_ui(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator*=(signed   long rhs) { fmpz_mul_si(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator*=(unsigned long rhs) { fmpz_mul_ui(this->mp, this->mp, rhs); return *this; }
  friend flint_mpz_class operator*(flint_mpz_class lhs, const flint_mpz_class& rhs) { return (lhs *= rhs); }

  // New arithmetic division implementation
  flint_mpz_class & operator/=(const flint_mpz_class& rhs) { fmpz_tdiv_q(this->mp, this->mp, rhs.mp); return *this; }
  flint_mpz_class & operator/=(signed   int  rhs) { fmpz_tdiv_q_si(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator/=(unsigned int  rhs) { fmpz_tdiv_q_ui(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator/=(signed   long rhs) { fmpz_tdiv_q_si(this->mp, this->mp, rhs); return *this; }
  flint_mpz_class & operator/=(unsigned long rhs) { fmpz_tdiv_q_ui(this->mp, this->mp, rhs); return *this; }
  friend flint_mpz_class operator/(flint_mpz_class lhs, const flint_mpz_class& rhs) { return (lhs /= rhs); }
  
  // New arithmetic modulus implementation
  flint_mpz_class & operator%=(const flint_mpz_class& rhs) { fmpz_mod(this->mp, this->mp, rhs.mp); return *this; }
  friend flint_mpz_class operator%(flint_mpz_class lhs, const flint_mpz_class& rhs) { return (lhs %= rhs); }

  // Some math
  inline flint_mpz_class getAbs() const {
    flint_mpz_class ret;
    fmpz_abs(ret.mp, this->mp);
    return ret;
  }

  inline flint_mpz_class getGCD(const flint_mpz_class& n1, const flint_mpz_class& n2) const {
    flint_mpz_class ret;
    fmpz_gcd(ret.mp, n1.mp, n2.mp);
    return ret;
  }

  inline flint_mpz_class getLCM(const flint_mpz_class& n1, const flint_mpz_class& n2) const {
    flint_mpz_class ret;
    fmpz_lcm(ret.mp, n1.mp, n2.mp);
    return ret;
  }

};


inline flint_mpz_class operator+(signed   int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret += rhs); }
inline flint_mpz_class operator+(unsigned int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret += rhs); }

inline flint_mpz_class operator-(signed   int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret -= rhs); }
inline flint_mpz_class operator-(unsigned int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret -= rhs); }

inline flint_mpz_class operator*(signed   int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret *= rhs); }
inline flint_mpz_class operator*(unsigned int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret *= rhs); }

inline flint_mpz_class operator/(signed   int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret /= rhs); }
inline flint_mpz_class operator/(unsigned int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret /= rhs); }

inline flint_mpz_class operator%(signed   int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret %= rhs); }
inline flint_mpz_class operator%(unsigned int  lhs, const flint_mpz_class& rhs) { flint_mpz_class ret(lhs); return (ret %= rhs); }


namespace Parma_Polyhedra_Library {
typedef flint_mpz_class Coefficient; 
};

#endif // !defined(flint_mpz_class_hh)

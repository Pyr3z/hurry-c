/*! ***************************************************************************
\ll ** -- FILE DETAILS ----------------------------------------------------- **
\ll ***************************************************************************
    \file     hurry/ctz.h
    \project  hurry
    \module   bitwise
    \author   [Levi Perez](https://leviperez.dev)  \n
    \email    <levi@leviperez.dev>                 \n
    \discord  [Leviathan#2318](https://discordapp.com/channels/@me)
    \copyleft @ref LICENSE (<https://unlicense.org>)
\ll ***************************************************************************
\ll ** -- FILE USAGE ------------------------------------------------------- **
\ll ***************************************************************************
    \brief    Lightning-fast, safe-anywhere, portable CTZ operation.
\ll ***************************************************************************
\ll ** -- DEVELOPMENT HISTORY & ROADMAP ------------------------------------ **
\ll ***************************************************************************
    \version  0.1.0
    \created  2020-02-07 (18:24:35)
******************************************************************************/

#pragma once

#ifndef HURRY_CTZ_H_
#define HURRY_CTZ_H_

# ifdef __cplusplus
extern "C" {
# endif

# if defined(HURRY_CTZ_SANITY)
#   include <stdio.h>
#   include <assert.h>
# endif

# include "hurry/defcommon.h" /* un-included at EOF */

# ifdef __cplusplus
#   define FUNC_OVERLOAD_(lhs, rhs) DEFER(lhs)
#   define REGISTER_
# else
#   define FUNC_OVERLOAD_(lhs, rhs) CONCAT(lhs, rhs)
#   define REGISTER_ register
# endif


typedef uint_fast8_t bitidx_t;



inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 8) (REGISTER_ uint8_t bits)
{
  REGISTER_ bitidx_t ctz = 0; REGISTER_ bitidx_t last = 0;

  ctz += (!(bits & 0x0F) << 2); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x03) << 1); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x01)     );

  /* valid return range: [0,7] */
  return ctz + !((bits >> (ctz - last)) & 1);
  /* invalid return range: bitsizeof(bits) (8 in this case) when passed 0 */
}


inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 16) (REGISTER_ uint16_t bits)
{
  REGISTER_ bitidx_t ctz = 0; REGISTER_ bitidx_t last = 0;

  ctz += (!(bits & 0xFF) << 3); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x0F) << 2); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x03) << 1); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x01)     );

  /* valid return range: [0,15] */
  return ctz + !((bits >> (ctz - last)) & 1);
  /* invalid return range: bitsizeof(bits) (16 in this case) when passed 0 */
}


inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 32) (REGISTER_ uint32_t bits)
{
  REGISTER_ bitidx_t ctz = 0; REGISTER_ bitidx_t last = 0;

  ctz += (!(bits & 0xFFFF) << 4); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x00FF) << 3); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x000F) << 2); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x0003) << 1); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x0001)     );

  /* valid return range: [0,31] */
  return ctz + !((bits >> (ctz - last)) & 1);
  /* invalid return range: bitsizeof(bits) (32 in this case) when passed 0 */
}


inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 64) (REGISTER_ uint64_t bits)
{
  REGISTER_ bitidx_t ctz = 0; REGISTER_ bitidx_t last = 0;

  ctz += (!(bits & 0xFFFFFFFF) << 5); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x0000FFFF) << 4); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x000000FF) << 3); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x0000000F) << 2); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x00000003) << 1); bits >>= (ctz - last); last = ctz;
  ctz += (!(bits & 0x00000001)     );

  /* valid return range: [0,63] */
  return ctz + !((bits >> (ctz - last)) & 1);
  /* returns bitsizeof(bits) (64 in this case) when passed 0 */
}

# ifndef __cplusplus
#   define ctz_nojump(bits) _Generic((bits),                  \
                                      default:  ctz_nojump32, \
                                      uint8_t:  ctz_nojump8,  \
                                      uint16_t: ctz_nojump16, \
                                      uint32_t: ctz_nojump32, \
                                      uint64_t: ctz_nojump64) (bits)
# endif

extern inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 8)  (REGISTER_ uint8_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 16) (REGISTER_ uint16_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 32) (REGISTER_ uint32_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz_nojump, 64) (REGISTER_ uint64_t);



inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 8) (REGISTER_ const uint8_t bits)
{
  static const uint8_t      key8        = 0x17; /* B(2,3) */
  static const uint_fast8_t lookup8[8]  = { 0, 1, 2, 4, 7, 3, 6, 5 };

  return lookup8[(uint8_t)((bits & -bits) * key8) >> 5] + (!bits * 8);
}

inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 16) (REGISTER_ const uint16_t bits)
{
  static const uint16_t     key16         = 0x9AF; /* B(2,4) */
  static const uint_fast8_t lookup16[16]  = { 0, 1, 2, 5, 3, 9, 6, 11,
                                              15, 4, 8, 10, 14, 7, 13, 12 };

  return lookup16[(uint16_t)((bits & -bits) * key16) >> 12] + (!bits * 16);
}

inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 32) (REGISTER_ const uint32_t bits)
{
  static const uint32_t     key32         = 0x4653ADF; /* B(2,5) */
  static const uint_fast8_t lookup32[32]  = { 0, 1, 2, 6, 3, 11, 7, 16, 4, 14,
                                              12, 21, 8, 23, 17, 26, 31, 5, 10,
                                              15, 13, 20, 22, 25, 30, 9, 19, 24,
                                              29, 18, 28, 27 };


  return lookup32[(uint32_t)((bits & -bits) * key32) >> 27] + (!bits * 32);
}

inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 64) (REGISTER_ const uint64_t bits)
{
  static const uint64_t     key64         = 0x218A392CD3D5DBF; /* B(2,6) */
  static const uint_fast8_t lookup64[64]  = { 0, 1, 2, 7, 3, 13, 8, 19, 4, 25,
                                              14, 28, 9, 34, 20, 40, 5, 17, 26,
                                              38, 15, 46, 29, 48, 10, 31, 35,
                                              54, 21, 50, 41, 57, 63, 6, 12, 18,
                                              24, 27, 33, 39, 16, 37, 45, 47,
                                              30, 53, 49, 56, 62, 11, 23, 32,
                                              36, 44, 52, 55, 61, 22, 43, 51,
                                              60, 42, 59, 58 };


  return lookup64[(uint64_t)((bits & -bits) * key64) >> 58] + (!bits * 64);
}

# ifndef __cplusplus
#   define ctz_perfhash(bits) _Generic((bits),                  \
                                      default:  ctz_perfhash32, \
                                      uint8_t:  ctz_perfhash8,  \
                                      uint16_t: ctz_perfhash16, \
                                      uint32_t: ctz_perfhash32, \
                                      uint64_t: ctz_perfhash64) (bits)
# endif

extern inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 8)  (REGISTER_ const uint8_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 16) (REGISTER_ const uint16_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 32) (REGISTER_ const uint32_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz_perfhash, 64) (REGISTER_ const uint64_t);




inline bitidx_t FUNC_OVERLOAD_(ctz, 8) (uint8_t bits)
{
# if defined(HURRY_CTZ_INTRINSICS) && (defined(__GNUC__) || defined(__clang__))
    return __builtin_ctz((uint_fast8_t)bits) + (!bits * 8);
# elif defined(HURRY_CTZ_PERFECT)
    return ctz_perfhash((uint_fast8_t)bits);
# else
    return ctz_nojump((uint_fast8_t)bits);
# endif
}

inline bitidx_t FUNC_OVERLOAD_(ctz, 16) (uint16_t bits)
{
# if defined(HURRY_CTZ_INTRINSICS) && (defined(__GNUC__) || defined(__clang__))
    return __builtin_ctz((uint_fast16_t)bits) + (!bits * 16);
# elif defined(HURRY_CTZ_PERFECT)
    return ctz_perfhash((uint_fast16_t)bits);
# else
    return ctz_nojump((uint_fast16_t)bits);
# endif
}

inline bitidx_t FUNC_OVERLOAD_(ctz, 32) (uint32_t bits)
{
# if defined(HURRY_CTZ_INTRINSICS) && (defined(__GNUC__) || defined(__clang__))
    return __builtin_ctz((uint_fast32_t)bits) + (!bits * 32);
# elif defined(HURRY_CTZ_PERFECT)
    return ctz_perfhash((uint_fast32_t)bits);
# else
    return ctz_nojump((uint_fast32_t)bits);
# endif
}

inline bitidx_t FUNC_OVERLOAD_(ctz, 64) (uint64_t bits)
{
# if defined(HURRY_CTZ_INTRINSICS) && (defined(__GNUC__) || defined(__clang__))
    return __builtin_ctzll((uint_fast64_t)bits) + (!bits * 64);
# elif defined(HURRY_CTZ_PERFECT)
    return ctz_perfhash((uint_fast64_t)bits);
# else
    return ctz_nojump((uint_fast64_t)bits);
# endif
}

# ifndef __cplusplus
#   define ctz(bits) _Generic((bits),          \
                              default:  ctz32, \
                              uint8_t:  ctz8,  \
                              uint16_t: ctz16, \
                              uint32_t: ctz32, \
                              uint64_t: ctz64) (bits)
# endif

extern inline bitidx_t FUNC_OVERLOAD_(ctz, 8)  (uint8_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz, 16) (uint16_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz, 32) (uint32_t);
extern inline bitidx_t FUNC_OVERLOAD_(ctz, 64) (uint64_t);

# if defined(HURRY_CTZ_SANITY) && HURRY_CTZ_SANITY

int hurry_ctz_sanity_check(FILE* out)
{
  int i, count = 0;

  assert(out);

  for (i = 0; i < 8; ++i)
  {
    count += fprintf(out, "ctz8 (1 << %2u) --> %2u\n",
                          (unsigned)i,
                          ctz((uint8_t)1 << i));
    count += fprintf(out, "       ...16() --> %2u\n",
                          ctz((uint16_t)1 << i));
    count += fprintf(out, "       ...32() --> %2u\n",
                          ctz((uint32_t)1 << i));
    count += fprintf(out, "       ...64() --> %2u\n",
                          ctz((uint64_t)1 << i));
  }

  fputc('\n', out);

  for (; i < 16; ++i)
  {
    count += fprintf(out, "ctz16(1 << %2u) --> %2u\n",
                          (unsigned)i,
                          ctz((uint16_t)1 << i));
    count += fprintf(out, "       ...32() --> %2u\n",
                          ctz((uint32_t)1 << i));
    count += fprintf(out, "       ...64() --> %2u\n",
                          ctz((uint64_t)1 << i));
  }

  fputc('\n', out);

  for (; i < 32; ++i)
  {
    count += fprintf(out, "ctz32(1 << %2u) --> %2u\n",
                          (unsigned)i,
                          ctz((uint32_t)1 << i));
    count += fprintf(out, "       ...64() --> %2u\n",
                          ctz((uint64_t)1 << i));
  }

  fputc('\n', out);

  for (; i < 64; ++i)
  {
    count += fprintf(out, "ctz64(1 << %2u) --> %2u\n",
                          (unsigned)i,
                          ctz((uint64_t)1 << i));
  }

  count += fprintf(out, "\nctz8 (0 <<  0) --> %2u\n", ctz((uint8_t)0));
  count += fprintf(out, "\nctz16(0 <<  0) --> %2u\n", ctz((uint16_t)0));
  count += fprintf(out, "\nctz32(0 <<  0) --> %2u\n", ctz((uint32_t)0));
  count += fprintf(out, "\nctz64(0 <<  0) --> %2u\n", ctz((uint64_t)0));

  return count;
}

#   if !defined(RELEASE) || !RELEASE
void hurry_ctz_assert()
{
  unsigned i;
  for (i = 0; i < 8; ++i)
  {
    assert(ctz((uint8_t) 1 << i) == i);
    assert(ctz((uint16_t)1 << i) == i);
    assert(ctz((uint32_t)1 << i) == i);
    assert(ctz((uint64_t)1 << i) == i);
  }
  for (; i < 16; ++i)
  {
    assert(ctz((uint16_t)1 << i) == i);
    assert(ctz((uint32_t)1 << i) == i);
    assert(ctz((uint64_t)1 << i) == i);
  }
  for (; i < 32; ++i)
  {
    assert(ctz((uint32_t)1 << i) == i);
    assert(ctz((uint64_t)1 << i) == i);
  }

  for (; i < 64; ++i)
  {
    assert(ctz((uint64_t)1 << i) == i);
  }

  assert(ctz((uint8_t) 0) > bitsizeof(uint8_t)  - 1);
  assert(ctz((uint16_t)0) > bitsizeof(uint16_t) - 1);
  assert(ctz((uint32_t)0) > bitsizeof(uint32_t) - 1);
  assert(ctz((uint64_t)0) > bitsizeof(uint64_t) - 1);
}
#   else
void hurry_ctz_assert() { assert(ctz(1 << 11) == 11); }
#   endif /* !RELEASE */

# endif /* HURRY_CTZ_SANITY */

# ifdef __cplusplus
} /* extern "C" */
# endif

# undef FUNC_OVERLOAD_
# undef REGISTER_
# include "hurry/undefcommon.h"

#endif /* ifndef HURRY_CTZ_H_ */

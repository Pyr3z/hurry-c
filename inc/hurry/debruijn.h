/*! ***************************************************************************
\ll ** -- FILE DETAILS ----------------------------------------------------- **
\ll ***************************************************************************
    \file     hurry/debruijn.h
    \project  hurry
    \module   debruijn
    \author   [Levi Perez](https://leviperez.dev)  \n
    \email    <levi@leviperez.dev>                 \n
    \discord  [Leviathan#2318](https://discordapp.com/channels/@me)
    \copyleft @ref LICENSE (<https://unlicense.org>)
\ll ***************************************************************************
\ll ** -- FILE USAGE ------------------------------------------------------- **
\ll ***************************************************************************
    \brief    Generate de Bruijn sequences with ease.
    \details  --
\ll ***************************************************************************
\ll ** -- DEVELOPMENT HISTORY & ROADMAP ------------------------------------ **
\ll ***************************************************************************
    \version  0.1.0
    \created  2020-02-10 (11:56:02)
******************************************************************************/

#pragma once

#ifndef HURRY_DEBRUIJN_H_
#define HURRY_DEBRUIJN_H_

# ifndef UINT_FAST8_MIN
#   include <stdint.h>
# endif

# include <stdlib.h>

# ifndef HURRY_PARSEBIN_H_
#   include "hurry/parsebin.h"
# endif



# ifdef __cplusplus
extern "C" {
# endif

/* The main workhorse: a DeBruijn Sequencer working with a binary alphabet */
size_t debruijn_01(const unsigned N, char* output, size_t len)
{
  /* local constants */
  static const char   ALPHABET[] = "01";
  static const size_t K = 2;

  /* initializations */
  size_t  idx       = 0;
  uint8_t seq[256]  = { 0 };

  /* begin nested function */
  void recurse(const unsigned a, const unsigned b) {
    if (a > N) {
      if (!(N % b)) {
        unsigned i;
        for (i = 1; i < b + 1; ++i) {
          if (idx == len)
            return;
          output[idx++] = ALPHABET[seq[i]];
        }
      }
    }
    else if (a >= b) {
      seq[a] = seq[a - b];
      recurse(a + 1, b);
      unsigned char j = seq[a - b] + 1;
      while (j < K) {
        seq[a] = j++;
        recurse(a + 1, a);
      }
    }
  }
  /* end nested function `recurse` */

  /* Simply invoke the recursive algorithm: */
  recurse(1, 1);

  /* Return value is the logical length of the output string */
  return idx;
}


/*
  The rest here are functions that generate binary DeBruijn keys with specific
  sequence lengths, converted to integers based on the corresponding
  representation in binary.
*/


uint8_t debruijn_key8()
{
  static char    seq8[8 + 1] = { 0 };
  static uint8_t key8 = 0x00;

  if (!key8)
  {
    size_t len = debruijn_01(3, seq8, 8);
    parsebin8(seq8, len, 0, &key8);
  }

  return key8;
}

uint16_t debruijn_key16()
{
  static char     seq16[16 + 1] = { 0 };
  static uint16_t key16 = 0x0000;

  if (!key16)
  {
    size_t len = debruijn_01(4, seq16, 16);
    parsebin16(seq16, len, 0, &key16);
  }

  return key16;
}

uint32_t debruijn_key32()
{
  static char     seq32[32 + 1] = { 0 };
  static uint32_t key32 = 0x00000000;

  if (!key32)
  {
    size_t len = debruijn_01(5, seq32, 32);
    parsebin32(seq32, len, 0, &key32);
  }

  return key32;
}

uint64_t debruijn_key64()
{
  static char     seq64[64 + 1] = { 0 };
  static uint64_t key64 = 0x0000000000000000;

  if (!key64)
  {
    size_t len = debruijn_01(6, seq64, 64);
    parsebin64(seq64, len, 0, &key64);
  }

  return key64;
}

# ifdef __cplusplus
} /* extern "C" */
# endif
#endif /* ifndef HURRY_DEBRUIJN_H_ */

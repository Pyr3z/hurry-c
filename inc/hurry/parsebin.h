/*! ***************************************************************************
\ll ** -- FILE DETAILS ----------------------------------------------------- **
\ll ***************************************************************************
    \file     hurry/parsebin.h
    \project  hurry
    \module   parsebin
    \author   [Levi Perez](https://leviperez.dev)  \n
    \email    <levi@leviperez.dev>                 \n
    \discord  [Leviathan#2318](https://discordapp.com/channels/@me)
    \copyleft @ref LICENSE (<https://unlicense.org>)
\ll ***************************************************************************
\ll ** -- FILE USAGE ------------------------------------------------------- **
\ll ***************************************************************************
    \brief    Parse an integral value from its binary representation.
\ll ***************************************************************************
\ll ** -- DEVELOPMENT HISTORY & ROADMAP ------------------------------------ **
\ll ***************************************************************************
    \version  0.1.0
    \created  2020-02-10 (13:29:40)
******************************************************************************/

#pragma once

#ifndef HURRY_PARSEBIN_H_
#define HURRY_PARSEBIN_H_

# include "hurry/defcommon.h" /* un-included at EOF */


# define PARSEBIN_FORMAT8 " %8[01]"


# ifdef __cplusplus
extern "C" {
# endif



bool parsebin8(const char* input, size_t len, unsigned octet, uint8_t* output)
{
  if (len < (8 * (octet + 1))) return false;

  input += len - (8 * (octet + 1));

  *output = ((!!(input[0] - '0')) << 7) |
            ((!!(input[1] - '0')) << 6) |
            ((!!(input[2] - '0')) << 5) |
            ((!!(input[3] - '0')) << 4) |
            ((!!(input[4] - '0')) << 3) |
            ((!!(input[5] - '0')) << 2) |
            ((!!(input[6] - '0')) << 1) |
            ((!!(input[7] - '0')) << 0);

  return true;
}

bool parsebin16(const char* input, size_t len, unsigned octet, uint16_t* output)
{
  union short_view
  {
    uint16_t  shyte;

    struct
    {
      uint8_t lobyte;
      uint8_t hibyte;
    };
  } *shyte = (union short_view*)output;

  return  parsebin8(input, len, octet + 0, &shyte->lobyte) &&
          parsebin8(input, len, octet + 1, &shyte->hibyte);
}

bool parsebin32(const char* input, size_t len, unsigned octet, uint32_t* output)
{
  union dword_view
  {
    uint32_t  dwyte;

    struct
    {
      uint16_t loshyte;
      uint16_t hishyte;
    };
  } *dwyte = (union dword_view*)output;

  return  parsebin16(input, len, octet + 0, &dwyte->loshyte) &&
          parsebin16(input, len, octet + 2, &dwyte->hishyte);
}

bool parsebin64(const char* input, size_t len, unsigned octet, uint64_t* output)
{
  union llong_view
  {
    uint64_t  llyte;

    struct
    {
      uint32_t lodwyte;
      uint32_t hidwyte;
    };
  } *llyte = (union llong_view*)output;

  return  parsebin32(input, len, octet + 0, &llyte->lodwyte) &&
          parsebin32(input, len, octet + 4, &llyte->hidwyte);
}



# ifdef __cplusplus
} /* extern "C" */
# endif

# include "hurry/undefcommon.h"

#endif /* ifndef HURRY_PARSEBIN_H_ */

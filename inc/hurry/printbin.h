/*! ***************************************************************************
\ll ** -- FILE DETAILS ----------------------------------------------------- **
\ll ***************************************************************************
    \file     hurry/printbin.h
    \project  hurry
    \module   printbin
    \author   [Levi Perez](https://leviperez.dev)  \n
    \email    <levi@leviperez.dev>                 \n
    \discord  [Leviathan#2318](https://discordapp.com/channels/@me)
    \copyleft @ref LICENSE (<https://unlicense.org>)
\ll ***************************************************************************
\ll ** -- FILE USAGE ------------------------------------------------------- **
\ll ***************************************************************************
    \brief    Print an integral value in its binary representation.
\ll ***************************************************************************
\ll ** -- DEVELOPMENT HISTORY & ROADMAP ------------------------------------ **
\ll ***************************************************************************
    \version  0.1.0
    \created  2020-02-07 (17:55:05)
******************************************************************************/

#pragma once

#ifndef HURRY_PRINTBIN_H_
#define HURRY_PRINTBIN_H_

# ifndef EOF
#   include <stdio.h>
# endif

# include "hurry/defcommon.h" /* un-included at EOF */



/*****************************************************************************/
/* MACROS ********************************************************************/


/* PRINTBIN: Format strings to represent binary notation. */


# define PRINTBIN_FORMAT8 "%c%c%c%c%c%c%c%c"


# define PRINTBIN_ARGS_FROM_BYTE(byte)          \
          ('0' + !!((uint8_t)(byte) & 0x80)),  \
          ('0' + !!((uint8_t)(byte) & 0x40)),  \
          ('0' + !!((uint8_t)(byte) & 0x20)),  \
          ('0' + !!((uint8_t)(byte) & 0x10)),  \
          ('0' + !!((uint8_t)(byte) & 0x08)),  \
          ('0' + !!((uint8_t)(byte) & 0x04)),  \
          ('0' + !!((uint8_t)(byte) & 0x02)),  \
          ('0' + !!((uint8_t)(byte) & 0x01))


# define PRINTBIN_MIN_BUFFER_SIZE(bits) (sizeof(bits) * 9)


# define PRINTBIN_BUFFER_8(buffname, byte) \
          sprintf(buffname, PRINTBIN_FORMAT8, PRINTBIN_ARGS_FROM_BYTE(byte));


# define PRINTBIN_BUFFER_16(buffname, shyte)                      \
          sprintf(buffname, PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8,                     \
                            PRINTBIN_ARGS_FROM_BYTE(shyte >> 8),  \
                            PRINTBIN_ARGS_FROM_BYTE(shyte >> 0));


# define PRINTBIN_BUFFER_32(buffname, dwyte)                      \
          sprintf(buffname, PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8,                     \
                            PRINTBIN_ARGS_FROM_BYTE(dwyte >> 24), \
                            PRINTBIN_ARGS_FROM_BYTE(dwyte >> 16), \
                            PRINTBIN_ARGS_FROM_BYTE(dwyte >>  8), \
                            PRINTBIN_ARGS_FROM_BYTE(dwyte >>  0));


# define PRINTBIN_BUFFER_64(buffname, llyte)                      \
          sprintf(buffname, PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8" "                   \
                            PRINTBIN_FORMAT8,                     \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >> 56), \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >> 48), \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >> 40), \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >> 32), \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >> 24), \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >> 16), \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >>  8), \
                            PRINTBIN_ARGS_FROM_BYTE(llyte >>  0));


# ifdef __cplusplus
extern "C" {
# endif


/* This should only be used to immediately pass to %s elsewhere; */
/* Not thread-safe! */
const char* printbin8(uint8_t byte)
{
  static char buffer[sizeof(uint8_t) * 9] = { 0 };
  PRINTBIN_BUFFER_8(buffer, byte);
  return buffer;
}

/* This should only be used to immediately pass to %s elsewhere; */
/* Not thread-safe! */
const char* printbin16(uint16_t shyte)
{
  static char buffer[sizeof(uint16_t) * 9] = { 0 };
  PRINTBIN_BUFFER_16(buffer, shyte);
  return buffer;
}

/* This should only be used to immediately pass to %s elsewhere; */
/* Not thread-safe! */
const char* printbin32(uint32_t dwyte)
{
  static char buffer[sizeof(uint32_t) * 9] = { 0 };
  PRINTBIN_BUFFER_32(buffer, dwyte);
  return buffer;
}

/* This should only be used to immediately pass to %s elsewhere; */
/* Not thread-safe! */
const char* printbin64(uint64_t llyte)
{
  static char buffer[sizeof(uint64_t) * 9] = { 0 };
  PRINTBIN_BUFFER_64(buffer, llyte);
  return buffer;
}

# ifndef __cplusplus
#   define printbin(bits) _Generic((bits),                \
                                    default:  printbin32, \
                                    uint8_t:  printbin8,  \
                                    uint16_t: printbin16, \
                                    uint32_t: printbin32, \
                                    uint64_t: printbin64) (bits)
# endif



# ifdef __cplusplus
} /* extern "C" */
# endif

# include "hurry/undefcommon.h"

#endif /* ifndef HURRY_PRINTBIN_H_ */

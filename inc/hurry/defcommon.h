/*! ***************************************************************************
\ll ** -- FILE DETAILS ----------------------------------------------------- **
\ll ***************************************************************************
    \file     hurry/defcommon.h
    \project  hurry
    \module   common
    \author   [Levi Perez](https://leviperez.dev)  \n
    \email    <levi@leviperez.dev>                 \n
    \discord  [Leviathan#2318](https://discordapp.com/channels/@me)
    \copyleft @ref LICENSE (<https://unlicense.org>)
\ll ***************************************************************************
\ll ** -- FILE USAGE ------------------------------------------------------- **
\ll ***************************************************************************
    \brief    Lightweight, safe-anywhere, portable C (++) boilerplate.
\ll ***************************************************************************
\ll ** -- DEVELOPMENT HISTORY & ROADMAP ------------------------------------ **
\ll ***************************************************************************
    \version  0.1.0
    \created  2020-02-07 (17:54:49)
******************************************************************************/

#ifndef HURRY_DEFCOMMON_H_
#define HURRY_DEFCOMMON_H_

# ifndef UINT_FAST8_MIN
#   include <stdint.h>
#   include <inttypes.h>
#   include <stdbool.h>
# endif

# ifndef DEFER
#   define DEFER(x) x
# endif

# ifndef ENCASE
#   define ENCASE(x) (x)
# endif

# ifndef STR
#   define STR_(s) #s
#   define STR(s) STR_(s)
# endif

# ifndef CONCAT
#   define CONCAT_(lhs, rhs) lhs ## rhs
#   define CONCAT(lhs, rhs) CONCAT_(lhs, rhs)
#   define TRICAT(a, b, c)  CONCAT_(a, CONCAT_(b, c))
# endif

# ifndef EXPAND
#   define EXPAND_(...) __VA_ARGS__
#   define EXPAND(...) EXPAND_(__VA_ARGS__)
# endif

# ifndef UNUSED
#   define UNUSED(symbol) ENCASE((void) ENCASE(symbol))
# endif

# ifndef bitsizeof
#   define bitsizeof(t) ENCASE(sizeof(t) * 8)
# endif

#endif /* HURRY_DEFCOMMON_H_ */

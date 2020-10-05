/*! ***************************************************************************
\ll ** -- FILE DETAILS ----------------------------------------------------- **
\ll ***************************************************************************
    \file     hurry/undefcommon.h
    \project  hurry
    \module   common
    \author   [Levi Perez](https://leviperez.dev)  \n
    \email    <levi@leviperez.dev>                 \n
    \discord  [Leviathan#2318](https://discordapp.com/channels/@me)
    \copyleft @ref LICENSE (<https://unlicense.org>)
\ll ***************************************************************************
\ll ** -- FILE USAGE ------------------------------------------------------- **
\ll ***************************************************************************
    \brief    Keep common defs local.
\ll ***************************************************************************
\ll ** -- DEVELOPMENT HISTORY & ROADMAP ------------------------------------ **
\ll ***************************************************************************
    \version  0.1.0
    \created  2020-02-07 (18:01:43)
******************************************************************************/

# ifdef HURRY_DEFCOMMON_H_
#   undef HURRY_DEFCOMMON_H_
#   undef DEFER
#   undef ENCASE
#   undef STR_
#   undef STR
#   undef CONCAT_
#   undef CONCAT
#   undef TRICAT
#   undef EXPAND_
#   undef EXPAND
#   undef UNUSED
#   undef bitsizeof
# endif

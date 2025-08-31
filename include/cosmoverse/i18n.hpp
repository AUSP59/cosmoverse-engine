
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <string>
#if defined(COSMO_I18N) && defined(HAVE_GETTEXT)
  #include <libintl.h>
  #define _(x) gettext(x)
#else
  #define _(x) x
#endif
inline const char* cosmo_gettext(const char* s) { return _(s); }

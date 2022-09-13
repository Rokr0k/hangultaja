bin_PROGRAMS = hangultaja

hangultaja_SOURCES = main.cpp hangul.cpp hangul.hpp taja.cpp taja.hpp
hangultaja_CXXFLAGS = $(ncursesw_CFLAGS) $(libhangul_CFLAGS)
hangultaja_LDADD = $(ncursesw_LIBS) $(libhangul_LIBS)

EXTRA_DIST = res
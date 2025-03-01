#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(CVM-S Improved, 4.26)
AC_CONFIG_SRCDIR([src])
AM_INIT_AUTOMAKE([foreign no-exeext])
AC_PROG_RANLIB

# Checks for programs.
AC_PROG_CC
AC_PROG_FC
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_RANLIB
AC_PROG_LN_S

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

##check optional large data path 
if test x"$CVM_LARGEDATA_DIR" != x; then
   # test directory existence
   CVMSI_LARGEDATA_DIR=$CVM_LARGEDATA_DIR/model/cvmsi_i26
   AC_CHECK_FILE($CVM_LARGEDATA_DIR/model/cvmsi_i26/box.dat, [], [AC_MSG_ERROR(["CVMSI data not found in cvmsi"])])
   AM_CONDITIONAL([WITH_CVMSI_LARGEDATA_DIR], true)
   AC_SUBST(CVMSI_LARGEDATA_DIR)
else
   AM_CONDITIONAL(WITH_CVMSI_LARGEDATA_DIR, false)
fi


# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset pow sqrt strchr])

AC_CONFIG_FILES([Makefile src/Makefile data/Makefile data/cvms/Makefile test/Makefile])
AC_OUTPUT

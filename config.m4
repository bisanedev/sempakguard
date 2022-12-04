dnl $Id$
dnl config.m4 for extension sempakguard

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(sempakguard, for sempakguard support,
dnl Make sure that the comment is aligned:
dnl [  --with-sempakguard             Include sempakguard support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(sempakguard, whether to enable sempakguard support,
dnl Make sure that the comment is aligned:
dnl [  --enable-sempakguard           Enable sempakguard support])

if test "$PHP_SEMPAKGUARD" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-sempakguard -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/sempakguard.h"  # you most likely want to change this
  dnl if test -r $PHP_SEMPAKGUARD/$SEARCH_FOR; then # path given as parameter
  dnl   SEMPAKGUARD_DIR=$PHP_SEMPAKGUARD
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for sempakguard files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SEMPAKGUARD_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SEMPAKGUARD_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the sempakguard distribution])
  dnl fi

  dnl # --with-sempakguard -> add include path
  dnl PHP_ADD_INCLUDE($SEMPAKGUARD_DIR/include)

  dnl # --with-sempakguard -> check for lib and symbol presence
  dnl LIBNAME=sempakguard # you may want to change this
  dnl LIBSYMBOL=sempakguard # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SEMPAKGUARD_DIR/$PHP_LIBDIR, SEMPAKGUARD_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SEMPAKGUARDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong sempakguard lib version or lib not found])
  dnl ],[
  dnl   -L$SEMPAKGUARD_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SEMPAKGUARD_SHARED_LIBADD)

  PHP_NEW_EXTENSION(sempakguard, sempakguard.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi

PHP_ARG_WITH(termbox, for termbox support,
[  --with-termbox             Include termbox support])

if test "$PHP_TERMBOX" != "no"; then
  dnl
  dnl Find header files
  dnl
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/termbox.h"  
  if test -r $PHP_TERMBOX/$SEARCH_FOR; then
    TERMBOX_DIR=$PHP_TERMBOX
  else
    AC_MSG_CHECKING([for termbox files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        TERMBOX_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  if test -z "$TERMBOX_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please install termbox development files])
  fi
  PHP_ADD_INCLUDE($TERMBOX_DIR/include)

  dnl
  dnl Check library
  dnl
  LIBNAME=termbox
  LIBSYMBOL=tb_init
  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TERMBOX_DIR/$PHP_LIBDIR, TERMBOX_SHARED_LIBADD)
    AC_DEFINE(HAVE_TERMBOXLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong termbox lib version or lib not found])
  ],[
    -L$TERMBOX_DIR/$PHP_LIBDIR -lm
  ])
  PHP_SUBST(TERMBOX_SHARED_LIBADD)

  PHP_NEW_EXTENSION(termbox, termbox.c, $ext_shared)
fi

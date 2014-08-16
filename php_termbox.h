/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_TERMBOX_H
#define PHP_TERMBOX_H

extern zend_module_entry termbox_module_entry;
#define phpext_termbox_ptr &termbox_module_entry

#ifdef PHP_WIN32
#	define PHP_TERMBOX_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_TERMBOX_API __attribute__ ((visibility("default")))
#else
#	define PHP_TERMBOX_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_TERMBOX_VERSION "0.1"

#include <termbox.h>

PHP_MINIT_FUNCTION(termbox);
PHP_MSHUTDOWN_FUNCTION(termbox);
PHP_MINFO_FUNCTION(termbox);

PHP_FUNCTION(termbox_init);
PHP_FUNCTION(termbox_shutdown);
PHP_FUNCTION(termbox_width);
PHP_FUNCTION(termbox_height);
PHP_FUNCTION(termbox_clear);
PHP_FUNCTION(termbox_set_clear_attributes);
PHP_FUNCTION(termbox_present);
PHP_FUNCTION(termbox_set_cursor);
PHP_FUNCTION(termbox_change_cell);
PHP_FUNCTION(termbox_select_input_mode);
PHP_FUNCTION(termbox_select_output_mode);
PHP_FUNCTION(termbox_peek_event);
PHP_FUNCTION(termbox_poll_event);
PHP_FUNCTION(termbox_utf8_char_to_unicode);
PHP_FUNCTION(termbox_utf8_unicode_to_char);
PHP_FUNCTION(termbox_print);

#endif	/* PHP_TERMBOX_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

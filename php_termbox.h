/*
  +----------------------------------------------------------------------+
  | termbox                                                              |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License"); you  |
  | may not use this file except in compliance with the License. You may |
  | obtain a copy of the License at                                      |
  | http://www.apache.org/licenses/LICENSE-2.0                           |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied. See the License for the specific language governing         |
  | permissions and limitations under the License.                       |
  +----------------------------------------------------------------------+
  | Author: Adam Saponara <adam@atoi.cc>                                 |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_TERMBOX_H
#define PHP_TERMBOX_H

extern zend_module_entry termbox_module_entry;
#define phpext_termbox_ptr &termbox_module_entry

#ifdef PHP_WIN32
#    define PHP_TERMBOX_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_TERMBOX_API __attribute__ ((visibility("default")))
#else
#    define PHP_TERMBOX_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_TERMBOX_VERSION "0.1.2"

#include <termbox.h>

#define TB_ERROR_NONE 0
#define TB_ERROR_NOT_INITIALIZED -100
#define TB_ERROR_ALREADY_INITIALIZED -101
#define TB_ERROR_COULD_NOT_READ_INPUT -102
#define TB_ERROR_INVALID_MODE -103

#define PHP_TERMBOX_ENSURE_INITIALIZED() do { \
    if (TERMBOX_G(is_initialized) != 1) { \
        TERMBOX_G(last_error) = TB_ERROR_NOT_INITIALIZED; \
        RETURN_FALSE; \
    } \
} while (0)

ZEND_BEGIN_MODULE_GLOBALS(termbox)
int is_initialized;
int last_error;
ZEND_END_MODULE_GLOBALS(termbox)

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
PHP_FUNCTION(termbox_set_input_mode);
PHP_FUNCTION(termbox_get_input_mode);
PHP_FUNCTION(termbox_set_output_mode);
PHP_FUNCTION(termbox_get_output_mode);
PHP_FUNCTION(termbox_peek_event);
PHP_FUNCTION(termbox_poll_event);
PHP_FUNCTION(termbox_utf8_char_to_unicode);
PHP_FUNCTION(termbox_utf8_unicode_to_char);
PHP_FUNCTION(termbox_print);
PHP_FUNCTION(termbox_last_error);

#ifdef ZTS
#define TERMBOX_G(v) TSRMG(termbox_globals_id, zend_termbox_globals *, v)
#else
#define TERMBOX_G(v) (termbox_globals.v)
#endif

#endif    /* PHP_TERMBOX_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

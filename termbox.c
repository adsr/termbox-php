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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_termbox.h"

#include <termbox.h>

ZEND_DECLARE_MODULE_GLOBALS(termbox)

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_set_clear_attributes, 0, 0, 2)
        ZEND_ARG_INFO(0, fg)
        ZEND_ARG_INFO(0, bg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_set_cursor, 0, 0, 2)
        ZEND_ARG_INFO(0, x)
        ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_change_cell, 0, 0, 5)
        ZEND_ARG_INFO(0, x)
        ZEND_ARG_INFO(0, y)
        ZEND_ARG_INFO(0, ch)
        ZEND_ARG_INFO(0, fg)
        ZEND_ARG_INFO(0, bg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_mode, 0, 0, 1)
        ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_peek_event, 0, 0, 1)
        ZEND_ARG_INFO(0, timeout_ms)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_utf8_char_to_unicode, 0, 0, 1)
        ZEND_ARG_INFO(0, char)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_utf8_unicode_to_char, 0, 0, 1)
        ZEND_ARG_INFO(0, unicode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_termbox_print, 0, 0, 5)
        ZEND_ARG_INFO(0, str)
        ZEND_ARG_INFO(0, x)
        ZEND_ARG_INFO(0, y)
        ZEND_ARG_INFO(0, fg)
        ZEND_ARG_INFO(0, bg)
ZEND_END_ARG_INFO()

/* {{{ termbox_functions[]
 *
 * Every user visible function must have an entry in termbox_functions[].
 */
const zend_function_entry termbox_functions[] = {
    PHP_FE(termbox_init,                 arginfo_termbox_none)
    PHP_FE(termbox_shutdown,             arginfo_termbox_none)
    PHP_FE(termbox_width,                arginfo_termbox_none)
    PHP_FE(termbox_height,               arginfo_termbox_none)
    PHP_FE(termbox_clear,                arginfo_termbox_none)
    PHP_FE(termbox_set_clear_attributes, arginfo_termbox_set_clear_attributes)
    PHP_FE(termbox_present,              arginfo_termbox_none)
    PHP_FE(termbox_set_cursor,           arginfo_termbox_set_cursor)
    PHP_FE(termbox_change_cell,          arginfo_termbox_change_cell)
    PHP_FE(termbox_set_input_mode,       arginfo_termbox_mode)
    PHP_FE(termbox_get_input_mode,       arginfo_termbox_none)
    PHP_FE(termbox_set_output_mode,      arginfo_termbox_mode)
    PHP_FE(termbox_get_output_mode,      arginfo_termbox_none)
    PHP_FE(termbox_peek_event,           arginfo_termbox_peek_event)
    PHP_FE(termbox_poll_event,           arginfo_termbox_none)
    PHP_FE(termbox_utf8_char_to_unicode, arginfo_termbox_utf8_char_to_unicode)
    PHP_FE(termbox_utf8_unicode_to_char, arginfo_termbox_utf8_unicode_to_char)
    PHP_FE(termbox_print,                arginfo_termbox_print)
    PHP_FE(termbox_last_error,           arginfo_termbox_none)
#ifdef PHP_FE_END
    PHP_FE_END    /* Must be the last line in termbox_functions[] */
#else
    {NULL, NULL, NULL}
#endif
};
/* }}} */

/* {{{ termbox_module_entry
 */
zend_module_entry termbox_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "termbox",
    termbox_functions,
    PHP_MINIT(termbox),
    PHP_MSHUTDOWN(termbox),
    NULL,
    NULL,
    PHP_MINFO(termbox),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_TERMBOX_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TERMBOX
ZEND_GET_MODULE(termbox)
#endif

/* {{{
 * Initialize module globals */
static void _termbox_init_globals(zend_termbox_globals *g)
{
    memset(g, 0, sizeof(zend_termbox_globals));
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(termbox)
{
    /** Init globals */
    ZEND_INIT_MODULE_GLOBALS(termbox, _termbox_init_globals, NULL);

    /** Register constants */
    #define PHP_TERMBOX_CONSTANT(NAME) \
        zend_register_long_constant(#NAME, sizeof(#NAME), NAME, CONST_CS | CONST_PERSISTENT, module_number TSRMLS_CC);
    #include "constants.h"
    #undef PHP_TERMBOX_CONSTANT
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(termbox)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(termbox)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "termbox support", "enabled");
    php_info_print_table_header(2, "extension version", PHP_TERMBOX_VERSION);
    /** TODO libtermbox version? */
    php_info_print_table_end();
}
/* }}} */

/* {{{ proto bool termbox_init(void)
   Initializes the termbox library. This function should be called before any
   other functions. Return FALSE if an error occurs. */
PHP_FUNCTION(termbox_init)
{
    int retval;
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    if (TERMBOX_G(is_initialized) == 0) {
        /** Attempt to initialize */
        if ((retval = tb_init()) == 0) {
            /** Success! Set is_initialized to 1 */
            TERMBOX_G(is_initialized) = 1;
        } else {
            /** Failure. Set last_error */
            TERMBOX_G(last_error) = retval;
            RETURN_FALSE;
        }
    } else {
        /** Already initialized. Set last_error */
        TERMBOX_G(last_error) = TB_ERROR_ALREADY_INITIALIZED;
        RETURN_FALSE;
    }
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool termbox_shutdown(void)
   After successful initialization, the library must be finalized using this
   function. Return FALSE if not initialized yet. */
PHP_FUNCTION(termbox_shutdown)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    tb_shutdown();
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto mixed termbox_width(void)
   Returns the width of the buffer. Return FALSE if not initialized yet. */
PHP_FUNCTION(termbox_width)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    RETURN_LONG(tb_width());
}
/* }}} */

/* {{{ proto mixed termbox_height(void)
   Returns the height of the buffer. Return FALSE if not initialized yet. */
PHP_FUNCTION(termbox_height)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    RETURN_LONG(tb_height());
}
/* }}} */

/* {{{ proto bool termbox_clear(void)
   Clears the buffer using TB_DEFAULT color or the color/attributes set by
   termbox_set_clear_attributes(). Return FALSE if not initialized yet. */
PHP_FUNCTION(termbox_clear)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    tb_clear();
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool termbox_set_clear_attributes(int fg, int bg)
   Sets the default foreground and background attributes. Return FALSE if not
   initialized yet. */
PHP_FUNCTION(termbox_set_clear_attributes)
{
    long fg, bg;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &fg, &bg) == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    tb_set_clear_attributes((uint16_t)fg, (uint16_t)bg);
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool termbox_present()
   Syncronizes the internal back buffer with the terminal. Return FALSE if not
   initialized yet. */
PHP_FUNCTION(termbox_present)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    tb_present();
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool termbox_set_cursor(int x, int y)
   Sets the position of the cursor. Upper-left character is (0, 0). If you
   pass TB_HIDE_CURSOR as both coordinates, then the cursor will be hidden.
   Cursor is hidden by default. Return FALSE if not initialized yet. */
PHP_FUNCTION(termbox_set_cursor)
{
    long x, y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x, &y) == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    tb_set_clear_attributes((int)x, (int)y);
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool termbox_change_cell(int x, int y, int ch, int fg, int bg)
   Changes cell's parameters in the internal back buffer at the specified
   position. Return FALSE if not initialized yet. */
PHP_FUNCTION(termbox_change_cell)
{
    long x, y, ch, fg, bg;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lllll", &x, &y, &ch, &fg, &bg) == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    tb_change_cell((int)x, (int)y, (uint32_t)ch, (uint16_t)fg, (uint16_t)bg);
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool termbox_set_input_mode(int mode)
    Sets the termbox input mode: TB_INPUT_ESC or TB_INPUT_ALT. Return FALSE
    if not yet initialized. */
PHP_FUNCTION(termbox_set_input_mode)
{
    long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &mode) == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    if (mode != TB_INPUT_ESC && mode != TB_INPUT_ALT) {
        TERMBOX_G(last_error) = TB_ERROR_INVALID_MODE;
        RETURN_FALSE;
    }
    tb_select_input_mode((int)mode);
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto mixed termbox_get_input_mode()
    Return the current termbox input mode: TB_INPUT_ESC or TB_INPUT_ALT.
    Return FALSE if not yet initialized. */
PHP_FUNCTION(termbox_get_input_mode) {
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    RETURN_LONG(tb_select_input_mode(TB_INPUT_CURRENT));
}
/* }}} */

/* {{{ proto bool termbox_set_output_mode(int mode)
   Sets the termbox output mode. Termbox has three output options:
   TB_OUTPUT_256, TB_OUTPUT_216, or TB_OUTPUT_GRAYSCALE. Return FALSE if not
   yet initialized. */
PHP_FUNCTION(termbox_set_output_mode)
{
    long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &mode) == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    if (mode != TB_OUTPUT_256 && mode != TB_OUTPUT_216 && mode != TB_OUTPUT_GRAYSCALE) {
        TERMBOX_G(last_error) = TB_ERROR_INVALID_MODE;
        RETURN_FALSE;
    }
    tb_select_output_mode((int)mode);
    RETURN_TRUE;
}
/* }}} */

/* {{{ proto mixed termbox_get_output_mode()
    Return the current termbox output mode: TB_OUTPUT_256, TB_OUTPUT_216, or
    TB_OUTPUT_GRAYSCALE. Return FALSE if not yet initialized. */
PHP_FUNCTION(termbox_get_output_mode) {
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    PHP_TERMBOX_ENSURE_INITIALIZED();
    RETURN_LONG(tb_select_output_mode(TB_OUTPUT_CURRENT));
}
/* }}} */

/* {{{ Convert a termbox event to a PHP array
 */
static void _termbox_event_to_php_array(struct tb_event *event, zval *event_arr) {
    add_assoc_long_ex(event_arr, "type", sizeof("type"), (long)event->type);
    add_assoc_long_ex(event_arr, "mod", sizeof("mod"), (long)event->mod);
    add_assoc_long_ex(event_arr, "key", sizeof("key"), (long)event->key);
    add_assoc_long_ex(event_arr, "ch", sizeof("ch"), (long)event->ch);
    add_assoc_long_ex(event_arr, "w", sizeof("w"), (long)event->w);
    add_assoc_long_ex(event_arr, "h", sizeof("h"), (long)event->h);
}
/* }}} */

/* {{{ proto mixed termbox_peek_event(int timeout_ms)
   Wait for an event up to 'timeout' milliseconds. If an event was available,
   return an array containing event info. If no event was available, return
   NULL. If an error occurrs, return FALSE. */
PHP_FUNCTION(termbox_peek_event)
{
    long timeout_ms;
    struct tb_event event;
    int rc;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &timeout_ms) == FAILURE) {
        return;
    }

    PHP_TERMBOX_ENSURE_INITIALIZED();

    rc = tb_peek_event(&event, (int)timeout_ms);
    if (rc == -1) {
        TERMBOX_G(last_error) = TB_ERROR_COULD_NOT_READ_INPUT;
        RETURN_FALSE;
    } else if (rc == 0) {
        RETURN_NULL();
    }

    array_init(return_value);
    _termbox_event_to_php_array(&event, return_value);
}
/* }}} */

/* {{{ proto mixed termbox_poll_event()
   Wait for an event forever and return an array containing event info. If an
   error occurs, return FALSE. */
PHP_FUNCTION(termbox_poll_event)
{
    struct tb_event event;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    PHP_TERMBOX_ENSURE_INITIALIZED();

    if (tb_poll_event(&event) == -1) {
        TERMBOX_G(last_error) = TB_ERROR_COULD_NOT_READ_INPUT;
        RETURN_FALSE;
    }

    array_init(return_value);
    _termbox_event_to_php_array(&event, return_value);
}
/* }}} */

/* {{{ proto mixed termbox_utf8_char_to_unicode(string char)
   Return the 32-bit unicode value of 'char' or FALSE if 'char' is empty. */
PHP_FUNCTION(termbox_utf8_char_to_unicode)
{
    char *str;
    int str_len;
    uint32_t unicode_int;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
        return;
    }

    unicode_int = 0;
    if (str_len < 1 || tb_utf8_char_to_unicode(&unicode_int, str) == TB_EOF) {
        RETURN_FALSE;
    }
    RETURN_LONG(unicode_int);
}
/* }}} */

/* {{{ proto string termbox_utf8_unicode_to_char(int char)
   Return the UTF8 string version of the 32-bit unicode value 'char'. */
PHP_FUNCTION(termbox_utf8_unicode_to_char)
{
    char str[7];
    int str_len;
    long unicode;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &unicode) == FAILURE) {
        return;
    }

    if (unicode > 0) {
        str_len = tb_utf8_unicode_to_char((char*)&str, (uint32_t)unicode);
    } else {
        str[0] = '\0';
        str_len = 0;
    }

    RETURN_STRINGL(str, str_len, 1);
}
/* }}} */

/* {{{ proto bool termbox_print(string str, int x, int y, int fg, int bg)
   Print str at coordinate x, y with attributes fg, bg. If an error occurs,
   return FALSE. */
PHP_FUNCTION(termbox_print)
{
    char *str;
    int str_len;
    long x, y, fg, bg;
    uint32_t unicode;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sllll", &str, &str_len, &x, &y, &fg, &bg) == FAILURE) {
        return;
    }

    PHP_TERMBOX_ENSURE_INITIALIZED();

    if (str_len > 0) {
        while (*str) {
            str += tb_utf8_char_to_unicode(&unicode, str);
            tb_change_cell(x, y, unicode, fg, bg);
            x += 1;
        }
    }

    RETURN_TRUE;
}

/* {{{ proto int termbox_last_error(void)
   Returns the last error code. */
PHP_FUNCTION(termbox_last_error)
{
    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }
    RETURN_LONG(TERMBOX_G(last_error));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

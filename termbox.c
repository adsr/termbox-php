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

/* {{{ termbox_functions[]
 *
 * Every user visible function must have an entry in termbox_functions[].
 */
const zend_function_entry termbox_functions[] = {
    PHP_FE(termbox_init, NULL)
    PHP_FE(termbox_shutdown, NULL)
    PHP_FE(termbox_width, NULL)
    PHP_FE(termbox_height, NULL)
    PHP_FE(termbox_clear, NULL)
    PHP_FE(termbox_set_clear_attributes, NULL)
    PHP_FE(termbox_present, NULL)
    PHP_FE(termbox_set_cursor, NULL)
    PHP_FE(termbox_change_cell, NULL)
    PHP_FE(termbox_select_input_mode, NULL)
    PHP_FE(termbox_select_output_mode, NULL)
    PHP_FE(termbox_peek_event, NULL)
    PHP_FE(termbox_poll_event, NULL)
    PHP_FE(termbox_utf8_char_to_unicode, NULL)
    PHP_FE(termbox_utf8_unicode_to_char, NULL)
    PHP_FE(termbox_print, NULL)
	PHP_FE_END	/* Must be the last line in termbox_functions[] */
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

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(termbox)
{
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
    php_info_print_table_header(2, "libtermbox version", "1.0.0");
	php_info_print_table_end();
}
/* }}} */

/* {{{ proto int termbox_init(void)
   Initializes the termbox library. This function should be called before any
   other functions. */
PHP_FUNCTION(termbox_init)
{
    RETURN_LONG(tb_init());
}
/* }}} */

/* {{{ proto void termbox_shutdown(void)
   After successful initialization, the library must be finalized using this
   function. */
PHP_FUNCTION(termbox_shutdown)
{
    tb_shutdown();
}
/* }}} */

/* {{{ proto int termbox_width(void)
   Returns the width of the buffer. */
PHP_FUNCTION(termbox_width)
{
    RETURN_LONG(tb_width());
}
/* }}} */

/* {{{ proto void termbox_height(void)
   Returns the height of the buffer. */
PHP_FUNCTION(termbox_height)
{
    RETURN_LONG(tb_height());
}
/* }}} */

/* {{{ proto void termbox_clear(void)
   Clears the buffer using TB_DEFAULT color or the color/attributes set by
   termbox_set_clear_attributes(). */
PHP_FUNCTION(termbox_clear)
{
    tb_clear();
}
/* }}} */

/* {{{ proto void termbox_set_clear_attributes(int fg, int bg)
   Sets the default foreground and background attributes. */
PHP_FUNCTION(termbox_set_clear_attributes)
{
    long fg, bg;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &fg, &bg) == FAILURE) {
        return;
    }
    tb_set_clear_attributes((uint16_t)fg, (uint16_t)bg);
}
/* }}} */

/* {{{ proto void termbox_present()
   Syncronizes the internal back buffer with the terminal. */
PHP_FUNCTION(termbox_present)
{
    tb_present();
}
/* }}} */

/* {{{ proto void termbox_set_cursor(int x, int y)
   Sets the position of the cursor. Upper-left character is (0, 0). If you
   pass TB_HIDE_CURSOR as both coordinates, then the cursor will be hidden.
   Cursor is hidden by default. */
PHP_FUNCTION(termbox_set_cursor)
{
    long x, y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x, &y) == FAILURE) {
        return;
    }
    tb_set_clear_attributes((int)x, (int)y);
}
/* }}} */

/* {{{ proto void termbox_change_cell(int x, int y, int ch, int fg, int bg)
   Changes cell's parameters in the internal back buffer at the specified
   position. */
PHP_FUNCTION(termbox_change_cell)
{
    long x, y, ch, fg, bg;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lllll", &x, &y, &ch, &fg, &bg) == FAILURE) {
        return;
    }
    tb_change_cell((int)x, (int)y, (uint32_t)ch, (uint16_t)fg, (uint16_t)bg);
}
/* }}} */

/* {{{ proto int termbox_select_input_mode(int mode)
    Sets the termbox input mode: TB_INPUT_ESC or TB_INPUT_ALT. If 'mode' is
    TB_INPUT_CURRENT, it returns the current input mode. */
PHP_FUNCTION(termbox_select_input_mode)
{
    long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &mode) == FAILURE) {
        return;
    }
    RETURN_LONG(tb_select_input_mode((int)mode));
}
/* }}} */

/* {{{ proto int termbox_select_output_mode(int mode)
   Sets the termbox output mode. Termbox has three output options:
   TB_OUTPUT_256, TB_OUTPUT_216, or TB_OUTPUT_GRAYSCALE. If 'mode' is
   TB_OUTPUT_CURRENT, it returns the current output mode. */
PHP_FUNCTION(termbox_select_output_mode)
{
    long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &mode) == FAILURE) {
        return;
    }
    RETURN_LONG(tb_select_output_mode((int)mode));

}
/* }}} */

/* {{{ Convert a termbox event to a PHP array
 */
static void _termbox_event_to_php_array(struct tb_event *event, zval *event_arr) {
    if (Z_TYPE_P(event_arr) != IS_ARRAY) {
        zval_dtor(event_arr);
        array_init(event_arr);
    } else {
        zend_hash_clean(Z_ARRVAL_P(event_arr));
    }
    add_assoc_long(event_arr, "type", (long)event->type);
    add_assoc_long(event_arr, "mod", (long)event->mod);
    add_assoc_long(event_arr, "key", (long)event->key);
    add_assoc_long(event_arr, "ch", (long)event->ch);
    add_assoc_long(event_arr, "w", (long)event->w);
    add_assoc_long(event_arr, "h", (long)event->h);
}
/* }}} */

/* {{{ proto int termbox_peek_event(array &event, int timeout_ms)
   Wait for an event up to 'timeout' milliseconds and fill the 'event' array
   with it, when the event is available. Returns the type of the event (one of
   TB_EVENT_* constants) or -1 if there was an error or 0 in case there were
   no event during 'timeout' period. */
PHP_FUNCTION(termbox_peek_event)
{
    zval *event_arr;
    long timeout_ms;
    struct tb_event event;
    int rc;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &event_arr, &timeout_ms) == FAILURE) {
        return;
    }

    if ((rc = tb_peek_event(&event, (int)timeout_ms)) > 0) {
        _termbox_event_to_php_array(&event, event_arr);
    }

    RETURN_LONG(rc);
}
/* }}} */

/* {{{ proto int termbox_poll_event(array &event)
   Wait for an event forever and fill the 'event' array with it, when the
   event is available. Returns the type of the event (one of TB_EVENT_*
   constants) or -1 if there was an error. */
PHP_FUNCTION(termbox_poll_event)
{
    zval *event_arr;
    struct tb_event event;
    int rc;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &event_arr) == FAILURE) {
        return;
    }

    if ((rc = tb_poll_event(&event)) > 0) {
        _termbox_event_to_php_array(&event, event_arr);
    }

    RETURN_LONG(rc);
}
/* }}} */

/* {{{ proto int termbox_utf8_char_to_unicode(string char, int &unicode)
   Return the 32-bit unicode value of 'char'. */
PHP_FUNCTION(termbox_utf8_char_to_unicode)
{
    char *str;
    int str_len;
    zval *unicode;
    uint32_t unicode_int;
    int rc;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz", &str, &str_len, &unicode) == FAILURE) {
        return;
    }

    rc = tb_utf8_char_to_unicode(&unicode_int, (const char*)str);

    convert_to_long_ex(&unicode);
    Z_LVAL_P(unicode) = unicode_int;

    RETURN_LONG(rc);
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

    str_len = tb_utf8_unicode_to_char((char*)&str, (uint32_t)unicode);

    RETURN_STRINGL(str, str_len, 1);
}
/* }}} */

/* {{{ proto void termbox_print(string str, int x, int y, int fg, int bg)
   Print str at coordinate x, y with attributes fg, bg. */
PHP_FUNCTION(termbox_print)
{
    char *str;
    int str_len;
    long x, y, fg, bg;
    uint32_t unicode;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sllll", &str, &str_len, &x, &y, &fg, &bg) == FAILURE) {
        return;
    }

    if (str_len > 0) {
        while (*str) {
            str += tb_utf8_char_to_unicode(&unicode, str);
            tb_change_cell(x, y, unicode, fg, bg);
            x += 1;
        }
    }
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

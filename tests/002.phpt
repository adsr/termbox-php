--TEST--
Check UTF-8 to Unicode conversion
--SKIPIF--
<?php if (!extension_loaded("termbox")) print "skip"; ?>
--FILE--
<?php 
var_dump(termbox_utf8_char_to_unicode('A'));
var_dump(termbox_utf8_char_to_unicode('0'));
var_dump(termbox_utf8_char_to_unicode(' '));
var_dump(termbox_utf8_char_to_unicode("\xc7\xa2"));
var_dump(termbox_utf8_char_to_unicode("\x00"));
var_dump(termbox_utf8_char_to_unicode(''));
--EXPECT--
int(65)
int(48)
int(32)
int(482)
bool(false)
bool(false)

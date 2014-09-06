--TEST--
Check correctness of UTF-8 functions
--SKIPIF--
<?php if (!extension_loaded("termbox")) print "skip"; ?>
--FILE--
<?php 
$uc = null;
var_dump(termbox_utf8_unicode_to_char(65));
var_dump(termbox_utf8_unicode_to_char(48));
var_dump(termbox_utf8_unicode_to_char(32));
var_dump(termbox_utf8_unicode_to_char(0));
$ae = termbox_utf8_unicode_to_char(482);
var_dump(mb_check_encoding($ae, 'UTF-8'));
var_dump(mb_strlen($ae));
--EXPECT--
string(1) "A"
string(1) "0"
string(1) " "
string(0) ""
bool(true)
int(2)

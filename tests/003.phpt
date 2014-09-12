--TEST--
Check Unicode to UTF-8 conversion
--SKIPIF--
<?php
if (!extension_loaded("termbox")) print "skip termbox extensio is not loaded";
if (!extension_loaded("mbstring")) print "skip mbstring extension is not loaded";
?>
--FILE--
<?php 
$uc = null;
var_dump(termbox_utf8_unicode_to_char(65));
var_dump(termbox_utf8_unicode_to_char(48));
var_dump(termbox_utf8_unicode_to_char(32));
var_dump(termbox_utf8_unicode_to_char(0));
$ae = termbox_utf8_unicode_to_char(482);
var_dump(mb_check_encoding($ae, 'UTF-8'));
var_dump(mb_strlen($ae, 'UTF-8'));
?>
--EXPECT--
string(1) "A"
string(1) "0"
string(1) " "
string(0) ""
bool(true)
int(1)

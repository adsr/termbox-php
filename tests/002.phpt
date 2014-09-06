--TEST--
Check correctness of UTF-8 functions
--SKIPIF--
<?php if (!extension_loaded("termbox")) print "skip"; ?>
--FILE--
<?php 
$uc = null;
termbox_utf8_char_to_unicode('A', $uc); var_dump($uc);
termbox_utf8_char_to_unicode('0', $uc); var_dump($uc);
termbox_utf8_char_to_unicode(' ', $uc); var_dump($uc);
termbox_utf8_char_to_unicode("\xc7\xa2", $uc); var_dump($uc);
termbox_utf8_char_to_unicode("\x00", $uc); var_dump($uc);
termbox_utf8_char_to_unicode('', $uc); var_dump($uc);
--EXPECT--
int(65)
int(48)
int(32)
int(482)
int(0)
int(0)

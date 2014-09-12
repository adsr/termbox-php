--TEST--
Check for error on uninitialized shutdown
--SKIPIF--
<?php if (!extension_loaded("termbox")) print "skip"; ?>
--FILE--
<?php 
var_dump(termbox_shutdown());
var_dump(termbox_last_error());
--EXPECT--
bool(false)
int(-100)

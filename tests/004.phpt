--TEST--
Check for defined constants
--SKIPIF--
<?php if (!extension_loaded("termbox")) print "skip"; ?>
--FILE--
<?php 
var_dump(defined('TB_KEY_F1'));
--EXPECT--
bool(true)

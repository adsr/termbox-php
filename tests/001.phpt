--TEST--
Check for termbox presence
--SKIPIF--
<?php if (!extension_loaded("termbox")) print "skip"; ?>
--FILE--
<?php 
echo "termbox extension is available";
--EXPECT--
termbox extension is available

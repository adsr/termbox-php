--TEST--
Check for non-integer return value on termbox_peek_event
--SKIPIF--
<?php if (!extension_loaded("termbox")) print "skip"; ?>
--FILE--
<?php
var_dump(is_int(termbox_peek_event(0)));
--EXPECT--
bool(false)

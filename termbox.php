<?php

if (!extension_loaded('termbox')) {
	dl('termbox.' . PHP_SHLIB_SUFFIX);
}

if (!function_exists('termbox_init')) {
    echo "termbox module not found\n";
    exit(1);
}

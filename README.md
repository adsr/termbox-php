# termbox-php

termbox-php is a termbox wrapper for PHP. termbox is a robust, minimal
alternative to ncurses. See https://github.com/nsf/termbox for more info.

### Requirements

* PHP
* termbox

Your distro may have pre-built packages for these. If not, you must build these 
from source as well.

### Building

    $ # Clone repo
    $ git clone https://github.com/adsr/termbox-php.git
    $ cd termbox-php
    $
    $ # Build extension
    $ phpize && ./configure && make
    $
    $ # Run keyboard demo
    $ php -dextension=`pwd`/modules/termbox.so examples/termbox.php
    $
    $ # Optionally install
    $ sudo make install

### PECL

You may also install termbox-php via PECL.

    $ sudo pecl install channel://pecl.php.net/termbox-0.1.3

### Screenshot

Below is a screenshot of termbox-php in action.

![termbox-php in action](http://i.imgur.com/vI52dsl.png)

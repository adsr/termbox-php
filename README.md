termbox-php
===========

termbox-php is a termbox wrapper for PHP. Termbox is a robust, minimal
alternative to ncurses. See https://github.com/nsf/termbox

To install:

    $ # Follow installation instructions for termbox
    $ git clone https://github.com/adsr/termbox-php.git
    $ cd termbox-php
    $ phpize && ./configure && make
    $ php -denable_dl=on -dextension=`pwd`/modules/termbox.so termbox.php
    $ sudo make install

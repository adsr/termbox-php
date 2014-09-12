termbox-php
===========

termbox-php is a termbox wrapper for PHP. Termbox is a robust, minimal
alternative to ncurses. See https://github.com/nsf/termbox

To install:

    $ # Follow installation instructions for termbox
    $
    $ # Clone repo
    $ git clone https://github.com/adsr/termbox-php.git
    $ cd termbox-php
    $
    $ # Build extension
    $ phpize && ./configure && make
    $
    $ # Run keyboard demo
    $ php -denable_dl=on -dextension=`pwd`/modules/termbox.so examples/termbox.php
    $
    $ # Optionally install
    $ sudo make install

Screenshot of termbox-php in action:

![termbox-php in action](http://i.imgur.com/vI52dsl.png)

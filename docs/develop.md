---
layout: default

---

# Develop your own game!

You can develop your own games with just a little knowledge of programming (C++ / Wiring). 

## Hello Arco

There is this game called "Hello Arco" which is an equivalent for classic "Hello World" programs. You can use it as a boilerplate for developing your game.

<img data-src="{{ '/assets/images/hello_arco.png' | prepend: site.baseurl }}" class="img-responsive float-left mr-3 image-border">

The game structure is simple. There must be a folder inside the "games" directory. Then, inside the folder, there must be an .ino file with the same name as folder. This file is the main and only required file. 

You can divide your code into several .ino files, but this is just for clarity.

<div class="clearfix"></div>

## Arduino IDE

You load the main file "hello_arco.ino" into Arduino IDE. But wait, before uploading it to console, you must specify a port to which your console is connected.

<img data-src=" {{ '/assets/images/arduino_ide_select_port.png' | prepend: site.baseurl }}" class="img-responsive image-border">

<div class="clearfix"></div>

## Gamelib

<img data-src="{{ '/assets/images/gamelib.png' | prepend: site.baseurl }}" class="img-responsive float-left mr-3 image-border">

This is our (optional to use) library which can help you create better games. 

It comes with simple interfaces - drawing on display, playing sounds, dealing with user inputs and score. 

You can find it in "arduino/portable/sketchbook/libraries/gamelib".

<div class="clearfix"></div>

## Emulator

For Linux users out there, we have an emulator. You can find it in "not_emulator" folder. There is a README.md file with simple instructions on how to use it.

## [<< Make](/make.html) | Develop | [Play >>](/play.html)

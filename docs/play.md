---
layout: default

---

# Play and develop games

## Prerequisities

1. Download latest release of ARCO software from [GitHub]({{ site.github_url }}releases).
2. Extract it somewhere.
2. And install USB driver "arduino/drivers/Arduino_USB_Drivers-master" (Windows only).

## Use upload app to smoothly upload games

This option is the fastest way to get games to your game console and play (Windows only)!

1. Connect your game console to PC with USB cable
2. Run "game_uploader/game_uploader.exe"

<img data-src="{{ '/assets/images/arco-game-uploader.png' | prepend: site.baseurl }}" class="img-responsive">

## Use Arduino IDE

If you:

- cannot (or don't want to) use our upload script
- want to edit games or develop your own
- run Linux / Mac

Then you should use Arduino IDE:

1. Open bundled Arduino IDE "arduino/arduino.exe"
3. Run some games from the "games" directory

You can develop your own games with just a little knowledge of programming (C++ / Wiring). 
There is also game called "Hello Arco" which is an equivalent for classic "Hello World" programs.


##  [<< Make](/make.html) | Play

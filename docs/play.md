---
layout: default

---

# How to upload games and play

## Prerequisites

1. Download latest release of ARCO software from [GitHub]({{site.github_url}}releases).
2. Extract it somewhere.
2. And install corresponding USB driver "arduino/drivers/Arduino_USB_Drivers-master" (Windows only).

## Use Game Uploader to smoothly upload games to console

This option is the fastest way to get games to your game console and play (Windows only)!

1. Connect your game console to PC with USB cable
2. Run "game_uploader/game_uploader.exe"

<img data-src="{{ '/assets/images/arco_game_uploader.png' | prepend: site.baseurl }}" class="img-responsive image-border">

## Use Arduino IDE

If you:

- cannot (or don't want to) use our upload script
- want to edit games or develop your own
- run Linux / Mac

Then you should use Arduino IDE:

1. Open bundled Arduino IDE "arduino/arduino.exe"
3. Run some games from the "games" directory

##  [<< Develop](/develop.html) | Play

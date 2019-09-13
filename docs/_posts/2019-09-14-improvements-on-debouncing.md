---
layout: post
title:  "Improvements on debounce"
---

Yesterday I solved one very long-term problem. All buttons, 
especially start and action, suffered from a bouncing problem. Once you press
the button, it can triggers more times than needed.

There are two options on dealing with bouncing. You can go with hardware solution
or software.

Hardware option is just putting a capacitor into the right spot.

[Software option](https://github.com/MichalSkoula/arco-1500/commit/d512ac3cfece537e1b4565388511b7f02c2dfd52) consist of remebering the last time button was pressed and
do not allow pressing it within a short period of time, lets say 100-200 ms.


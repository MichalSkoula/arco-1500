---
# You don't need to edit this file, it's empty on purpose.
# Edit theme's home layout instead if you wanna make some changes
# See: https://jekyllrb.com/docs/themes/#overriding-theme-defaults
layout: default

---

## The gaming console, you've actually built!

ARCO 1500 is an open source, 8 bit DIY gaming console - both software and hardware. It comes bundled with:

- Arduino IDE (with U8G2 and our own Gamelib libraries)
- Game Uploader - for easy games uploading to console (Windows)
- Not Emulator - emulator for playing games on PCB (Linux)
- Games - currently 5 extra funny games
- Console case for 3D print


### A/ I want to build it all alone, with my parts

All you need is some affordable electronic stuff (Arduino), 3D printed case (optional) and programing skills. 
No PCB, soldering - just Arduino, breadboard, OLED, joystick, buzzer and some jumper cables. Use the 
<a href="{{ site.github_url }}">GitHub link</a> to get source files.

### B/ Where can i buy it?

You can also buy a nice, complete set and start in a few minutes. Visit our <a href="{{ site.bastlime_url }}">store</a>.


## Games

You can write your own games too!

<div class="photo-gallery">
    {% for image in site.data.games %}
        <a href="{{ image.image_path }}" data-fancybox="games" data-caption="{{ image.title}}">
            <figure>
                <img src="{{ image.image_path }}" alt="{{ image.title}}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

## Game console

If you want proper game experience

<div class="photo-gallery">
    {% for image in site.data.consoles %}
        <a href="{{ image.image_path }}" data-fancybox="gallery" data-caption="{{ image.title}}">
            <figure>
                <img src="{{ image.image_path }}" alt="{{ image.title}}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

## Prototypes

Some development moments

<div class="photo-gallery">
    {% for image in site.data.prototypes %}
        <a href="{{ image.image_path }}" data-fancybox="prototypes" data-caption="{{ image.title}}">
            <figure>
                <img src="{{ image.image_path }}" alt="{{ image.title}}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

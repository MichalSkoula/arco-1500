---
layout: default

---

## The gaming console, you can build by yourself!

ARCO 1500 is an open source, 8 bit DIY gaming console - both software and hardware. 

### A/ *I want to build it all alone, with my parts* [See how to build it](/build.html).

### B/ *I want to buy complete set.* [See where to buy it](/buy.html).

It comes with:

- Arduino IDE (with U8G2 and our own Gamelib libraries)
- Game Uploader - for easy games uploading to console (Windows)
- Not Emulator - emulator for playing games on PC, without console (Linux)
- [Games](#games) - currently {{ site.data.games | size }} extra funny games
- 3D printed [Console case](#game-console) 

## Games

You can write your own games too! Currently {{ site.data.games | size }} games.

<div class="photo-gallery">
    {% for image in site.data.games %}
        <a href="{{ image.image_path }}" data-fancybox="games-gallery" data-caption="{{ image.title | escape }}">
            <figure>
                <img src="{{ image.image_path }}" alt="{{ image.title | escape }}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

## Game console

If you want proper game experience.

<div class="photo-gallery">
    {% for image in site.data.consoles %}
        <a href="{{ image.image_path }}" data-fancybox="console-gallery" data-caption="{{ image.title | escape }}">
            <figure>
                <img src="{{ image.image_path }}" alt="{{ image.title | escape }}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

## Prototypes / Development

Some development moments captured for your pleasure.

<div class="photo-gallery">
    {% for image in site.data.prototypes %}
        <a href="{{ image.image_path }}" data-fancybox="prototypes-gallery" data-caption="{{ image.title | escape }}">
            <figure>
                <img src="{{ image.image_path }}" alt="{{ image.title | escape }}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

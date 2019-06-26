---
layout: default

---

## The gaming console, you can build by yourself!

ARCO 1500 is an open source, 8 bit DIY gaming console - both software and hardware. It comes with:

- Arduino IDE (with U8G2 and our own Gamelib libraries)
- Game Uploader - for easy games uploading to console (Windows)
- Not Emulator - emulator for playing games on PC, without console (Linux)
- [Games](#games) - currently {{ site.data.games | size }} extra funny games
- 3D printed [Console case](#game-console) 

## *I am ready!* [Get ARCO 1500](/get.html).

## Games

You can write your own games too! Currently {{ site.data.games | size }} games.

<div class="photo-gallery">
    {% for image in site.data.games %}
        <a href="{{ image.image_path }}" data-fancybox="games-gallery" data-caption="{{ image.title | escape }}">
            <figure>
                <img data-src="{{ image.image_path }}" alt="{{ image.title | escape }}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

## Game console

Get our [original game console](/get.html) to experience the proper feeling. Also some development moments captured for your pleasure.

<div class="photo-gallery">
    {% for image in site.data.prototypes %}
        <a href="{{ image.image_path }}" data-fancybox="prototypes-gallery" data-caption="{{ image.title | escape }}">
            <figure>
                <img data-src="{{ image.image_path }}" alt="{{ image.title | escape }}" />
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

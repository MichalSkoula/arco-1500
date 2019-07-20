---
layout: default

---

# The gaming console, you can build by yourself!

<div class="row">
    <div class="col-sm">
        <img data-src="/assets/images/prototypes/{{ site.data.prototypes[0].filename }}" alt="{{ image.title | escape }}" class="image-border" />
    </div>
    <div class="col-sm">
        <p>ARCO 1500 is an open source, 8 bit DIY gaming console - both software and hardware. It comes with:</p>
        <ul>
            <li><strong><a href="#games">Games</a></strong> - currently {{ site.data.games | size }} extra funny games + 1 boilerplate (Hello Arco)</li>
            <li>3D printed <strong><a href="#game-console">Console case</a></strong> </li>
            <li><strong>Arduino IDE</strong> (with U8G2 and our own Gamelib libraries) - to develop your own games</li>
            <li><strong>Game Uploader</strong> - for easy games uploading to console (only Windows)</li>
            <li><strong>Not Emulator</strong> - emulator for playing / testing games on PC, without console (only Linux)</li>
        </ul>
    </div>
</div>
# *I am ready!* &nbsp;&nbsp; [Get ARCO 1500](/get.html).


# Games

You can write your own games too! Currently {{ site.data.games | size }} games. These are screenhots from the emulator.

<div class="photo-gallery">
    {% for image in site.data.games %}
        <a href="/assets/images/games/{{ image.filename }}" data-fancybox="games-gallery" data-caption="{{ image.title | escape }}">
            <figure>
                <img data-src="/assets/images/games/{{ image.filename }}" alt="{{ image.title | escape }}" class="image-border"/>
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

# Game console

Get our [original game console](/get.html) to experience the proper feeling. Also some development moments captured for your pleasure.

<div class="photo-gallery">
    {% for image in site.data.prototypes %}
        <a href="/assets/images/prototypes/{{ image.filename }}" data-fancybox="prototypes-gallery" data-caption="{{ image.title | escape }}">
            <figure>
                <img data-src="/assets/images/prototypes/thumbnails/{{ image.filename }}" alt="{{ image.title | escape }}" class="image-border"/>
                <figcaption>
                    {{ image.title}}
                </figcaption>
            </figure>
        </a>
    {% endfor %}
</div>

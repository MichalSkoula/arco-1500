---
layout: default

---

# The gaming console, you can build by yourself!

<div class="row">
    <div class="col-sm">
        <a href="/assets/images/prototypes/{{ site.data.prototypes.first.filename }}" data-fancybox="main-image" data-caption="ARCO 1500">
            <img data-src="/assets/images/prototypes/thumbnails/{{ site.data.prototypes.first.filename }}" alt="{{ image.title | escape }}" class="image-border" />
        </a>
    </div>
    <div class="col-sm">
        <p>ARCO1500 is an open source, 8 bit DIY gaming console - both software and hardware.</p>
        <ul>
            <li><strong><a href="/games.html">Games</a></strong> - currently {{ site.data.games | size }} extra funny games</li>
            <li>3D printed <strong><a href="#game-console">Console case</a></strong> </li>
            <li><strong>Arduino IDE</strong> (with libraries) - to develop your own games</li>
            <li><strong>Game Uploader</strong> - so you can upload games easily to the console (Windows)</li>
            <li><strong>Not Emulator</strong> - emulator for testing games on PC (Windows, Linux), without console</li>
        </ul>
    </div>
</div>

# *I am ready!* &nbsp;[Get ARCO 1500](/get.html) &nbsp;now for just {{ site.arco_price }}€!

# Games 

Currently {{ site.data.games | size }} games.

<div class="photo-gallery">
    {% for image in site.data.games limit:4 %}
        <figure>
            <a href="/assets/images/games/{{ image.filename }}.png" data-fancybox="games-gallery" data-caption="{{ image.title | escape }}">
                <img data-src="/assets/images/games/{{ image.filename }}.png" alt="{{ image.title | escape }}" class="image-border"/>
            </a>
            <figcaption>
                {{ image.title}}
            </figcaption>
        </figure>
    {% endfor %}

    <a href="/games.html">Show all games >></a>
</div>

# Game console development

ARCO1500 is still in development stage. Here are some moments captured for your pleasure.

<div class="photo-gallery">
    {% for image in site.data.prototypes limit:4 %}
        <figure>
            <a href="/assets/images/prototypes/{{ image.filename }}" data-fancybox="prototypes-gallery" data-caption="{{ image.title | escape }}">
                <img data-src="/assets/images/prototypes/thumbnails/{{ image.filename }}" alt="{{ image.title | escape }}" class="image-border"/>
            </a>
            <figcaption>
                {{ image.title}}
            </figcaption>
        </figure>
    {% endfor %}
</div>
<a href="#all-prototypes" id="show-all-prototypes">Show all prototypes >></a>
<div class="photo-gallery" id="all-prototypes">
    {% for image in site.data.prototypes offset:4 %}
        <figure>
            <a href="/assets/images/prototypes/{{ image.filename }}" data-fancybox="prototypes-gallery" data-caption="{{ image.title | escape }}">
                <img data-src="/assets/images/prototypes/thumbnails/{{ image.filename }}" alt="{{ image.title | escape }}" class="image-border"/>
            </a>
            <figcaption>
                {{ image.title}}
            </figcaption>
        </figure>
    {% endfor %}
</div>

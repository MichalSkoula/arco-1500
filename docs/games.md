---
layout: default

---
<small><a href="/">Home</a> / Games</small>

# Games

Currently {{ site.data.games | size }} games. These are screenshots from the emulator.

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

## Your own game?

Learn how to develop your own game on [Develop](/develop.html) page.

Made your own game? Send it to us: <a href="mailto:{{ site.email }}">{{ site.email }}</a> and we will publish it here!

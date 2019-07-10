---
layout: default

---

# Develop games

Here's how you can open and run games like a pro:

1. Install USB driver CH341 (arduino/drivers/Arduino_USB_Drivers-master)
2. Open bundled Arduino IDE (arduino/arduino.exe)
3. Run some games from games directory

You can develop your own games with just a little knowledge of programming (C++ / Wiring).



## Premade games (currently {{ site.data.games | size }})

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



## [<< Make](/make.html) | Develop | [Play >>](/play.html)

---
# You don't need to edit this file, it's empty on purpose.
# Edit theme's home layout instead if you wanna make some changes
# See: https://jekyllrb.com/docs/themes/#overriding-theme-defaults
layout: default

images:
  - image_path: /assets/images/IMG_20190416_205053.jpg
    title: 3D printed case v1
  - image_path: /assets/images/IMG_20190417_142112.jpg
    title: 3D printed case v2

---

## More stuff coming soon

## Gallery 

<div class="photo-gallery">
    {% for image in page.images %}
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

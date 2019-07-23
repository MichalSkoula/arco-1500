---
layout: default

---

# Blog

<i class="fas fa-rss"></i> [RSS feed](feed.xml)


<ul>
  {% for post in site.posts %}
    <li>
        {{ post.date | date: "%-d %B %Y" }} <a href="{{ post.url }}">{{ post.title }}</a>
    </li>
  {% endfor %}
</ul>

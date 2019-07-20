## Jekyll on Windows + generating site

1. Ruby installer - https://jekyllrb.com/docs/installation/windows/
2. bundle install
3. bundle exec jekyll serve - then open localhost:4000

thumbnails are generated + commited with ImageMagick + git pre-commit hook:

```
#!/bin/sh
magick mogrify -path 'docs/assets/images/prototypes/thumbnails' -thumbnail 650x650  'docs/assets/images/prototypes/*'
git diff --name-only --cached | xargs -l git add
```

## Jekyll on Fedora + generating site

Dependencies - https://jekyllrb.com/docs/installation/other-linux/

zlib-devel

Then - https://jekyllrb.com/docs/installation/ubuntu/

But - https://ask.fedoraproject.org/en/question/91815/problem-installing-jekyll-in-fedora-24/?answer=91956#post-id-91956

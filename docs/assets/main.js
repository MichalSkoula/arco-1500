$(document).ready(function() {
    $('[data-fancybox="gallery"]').fancybox();

    $('a[href ^= "#"').smoothScroll();

    $("img[data-src]").Lazy();
});

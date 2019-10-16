$(document).ready(function() {
    $('[data-fancybox="gallery"]').fancybox();

    $('a[href ^= "#"]:not(#show-all-prototypes)').smoothScroll();

    $("img[data-src]").Lazy();

    $('#show-all-prototypes').click(function(event) {
        event.preventDefault();
        $(this).hide();
        $('#all-prototypes').css('display', 'flex');
    })
});

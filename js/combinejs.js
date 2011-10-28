/*
 *    Copyright (c) 2010 Just Another Video script
 *
 *    This file is part of Just Another Video script.
 *    Come to website for support or buying additional plugins/modules.
 *    http://justanothervideoscript.com/	
 */
function mycarousel_initCallback(carousel) {
    carousel.buttonNext.bind('click', function() {
        carousel.startAuto(0);
    });
    carousel.buttonPrev.bind('click', function() {
        carousel.startAuto(0);
    });
    carousel.clip.hover(function() {
        carousel.stopAuto();
    }, function() {
        carousel.startAuto();
    });
};
jQuery(document).ready(function() {
    jQuery('#mycarousel').jcarousel({
        auto: 5,
        wrap: 'last',
        initCallback: mycarousel_initCallback
    });
});


	buffcol="#2C4C5E";
	progcol="#007CC2";
	butcol="#007CC2";
	butovercol="#6CB9E4";
	tooltipcol="#007CC2";
	

		
try {
document.execCommand("BackgroundImageCache", false, true);
}
catch (err) {
}
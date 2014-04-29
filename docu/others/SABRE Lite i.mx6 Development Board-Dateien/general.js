jQuery( document ).ready( function() {

/*-----------------------------------------------------------------------------------*/
/* Add alt-row styling to tables */
/*-----------------------------------------------------------------------------------*/

	jQuery('.entry table tr:odd').addClass('alt-table-row');


/*-----------------------------------------------------------------------------------*/
/* Superfish navigation dropdown */
/*-----------------------------------------------------------------------------------*/

	if( jQuery().superfish ) {

		jQuery('ul.nav').superfish({
			delay: 200,
			animation: {opacity:'show', height:'show'},
			speed: 'fast',
			dropShadows: false
		});
	
	}

/*-----------------------------------------------------------------------------------*/
/* Innerfade Setup */
/*-----------------------------------------------------------------------------------*/

	if ( jQuery('.quotes').length ) {
	
		fadeArgs = new Object();
		
		fadeArgs.fadeSpeed = woo_innerfade_settings.timeout;
		fadeArgs.crossfade = false;
		fadeArgs.container = 'quotes';
		fadeArgs.effect = 'fade';
		fadeArgs.autoHeight = true;
		fadeArgs.generatePagination = false;
		
		if ( woo_innerfade_settings.can_fade == 'true' ) {
			fadeArgs.play = woo_innerfade_settings.timeout;
		}
		
		jQuery( '#testimonials' ).slides( fadeArgs );
	}
});

/*-----------------------------------------------------------------------------------*/
/* Center Nav Sub Menus */
/*-----------------------------------------------------------------------------------*/

jQuery(document).ready(function(){

	jQuery('.nav li ul').each(function(){
	
		li_width = jQuery(this).parent('li').width();
		li_width = li_width / 2;
		li_width = 100 - li_width - 10;
		
		jQuery(this).css('margin-left', - li_width);
	
	});


/*-----------------------------------------------------------------------------------*/
/* Single Portfolio Gallery */
/*-----------------------------------------------------------------------------------*/

jQuery(document).ready(function() {

	var show_thumbs = 3;
	
    jQuery('#slides.gallery ul.pagination').jcarousel({
    	visible: show_thumbs,
    	wrap: 'both'
    });
});


});
// JavaScript Document

jQuery(document).ready(function(e) {
	jQuery(".panel").hide();
	jQuery(".tabs li:first").addClass("active");
	jQuery(".panel:first").show();
    jQuery(".tabs a").click(function(){
		jQuery(".active").removeClass("active");
		jQuery(this).parent().addClass("active");
		jQuery(".panel").hide();
		jQuery(jQuery(this).attr("href")).show();
	});
});

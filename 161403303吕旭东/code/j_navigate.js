$(document).ready(function () {
  var h_l1 = $('#m1').offset().top;
  var h_l2 = $('#m2').offset().top;
  var h_l3 = $('#m3').offset().top;
  var h_l4 = $('#m4').offset().top;
  var h_l5 = $('#m5').offset().top;
  var h_l6 = $('#m6').offset().top;
  var buffer = 50;

  $(window).scroll(function (event) {
    var  winPos = $(window).scrollTop();
    $('#l1').removeClass('scrolling');
    $('#l2').removeClass('scrolling');
    $('#l3').removeClass('scrolling');
    $('#l4').removeClass('scrolling');
    $('#l5').removeClass('scrolling');
    $('#l6').removeClass('scrolling');
    $('#L1').removeClass('scrolling');
    $('#L2').removeClass('scrolling');
    $('#L3').removeClass('scrolling');
    $('#L4').removeClass('scrolling');
    $('#L5').removeClass('scrolling');
    $('#L6').removeClass('scrolling');
    if(winPos>=h_l6-buffer){$('#l6').addClass('scrolling');$('#L6').addClass('scrolling');}
    else if(winPos>=h_l5-buffer){$('#l5').addClass('scrolling');$('#L5').addClass('scrolling');}
    else if(winPos>=h_l4-buffer){$('#l4').addClass('scrolling');$('#L4').addClass('scrolling');}
    else if(winPos>=h_l3-buffer){$('#l3').addClass('scrolling');$('#L3').addClass('scrolling');}
    else if(winPos>=h_l2-buffer){$('#l2').addClass('scrolling');$('#L2').addClass('scrolling');}
    else if(winPos>=h_l1-buffer){$('#l1').addClass('scrolling');$('#L1').addClass('scrolling');}
  });
  $('#l1').click(function (event) {$('html,body').animate({scrollTop:(h_l1)+'px'},800);});
  $('#l2').click(function (event) {$('html,body').animate({scrollTop:(h_l2)+'px'},800);});
  $('#l3').click(function (event) {$('html,body').animate({scrollTop:(h_l3)+'px'},800);});
  $('#l4').click(function (event) {$('html,body').animate({scrollTop:(h_l4)+'px'},800);});
  $('#l5').click(function (event) {$('html,body').animate({scrollTop:(h_l5)+'px'},800);});
  $('#l6').click(function (event) {$('html,body').animate({scrollTop:(h_l6)+'px'},800);});
});

$(document).ready(function () {
  var personal_per = $('#personal_per').offset().top;
  var personal_pay = $('#personal_pay').offset().top;
  var personal_safe = $('#personal_safe').offset().top;
  var personal_job = $('#personal_job').offset().top;

  var buffer = 50;

  $(window).scroll(function (event) {
    var  winPos = $(window).scrollTop();
    $('#personal_v_per').removeClass('scrolling');
    $('#personal_v_pay').removeClass('scrolling');
    $('#personal_v_safe').removeClass('scrolling');
    $('#personal_v_job').removeClass('scrolling');

    if(winPos>=personal_job-buffer){$('#personal_v_job').addClass('scrolling')}
    else if(winPos>=personal_safe-buffer){$('#personal_v_safe').addClass('scrolling');}
    else if(winPos>=personal_pay-buffer){$('#personal_v_pay').addClass('scrolling');}
    else if(winPos>=personal_per-buffer){$('#personal_v_per').addClass('scrolling');}

  });
  $('#personal_v_per').click(function (event) {$('html,body').animate({scrollTop:(personal_per)+'px'},800);});
  $('#personal_v_pay').click(function (event) {$('html,body').animate({scrollTop:(personal_pay)+'px'},800);});
  $('#personal_v_safe').click(function (event) {$('html,body').animate({scrollTop:(personal_safe)+'px'},800);});
  $('#personal_v_job').click(function (event) {$('html,body').animate({scrollTop:(personal_job)+'px'},800);});
});

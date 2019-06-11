$(document).ready(function () {
  $('#re1').click(function (e) {
    e.preventDefault();
    $('#reg2').toggleClass('show');
    $('#reg1').toggleClass('show')
  });
});
$(document).ready(function () {
  $('#re2').click(function (e) {
    e.preventDefault();
    $('#reg2').toggleClass('show');
    $('#reg1').toggleClass('show')
  });
});

$(document).ready(function () {
  $('#r1').click(function (e) {
    e.preventDefault();
    $('#r1,#r2').toggleClass('show');
    $('#reg3').addClass('show');
    $('#reg1').removeClass('show');
    $('#reg2').removeClass('show');
  });
});
$(document).ready(function () {
  $('#r2').click(function (e) {
    e.preventDefault();
    $('#r1,#r2').toggleClass('show');
    $('#reg3').toggleClass('show');
    $('#reg1').toggleClass('show')
  });
});


$(document).ready(function () {
  $('.close').click(function (e) {
    e.preventDefault();
    $('.Rmain').toggleClass('show');
  });
});
$(document).ready(function () {
  $('.head_Register').click(function (e) {
    e.preventDefault();
    $('.Rmain').toggleClass('show');
  });
});

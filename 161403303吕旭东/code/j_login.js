$(document).ready(function () {
  $('.login_button_1').click(function () {
    $('#login_head_1').toggleClass('login_h_color');
    $('#login_head_2').toggleClass('login_h_color');
    $('#login_1').toggleClass('show');
    $('#login_2').toggleClass('show');
  });
});
$(document).ready(function () {
  $('.login_button_2').click(function () {
    $('#login_head_2').toggleClass('login_h_color');
    $('#login_head_3').toggleClass('login_h_color');
    $('#login_2').toggleClass('show');
    $('#login_3').toggleClass('show');
  });
});


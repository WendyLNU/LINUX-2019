$(document).ready(function(){
  var duration = 3000;
  var speed = 1000;
  var width = $('#slideshow').width();
  var curIndex = 0;
  var totalIndex = $('#slideshow > ul > li').length;
  var timer;

  $('#slideshow > ul > li').each(function (index) {
    $(this).css("left",index * width + "px");
    $('#slideshow-nav').append("<span>" + (index + 1) + "</span>");
  });

  $('#slideshow-nav > span').eq(0).addClass("active");
  var firstChild = $('#slideshow > ul > li').eq(0).clone();
  $('#slideshow > ul').append(firstChild);
  firstChild.css("left",totalIndex * width + "px");

  function move() {
    curIndex ++;
    if(curIndex >totalIndex){
      curIndex = 1;
      $('#slideshow > ul').css("left","0");
    }
    for(var i=0;i < totalIndex;i ++){
      $('#slideshow-nav > span').eq(i).removeClass("active");
    }
    if(curIndex === totalIndex){
      $('#slideshow-nav > span').eq(0).addClass("active");
    }
    else{
      $('#slideshow-nav > span').eq(curIndex).addClass("active");
    }

    $('#slideshow > ul').animate({left:width * curIndex * -1 + "px"},speed);
    //timer = setTimeout(move,duration + speed);
  }
//  timer = setTimeout(move,duration);

  $('#slideshow-nav > span').each(function (index) {
    $(this).attr("index",index);
    $(this).click(function () {
      curIndex = $(this).attr("index")-1;
      clearTimeout(timer);
      move();
    });
  });
});

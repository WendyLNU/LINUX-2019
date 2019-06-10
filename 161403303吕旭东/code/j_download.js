var nav_pc = document.getElementById("nav-pc");
var nav_pe = document.getElementById("nav-pe");
var pc = document.getElementById("pc");
var pe = document.getElementById("pe");

hideAll();

pc.style.display = "block";
pe.style.display = "none";
nav_pc.style.background = "#a967f0";

function hideAll() {
  pc.style.display = "none";
  pe.style.display = "none";
  nav_pc.style.background = "#b4b0cb";
  nav_pe.style.background = "#b4b0cb";
}
nav_pc.onclick = function () {
  hideAll();
  pc.style.display = "block";
  nav_pc.style.background = "#a967f0";
};
nav_pe.onclick = function () {
  hideAll();
  pe.style.display = "block";
  nav_pe.style.background = "#a967f0";
};

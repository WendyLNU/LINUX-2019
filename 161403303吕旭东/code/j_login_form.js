function AddElement(mytype){
  var mytype,TemO=document.getElementById("login_add");
  var newInput = document.createElement("input");
  newInput.type=mytype;
  newInput.name="input1";
  TemO.appendChild(newInput);
  var newline= document.createElement("br");
  TemO.appendChild(newline);
}

$.extend($.fn.validatebox.defaults.rules, {
  equals:{
    validator:function(value,param){
      return value == $(param[0]).val();
    },
    message:'两次输入密码不一致'
  }
});

/*
check if the passwords are consistent
*/

function checkRePasswd()
{
    //获取密码输入
    var uPass = document.getElementById("passwd1").value;
				
    //获取确认密码输入
    var uRePass = document.getElementById("passwd2").value;
    
    
    var span = document.getElementById("span_repasswd");
    if(uPass != uRePass)
    {
        span.innerHTML = "<font color='red' size='2'>密码不一致!</font>";
		return false;

    }
    else
    {
        span.innerHTML = "";
        return true;
    }
};
/*
check register
*/
function signsubmit()
{  
    var username = document.getElementById("sign_name").value;
    var nickname = document.getElementById("sign_nickname").value;
    var uPass = document.getElementById("passwd1").value;
    var uRePass = document.getElementById("passwd2").value;
    var div = document.getElementById("div_sign_check");
    
    if(username.length<1 || nickname.length<1)
    {
        div.innerHTML = "<font color='red' size='2'>用户名或昵称不能为空</font>";
        
        return false;
    }
    else if(uPass.length < 6)
    {
        div.innerHTML = "<font color='red' size='2'>密码太短</font>";
        return false;
    }
    else if(uPass != uRePass)
    {
        div.innerHTML = "";
        return false;
    }
    else
    {
        div.innerHTML = "<font color='green' size='2'>连接中...</font>";
        post_register();
        return false;
    }
}
/*
check login
*/
function loginsubmit()
{  
    var username = document.getElementById("login_name").value;
    var passwd = document.getElementById("passwd0").value;
  
    var div = document.getElementById("div_login_check");
    
    if(username.length<1 || passwd.length<1)
    {
        div.innerHTML = "<font color='red' size='2'>用户名或密码不能为空</font>";
        
        return false;
    }
    else
    {
        div.innerHTML = "<font color='green' size='2'>连接中...</font>";
        post_login();
        return false;
    }
}
/*
 * 
 */
function  ajaxFunction(){
    var xmlHttp;
    try{ // Firefox, Opera 8.0+, Safari
         xmlHttp=new XMLHttpRequest();
     }
     catch (e){
        try{// Internet Explorer
              xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
           }
         catch (e){
           try{
              xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
           }
           catch (e){}
           }
     }

     return xmlHttp;
  }
/*
 * 
 * 
 */
function post_login()
{
	var request = ajaxFunction();
	request.open( "POST", "Login", true );
	request.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	var username = document.getElementById("login_name").value;
    var passwd = document.getElementById("passwd0").value;
    //获取响应数据
    
    request.onreadystatechange = function(){
        
        if(request.readyState == 4 && request.status == 200){
            
        	if(request.responseText.trim() =="true".trim())
        		{
        		document.getElementById("loginform").submit();
        		
        		}
        	else
        	{
        		document.getElementById("div_login_check").innerHTML="<font color='red' size='2'>用户名或密码错误</font>";
        	}
        }
        
    }
    //异步发送数据
	request.send("user_id="+username+"&password="+passwd);
}
/*
 * 
 */
function post_register()
{
	var request = ajaxFunction();
	request.open( "POST", "Register", true );
	request.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	var username = document.getElementById("sign_name").value;
    var passwd = document.getElementById("passwd1").value;
    var nick = document.getElementById("sign_nickname").value;
    var email = document.getElementById("email").value;
    var school = document.getElementById("school").value;
    request.onreadystatechange = function(){
    	if(request.readyState == 4 && request.status == 200){
            
        	if(request.responseText.trim() =="true".trim())
        		{
        		document.getElementById("signform").submit();
        		
        		}
        	else
        	{
        		document.getElementById("div_sign_check").innerHTML="<font color='red' size='2'>"+request.responseText.trim()+"</font>";
        	}
        }
        

    }
    
    request.send("user_id="+username+"&password="+passwd+"&nick="+nick+"&email="+email+"&school="+school);
    
}




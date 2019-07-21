<!DOCTYPE html>
<html lang="zh">

<head>
    <title>少女前线与明日方舟 工具站</title>
</head>

<body>
    <script>
        function jumpPage(command) {
            if (command === 'gf') window.location.href = "GF.php";
            else if (command === 'ak') window.location.href = "02-1.php";
        }
    </script>
    <table align="center" width="40%" border="2">
      <tr height="80px">
	<td bgcolor="#cccccc" align="center" style="font-size:36px">欢迎访问 少女前线与明日方舟 工具站</td>
      </tr>	
      <tr height="60px">
	<td align="center" style="font-size:30px">make a selection</td>
      </tr>
      <tr>
	<td align="center"><img src="btn_GF.png" style="cursor:pointer" onclick='jumpPage("gf")'></td>
      </tr>
      <tr>
	<td align="center"><img src="btn_AK.png" style="cursor:pointer" onclick='jumpPage("ak")'></td>
      </tr>
    </table>
                                 
                      
</body>

</html>


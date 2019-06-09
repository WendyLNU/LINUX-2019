<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Title</title>
  <link rel="stylesheet" type="text/css" href="c_login.css">
</head>
<style>
  #mess_m{
    width: 900px;
    position: relative;
    left: 50%;
    margin-left: -400px;
    padding-top: 35px;
    overflow-x: hidden;
    margin-bottom: 200px;
  }
  #mess_m h2{
    font-size: 20px;
    margin-bottom: 20px;
  }
  #mess_m p{
    position: relative;
    left: 200px;
  }
  #mess_m p a{
    color: blue;
    cursor: pointer;
  }
  #mess_m input{
    border: 0;
    background: rgba(0,0,0,0);
    color: rgba(0,0,0,.5);
    margin-bottom: 10px;
    position: relative;
    left: 200px;
    border-radius: 4px;
  }
  #mess_m select{
    border: 0;
    background: rgba(0,0,0,0);
    color: rgba(0,0,0,.5);
    margin-bottom: 10px;
    position: relative;
    left: 200px;
    border-radius: 4px;
  }
</style>
<body>
<?php
include "index_head.php";
include "idx_register.php";

$D = $_GET['D'];
if($D == 1){$A = 'P001';}
$j = $_COOKIE['j'];
if (!isset($_SESSION["username"])){
  echo "<script>alert('您还未登录!');window.location='idx_join_main.php';</script>";
}
else{
  $result = mysqli_query($mysqli,"SELECT * FROM zcode_customer left join zcode_cus_safe on zcode_customer.CusId = zcode_cus_safe.CusId where CusEmail = '".$_SESSION["username"]."'");
  $row = mysqli_fetch_array($result);
  echo "
  <div id=\"mess_m\">
  <h1>招贤纳才</h1><br>
  <h5>请完整的填写您的档案，信息越丰富，越能帮助我们找到与你兴趣相符的职位</h5>
  <form action = 'idx_join_rul.php' method='post'>
  <p style=\"opacity: .3;left: 0;\">--------------------------------------------------------------------------------------------------------</p>
  <h2>联系信息</h2>
  <p>姓氏</p><input type=\"text\" name='fname' value=\"".$row['CusLName']."\">
  <p>名字</p><input type=\"text\" name='lname' value=\"".$row['CusFName']."\">
  <p>首选电子邮件</p><input type=\"text\" name='email' value=\"".$row['CusEmail']."\">
  <p>首选电话号码</p><input type=\"text\" name='phone' value=\"".$row['CusPhone']."\">
  <p>首选地址</p><input type=\"text\" name='address' value=\"".$row['CusAds']."\">
  <p>邮政编码</p><input type=\"text\" name='potl' value=\"".$row['potalcode']."\">
    <input name=\"j\" value=\"".$j."\" style='display:none'>
    <input name=\"j\" value=\"".$A."\" style='display:none'>";}?>
  <p style="opacity: .3;left: 0;">--------------------------------------------------------------------------------------------------------</p>

  <h2>简历/职业档案</h2>
  <p>简历</p><input type="text" value="Luciux.pdf">
  <p>职业档案</p><input type="text" value="http:/www.linkedin/li/">
  <p style="opacity: .3;left: 0;">--------------------------------------------------------------------------------------------------------</p>
  <h2>其他文件和链接</h2>
  <p>辅助文件</p><input type="text" value="未填写">
  <p>辅助链接</p><input type="text" value="未填写">
  <p style="opacity: .3;left: 0;">- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </p>
  <h2>教育背景</h2>
  <p>学位</p><select>
               <option value='本科'>本科</option>
               <option value='专科'>专科</option>
               <option value='硕士'>硕士</option>
               <option value='博士'>博士</option>       
             </select>
  <p>毕业结业</p><select>
                    <option value='未毕业'>未毕业</option>
                    <option value='已毕业'>已毕业</option>
                 </select>
  <p>学校</p><input type="text" value="辽宁大学">
  <p>专业/研究领域</p><input type="text" value="软件工程">
  <p style="opacity: .3;left: 0;">- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </p>
  <h2>职业背景</h2>
  <input type="text" value="未填写">
  <p style="opacity: .3;left: 0;">--------------------------------------------------------------------------------------------------------</p>
  <h2>首选工作地点</h2><select name='sl1'>
                          <option value="null">未填写</option>
                         <option value='上海'>上海</option>
                         <option value='北京'>北京</option>
                         <option value='武汉'>武汉</option>
                         <option value='大连'>大连</option>
                         <option value='广州'>广州</option>
                         <option value='杭州'>杭州</option>
                       </select>&nbsp&nbsp&nbsp
                      <select name='sl2'>
                        <option value="null">未填写</option>
                        <option value='上海'>上海</option>
                        <option value='北京'>北京</option>
                        <option value='武汉'>武汉</option>
                        <option value='大连'>大连</option>
                        <option value='广州'>广州</option>
                        <option value='杭州'>杭州</option>
                      </select>&nbsp&nbsp&nbsp
                      <select name='sl3'>
                        <option value="null">未填写</option>
                        <option value='上海'>上海</option>
                        <option value='北京'>北京</option>
                        <option value='武汉'>武汉</option>
                        <option value='大连'>大连</option>
                        <option value='广州'>广州</option>
                        <option value='杭州'>杭州</option>
                      </select>
  <p style="opacity: .3;left: 0;">- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </p>
  <h2>调动意向</h2>
  <p>是否愿意调动工作地点</p><select>
                    <option value='未填写'>未填写</option>
                    <option value='是'>是</option>
                    <option value='否'>否</option>
                 </select>
  <p>是否愿意出差</p><select>
                    <option value='未填写'>未填写</option>
                    <option value='是'>是</option>
                    <option value='否'>否</option>
                 </select>
  <p style="opacity: .3;left: 0;">--------------------------------------------------------------------------------------------------------</p>
  <h2>自我信息披露及隐私</h2>
  <p><a id="p_agreement_p">应聘者隐私政策同意书</a></p>
  <p style="opacity: .3;left: 0;">- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - </p>
  <h2>技能</h2><select>
                    <option value='java'>java</option>
                    <option value='c/c++'>c/c++</option>
                    <option value='php'>php</option>
                    <option value='python'>python</option>
                 </select>
  <p style="opacity: .3;left: 0;">--------------------------------------------------------------------------------------------------------</p>
  <h2>语言能力</h2>
  <p>语言</p><select>
                    <option value='英语'>英语</option>
                    <option value='汉语'>汉语</option>
                    <option value='日语'>日语</option>
                    <option value='法语'>法语</option>
                    <option value='俄语'>俄语</option>
                    <option value='德语'>德语</option>
                 </select>

  <p>首选</p><select>
                    <option value='未填写'>未填写</option>
                    <option value='是'>是</option>
                    <option value='否'>否</option>
                 </select>
  <p>熟练程度</p><select>
                    <option value='未填写'>未填写</option>
                    <option value='流利'>流利</option>
                    <option value='凑合'>凑合</option>
                 </select><br>
                <input type="submit" style="width: 70px;height: 30px;font-size: 20px;left: 700px;">
  </form>
</div>

<div id="agreement" class="hidden">
  <div id="agreement_main">
    <div id="agreement_text">
      <pre>

      </pre>
    </div>
    <div id="agreement_close">关闭</div>
  </div>
  <div id="agreement_back"></div>
</div>
</body>
</html>

<script src="http://libs.baidu.com/jquery/2.1.4/jquery.min.js"></script>
<script type="text/javascript">
    $(document).ready(function () {
      $('#p_agreement_p,#agreement_close').click(function (e) {
        e.preventDefault();
        $('#agreement').toggleClass('show');
        $('#agreement').toggleClass('hidden');
      });
    });
</script>

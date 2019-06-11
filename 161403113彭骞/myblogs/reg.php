<?php  

    if(isset($_POST["submit"]))  

    {  

        $user = $_POST["username"];  

        $pw = $_POST["pw"];  

        $repw = $_POST["repw"];  

        if($user == "" || $pw == "" || $repw == "")  

        {  

            echo "<script>alert('请确认信息完整性！'); history.go(-1);</script>";  

        }  

        else 

        {  

            if($pw == $repw)  

            {  

                mysql_connect("localhost","debian-sys-maint","clwKlOWnhyqrM5Zf");;   //连接数据库  

                mysql_select_db("taka",$conn);  //选择数据库  

                mysql_query("set names 'gdk'"); //设定字符集  

                $sql = "select username from user where username = '$_POST[username]'"; //SQL语句  

                $result = mysql_query($sql);    //执行SQL语句  

                $num = mysql_num_rows($result); //统计执行结果影响的行数  

                if($num)    //如果已经存在该用户  

                {  

                    echo "<script>alert('用户名已存在'); history.go(-1);</script>";  

                }  

                else    //不存在当前注册用户名称  

                {  

                    $sql_insert = "insert into user (username,password,phone,address) values('$_POST[username]','$_POST[pw]','','')";  

                    $res_insert = mysql_query($sql_insert);  


                    if($res_insert)  

                    {  

                        #echo "注册成功 <a href='login.html'>点击登录</a>";
                        echo "<script>alert('注册成功！'); window.location.href='login.html';</script>";   

                    }  

                    else 

                    {  

                        echo "<script>alert('系统繁忙，请稍候！'); history.go(-1);</script>";  

                    }  

                }  

            }  

            else 

            {  

                echo "<script>alert('密码不一致！'); history.go(-1);</script>";  

            }  

        }  

    }  

    else 

    {  

        echo "<script>alert('提交未成功！'); history.go(-1);</script>";  

    }  

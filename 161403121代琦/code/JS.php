<SCRIPT LANGUAGE="JavaScript">
    <!-- Begin
    var now = new Date();
    var month_array = new Array("january","february","march","April","May","June","July","August","September","October","November","December");
    document.write("<form name=date_list><table bgcolor=silver><tr><td>");
    document.write("<select name=month onchange=change_month(this.options.selectedIndex)>");
    for(i=0;i<month_array.length;i++)
    {
    if (now.getMonth() != i)
    {document.write ("<option value="+i+">"+month_array[i]);}
    else
    {document.write ("<option value="+i+" selected>"+month_array[i]);}
    }
    document.write("</select>");
    document.write("</td><td>");
    document.write ("<select name=year onchange=change_year(this.options[this.options.selectedIndex])>");
    for(i=1950;i<3000;i++)
    {
    if (now.getYear() != i)
    {document.write("<option value="+i+">"+i);}
    else
    {document.write("<option value="+i+" selected>"+i);}
    }
    document.write("</select></td></tr><tr><td colspan=2><center>");
    document.write("<table bgcolor=white border=0 cellspacing = 0 cellpading = 0 width=100%><tr bgcolor=gray align=center>");
    document.write("<td><font color=silver>M</font></td><td><font color=silver>T</td><td><font color=silver>W</td><td><font color=silver>T</td><td><font color=silver>F</td><td ><font color=silver>S</td><td ><font color=silver>S</td>");
    document.write("</tr><tr>");
    for(j=0;j<6;j++)
    {
    for(i=0;i<7;i++)
    {
    document.write("<td align=center id=d"+i+"r"+j+"></td>")
    }
    document.write("</tr>");
    }
    document.write("</table>");
    document.write("</center></from></td></tr></table>");
    var show_date = new Date();
    function set_cal(show_date)
    {
    begin_day = new Date (show_date.getYear(),show_date.getMonth(),1);
    begin_day_date = begin_day.getDay();
    end_day = new Date (show_date.getYear(),show_date.getMonth()+1,1);
    count_day = (end_day - begin_day)/1000/60/60/24;
    input_table(begin_day_date,count_day);
    }
    set_cal(show_date);
    function input_table(begin,count)
    {
    init();
    j=0;
    if (begin!=0){i=begin-1;}else{i=6}
    for (c=1;c<count+1;c++)
    {
    colum_name = eval("d"+i+"r"+j);
    if ((now.getDate() == c)&&(show_date.getMonth() == now.getMonth())&&(show_date.getYear() == now.getYear())) {colum_name.style.backgroundColor = "blue";colum_name.style.color = "white";};
    colum_name.innerText =  c;
    i++;
    if (i==7){i=0;j++;}
    }
    }
    function init()
    {
    for(j=0;j<6;j++)
    {
    for(i=0;i<7;i++)
    {
    colum_name = eval("d"+i+"r"+j);
    colum_name.innerText =  "-";
    colum_name.style.backgroundColor ="";
    colum_name.style.color ="";
    }
    }
    }
    function change_month(sel_month)
    {
    show_date = new Date(show_date.getYear(),sel_month,1);
    set_cal(show_date);
    }
    function change_year(sel_year)
    {
    sel_year = sel_year.value;
    show_date = new Date(sel_year,show_date.getMonth(),1);
    set_cal(show_date);
    }
    //  End -->
    </script>
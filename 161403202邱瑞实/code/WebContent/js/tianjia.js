function add(){
    var award_list=document.getElementById("award_list");
    var award_row=document.getElementById('award_row');
    var new_div=document.createElement('div');
    new_div.id="valuedel";
    new_div.innerHTML=award_row.innerHTML;
    award_list.appendChild(new_div);
}
function del(){
    var award_list=document.getElementById("award_list");
    var len=award_list.childElementCount;
    if(len==1){
        alert("只剩下一个了");
    }
    else{
        award_list.removeChild(award_list.children[len-1])
    }
}
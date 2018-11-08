window.onload=function(){ //trb sa existe window......nu merge altfel in cazul asta
   
    var b=document.getElementById("buton_baza");
    b.onclick=function(){
    var x=document.getElementById("check");
    x.checked=true;
    var newbutton=document.createElement("INPUT");
    newbutton.type="button";
    newbutton.value="...apasati tabul 'Produse'";
    newbutton.style.color="red";
    document.getElementById("section").appendChild(newbutton);
    }

}
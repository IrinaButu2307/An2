window.onload = function(){
    alert("Sunteti cititorul cu nr " + parseInt((((Math.random())+1)*100))+ '\n' + "Daca veti da Subscribe, veti fi inscris la tombola pentru premiul special");

   /* this.document.getElementById("form").onsubmit = answer; */
    var f = this.document.getElementById("form");
    f.onsubmit=function(event){
      //  event.preventDefault();
        var data = new FormData(f);
        //datele din form
        var xhr = new XMLHttpRequest();
        xhr.open('POST', f.action, true); 
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4) 
            if (xhr.status == 200) 
                document.getElementById("info").innerHTML=xhr.responseText;
                              else alert("date primite"); 
        }; 
        xhr.send(data);
    
        if(f.elements[3].checked==true) 
        alert("Felicitari! De acum urmariti pagina noastra, sunteti abonat");
            else alert("Este obligatoriu sa acceptati Termenii si Conditiile");

    }

    var ok=1;
    document.getElementById("txt").onkeyup=function(event){
        switch(event.key){
            case "=":alert("Tasta nu este permisa in campul de dialog"); ok=0; return; 
            case ">":alert("Tasta nu este permisa in campul de dialog"); ok=0; return; 
            case "<":alert("Tasta nu este permisa in campul de dialog"); ok=0; return; 
            case "/":alert("Tasta nu este permisa in campul de dialog"); ok=0;return; 
        }

    }

    document.getElementById("txt").onchange = function (){  
        if (ok==1)
        alert("MESAJUL DVS " + document.getElementById("txt").value + "VA FI TRANSMIS"); 
    }

    if(typeof(Storage) !== "undefined") {
        if (localStorage.onloadcount) {
          localStorage.onloadcount = Number(localStorage.onloadcount)+1;
        } else {
          localStorage.onloadcount = 1;
        }
        document.getElementById("count").innerHTML = "You have loaded the page " + localStorage.onloadcount + " time(s).";
      } else {
        document.getElementById("count").innerHTML = "Sorry, your browser does not support web storage";
      }

}
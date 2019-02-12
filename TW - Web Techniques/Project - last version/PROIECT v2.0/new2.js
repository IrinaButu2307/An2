window.onload= myfunction;
var myWindow; 
var indice=0;
function myfunction(){
   // var b1 = document.getElementById("openbtn").addEventListener("click", function(){ myWindow = window.open("https://www.csid.ro/");  document.getElementById("firstdiv").innerHTML += "Verificati pagina selectata";}, true);
    //var b2 = document.getElementById("closebtn").addEventListener("click",function(){myWindow.close("https://www.csid.ro/");}, true);
    var b1 = document.getElementById("openbtn");
    var b2 = document.getElementById("closebtn");
    b1.ok=0;
    
    if(ok==0){ //only the first click
    b1.onclick=function(){
        myWindow = window.open("https://www.csid.ro/"); 
        document.getElementById("firstdiv").innerHTML += "Verificati pagina selectata";
    }
    ok=1;
    }
    b2.onclick=function(){
        myWindow.close("https://www.csid.ro/");
    }
    

var s  = document.querySelectorAll("section");
var scopil = s[1].children;
console.log("Sectiunea 1 are " + scopil.length + "copii" +'\n' );
for (let i=0; i<s.length; i++){
    s[i].onmouseover = function(){
        console.log("Nodul parinte " + this.parentNode +'\n');
        if(i%2 == 1){
            s[i].classList.add("a");
            s[i].style.color="blue";}
                else
            {s[i].classList.add("b");
            s[i].style.color="yellow";}
    }
}

var p = document.getElementsByClassName("titlu");
var pp = document.querySelectorAll("p:first-child");
var timer = setInterval(setcolor, 2000);

function setcolor(){
        if(indice < p.length)
        {p[indice].style.color="red";
        indice++;
        }
        if(indice >=p.length)
        {
            clearInterval(timer);
            var cssobj = window.getComputedStyle(pp[0], null); /*preiau prop default */
            alert(cssobj.color);
            for(let i=0; i<p.length; i++)
                p[i].style.color=cssobj.color;
        }
}




    /*preiau toate propr elem */
 
   /* for(let i=0; i, cssobj.length; i++){ 
        daca am mai multe propr de prluat...cum fac????? 
        cssobjprop = cssobj.item(i);
        p[i].style += cssobjprop;
        */
}


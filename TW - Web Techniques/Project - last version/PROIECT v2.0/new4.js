window.onload=function()
{
var bunic=document.body;
var parinte=document.getElementById("parinte");
var copil=document.getElementById("copil");
var nrcopii = document.getElementById("parinte").children.length;
bunic.addEventListener("click",function(event){alert("BODY"+'\n' + "event.type:"  + event.type + '\n' + "event.target: " + event.target.nodeName + '\n' + "event.currentTarget: " + event.currentTarget.nodeName + '\n');bunic.className="rosu";});
parinte.addEventListener("click",function(event){event.stopPropagation();
alert("DIV"+'\n' + "event.type:"  + event.type + '\n' + "event.target: " + event.target.nodeName + '\n' + "event.currentTarget: " + event.currentTarget.nodeName + '\n'+ "cu nr de copii: "+nrcopii);parinte.className="galben";},true);
copil.addEventListener("click",function(event){alert("P" +'\n' + "event.type:"  + event.type + '\n' + "event.target: " + event.target.nodeName + '\n' + "event.currentTarget: " + event.currentTarget.nodeName + '\n' + "event.pageX-Y: " + event.pageX + ' ' + event.pageY + '\n');copil.className="verde";});   

}
function allowDrop(ev) {
    ev.preventDefault();
  }
  
  function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
  }
  
  function drop(ev) {
    ev.preventDefault();
    var data = ev.dataTransfer.getData("text");
    ev.target.appendChild(document.getElementById(data));
  }

/*current target e zona in care s a ajuns cu propagarea*/
/* target e fix pe ce am dat click */
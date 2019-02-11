var puncte = [];		// vectorul in care punem coordonatele punctelor 
var n;		// lungimea vectorului
var aux;		// folosit la sortare
var stiva = [];		// stiva pt algoritm
var v_sup = [];  
var pasi = [];		// vectorul in care am pus tot ce intra in functia de viraj, toti pasii facuti de algoritm
var front_sup = [];		// frontiera superioara a acoperirii convexe
var front_inf = [];		// frontiera inferioara a acoperirii convexe
var nr_click;		// contor pentru numarul de click-uri al butonului pt afisarea pasilor (se opreste cand algoritmul ajunge la final)

/// MISCAREA DEFAVORABILA : atunci cand gasesc viraj la dreapta 
///

var canvas = document.getElementById("myCanvas");		
canvas.addEventListener("click", coordonate);		// de fiecare data cand dam click in canvas, punctul e preluat si desenat

function coordonate(event)		
{ 
  var text;
  var x_coord = event.clientX;		// preia coordonatele punctului in care am dat click
  var y_coord = event.clientY;
	
 puncte.push( { x : x_coord, y : y_coord } );		// baga coordonatele in vectorul de puncte 
  
 deseneaza_punct(x_coord, y_coord);		//apoi trimite coordonatele catre functia care deseneaza efectiv punctul
}

function deseneaza_punct(x, y) 
{
	var c = document.getElementById("myCanvas");
	var ctx = c.getContext("2d");
	ctx.beginPath();		
	ctx.arc(x, y, 4, 0, 2 * Math.PI);		// un punct este de fapt un cerc plin 
	ctx.fill();
	
	ctx.font = "15px Arial";
    ctx.fillText("("+ x + ",", x - 30, y - 10);
	ctx.fillText(y + ")",x + 10,y - 10);
}
 
function viraj_dreapta(a, b, c)		// functia de viraj 
{ 
   pasi.push( { x : a.x, y : a.y } );// sunt bagate in vectorul de pasi toate punctele care intra in functie (testele sau altfel spus, 
   //pasii facuti de algoritm)
		
   pasi.push( { x : b.x, y : b.y } );
		
   pasi.push( { x : c.x, y : c.y } );
   d= (b.x*c.y + a.x*b.y + a.y*c.x)-(a.y* b.x + b.y*c.x + a.x*c.y);  
   if(d>0)
	   return 1;
   return 0;   
  // return ((c.x - b.x) * (a.y - b.y)) - ((c.y - b.y) * (a.x - b.x));  
} 

										///doresc sa se umple aria poligonului inainte de a introduce pct exterior
function deseneaza_poligon(){
	//var lin = document.getElementById("myCanvas");
	var ctx = canvas.getContext("2d");
	
	ctx.beginPath();  
	ctx.moveTo(puncte[0].x,puncte[0].y);        
												
	for(i=1; i<n; i++)
	{
		ctx.lineTo(puncte[i].x,puncte[i].y);
	}	
	ctx.closePath();
	ctx.fillStyle = "yellow";
	ctx.fill();					     	
}

/////////////////////////

function frontiera_inferioara()		// detectarea frontierei inferioare a acoperirii convexe
{
   n = puncte.length;		// dimensiunea vectorului de puncte
  if(n == 1)
   { 
	 alert("Nu se poate determina frontiera inferioara a acoperirii convexe a unui singur punct.");
   }
   else
   {
     for(i=0; i < n-1; i++)		// sortarea cresactoare a vectorului de puncte 
	  for (j = i + 1; j < n; j++)
	  {
	    if (puncte[i].x != puncte[j].x)
		{
			if (puncte[i].x > puncte[j].x)
			{
				aux = puncte[i];
		     	puncte[i] = puncte[j];
				puncte[j] = aux;
			}
		}
		else	
		if (puncte[i].x == puncte[j].x)
		{
		    if (puncte[i].y > puncte[j].y)
			{
				aux = puncte[i];
				puncte[i] = puncte[j];
				puncte[j] = aux;
			}
		}
	  }
		
	  var t;
      var ok = 0;
  
	  // initializam stiva cu primele doua pucte din vectorul de puncte 
	  // cele mai mici 2 pct 
  
	  stiva[0] = puncte[0];
	  stiva[1] = puncte[1];
								
	  var k = 2;
		for (i = 2; i < n; i++)
		{
			stiva[k] = puncte[i];		// adaugam in stiva urmatorul punct din vector 
			if(k >= 2)
			{    
				// cat timp ultimele trei puncte formeaza un VIRAJ LA DREAPTA 
				while (viraj_dreapta(stiva[k - 2], stiva[k-1], stiva[k]) == 1 && k >= 2) 
				{  
					stiva[k - 1] = stiva[k];		// stergem penultimul punct din stiva
					k--;
					ok = 1;	  
			
					if(k == 1)		// daca mai avem doar doua elem in stiva, pentru a nu se intoarce in while si a se apela functia viraj_dreapta cu un parametru undefined, iesim din while cu break  
					{ break; }
				}
			}
	 
			k++; // crestem capatul stivei pentru a adauga un nou element (fie ca am sters sau ca doar vrem sa adaugam mai departe)
		}

		// a fost creata forntiera inferioara, o avem pe stiva, mai ramane sa trasam linii intre fiecare doua elemente din stiva )

		var lin_inf = document.getElementById("myCanvas");
		var ctx = lin_inf.getContext("2d");
	
		for (i = 0; i <= k-2; i++)
		{   
			ctx.beginPath();  
			ctx.lineWidth = 3;
			ctx.strokeStyle="#0000ff";
			ctx.moveTo(stiva[i].x, stiva[i].y);
			
			if(typeof(stiva[i+1]) != "undefined")		// ca sa evitam situatia cand celalalt capat al liniei e undefined
			{	
				ctx.lineTo(stiva[i+1].x, stiva[i+1].y);
				ctx.lineWidth = 3;
				ctx.stroke(); 
			}
		}
	
		// golim stiva 	
		while (k > -1)
		{
			for (i = 0; i < k-1; i++)
			{
				stiva[i] = stiva[i + 1];
			}
			k--;
		}
   }
}

function frontiera_superioara()		// detectarea frontierei superioare a acoperirii convexe
{
	n = puncte.length;		// dimensiunea vectorului de puncte
  
   if(n == 1)
   { 
	 alert("Nu se poate determina frontiera superioara a acoperirii convexe a unui singur punct.");
   }
   else
   {
	 for(i=0; i < n-1; i++)		// sortarea cresactoare a vectorului de puncte 
	  for (j = i + 1; j < n; j++)
	  {
		if (puncte[i].x != puncte[j].x)
		{
			if (puncte[i].x > puncte[j].x)
			{
				aux = puncte[i];
				puncte[i] = puncte[j];
				puncte[j] = aux;
			}
		}
		else
		{	
			if (puncte[i].x == puncte[j].x)
			{
				if (puncte[i].y > puncte[j].y)
				{
					aux = puncte[i];
					puncte[i] = puncte[j];
					puncte[j] = aux;
				}
			}
		} 
	  }
		var t = 0;
		n = puncte.length;
		
		for (i = n-1; i >= 0; i--)
		{
			v_sup[t] = puncte[i];
			t++;
		} 
		var ok = 0;	
	
		// initializam stiva cu primele doua pucte din vectorul de puncte 
		// cele mai mari 2 pct
		
		stiva[0] = v_sup[0];
		stiva[1] = v_sup[1];
		var k = 2;
		for (i = 2; i < n; i++)
		{   
			stiva[k] = v_sup[i];		// adaugam in stiva urmatorul punct din vector 

			if(k >= 2)
			{    
			   // cat timp ultimele trei puncte formeaza un VIRAJ LA DREAPTA 
		
				while (viraj_dreapta(stiva[k - 2], stiva[k - 1], stiva[k]) == 1 && k >= 2)
				{  
					stiva[k - 1] = stiva[k];		// stergem penultimul punct din stiva	
					k--;
					ok = 1;
					
					if(k == 1)		// daca suntem in situatia in care mai avem doar doua elem in stiva, pentru a nu se intoarce in while si a se apela functia viraj_stanga cu un parametru undefined, iesim din while cu break  
					  { break; }
				}	
			}
				
			k++;// crestem capatul stivei pentru a adauga un nou element (fie ca am sters sau ca doar vrem sa adaugam mai departe)
		}
	
	
	  // a fost creata forntiera superioara, o avem pe stiva, mai ramane sa afisam elementele stivei doua cate doua
	  // (adica sa trasam linii intre fiecare doua elemente din stiva )
		
		var lin_sup = document.getElementById("myCanvas");
		var ctx = lin_sup.getContext("2d");
		
		for (i = 0; i <= k-2; i++)
		{   
			ctx.beginPath();  
			ctx.lineWidth = 3;
			ctx.strokeStyle="#ff0000";
			ctx.moveTo(stiva[i].x, stiva[i].y);
			
			if( (typeof(stiva[i+1]) != "undefined") )		// ca sa evitam situatia cand celalalt capat al liniei e undefined
			{
			 ctx.lineTo(stiva[i+1].x, stiva[i+1].y);
			 ctx.lineWidth = 3;
			 ctx.stroke(); 
			}
		}
	  // golim stiva 	
		while (k > -1)
		{
			for (i = 0; i < k-1; i++)
			{
				stiva[i] = stiva[i + 1];
			}
			k--;
		}
   }
}	

function pe_pasi()		//functia creeaza frontiera inferioara, frontiera superioara si vecotrul de pasi
{   
   n = puncte.length;
   // dimensiunea vectorului de puncte
   if(n == 1)
   { 
	 alert("Nu se poate determina frontiera acoperirii convexe a unui singur punct.");
   }
   else
   {
     for(i=0; i < n-1; i++)		// sortarea cresactoare a vectorului de puncte 
	  for (j = i + 1; j < n; j++)
	  {
	    if (puncte[i].x != puncte[j].x)
		{
			if (puncte[i].x > puncte[j].x)
			{
				aux = puncte[i];
		     	puncte[i] = puncte[j];
				puncte[j] = aux;
			}
		}
		
		else
		
		if (puncte[i].x == puncte[j].x)
		{
		    if (puncte[i].y > puncte[j].y)
			{
				aux = puncte[i];
				puncte[i] = puncte[j];
				puncte[j] = aux;
			}
		}
	  }
		 
	  var t;
	  var ok = 0;
	  // initializam stiva cu primele doua pucte din vectorul de puncte 	
	  //cele mai mici 2 pct
	  stiva[0] = puncte[0];
	  stiva[1] = puncte[1];
	  var k = 2;
	  
	   if(puncte[2] === undefined)
	   {
		 for (i = 0; i < k; i++)
		 {
			front_inf.push( { x : stiva[i].x, y : stiva[i].y } );
		 }
	   }
	   else
	   {
			for (i = 2; i < n; i++)
			{
				stiva[k] = puncte[i];		// adaugam in stiva urmatorul punct din vector 
			
				if(k >= 2)
				{    
				   // cat timp daca ultimele trei puncte formeaza un VIRAJ LA DREAPTA 
				  
					while (viraj_dreapta(stiva[k - 2], stiva[k-1], stiva[k]) == 1 && k >= 2)
					{ 
						stiva[k - 1] = stiva[k];		// stergem penultimul punct din stiva
						k--;
						ok = 1;	  
						
						if(k == 1)		// daca suntem in situatia in care mai avem doar doua elem in stiva, pentru a nu se intoarce in while si a se apela functia viraj_stanga cu un parametru undefined, iesim din while cu break 
						{ break; }	
					}
				 }
				 
				 k++;		// crestem capatul stivei pentru a adauga un nou element (fie ca am sters sau ca doar vrem sa adaugam mai departe)
			}

			// a fost creata forntiera inferioara, o avem pe stiva
			// cream o copie a frontierei inferioare	

			for (i = 0; i < k; i++)
			{
				front_inf.push( { x : stiva[i].x, y : stiva[i].y } );
			}
		
	   }
			// golim stiva 
			while (k > -1)
			{
				for (i = 0; i < k-1; i++)
				{
					stiva[i] = stiva[i + 1];
				}
				k--;
			} 
			
			var t = 0;
			n = puncte.length;
			
			// cream v_sup, vector care contine vectorul de puncte citit invers	
				
			for (i = n-1; i >= 0; i--)
			{
				v_sup[t] = puncte[i];
				t++;
			} 
		
			var ok = 0;	
			
			// initializam stiva cu primele doua pucte din vectorul de puncte 	
			// cele mai mari 2 elem 
			stiva[0] = v_sup[0];
			stiva[1] = v_sup[1];
			
			var k = 2;
		
			if(v_sup[2] === undefined)
			{
			  for (i = 0; i < k; i++)
			  {
				front_sup.push( { x : stiva[i].x, y : stiva[i].y } );
			  }
			}
			else
			{
				for (i = 2; i < n; i++)
				{   
					stiva[k] = v_sup[i];		// adaugam in stiva urmatorul punct din vector 

					if(k >= 2)
					{    
					   // cat timp daca ultimele trei puncte formeaza un VIRAJ LA DREAPTA
					   while (viraj_dreapta(stiva[k - 2], stiva[k - 1], stiva[k]) == 1 && k >= 2)
						{   
							stiva[k - 1] = stiva[k];		// stergem penultimul punct din stiva	
							k--;
							ok = 1;
							
							if(k == 1)		// daca suntem in situatia in care mai avem doar doua elem in stiva, pentru a nu se intoarce in while si a se apela functia viraj_stanga cu un parametru undefined, iesim din while cu break 
							  { break; }
						 }	
					 }
					k++;		// crestem capatul stivei pentru a adauga un nou element (fie ca am sters sau ca doar vrem sa adaugam mai departe)
				}
		
				// cream o copie a frontierei superioare
				for (i = 0; i < k; i++)
				{
					front_sup.push( { x : stiva[i].x, y : stiva[i].y } );
				}
			}
			// golim stiva 
			while (k > -1)
			{
				for (i = 0; i < k-1; i++)
				{
					stiva[i] = stiva[i + 1];
				}
				k--;
			}
    }
}	

w = 1; // ii dam lui w val 1 si o scadem in functie pt a executa o singura data functia pe_pasi
nr_click = 0;

function functie_intermediara()
{
	while(w > 0) // executa functia pe_pasi o singura data
	{ pe_pasi();
      w--;
	}
	ps = pasi.length; // punem in ps lungimea vectorului de pasi pe care l-am creat in functia pe_pasi 
	
	if(nr_click > ps-2)	// daca am ajuns cu numarul de click-uri peste numarul de elem al vecorului de pasi - 2
	{ 					//trasare frontinf si frontsup FINALA
	
	var lin_inf = document.getElementById("myCanvas");
	var ctx = lin_inf.getContext("2d");
	
	 for (i = 0; i <= front_inf.length-2; i++)
	{   
        ctx.beginPath();  
		ctx.lineWidth = 3;
        ctx.strokeStyle="#000099";
		ctx.moveTo(front_inf[i].x, front_inf[i].y);
		
		if(typeof(front_inf[i+1]) != "undefined")		// ca sa evitam situatia cand celalalt capat al liniei e undefined
		{	
			ctx.lineTo(front_inf[i+1].x, front_inf[i+1].y);
			ctx.lineWidth = 3;
			ctx.stroke(); 
		}
	}
	
	var lin_sup = document.getElementById("myCanvas");
	var ctx = lin_sup.getContext("2d");
	
	for (i = 0; i <= front_sup.length-2; i++)
	{   
        ctx.beginPath();  
		ctx.lineWidth = 3;
        ctx.strokeStyle="#FF0000";
		ctx.moveTo(front_sup[i].x, front_sup[i].y);
		
		if(typeof(front_sup[i+1]) != "undefined")		// ca sa evitam situatia cand celalalt capat al liniei e undefined
		{	
			ctx.lineTo(front_sup[i+1].x, front_sup[i+1].y);
			ctx.lineWidth = 3;
			ctx.stroke(); 
		}
	}
	
	//   alert("Algorimul s-a sfarsit."); 
	//   $(document).ready(function(){
	// 	$("ol").append("Frontiera superioara" + "\n");});
	// 	for (i = 0; i <= front_sup.length-2; i++){
	// 		$(document).ready(function(){
	// 			$("ol").append((front_sup[i].x).toString() +" "+  (front_sup[i].y).toString() + " --- " + (front_sup[i+1].x).toString() + " "+ (front_sup[i+1].y).toString());});
	// 	}
	// $(document).ready(function(){
	// 	$("ol").append("Frontiera superioara" + "\n");});
	// for (i = 0; i <= front_sup.length-2; i++){
	// 				$(document).ready(function(){
	// 					$("ol").append(front_sup[i].x +" "+  front_sup[i].y + " --- " + front_sup[i+1].x + " "+ front_sup[i+1].y);});
	// 				  }
	  alert ("Frontiera superioara" + "\n");
	  for (i = 0; i <= front_sup.length-2; i++){
		  alert(front_sup[i].x +" "+  front_sup[i].y + " --- " + front_sup[i+1].x + " "+ front_sup[i+1].y);
	  }
	  alert ("Frontiera inferioara" + "\n");
	  for (i = 0; i <= front_inf.length-2; i++){
		  alert(front_inf[i].x +" "+  front_inf[i].y + " --- " + front_inf[i+1].x + " "+ front_inf[i+1].y);
	  }
	}
	pas(nr_click); // daca nu s-a terminat, apelam functia pas cu parametrul nr_click, 
	              // care va fi si pozitia din vectorul de pasi din care incepem sa afisam
				  
	nr_click = nr_click +3;		
// crestem contorul click din 3 in 3, pentru ca parcurgem vectorul de pasi din 3 in 3
	
}

function pas(nr_click)   ///apar 2 linii intre cele 3 pct curente
						/// trasare frontinf si frontsup INERMEDIARA
{     
       var ok_sup = 0, ok_inf = 0;  i= nr_click;  

	/// daca la click-ul/pasul curent o portiune din frontinf/ frontsup corespunde cu grupul de 3 pct din vectorul pasi
	/// inseamna ca partea asta a fost ok, deci un viraj acceptat de noi, adica viraj la stanga

	   for (j = 0; j <= front_sup.length - 2; j++)
	   {   if( (front_sup[j].x == pasi[i].x && front_sup[j].y == pasi[i].y &&
		        front_sup[j+1].x == pasi[i+1].x && front_sup[j+1].y == pasi[i+1].y &&
			    front_sup[j+2].x == pasi[i+2].x && front_sup[j+2].y == pasi[i+2].y ) ) 
		   ok_sup = 1;	   }
		   
	   for (j = 0; j <= front_inf.length - 2; j++)
	   {   if( (front_inf[j].x == pasi[i].x && front_inf[j].y == pasi[i].y &&
		        front_inf[j+1].x == pasi[i+1].x && front_inf[j+1].y == pasi[i+1].y &&
			    front_inf[j+2].x == pasi[i+2].x && front_inf[j+2].y == pasi[i+2].y ) )
		   ok_inf = 1;	  }
		   
	   if( ok_sup == 1)
	   {    
            var lin_sup = document.getElementById("myCanvas");
			var ctx = lin_sup.getContext("2d");
			ctx.beginPath();  
			ctx.strokeStyle="#ff0000";
			ctx.moveTo(pasi[i].x, pasi[i].y);      ctx.lineTo(pasi[i+1].x, pasi[i+1].y);
			ctx.lineWidth = 3;
			ctx.stroke(); 
			ctx.beginPath();  
			ctx.moveTo(pasi[i+1].x, pasi[i+1].y);  ctx.lineTo(pasi[i+2].x, pasi[i+2].y);
			ctx.lineWidth = 3;
			ctx.stroke(); 
			
			$(document).ready(function(){
            $("ol").append("<li>Viraj stanga: " + "(" + (pasi[i].x).toString() + "," +  (pasi[i].y).toString() + ")" + " ; " + "(" + (pasi[i+1].x).toString() + "," +  (pasi[i+1].y).toString() + ")" + " ; " + "(" + (pasi[i+2].x).toString() + "," +  (pasi[i+2].y).toString() + ") </li>"); }); 
			
	   }
					
	   if( ok_inf == 1)
	   {    
            var lin_sup = document.getElementById("myCanvas");
			var ctx = lin_sup.getContext("2d");
			ctx.beginPath();  
			ctx.strokeStyle="#0000ff";
			ctx.moveTo(pasi[i].x, pasi[i].y);      ctx.lineTo(pasi[i+1].x, pasi[i+1].y);
			ctx.lineWidth = 3;
			ctx.stroke(); 
			ctx.beginPath();
			ctx.moveTo(pasi[i+1].x, pasi[i+1].y);  ctx.lineTo(pasi[i+2].x, pasi[i+2].y);
			ctx.lineWidth = 3;
			ctx.stroke();  

			$(document).ready(function(){
            $("ol").append("<li>Viraj stanga: " + "(" + (pasi[i].x).toString() + "," +  (pasi[i].y).toString() + ")" + " ; " + "(" + (pasi[i+1].x).toString() + "," +  (pasi[i+1].y).toString() + ")" + " ; " + "(" + (pasi[i+2].x).toString() + "," +  (pasi[i+2].y).toString() + ") </li>" ); }); 

	   }  
	   
	   //daca portiunile nu coincid, fac testul de orientare
	    if(ok_sup == 0 && ok_inf == 0)  
		{   
			//daca verif_viraj <=0 ->viraj stanga
			var verif_viraj = (((pasi[i+2].x - pasi[i+1].x) * (pasi[i].y - pasi[i+1].y)) - ((pasi[i+2].y - pasi[i+1].y) * (pasi[i].x - pasi[i+1].x)));
			if(verif_viraj <= 0)
		    {
	          var lin = document.getElementById("myCanvas");
			  var ctx = lin.getContext("2d");
			  ctx.beginPath();  
			  ctx.strokeStyle="#00ff00";
			  ctx.moveTo(pasi[i].x, pasi[i].y);      ctx.lineTo(pasi[i+1].x, pasi[i+1].y);
			  ctx.lineWidth = 3;
			  ctx.stroke();
		      ctx.beginPath();  
			  ctx.moveTo(pasi[i+1].x, pasi[i+1].y);  ctx.lineTo(pasi[i+2].x, pasi[i+2].y);
			  ctx.lineWidth = 3;
			  ctx.stroke();  
			  
			  $(document).ready(function(){
              $("ol").append("<li> Viraj stanga: " + "(" + (pasi[i].x).toString() + "," +  (pasi[i].y).toString() + ")" + " ; " + "(" + (pasi[i+1].x).toString() + "," +  (pasi[i+1].y).toString() + ")" + " ; " + "(" + (pasi[i+2].x).toString() + "," +  (pasi[i+2].y).toString() + ") </li>" ); }); 
			
			}
			else
			{
	          var lin = document.getElementById("myCanvas");
			  var ctx = lin.getContext("2d");
			  ctx.beginPath();  
			  ctx.strokeStyle="#f213f2";
			  ctx.moveTo(pasi[i].x, pasi[i].y);      ctx.lineTo(pasi[i+1].x, pasi[i+1].y);
			  ctx.lineWidth = 3;
			  ctx.stroke();
		      ctx.beginPath();  
			  ctx.moveTo(pasi[i+1].x, pasi[i+1].y);  ctx.lineTo(pasi[i+2].x, pasi[i+2].y);
			  ctx.lineWidth = 3;
			  ctx.stroke();  
			 
			  $(document).ready(function(){
              $("ol").append("<li>Viraj dreapta: " + "(" + (pasi[i].x).toString() + "," +  (pasi[i].y).toString() + ")" + " ; " + "(" + (pasi[i+1].x).toString() + "," +  (pasi[i+1].y).toString() + ")" + " ; " + "(" + (pasi[i+2].x).toString() + "," +  (pasi[i+2].y).toString() + ") </li>" ); }); 
			 
			}
	 
   	    }   
}	

$(document).ready(function(){
    $("#flip").click(function(){
        $("#panel").slideToggle("slow");
    });
});
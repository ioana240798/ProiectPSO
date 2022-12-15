

var row=1;

var entry = document.getElementById("entry");
entry.addEventListener("click", displayDetails);


function displayDetails()
{
    var nume=document.getElementById("nume").value;
    var varsta=document.getElementById("varsta").value;
    var categorie=document.getElementById("categorie").value;



    if(!nume||!varsta||!categorie) {
        alert("Completeaza toate casutele!");
        return;
    }

    var display=document.getElementById("display");

    var newRow=display.insertRow(row);

    var cell1=newRow.insertCell(0);
    var cell2=newRow.insertCell(1);
    var cell3=newRow.insertCell(2);

    cell1.innerHTML=nume;
    cell2.innerHTML=varsta;
    cell3.innerHTML=categorie;


    row++;
}
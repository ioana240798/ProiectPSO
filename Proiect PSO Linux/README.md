# Server Linux 


## Notiuni teoretice

<br />
Mecanismul de comunicare prin socket-uri conține câteva apeluri sistem. Apelul sistem socket stabilește punctul final al unei legături de comunicație.
<br />
```c
sd = socket(format, type, protocol)
```
unde parametrul format precizează domeniul de comunicație (domeniul UNIX, sau domeniul Internet), type indică tipul de comunicație prin socket (circuit virtual, sau datagrama), iar protocol precizează un anumit protocol pentru controlul comunicației. În cadrul altor apeluri sistem, procesele vor întrebuința descriptorul de socket, sd. Apelul sistem close închide socket-urile.


<br />

Apelul sistem bind asociază un nume descriptorului de socket

```c
bind(sd, address, length)
```

unde sd este descriptorul de socket, iar address este adresa unei structuri care precizează un indicator al domeniului și protocolului de comunicație, precizate în cadrul apelului sistem socket. 
Parametrul length reprezintă lungimea structurii de date address, făra acest parametru nucleul nu ar ști cât de lungă este adresa, deoarece lungimea acesteia poate diferi de la un domeniu (sau protocol) la altul. De exemplu, în cadrul domeniului UNIX, o adresă este un nume de fișier. Procesul server atașează adresele din apelul bind unor socket-uri si face publice numele lor pentru a fi identificate de către procesele client.


<br />
Apelul sistem connect cere nucleului să facă o conexiune cu un socket existent
<br />
```c
connect(sd, address, length)
```

unde semnificația parametrilor este aceeași ca la apelul bind, cu deosebirea că parametrul address reprezintă adresa socket-ului destinație care va constitui celalalt capat al liniei de comunicație. Ambele socket-uri trebuie să folosească același domeniu și protocol de comunicație, rămânând în sarcina nucleului inițializarea corectă a legăturilor de comunicație.
Dacă tipul socket-ului este datagrama, atunci apelul connect informează nucleul asupra adresei de utilizat în cadrul apelurilor send ulterioare prin socket-ul respectiv în momentul apelului nu se realizează nici o legatură.

<br />

Atunci când un proces server acceptă legăturile printr-un circuit virtual, nucleul trebuie să pună într-o coadă de așteptare cererile care sosesc, până în momentul în care va putea să le satisfacă. Apelul sistem listen precizează lungimea maximă a cozii de așteptare 

```c
listen(sd, qlength)
```

unde sd este descriptorul de socket și qlength reprezintă numarul maxim de cereri care vor fi luate în considerație.
Apelul sistem accept primește cererile de conectare la un proces server

```c
nsd = accept(sd, address, addrlen)
```

unde sd este descriptorul de socket, address indică o zonă de date utilizator pe care nucleul o completează cu adresa de retur a procesului client care se conecteaza, iar addrlen precizează dimensiunea acestei zone. 
La revenirea din apelul accept, nucleul scrie în addrlen un număr care semnifică dimensiunea spațiului ocupat în zona de date. 
Apelul accept întoarce un nou descriptor de socket, nsd, diferit de descriptorul sd. Un proces server poate continua să asculte la socket-ul anunțat, în timp ce comunica cu un proces client pe un canal separat de comunicație.
<br />
Apelurile sistem send și recv permit transferul datelor printr-un socket. Sintaxa apelului sistem send este

```c
count = send(sd, msg, length, flags)
```

unde   sd este descriptorul de socket, msg este un pointer către datele care urmează să fie transmise, length reprezintă lungimea datelor de transmis, iar count este numărul de octeti efectiv transmiși.




























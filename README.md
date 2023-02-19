# Descriere fisiere

Am mers pe structura arborilor predati la curs. Astfel, in fisierul TArb.c sunt principalele functii generice cu arbori(mare parte facute la curs), iar structura unui nod contine arborele stang, drept si informatia care este de tip void *
Numele functiilor este destul de intuitiv, asa ca nu o sa mai descriu exact ce ar trebui sa faca

## Fisierul main.c
	-> am creat un nou nod de tip director (root-ul)
	-> mai am nevoie de o variabila(initroot) ca sa pastrez radacina tuturor fisierelor, pentru momentul in care root-ul se schimba(la comanda cd)
	-> am citit de la tastatura comenzile

### Comanda mkdir:
	 -> verific daca numele noului director se gaseste in lista de fisiere a root ului folosindu-ma de functia CautaNod careia ii dau ca parametrii arborele unde sa caute, numele si functia de comparare
	 -> in cazul in care nu s-a gasit apelez functia mkdir care se gaseste in fisierul functions.c
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#### Functia mkdir (directorul radacina unde urmeaza sa fie inserat, numele directorului)

	-> creez un nou nod de tip director (dir) 
	-> daca directorul radacina nu mai are alte directoare actualizez campul directories din info
	-> in caz contrar apelez functia AddNod care imi returneaza 0 sau 1 in cazul in care a reusit adaugarea in arbore

Functia returneaza la randul ei 0 sau 1 daca a reusit creerea directorului
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### Comanda touch:
	-> verific daca numele noului fisier se gaseste in lista de directoarelor a root ului folosindu-ma de functia CautaNod 
	-> in cazul in care nu s-a gasit apelez functia touch care se gaseste in fisierul functions.c
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#### Functia touch (directorul radacina unde urmeaza sa fie inserat, numele fisierului)

	-> creez un nou nod de tip fisier (file) 
	-> daca directorul radacina nu mai are alte fisiere actualizez campul files din info
	-> in caz contrar apelez functia AddNod care imi returneaza 0 sau 1 in cazul in care a reusit adaugarea in arbore

Functia returneaza la randul ei 0 sau 1 daca a reusit creerea fisierului
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### Comanda ls:
	-> apelez functia PrintArb care are ca parametri arborele ce trebuie afisat in inordine si functia de afisare specifica pentru tipul de informatie
	-> apelam prima data pentru directoare si dupa pentru fisiere
### Comanda rm:
	-> apelez functia rm care se gaseste in fisierul functions.c si are ca parametrii radacina si numele fisierului de sters
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#### Functia rm
	-> prima data ma folosesc de functia CautaNod(care se gaseste in TArb.c) pentru a cauta si returna nodul care are in informatie numele dat
	-> daca rezultatul functiei este NULL, inseamna ca nu exista fisierul in radacina
	-> in caz contrar ne folosim de functia ParinteNod pentru a afla parintele nodului aflat anterior
	-> Apelam functia StergeNod care imi sterge conform algoritmului de la curs nodul dat ca parametru si imi returneaza ceea ce se gaseste pe pozitia lui
	-> actualizez parintele 
	-> fac distrugerile necesare pentru a elibera memoria
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### Comanda rmdir
	-> apelez functia rmdir care se gaseste in fisierul functions.c si are ca parametrii radacina si numele directorului de sters
	-> functia rmdir se comporta la fel ca rm, tot ceea ce difera este locul unde se fac cautarile, respectiv tipul de distrugeri

### Comanda cd
	-> daca dupa functia cd urmeaza ".." noul root o sa fie parintele celui vechi
	-> in caz contrar se apeleaza functia CautaNod, iar in cazul in care returneaza ceva diferit de NULL se actualizeaza root

### Comanda pwd
	-> apelam functia pwd care se gaseste in fisierul functions.c
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#### Functia pwd(directorul radacina)
	-> se apeleaza recursiv functia, pana cand parintele directorului curent este NULL
	-> de acolo incepe afisarea
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### Comanda find
	-> apelam functia FindF sau FindD in functie de argumentul primit, functii care se gasesc in fisierul functions.c
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#### Functia FindF
	-> principala idee a acestei functii este ca eu trebuie de fiecare data sa verific atat in arborele curent daca gasesc fisierul (Acest lucru se face usor cu ajutorul functiei CautaNod), dar si in fiecare dintre directoarele care se gasesc in campul direcotries
	-> acest lucru se face apeland recursiv functia pentru nodurile din stanga si din dreapta a nodului curent

Functia returneaza 0 sau 1 in cazul in care a reusit sau nu
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#### Functia FindD 

Se comporta la fel ca FindF, difera doar locul unde se face cautarea si ceea ce se afiseaza				
			


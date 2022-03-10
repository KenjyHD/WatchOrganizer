# Descriere
Presupunem ca dorim sa gestionam mai eficient filmele si serialele pe care le priveste Andrei.

Vom gestiona serialele după cum urmează:
Există 4 categorii de seriale:
1. Tendințe
2. Documentare
3. Tutoriale pentru limbajul C
4. Top10 în România

Fiecare serial are un ID al categoriei din care face parte, un nume unic, un rating, și un număr de
sezoane. Un serial este o coadă de unul sau mai multe sezoane, iar un sezon este o coadă de unul sau
mai multe episoade.

Fiecare sezon are un număr de episoade, iar fiecare episod are o durată în minute.
# Implementare
Pentru gestionarea serialelor vom folosi următoarele structuri de date:
## Liste pentru gestionarea categoriilor de seriale
Cele 4 categorii de seriale vor fi gestionate folosind liste generice simplu înlănțuite.
Serialele din interiorul fiecărei liste vor fi ordonate descrescător după rating, iar în caz de rating egal,
crescător după nume.

Serialele din Top10 sunt speciale, așa că ele vor avea pe lângă nume, rating, ID, număr de sezoane
și un număr de ordine reprezentând poziția lor în Top10. În lista Top10 vor fi păstrate întotdeauna
maxim 10 intrări.
## Coada watch_later
În această coadă vor fi mutate seriale pe care Andrei dorește să le urmărească în viitor.
Adăugarea unui serial în coada watch_later presupune eliminarea serialului din lista categoriei lui și
inserarea în coada watch_later.
## Stiva currently_watching
Această stivă gestionează serialele pe care Andrei a început să le vizioneze. Serialele din stivă
vor fi păstrate ordonat, în vârful stivei aflându-se serialul la care Andrei s-a uitat cel mai recent.
## Stiva history
Serialele vizionate integral vor fi mutate în stiva history. Serialele vor fi păstrate ordonat in
stivă, ultimul serial vizionat integral va fi în vârful stivei.

### Vom gestiona serialele lui Andrei pe baza unui set de comenzi citite dintr-un fișier.

# Descrierea operațiilor și a datelor de intrare
## A. Adăugare serial în baza de date
```
Sintaxă: add <ID> <nume> <rating> <#sezoane> <#epSez1>
<durataEp1>
<durataEp2>...<#epSez2> <durtaEp1> <durataEp2>
Mod de funcționare: Adaugă un serial nou în categoria 1<=ID<=3. Se va afișa un mesajul:
Serialul <nume> a fost adaugat la pozitia %d.\n
Exemplu: add 3 numeA 8.9 2 3 10 8 9 2 7 6 /* se cere adăugarea unui serial
în categoria 3, rating 8.9, serialul are 2 sezoane, primul sezon are 3 episoade de câte 10, 8, 9
minute, al doilea sezon are 2 episoade de câte 7, 6 minute*/
Serialul numeA a fost adaugat la pozitia 1.\n
```
## B. Adăugare sezon integral
```
Sintaxă: add_sez <nume> <#ep> <durataEp1> <durataEp2>
Mod de funcționare: Adaugă un sezon nou pentru serialul cu numele nume. Se pot adăuga
sezoane pentru orice serial care nu se află deja în history. Se va afișa un mesaj de forma:
Serialul <nume> are un sezon nou.\n
Exemplu: add_sez numeA 3 10 8 9 /* se cere adăugarea unui sezon de 3 episoade
pentru serialul numeA, episoadele au 10, 8, 9 minute*/
Serialul numeA are un sezon nou.\n
```
## C. Adăugare serial în Top10
```
Sintaxă: add_top <poz> <nume> <rating> <#sezoane> <#epSez1>
<durataEp1> <durataEp2>...<#epSez2> <durataEp1> <durataEp2>
Mod de funcționare: Adaugă un serial nou în categoria Top10. În Top10 vor fi păstrate
întotdeauna maxim 10 seriale. Serialele care au ieșit din Top10 nu vor mai reveni în top. Se
garantează că pozițiile din top sunt continue în momentul inserării. Se va afișa un mesaj de
forma:
Categoria top10: [(<nume1>, <rating1>), (<nume2>,
<rating2>)].\n
Exemplu: add_top 2 numeB 8.0 1 3 10 11 12 /* se cere adăugarea unui serial
în categoria top10, pe poziția 2, cu rating 8.0, serialul are 1 sezon cu 3 episoade de câte 10, 11,
12 minute (în top există deja un alt serial, care este primul) */
Categoria top10: [(primul_in_top, 7.5), (numeB, 8.0)].\n
```
## D. Adăugare serial în watch_later
```
Sintaxă: later <nume>
Mod de funcționare: Mută un serial din cele 4 categorii în coada watch_later. Se va afișa un
mesaj de forma:
Serialul <nume> se afla in coada de asteptare pe pozitia %d.\n
Exemplu: later numeX /* se cere mutarea serialului numeX în coada watch_later */
Serialul numeX se afla in coada de asteptare pe pozitia 3.\n
```
## E. Vizionare serial
```
Sintaxă: watch <nume> <durata>
Mod de funcționare: Mută un serial în stiva currently_watching dacă nu există deja, apoi
vizionează durata minute din serialul nume. Dacă întreg serialul are mai puțin de durata
minute de vizionat, acesta va fi vizionat integral. Se va cere vizionarea unui serial care nu se
află deja în history. Mutarea unui serial din Top10 presupune actualizarea (decrementarea)
numărului de ordine pentru serialele aflate mai jos în top. Dacă serialul a fost vizionat integral,
se va afișa mesajul următor:
Serialul <nume> a fost vizionat integral.\n
Exemplu: watch numeX 100 /* se cere vizionarea serialului numeX timp de maxim 100 de
minute */
```
## F. Afișare seriale
```
Sintaxă: show <X> ; X∈{ 1, 2, 3, top10, later, watching, history
}
Mod de funcționare: Afișează lista cu serialele din categoria X. Se va afișa un mesaj de forma:
Categoria <X>: [(<numeA>, <rA>), (<numeB>, <rB>)].\n
Exemplu: show later /* se cere afișarea serialelor din watch later */
Categoria later: [(A, 9.7), (B, 8.5)].\n
Exemplu: show 1
Categoria 1: [(A, 9.0), (B, 9.0)].
```
# Descriere functionalitati functii
### Functia show_lista
- Parcurge lista si afiseaza numele si ratingul serialelor

### Functia show_coada
- Parcurge coada si afiseaza numele si ratingul serialelor

### Functia show_stiva
- Parcurge stiva si afiseaza numele si ratingul serialelor

### Functia cauta_in_lista
- Cauta in lista serialul si retuneaza serialul/NULL daca il gaseste/nu il gaseste

### Functia cauta_in_coada_si_elimina
- Cauta serialul in coada, il elimina daca il gaseste si 
il returneaza daca il gaseste/nu il gaseste

### Functia add_sez_coada
- Cauta serialul in coada si adauga noul sezon la coada de sezoane al serialului

### Functia add_sez_stiva
- Cauta serialul in stiva si adauga noul sezon la coada de sezoane al serialului

### Functia cauta_in_stiva_si_elimina
- Cauta serialul in stiva, daca il gaseste il elimina si il returneaza, 
altfel returneaza NULL

### Functia cauta_in_coada_si_elimina
- Cauta serialul in coada, daca il gaseste il elimina si il returneaza, 
altfel returneaza NULL

### Functia muta_lista_stiva
- Cauta serialul in lista, daca il gaseste il muta in varful stivei si 
il returneaza, altfel returneaza NULL

### Functia muta_lista_coada
- Cauta serialul in lista, daca il gaseste il muta in coada si 
il returneaza, altfel returneaza NULL

### Functia actualizare_top
- Parcurge serialele din top, actualizeaza numarul de ordine din top 
si elimina serialele cu ordinul din top mai mare de 10

### Functia AlocCelulaG
- Aloca si retuneaza celula cu informatia respectiva

### Functia InsLG
- Insereaza serialul in una din primele 3 liste ordonat descrescator dupa rating 
si crescator dupa nume in cazul ratingurilor egale

### Functia InsTop
- Insereaza serialul in lista top10 in locul corespunzator ordinii din top

### Functia Eliminare
- Elimina serialul din lista

---
Drepturile de autor fata de crearea checkerului si conditiei apartin echipei de Structuri de Date 2021 UPB

Implementarea codului: Calmis Liviu
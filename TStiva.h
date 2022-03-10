/* Calmis Liviu - 311 CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef _FUNCTII_
#define _FUNCTII_
  typedef int (* TF1)(void *,...);
  typedef int (* TF2)(const void *, const void *);
  typedef int (* TF3)(char *);
#endif

#ifndef STIVA
#define STIVA

/* initializeaza stiva cu elem.de dimensiune d; 
anumite implementari pot necesita si alti parametri */
void* InitS(size_t d,...);
/* pune element in varful stivei */
int Push(void* a, void* ae);
/* extrage elementul din varful stivei la adresa ae */
int Pop (void* a, void* ae);
/* copiaza elementul din varful stivei la adresa ae */
int Top (void* a, void* ae);
/* test stiva vida */
int VidaS(void* a);
/* numarul de elemente din stiva */
size_t NrES (void* a);
/* dimensiunea elementelor din stiva */
size_t DimES(void* a);
/* transforma stiva in stiva vida */
void ResetS (void* a);
/* elibereaza intregul spatiu ocupat de stiva */
void DistrS (void** aa);
/* inverseaza continutul stivei */
int InvS(void* a);

int eNumar(char *s);
int AfiString(void *a);
/*- prelucrarea tuturor elementelor din stiva folosind o  functie parametru */
size_t Prel_V_B(void* a, TF1 f); /* prelucreaza de la Varf spre Baza */
size_t Prel_B_V(void* a, TF1 f); /* prelucreaza de la Baza spre Varf */

/* Operatii de deplasare in stiva destinatie din stiva sursa.
Rezultat < 0 in caz de eroare (de exemplu dimensiunile elementelor difera),
0 daca sursa vida, 1 = succes */
/* muta elementul din varful stivei sursa */
int MutaS(void* ad, void* as);
/* muta stiva sursa peste destinatie */
int Suprapune(void* ad, void* as);
/* suprapune inversul sursei peste destinatie */
int Rastoarna(void* ad, void* as);

#endif

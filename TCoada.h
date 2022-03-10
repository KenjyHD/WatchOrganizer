/* Calmis Liviu - 311 CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef _FUNCTII_
#define _FUNCTII_
  typedef int (*TF1)(void *, FILE *);
  typedef int (*TF2)(const void *, const void *);
#endif

#ifndef COADA
#define COADA
/* creeaza coada vida cu elemente de dimensiune d;
anumite implementari pot necesita si alti parametri */
void* InitQ(size_t d,...);
/* adauga element la sfarsitul cozii */
int IntrQ(void* a, void* ae);
/* extrage primul element din coada la adresa ae */
int ExtrQ(void* a, void* ae);
/* copiaza primul element din coada la adresa ae */
int PrimQ(void* a, void* ae);
/* test coada vida */
int VidaQ(void* a);
/* numarul de elemente din coada */
size_t NrEQ(void* a);
/* dimensiunea elementelor din coada */
size_t DimEQ(void* a);
/* transforma coada in coada vida */
void ResetQ(void* a);
/* elibereaza intregul spatiu ocupat de coada */
void DistrQ(void** aa);
/* prelucreaza elementele, folosind functia f;
rezultat = numarul de elemente pentru care f != 0 */
size_t PrelQ(void* a, TF1 f, FILE *g);

/* Operatii de deplasare in coada destinatie din coada sursa.
Rezultat < 0 in caz de eroare (de exemplu dimensiunile elementelor difera),
0 daca sursa vida, 1 = succes */
/* muta in coada dest. primul element din sursa */
int MutaQ(void *ad, void *as);
/* concatenare (muta toate elem.din sursa) */
int ConcatQ(void *ad, void *as);

#endif

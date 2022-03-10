/* Calmis Liviu - 311 CB */

#include "tlg.h"

/* Aloca celula cu informatia data parametru si o retuneaza */
TLG AlocCelulaG(void* x)
{
    TLG aux;
    aux = (TLG)malloc(sizeof(TCelulaG));
    
    if (!aux) return NULL;
    aux->info = x;
    aux->urm = NULL;
    return aux;
}
 /* Insereaza serialul in listele 1, 2 sau 3 ordonat dupa rating si 
 respectiv nume */
int InsLG(TLG* aL, void* ae)
{
	TLG cur;
	TLG aux = AlocCelulaG(ae);
	int n = 1;
	
	if(*aL == NULL || 
	(((TSerial*)(*aL)->info)->rating < ((TSerial*)ae)->rating) || 
	((((TSerial*)(*aL)->info)->rating == ((TSerial*)ae)->rating) && 
	(strcmp(((TSerial*)(*aL)->info)->nume, ((TSerial*)ae)->nume) > 0))){
		//printf("Heloo\n");
		aux->urm = *aL;
		*aL = aux;
	}
	else{
		cur = *aL;
		n++;
		while(cur->urm != NULL && 
		((((TSerial*)(cur->urm)->info)->rating > ((TSerial*)ae)->rating) || 
		((((TSerial*)(cur->urm)->info)->rating == ((TSerial*)ae)->rating) && 
		(strcmp(((TSerial*)(cur->urm)->info)->nume, 
		((TSerial*)ae)->nume) < 0)))){
			cur = cur->urm;
			n++;
		}
		aux->urm = cur->urm;
		cur->urm = aux;
	}
	return n;
}

/* Insereaza serialul in lista top10 comform ordinii din top */
int InsTop(TLG* aL, void* ae)
{
	TLG cur;
	TLG aux = AlocCelulaG(ae);
	int i = 1;
	if(!*aL || ((TSerial*)ae)->ordin_top == 1){
		aux->urm = *aL;
		*aL = aux;
	}
	else {
		cur = *aL;
		while(cur->urm != NULL && ((i + 1) != ((TSerial*)ae)->ordin_top)){
			i++;
			cur = cur->urm;
		}
			
		aux->urm = cur->urm;
		cur->urm = aux;
	}
	return 1;
}

void Distruge(TLG* aL, TF free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

size_t LungimeLG(TLG* a)      /* numarul de elemente din lista */
{
	size_t lg = 0;
	TLG p = *a;

    /* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->urm)
        lg++;

	return lg;
}

/* Elimina serialul din lista */
void Eliminare(TLG *aL, char *nume)
{
	TLG temp = *aL;
	TLG pre = NULL;
	
	if(temp != NULL && 
	(strcmp(((TSerial*)temp->info)->nume, nume) == 0)){
		*aL = temp->urm;
		free(temp);
	}
	else{
		while(temp != NULL && 
		(strcmp(((TSerial*)temp->info)->nume, nume) != 0)){
			pre = temp;
			temp = temp->urm;
		}
		if(temp == NULL) return;
		pre->urm = temp->urm;
	}
}

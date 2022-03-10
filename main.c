/* Calmis Liviu - 311 CB */

#include <stdio.h>
#include <stdlib.h>
#include "TCoada.h"
#include "TStiva.h"
#include "tlg.h"
#include "TCoada-V.h"
#include <string.h>

/* Functia de afisare a serialelor din lista */
int show_lista(TLG *aL, FILE* g)
{
    
    TLG cur;
    if(!*aL) return 0;
    for (cur = *aL; cur->urm != NULL; cur = cur->urm){
        fprintf(g, "(%s, %0.1f), ", ((TSerial*)cur->info)->nume, 
        ((TSerial*)cur->info)->rating);
    }
    fprintf(g, "(%s, %0.1f)", ((TSerial*)cur->info)->nume, 
    ((TSerial*)cur->info)->rating);
    return 1;
}

/* Functia de afisare a serialelor din coada watch_later */
int show_coada(void *coada, FILE* g)
{
    void *aux = InitQ(DIME(coada), 2048);
    void *el = malloc(sizeof(TSerial));

    if(VidaQ(coada)) return 0;
    while(NrEQ(coada) > 1){
        ExtrQ(coada, el);
        IntrQ(aux, el);
        fprintf(g, "(%s, %0.1f), ", ((TSerial*)el)->nume, 
        ((TSerial*)el)->rating);
    }
    ExtrQ(coada, el);
    IntrQ(aux, el);
    fprintf(g, "(%s, %0.1f)", ((TSerial*)el)->nume, 
    ((TSerial*)el)->rating);
    ConcatQ(coada, aux);
    return 1;
}

/* Functia de afisare a serialelor din stiva */
int show_stiva(void *stiva, FILE* g)
{
    void *aux = InitS(DIME(stiva), 2048);
    void *el = malloc(sizeof(TSerial));

    if(VidaS(stiva)) return 0;
    while(NrES(stiva) > 1){
        Pop(stiva, el);
        Push(aux, el);
        fprintf(g, "(%s, %0.1f), ", ((TSerial*)el)->nume, 
        ((TSerial*)el)->rating);
    }
    Pop(stiva, el);
    Push(aux, el);
    fprintf(g, "(%s, %0.1f)", ((TSerial*)el)->nume, 
    ((TSerial*)el)->rating);
    Rastoarna(stiva, aux);
    return 1;
}

/* Cauta in lista serialul dupa nume si returneaza serialul/NULL */
TSerial *cauta_in_lista(TLG *aL, char *nume)
{
    TLG cur;
    for (cur = *aL; cur != NULL; cur = cur->urm){
        if(strcmp(((TSerial*)(cur->info))->nume, nume) == 0)
            return ((TSerial*)(cur->info));
    }
    return NULL;
}

/* Cauta si elimina din coada serialul si returneaza serialul/NULL */
TSerial *cauta_in_coada_si_elimina(void *watch_later, char *nume)
{
    void *aux = InitQ(DimEQ(watch_later), 2048);
    void *el = malloc(sizeof(TSerial));
    void *res = malloc(sizeof(TSerial));

    while(!VidaQ(watch_later)){
        PrimQ(watch_later, res);
        ExtrQ(watch_later, el);
        if(strcmp(((TSerial*)el)->nume, nume) == 0){
            while(!VidaQ(watch_later)){
                MutaQ(aux, watch_later);
            }
            ConcatQ(watch_later, aux);
            return (TSerial*)res;
        }
        IntrQ(aux, el);
    }
    ConcatQ(watch_later, aux);
    return NULL;
}

/* Cauta in coada serialul si adauga la coada de sezoane noul sezon */
void add_sez_coada(void *coada, char *nume, void *coada_sezon, 
int durata_sezon)
{
    void *aux = InitQ(DimEQ(coada), 2048);
    void *el = malloc(sizeof(TSerial));
    
    while(!VidaQ(coada)){
        ExtrQ(coada, el);
        if(strcmp(((TSerial*)el)->nume, nume) == 0){
            IntrQ(((TSerial*)el)->coada, coada_sezon);
            ((TSerial*)el)->min += durata_sezon;
        }
        IntrQ(aux, el);
    }
    ConcatQ(coada, aux);
    return;
}

/* Cauta si elimina din stiva serialul si returneaza serialul/NULL */
TSerial *cauta_in_stiva_si_elimina(void *stiva, char *nume)
{
    void *aux = InitS(DimES(stiva), 2048);
    void *el = malloc(sizeof(TSerial));
    void *res = NULL;
    
    while(!VidaS(stiva)){
        Pop(stiva, el);
        Push(aux, el);
        if(strcmp(((TSerial*)el)->nume, nume) == 0){
            res = malloc(sizeof(TSerial));
            Pop(aux, res);
            while(!VidaS(aux)){
                Pop(aux, el);
                Push(stiva, el);
            }
            
            return (TSerial*)res;
        }
    }
    while(!VidaS(aux)){
        Pop(aux, el);
        Push(stiva, el);
    }
    return NULL;
}

/* Cauta in stiva serialul si adauga la coada de sezoane noul sezon */
void add_sez_stiva(void *stiva, char *nume, void *coada_sezon, 
int durata_sezon)
{
    void *aux = InitS(DimES(stiva), 2048);
    void *el = malloc(sizeof(TSerial));
    void *res = NULL;
    
    while(!VidaS(stiva)){
        Pop(stiva, el);
        Push(aux, el);
        if(strcmp(((TSerial*)el)->nume, nume) == 0){
            res = malloc(sizeof(TSerial));
            Pop(aux, res);
            IntrQ(((TSerial*)res)->coada, coada_sezon);
            ((TSerial*)res)->min += durata_sezon;
            Push(aux, res);
            while(!VidaS(aux)){
                Pop(aux, el);
                Push(stiva, el);
            }
            
            return;
        }
    }
    while(!VidaS(aux)){
        Pop(aux, el);
        Push(stiva, el);
    }
    return;
}

/* Muta serialul din lista in stiva daca exista si returneaza serialul/NULL */
TSerial *muta_lista_stiva(TLG *aL, char *nume, int d, void *stiva, FILE *g)
{
    TLG cur;
    void *el = malloc(sizeof(TSerial));
    for (cur = *aL; cur != NULL; cur = cur->urm){
        if(strcmp(((TSerial*)(cur->info))->nume, nume) == 0){
            ((TSerial*)(cur->info))->minVizionate += d;
            Push(stiva, ((TSerial*)(cur->info)));
            Eliminare(aL, nume);
            Top(stiva, el);
            return ((TSerial*)(el));
        }
    }
    return NULL;
}

/* Muta serialul din lista in coada daca exista */
void muta_lista_coada(TLG *aL, char *nume, void *coada)
{
    TLG cur;
    for (cur = *aL; cur != NULL; cur = cur->urm){
        if(strcmp(((TSerial*)(cur->info))->nume, nume) == 0){
            IntrQ(coada, ((TSerial*)(cur->info)));
            Eliminare(aL, nume);
            return;
        }
    }
    return;
}

/* Parcurge serialele din top, le actualizeaza ordinul in top si 
elimina serialele cu ordinul mai mic de 10 */
int actualizare_top(TLG *aL)
{
    TLG cur;
    int i = 1;
    for (cur = *aL; cur != NULL; cur = cur->urm){
        if(i > 10){
            Eliminare(aL, ((TSerial*)(cur->info))->nume);
            return 1;
        }
        else{
            (((TSerial*)cur->info)->ordin_top) = i;
            i++;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{   
    FILE *f, *g;
    char *line = NULL;
	size_t len = 0;
	int i = 0;
	int j = 0;
    void *c_sezon, *watch_later;
	void *el = malloc(sizeof(TSerial));
    watch_later = InitQ(sizeof(TSerial), 2048);
    void *currently_watching = InitS(sizeof(TSerial), 2048);
    void *history = InitS(sizeof(TSerial), 2048);
    TSerial *serial;
    TLG tendinte = NULL, documentare = NULL, tutoriale = NULL, top = NULL;
	
	
    f = fopen(argv[1], "r");
	g = fopen(argv[2], "w");
	if (f == NULL)
		return 1;

 	// Citesc fisierul .in
    while (getline(&line, &len, f) != -1) {
        serial = malloc(sizeof(TSerial));
        serial->min = 0;
        serial->minVizionate = 0;
        serial->coada = InitQ(sizeof(TCoadaV), 20);
        serial->nume = malloc(100 * sizeof(char));
        c_sezon = InitQ(sizeof(int), 40);
        char *comm = strtok(line, " ");

        /* Pentru comanda add sau add_top */
        if(strcmp(comm, "add") == 0 || strcmp(comm, "add_top") == 0){
            char *id = strtok(NULL, " ");

            /* Pentru serialele din top10 id-ul va fi 4 */
            if(strcmp(comm, "add_top") == 0){
                serial->id = 4;
                serial->ordin_top = atoi(id);
            }
            /* Pentru celelalte seriale ordinul in top va fi 0 */
            else{
                serial->id = atoi(id);
                serial->ordin_top = 0;
            }

            char *nume = strtok(NULL, " ");
            strcpy(serial->nume, nume);

            char *rate = strtok(NULL, " ");
            serial->rating = atof(rate);

            char *nr_sez = strtok(NULL, " ");
            serial->nr_sez = atoi(nr_sez);
            
            int ns = atoi(nr_sez);
            /* Citesc sezoanele */
            for(i = 0; i < ns; i++){
                char *nr_ep = strtok(NULL, " ");
                int ne = atoi(nr_ep);
                /* Citesc durata fiecarui episod */
                for(j = 0; j < ne; j++){
                    char *durata_ep = strtok(NULL, " ");
                    int de = atoi(durata_ep);
                    IntrQ(c_sezon, &de);
                    serial->min += de;
	            }
                IntrQ(serial->coada, c_sezon);
	        }
            /*Pt fiecare id introduce serialul in lista respectiva */
            if(serial->id == 1)
                fprintf(g, "Serialul %s a fost adaugat la pozitia %d.\n", 
                serial->nume, InsLG(&tendinte, (void *)serial));
            if(serial->id == 2)
                fprintf(g, "Serialul %s a fost adaugat la pozitia %d.\n", 
                serial->nume, InsLG(&documentare, (void *)serial));
            if(serial->id == 3)
                fprintf(g, "Serialul %s a fost adaugat la pozitia %d.\n", 
                serial->nume, InsLG(&tutoriale, (void *)serial));
            if(serial->id == 4){
                InsTop(&top, (void *)serial);
                actualizare_top(&top);
                fprintf(g, "Categoria top10: [");
                show_lista(&top, g);
                fprintf(g, "].\n");
            }
        }
        
        /* Pt comanda add_sez */
        if(strcmp(comm, "add_sez") == 0){
            char *nume = strtok(NULL, " ");
            char *nr_ep = strtok(NULL, " ");
            int ne = atoi(nr_ep);
            int durata_sezon = 0;
            c_sezon = InitQ(sizeof(int), 20);
            /* Construesc coada-sezon */
            for(j = 0; j < ne; j++){
                char *durata_ep = strtok(NULL, " ");
                int de = atoi(durata_ep);
                IntrQ(c_sezon, &de);
                /* Memorez durata sezonului */
                durata_sezon += de;
	        }

            serial = cauta_in_lista(&tendinte, nume);
            /* Caut serialul in toate listele, cozile si stivele 
            si adaug sezonul la coada de sezoane a serialului; 
            deasemenea actualizeaza nr total de minute al serialului*/
            if (serial){
                IntrQ(serial->coada, c_sezon);
                serial->min += durata_sezon;
            }

            serial = cauta_in_lista(&documentare, nume);
            if (serial){
                IntrQ(serial->coada, c_sezon);
                serial->min += durata_sezon;
            }

            serial = cauta_in_lista(&tutoriale, nume);
            if (serial){
                IntrQ(serial->coada, c_sezon);
                serial->min += durata_sezon;
            }

            serial = cauta_in_lista(&top, nume);
            if (serial){
                IntrQ(serial->coada, c_sezon);
                serial->min += durata_sezon;
            }

            add_sez_coada(watch_later, nume, c_sezon, durata_sezon);
            add_sez_stiva(currently_watching, nume, c_sezon, durata_sezon);
            fprintf(g, "Serialul %s are un sezon nou.\n", nume);
        }

        /* Pentru comanda later */
        if(strcmp(comm, "later") == 0){
            char *nume = strtok(NULL, " ");
            
            if(nume != NULL && nume[strlen(nume) - 1] == '\n') 
                nume[strlen(nume) - 1] = '\0';
            /* Cauta serialele in toate listele si il muta in 
            coada watch_later cand il gaseste*/
            muta_lista_coada(&tendinte, nume, watch_later);
            muta_lista_coada(&documentare, nume, watch_later);
            muta_lista_coada(&tutoriale, nume, watch_later);
            muta_lista_coada(&top, nume, watch_later);
            fprintf(g, 
            "Serialul %s se afla in coada de asteptare pe pozitia %ld.\n", 
            nume, NrEQ(watch_later));
        }

        /* Pentru comanda watch */
        if(strcmp(comm, "watch") == 0){
            
            char *nume = strtok(NULL, " ");
            char *durata = strtok(NULL, " ");
            int d = atoi(durata);
            
            /* Cauta serialul in toate listele, stivele si cozile; 
            muta in stiva currently_watching si actualizeaza nr de 
            minute vizionate; daca nr de minute vizionate e mai mare 
            de nr total de minute al serialullui atunci muta serialul din 
            currently_watching in stiva history */
            serial = cauta_in_stiva_si_elimina(currently_watching, nume);
            if(serial){
            serial->minVizionate += d;
            Push(currently_watching, serial);
            }
            if(serial && serial->min <= serial->minVizionate){
                fprintf(g, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, el);
                Push(history, el);
            }
            
            serial = cauta_in_coada_si_elimina(watch_later, nume);
            if(serial){
            serial->minVizionate += d;
            Push(currently_watching, serial);    
            }
            if(serial && serial->min <= serial->minVizionate){
                fprintf(g, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, el);
                Push(history, el);
            }

            serial = muta_lista_stiva(&top, nume, d, 
            currently_watching, g);
            if(serial) actualizare_top(&top);
            if(serial && serial->min <= serial->minVizionate){
                
                fprintf(g, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, el);
                Push(history, el);
            }

            serial = muta_lista_stiva(&tendinte, nume, d, 
            currently_watching, g);
            if(serial && serial->min <= serial->minVizionate){
                fprintf(g, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, el);
                Push(history, el);
            }

            serial = muta_lista_stiva(&documentare, nume, d, 
            currently_watching, g);
            if(serial && serial->min <= serial->minVizionate){
                fprintf(g, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, el);
                Push(history, el);
            }

            serial = muta_lista_stiva(&tutoriale, nume, d, 
            currently_watching, g);
            if(serial && serial->min <= serial->minVizionate){
                fprintf(g, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, el);
                Push(history, el);
            }
        }

        /* Pentru comanda show */
        if(strcmp(comm, "show") == 0){
            char *cat = strtok(NULL, " ");
            if(cat && cat[strlen(cat) - 1] == '\n') 
                cat[strlen(cat) - 1] = '\0';
            /* Afla ce este necesar de afisat si afiseaza serialele din 
            lista/coada/stiva respectiva */
            fprintf(g, "Categoria %s: [", cat);
            if(strcmp(cat, "1") == 0) show_lista(&tendinte, g);
            if(strcmp(cat, "2") == 0) show_lista(&documentare, g);
            if(strcmp(cat, "3") == 0) show_lista(&tutoriale, g);
            if(strcmp(cat, "top10") == 0) show_lista(&top, g);
            if(strcmp(cat, "later") == 0) show_coada(watch_later, g);
            if(strcmp(cat, "watching") == 0) show_stiva(currently_watching, g);
            if(strcmp(cat, "history") == 0) show_stiva(history, g);
            fprintf(g, "].\n");
        }
    }
  return 0;
}

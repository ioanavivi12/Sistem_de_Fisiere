//DABELEA IOANA-VIVIANA 313CB
#include "functions.h"
 
TArb NewNod(char *nume, TArb p, void *(*NewInfo)(char *, TArb)){
    TArb aux = (TArb)malloc(sizeof(TNod));
    if(!aux) return NULL;
    aux->info = NewInfo(nume, p);
    if(!aux->info){
        free(aux);
        return NULL;
    }
    aux->st = NULL;
    aux->dr = NULL;
}
TArb CautaNod(TArb root, char *nume, int(*CompName)(void *, char *)){
    TArb aux = root;
    while(aux){
        if(CompName(aux->info, nume) > 0)
            aux = aux->st;
        else 
        if(CompName(aux->info, nume) < 0)   
            aux = aux->dr;
        else
            return aux;
    }
    return NULL;
}
int AddNod(TArb root, TArb newnod, int (*CompInfo)(void *, void *)){
    TArb aux = root, ant = NULL;
    while(aux){
        ant = aux;
        if(CompInfo(aux->info, newnod->info) > 0)
            aux = aux->st;
        else 
        if(CompInfo(aux->info, newnod->info) < 0)   
            aux = aux->dr;
        else
            return 0;
    }
    if(CompInfo(ant->info, newnod->info) > 0)
        ant->st = newnod;
    else
        ant->dr = newnod;
    return 1;
}
void PrintArb(TArb nod, void (*PrintInfo)(void *)){
    if(!nod)
        return ;
    PrintArb(nod->st, PrintInfo);
    PrintInfo(nod->info);
    PrintArb(nod->dr, PrintInfo);
}
void DistrugereNod(TArb *nod, void (*DistrugereInfo)(void **)){
    DistrugereInfo(&((*nod)->info));
    (*nod)->st = (*nod)->dr = NULL;
    free(*nod);
}
void DistrugereArbore(TArb *arb,  void (*DistrugereInfo)(void **)){
    if(!(*arb))
        return;
    if((*arb)->st != NULL){
        DistrugereArbore(&(*arb)->st, DistrugereInfo);
    }
    if((*arb)->dr != NULL){
        DistrugereArbore(&(*arb)->dr, DistrugereInfo);
    }
    DistrugereNod(arb, DistrugereInfo);
}
TArb ParinteNod(TArb arb, TArb nod, int (*CompInfo)(void *, void *)){
    TArb ant = NULL;
    TArb aux = arb;
    while(aux){
        if(CompInfo(aux->info, nod->info) < 0){
            ant = aux;
            aux = aux->dr;
        }
        else
        if(CompInfo(aux->info, nod->info) > 0){
            ant = aux;
            aux = aux->st;
        }
        else
            return ant;
    }
}
TArb StergereNod(TArb nod, void (*DistrugereInfo)(void **)){
    //functia o sa returneze ce a ramas "in locul" nodului sters

    if(nod->st == NULL && nod->dr == NULL)
        return NULL;
    else
    if(nod->st != NULL && nod->dr == NULL)
        return nod->st;
    else
    if(nod->st == NULL && nod->dr != NULL)
        return nod->dr;
    else{
        TArb aux = nod->st, ant = nod;
        int ok = 0;
        while(aux->dr){
            ant = aux;
            aux = aux->dr;
            ok = 1;
        }
        void *swap = aux->info;
        aux->info = nod->info;
        nod->info = swap;
        if(ok == 1)
            ant->dr = aux->st;
        else 
            ant->st = aux->st;
        DistrugereNod(&aux, DistrugereInfo);
        return nod;
    }
}
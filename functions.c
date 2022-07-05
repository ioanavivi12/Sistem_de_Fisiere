//DABELEA IOANA-VIVIANA 313CB
#include "functions.h"

int max(int a, int b){
    if(a < b)
        return b;
    return a;
}
void pwd(TArb root){
    InfoDir d = *(InfoDir *)(root->info);
    if(d.parent != NULL)
        pwd(d.parent);
    printf("/%s", d.name);
}
void DistrugereInfoD(void **info){
    InfoDir *d = (InfoDir *)(*info);
    if(d->directories != NULL)
        DistrugereDir(&(d->directories));
    if(d->files != NULL)
        DistrugereArbore(&(d->files), DistrugereInfoF);
    free(d->name);
    free(d); 
}
void DistrugereInfoF(void **info){
    InfoFile *f = (InfoFile *)(*info);
    free(f->name);
    free(f); 
}
int CmpNumeDir(void *a, char *nume){
    InfoDir d1 = *(InfoDir *)a;
    return strcmp(d1.name, nume);
}
int CmpNumeFile(void *a, char *nume){
    InfoFile f1 = *(InfoFile *)a;
    return strcmp(f1.name, nume);
}
void PrintDir(void *a){
    InfoDir d1 = *(InfoDir *)a;
    printf("%s ", d1.name);
}
void PrintFile(void *a){
    InfoFile f1 = *(InfoFile *)a;
    printf("%s ", f1.name);
}
int CmpDir(void *a, void *b){
    InfoDir d1 = *(InfoDir *)a;
    InfoDir d2 = *(InfoDir *)b;
    return strcmp(d1.name, d2.name);
}
int CmpFile(void *a, void *b){
    InfoFile f1 = *(InfoFile *)a;
    InfoFile f2 = *(InfoFile *)b;
    return strcmp(f1.name, f2.name);
}

void *NewDirectory(char *nume, TArb p){
    InfoDir *var = (InfoDir *) malloc(sizeof(InfoDir));
    if(!var)
        return NULL;
    var->name = (char *)malloc(strlen(nume) + 1);
    if(!var->name){
        free(var);
        return NULL;
    }
    strncpy(var->name, nume, strlen(nume));
    var->name[strlen(nume)] = '\0';
    var->parent = p;
    var->directories = NULL;
    var->files = NULL;
    return (void *)var;
    
}
void *NewFile(char *nume, TArb p){
    InfoFile *var = (InfoFile *)malloc(sizeof(InfoFile));
    if(!var)
        return NULL;
    var->name = (char *)malloc(strlen(nume) + 1);
    if(!var->name){
        free(var);
        return NULL;
    }
    strncpy(var->name, nume, strlen(nume));
    var->name[strlen(nume)] = '\0'; // nu am idee de ce trebuie sa pun asta
    //dar doar asa merge :(
    var->parent = p;
    return (void *)var;
}
int mkdir(TArb root, char *nume){
    TArb dir = NewNod(nume, root, NewDirectory);
    if(!dir)
        return -1;
    InfoDir *var = ((InfoDir *)root->info);
    if(var->directories == NULL){
        var->directories = dir;
        return 1;
    }
    else{
        int ok = AddNod(var->directories, dir, CmpDir);
        if(ok == 0)
            DistrugereNod(&dir, DistrugereInfoD);
        return ok;
    }
}
int touch(TArb root, char *nume){
    TArb file = NewNod(nume, root, NewFile);
    if(!file)
        return -1;
    InfoDir *var = ((InfoDir *)root->info);
    if(var->files == NULL){
        var->files = file;
        return 1;
    }
    else{
        int ok = AddNod(var->files, file, CmpFile);
        if(ok == 0)
            DistrugereNod(&file, DistrugereInfoF);
        return ok;
    }
}
void ls(TArb root){
    InfoDir d = *(InfoDir *)(root->info);
    PrintArb(d.directories, PrintDir);
    PrintArb(d.files, PrintFile);
}
void rm(TArb root, char *nume){
    InfoDir *dir = (InfoDir *)root->info;
    TArb nod = CautaNod(dir->files, nume, CmpNumeFile);
    if(nod == NULL){
        printf("File %s doesn't exist!\n", nume);
        return;
    }
    TArb parinte = ParinteNod(dir->files, nod, CmpFile);
    TArb new = StergereNod(nod, DistrugereInfoF);
   
    if(parinte == NULL)
        dir->files = new;
    else
    if(parinte->dr != NULL && CmpFile(parinte->dr->info, nod->info) == 0)
        parinte->dr = new;
    else
    if(parinte->st != NULL && CmpFile(parinte->st->info, nod->info) == 0)
        parinte->st = new;

    if(((nod->st == NULL || nod->dr == NULL) && (new != NULL && CmpFile(nod->info, new->info) != 0)) || (new == NULL))
        DistrugereNod(&nod, DistrugereInfoF);
}
void rmdir(TArb root, char *nume){
    InfoDir *dir = (InfoDir *)root->info;
    TArb nod = CautaNod(dir->directories, nume, CmpNumeDir);
    if(nod == NULL){
        printf("Directory %s doesn't exist!\n", nume);
        return;
    }
    TArb parinte = ParinteNod(dir->directories, nod, CmpDir);
    TArb new = StergereNod(nod, DistrugereInfoD);

    if(parinte == NULL)
        dir->directories = new;
    else
    if(parinte->dr != NULL && CmpDir(parinte->dr->info, nod->info) == 0)
        parinte->dr = new;
    else
    if(parinte->st != NULL && CmpDir(parinte->st->info, nod->info) == 0)
        parinte->st = new;
    if(((nod->st == NULL || nod->dr == NULL) && (new != NULL && CmpDir(nod->info, new->info) != 0)) || new == NULL)
        DistrugereNod(&nod, DistrugereInfoD);
}
int FindF(TArb arb, char *nume){
    if(!arb)
        return 0;
    InfoDir d = *(InfoDir *)(arb->info);
    TArb nod;
    if(d.files != NULL){
        nod = CautaNod(d.files, nume, CmpNumeFile);
        if(nod != NULL){
            printf("File %s found!\n", nume);
            pwd(arb);
            return 1;
        }
    }
    int ok = FindF(d.directories, nume);
    if(ok == 1)
        return 1;
    return max(FindF(arb->st,nume), FindF(arb->dr, nume));
}
int FindD(TArb arb, char *nume){
    if(!arb)
        return 0;
    InfoDir d = *(InfoDir *)(arb->info);
    TArb nod;
    if(d.directories != NULL){
        nod = CautaNod(d.directories, nume, CmpNumeDir);
        if(nod != NULL){
            printf("Directory %s found!\n", nume);
            pwd(nod);
            return 1;
        }
    }
    int ok = FindD(d.directories, nume);
    if(ok == 1)
        return 1;
    return max(FindD(arb->st,nume), FindD(arb->dr, nume));
}
void DistrugereDir(TArb *arb){
    //Primeste ca parametru radacina si trebuie sa stearga toate directoarele si fisierele din el + radacina
    if(!(*arb))
        return;
    InfoDir *d = (InfoDir *)(*arb)->info;
    if(d->files != NULL){
        DistrugereArbore(&d->files, DistrugereInfoF);
        d->files = NULL;
    }
    if(d->directories != NULL){
       DistrugereDir(&(d->directories));
       d->directories = NULL;
    }
    if((*arb)->dr != NULL){
        DistrugereDir(&((*arb)->dr));
        (*arb)->dr = NULL;
    }
    if((*arb)->st != NULL){
        DistrugereDir(&((*arb)->st));
        (*arb)->st = NULL;
    }
    DistrugereNod(arb, DistrugereInfoD);
}
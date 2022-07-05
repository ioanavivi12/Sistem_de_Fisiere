#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TArb.h"
//Campul informatie al directorului o sa contina un element de tipul InfoDir
typedef struct InfoDir{
    char *name;
    TArb parent;
    TArb directories;
    TArb files;
}InfoDir;
//Campul informatie al fisierelor o sa contina un element de tipul InfoFile
typedef struct InfoFile{
    char *name;
    TArb parent;
}InfoFile;

int max(int a, int b);
void PrintDir(void *a);
void PrintFile(void *a);
int CmpDir(void *a, void *b);
int CmpFile(void *a, void *b);
int mkdir(TArb root, char *nume);
int touch(TArb root, char *nume);
void ls(TArb root);
int CmpNumeDir(void *a, char *nume);
int CmpNumeFile(void *a, char *nume);
void DistrugereInfoF(void **info);
void DistrugereInfoD(void **info);
void pwd(TArb root);
void rm(TArb root, char *nume);
void rmdir(TArb root, char *nume);
int FindF(TArb arb, char *nume);
int FindD(TArb arb, char *nume);
void DistrugereDir(TArb *arb);
void *NewDirectory(char *nume, TArb p);
void *NewFile(char *nume, TArb p);

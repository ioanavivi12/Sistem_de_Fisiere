//DABELEA IOANA-VIVIANA 313CB
#include "functions.h"

int main(){
    char *line = NULL, *sep = " \n", *com;
    size_t len = 0;
    TArb root = NewNod("root", NULL, NewDirectory);
    TArb initroot = root;
    if(!root)
        return -1;
    while(getline(&line, &len, stdin) != 0 && strstr(line, "quit") == 0){
        InfoDir d = *(InfoDir *)(root->info);
        com = strtok(line, sep);
        if(strstr(com, "mkdir") != 0){
            char *nume = strtok(NULL, sep);
            if(CautaNod(d.files, nume, CmpNumeFile) != NULL)
                printf("File %s already exists!\n", nume);
            else{
                int ok = mkdir(root, nume);
                if(ok == 0)
                    printf("Directory %s already exists!\n", nume);
            }
        }
        else
        if(strstr(com, "touch") != 0){
            char *nume = strtok(NULL, sep);
            if(CautaNod(d.directories, nume, CmpNumeDir) != NULL)
                printf("Directory %s already exists!\n", nume);
            else{
                int ok = touch(root, nume);
                if(ok == 0)
                    printf("File %s already exists!\n", nume);
            }
        }
        else
        if(strstr(com, "ls") != 0){
            PrintArb(d.directories, PrintDir);
            PrintArb(d.files, PrintFile);
            printf("\n");
        }
        else
        if(strcmp(com, "rm") == 0){
            char *nume = strtok(NULL, sep);
            rm(root, nume);
        }
        else
        if(strstr(com, "rmdir") != 0){
            char *nume = strtok(NULL, sep);
            rmdir(root, nume);
        }
        else
        if(strstr(com, "cd") != 0){
            char *nume = strtok(NULL, sep);
            if(strstr(nume, "..") != 0){
                if(d.parent != NULL)
                    root = d.parent;
            }
            else{
                TArb aux = CautaNod(d.directories, nume, CmpNumeDir);
                if(aux == NULL)
                    printf("Directory not found!\n");
                else
                    root = aux;
            }
        }   
        else
        if(strstr(com, "pwd") != 0){
            pwd(root);
            printf("\n");
        }
        else
        if(strstr(com, "find") != 0){
            char *type = strtok(NULL, sep);
            char *nume = strtok(NULL, sep);
            if(strcmp(type, "-f") == 0){
                int ok = FindF(initroot, nume);
                if(ok == 0)
                    printf("File %s not found!",nume);
            }  
            else if(strcmp(type, "-d") == 0){
                int ok = FindD(initroot, nume);
                if(ok == 0)
                    printf("Directory %s not found!",nume);
            }  
            printf("\n");
        }
                  
    }
    free(line);
    DistrugereNod(&initroot, DistrugereInfoD);
    return 0;
}
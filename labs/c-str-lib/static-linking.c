#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mystrlen(char *str);
char *mystradd(char *origin, char *addition);
int mystrfind(char *origin, char *substr);

int main(int argc, char **argv) {
    if(argc < 4){
        return 0;
    }

    if(!strcmp(argv[1], "-add")){
        char *q = NULL;
        printf("Initial Lenght      : %d\n", mystrlen(argv[2]));
        q = mystradd(argv[2], argv[3]);
        printf("New String          : %s\n", q);
        printf("New length          : %d\n", mystrlen(q));
    }else if(!strcmp(argv[1], "-find")){
        int pos = mystrfind(argv[2], argv[3]);
        printf("[%s] string was found at [%d] position\n", argv[2], pos);
    }

    
    return 0;
}

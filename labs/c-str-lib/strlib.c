#include <stdio.h>
#include <stdlib.h>

int mystrlen(char *str){
    int len=0;
    while(*str!='\0')
    {
        len++;
        *str++;
    }
    return len;
}

char *mystradd(char *origin, char *addition){
    char *q = NULL;
    int len1 = mystrlen(origin);
    int len2 = mystrlen(addition);
    q = (char *)malloc(len1 + len2 + 1);
    for (int i = 0; i < mystrlen(origin); i++)
    {
        q[i] = origin[i]; 
    }
    
    for (int i =  0; i < len2; i++)
    {
        q[i+len1] = addition[i];
    }
    q[len1 + len2 + 1] = '\0';
    
    return q;
}

int mystrfind(char *origin, char *substr){
    int i=0;
    int len = mystrlen(substr);
    int pos = 0;
    int firstletter = 0;
    while(*origin!='\0')
    {
        if(substr[i] == *origin){
            if(i == 0){
                firstletter = pos;
            }
            if (i == len-1){
                return firstletter;
            }
            i++;
        }else{
            i = 0;
        }

        if(*origin == ' '){
            pos++;
        }

        *origin++;
    }

    return -1;
}

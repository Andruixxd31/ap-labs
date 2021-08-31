#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//first arg is operation - string
//all other agruments are number
//print all numbers plus operators and resulto
// Ex:  1 + 2 + 3 = 6
//Check type of all arguments to have exceptions

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    int total = 0;

    if(operator == 1){
        for(int i = 0; i < nValues; i++){
            total += values[i];
            printf("%d ", values[i]);
            if(i == nValues- 1) continue;
            printf("+ ");
        }
    }else if(operator == 2){
        total = values[0];
        for(int i = 0; i < nValues; i++){
            if(i != 0) total -= values[i];
            
            printf(" %d ", values[i]);
            if(i == nValues- 1) continue;
            printf("- ");
        }
    }else{
        total = values[0];
        for(int i = 0; i < nValues; i++){
            if(i != 0) total *= values[i];
            printf(" %d ", values[i]);
            if(i == nValues- 1) continue;
            printf("* ");
        }
    }
    printf(" = %d\n", total);
    return 0;
}

int main(int argc, char **argv) {
    int operator;
    
    if(argc < 4){
        printf("Not enough arguments\n");
    }else{
        if(strcmp(argv[1], "add") == 0) operator = 1;
        else if(strcmp(argv[1], "sub") == 0) operator = 2;
        else if(strcmp(argv[1], "mult") == 0) operator = 3;
        else{
            printf("Not a valid operation\n");
            return -1;
        }

        int arr[argc-2];
        for(int i = 2; i < argc; i++){
            arr[i-2] = atoi(argv[i]);
        }
        return calc(operator, argc-2, arr);
    }
    return -1;
}
 
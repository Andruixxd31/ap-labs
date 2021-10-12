#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quicksort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
void mergeSort(void *lineptr[], int left, int right, int (*comp)(void *, void *));

void readFile(char *name, void *numbers[]);
void writeFile(char *name, void *arr[]);
int numcmp(char *x, char *y);
int stringcmp(char *string1, char *string2);

int main(int argc, char **argv)
{
    int idx = 0;
	void *arr[100];
	if(argc > 4){
        if(!strcmp(argv[1], "-n")){
            idx = 1;
        }
        readFile(argv[1+idx], arr);

		if(!strcmp(argv[2+idx], "-quicksort")){
                quicksort(arr, 0, 100, (int (*)(void *, void *))(idx ? numcmp : stringcmp));
        }else{
            mergeSort(arr, 0, 100, (int (*)(void *, void *))(idx ? numcmp : stringcmp));
        }

        printf("... sorting %s file with %s\n", argv[1+idx],argv[2+idx]);
        writeFile(argv[4+idx], arr);
        printf("... Results file can be found at ./%s\n", argv[4+idx]);
	}

    return 0;
}

void readFile(char *name, void *numbers[]){
    FILE *filePointer;
	filePointer = fopen(name, "r");
	char currentline[100];
    int i = 0;

	while(fgets(currentline, sizeof(currentline), filePointer) != NULL){
        char *str = NULL;
        str = (char *)malloc(strlen(currentline));
        strncpy(str,currentline, strlen(currentline)-1);
        numbers[i] = str;
        i++;
	}
	fclose(filePointer);
}

void writeFile(char *name, void *arr[]){
    FILE *filePointer;
	filePointer = fopen(name, "w");
    for(int i=0;i<100;i++){
            fprintf(filePointer, "%s\n", arr[i]);
    }
    fclose(filePointer);
}

int numcmp(char *x, char *y){
    int xtoi = atoi(x);
    int ytoi = atoi(y);
    if(xtoi==ytoi){
        return 0;
    }else if(xtoi<ytoi){
        return -1;
    }else{
        return 1;
    } 
	return 0;
}


int stringcmp(char *string1, char *string2){
    return strcmp(string1, string2);
}
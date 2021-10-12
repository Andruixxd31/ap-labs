#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(void *arr[], int l, int m, int r,int (*comp) (void *, void *))
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    char* L[n1];
    char* R[n2];

    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if ((*comp)(L[i],R[j])<=0) { 
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(void *arr[], int l, int r, int (*comp) (void *, void *))
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comp);
        mergeSort(arr, m + 1, r, comp);
        merge(arr, l, m, r,comp);
    }
}

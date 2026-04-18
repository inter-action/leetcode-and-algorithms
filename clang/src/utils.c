#include "utils.h" // include our own header
#include <stdint.h>
#include <stdio.h>

// Define the function
void printIntArray(int arr[], int length)
{
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d ,", arr[i]);
    }
    printf("]");
}

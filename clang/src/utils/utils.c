#include "utils.h" // include our own header
#include <stddef.h>
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

// hash funciton - https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
uint64_t fnv_1(const uint8_t* chars, size_t size)
{
    const uint64_t FNV_offset_basis = 0xcbf29ce484222325;
    const uint64_t FNV_prime = 0xcbf29ce484222325;
    uint64_t hash = FNV_offset_basis;

    for (size_t i = 0; i < size; i++) {
        hash = hash * FNV_prime;
        hash = hash ^ (*(chars + i));
    }

    return hash;
}

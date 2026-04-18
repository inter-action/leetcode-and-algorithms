// Define the function
#pragma once

#define print_format(x) _Generic((x), \
    int: "%d ",                       \
    float: "%.2f ",                   \
    double: "%.2lf ",                 \
    char: "%c ")

// typeof type refection
#define SWAP(a, b)          \
    do {                    \
        typeof(a) temp = a; \
        a = b;              \
        b = temp;           \
    } while (0)

#define print_array(arr, len)                         \
    do {                                              \
        for (size_t i = 0; i < (size_t)len; i++) {    \
            printf(print_format((arr)[i]), (arr)[i]); \
        }                                             \
        printf("\n");                                 \
    } while (0)

void printIntArray(int arr[], int length);

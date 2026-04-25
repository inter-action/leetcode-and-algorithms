#ifndef UTILS_UTILS
#define UTILS_UTILS

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define print_format(x) _Generic((x), \
    int: "%d",                        \
    float: "%.2f",                    \
    double: "%.2lf",                  \
    char: "%c")

// typeof type refection
#define SWAP(a, b)          \
    do {                    \
        typeof(a) temp = a; \
        a = b;              \
        b = temp;           \
    } while (0)

#define print_array(arr, len)                         \
    do {                                              \
        printf("[");                                  \
        for (size_t i = 0; i < (size_t)len; i++) {    \
            printf(print_format((arr)[i]), (arr)[i]); \
            printf(", ");                             \
        }                                             \
        printf("]");                                  \
        printf("\n");                                 \
    } while (0)

void printIntArray(int arr[], int length);

// ------ hash map

uint64_t fnv_1(const uint8_t* chars, size_t size);

typedef struct {
    const void* bytes;
    const size_t bytes_size;
} BytesRange;

typedef struct {
    uint64_t (*hash_func)(const void* self);
    bool (*compare)(const void* self, const void* other);
    uint64_t hash;
    const BytesRange key;
    const BytesRange value;
} HashMap_Record;

typedef struct {
    HashMap_Record* mem;
    size_t size;
    size_t capacity;
    size_t element_size;
} HashMap;

size_t HashMap_probe(HashMap* self, size_t start, uint64_t target_hash);
void HashMap_ensure_size(HashMap* self);
void HashMap_set(HashMap* self, HashMap_Record record);
void HashMap_get(HashMap* self, HashMap_Record key, HashMap_Record* result);

#endif // !UTILS

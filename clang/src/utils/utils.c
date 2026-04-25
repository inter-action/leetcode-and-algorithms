#include "utils.h" // include our own header
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

size_t HashMap_probe(HashMap* self, size_t start, uint64_t target_hash)
{
    size_t j = start;
    size_t k = start;
    size_t t = -1;

    while (true) {
        HashMap_Record r = *(self->mem + j);
        if (r.hash == target_hash) { // hasn't being filed yet
            t = j; // found our target
            break;
        }

        j = k++ % self->capacity;

        if (k - start >= self->capacity - 1) { // target out found
            fputs("HashMap: this should never happen!\n", stderr);
            abort();
        }
    }

    return t;
}

void HashMap_ensure_size(HashMap* self)
{
    const uint64_t element_size = sizeof(HashMap_Record);
    if (self->capacity == 0) {
        self->mem = calloc(4, element_size);
        self->size = 0;
        self->capacity = 4;
    } else if (self->size * 0.7 >= self->capacity) {
        uint64_t new_capacity = self->capacity * 2;
        void* doubled = calloc(new_capacity, element_size);

        for (size_t i = 0; i < self->capacity; i++) {
            HashMap_Record record = *(self->mem + i);
            if (record.hash != 0) { // record not empty, rehash
                uint64_t hash = record.hash_func(&record);
                record.hash = hash;
                size_t start = hash % new_capacity;

                size_t t = HashMap_probe(self, start, 0);
                memcpy((void*)(doubled + start), &record, element_size);
            }
        }


        free(self->mem);
        self->capacity = new_capacity;
        self->mem = doubled;
    }
}

void HashMap_set(HashMap* self, HashMap_Record record)
{
    const uint64_t element_size = sizeof(HashMap_Record);
    HashMap_ensure_size(self);
    uint64_t hash = record.hash_func(&record);
    record.hash = hash;
    size_t start = hash % self->capacity;

    size_t i = start;
    size_t k = start;
    while (true) {
        HashMap_Record irecord = *(self->mem + i);

        if (irecord.hash == 0) {
            memcpy((void*)self->mem + i, &record, element_size);
            self->size +=1;
            break;
        }

        if (irecord.hash == hash && irecord.compare(&irecord, &record) == true) {
            memcpy((void*)self->mem + i, &record, element_size);
            self->size +=1;
            break;
        }

        if ((k - start) >= self->capacity) {
            fputs("HashMap: this should never happen, failed to set!\n", stderr);
            abort();
        }

        i = k++ % self->capacity;
    }
}

void HashMap_get(HashMap* self, HashMap_Record key, HashMap_Record* result)
{
    const uint64_t element_size = sizeof(HashMap_Record);
    uint64_t hash = key.hash_func(&key);
    size_t start = hash % self->capacity;
    HashMap_Record found = *(self->mem + start);
    if (found.hash == hash && key.compare(&key, &found) == true) {
        memcpy((void*)result, &found, element_size);
    }
}

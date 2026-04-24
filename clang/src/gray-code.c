// the only hard part of this quiz is the formula: i^(i >> 1)
//
//
// https://leetcode.cn/problems/gray-code/?envType=problem-list-v2&envId=bit-manipulation
//
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

int* grayCode(int n, int* returnSize)
{
    int* result = malloc(sizeof(int) * 1 << n);

    result[0] = 0;
    for (int j = 1; j < 1 << n; j++) {
        result[j] = 0;
        result[j] = j ^ (j >> 1);
    }

    *returnSize = 1 << n;
    return result;
}

// 000, 001, 011, 010, 110, 111, 101, 100

int main(int argc, char* argv[])
{
    int returnSize = 0;
    int* array = grayCode(2, &returnSize);
    printf("size=%d \nArray is:", returnSize);

    print_array(array, returnSize);

    free(array);

    return EXIT_SUCCESS;
}

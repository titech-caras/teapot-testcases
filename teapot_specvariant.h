#pragma once

#include <stdint.h>

#ifdef SPECTRE_VARIANT
#define DIFT_MEM_ADDR(addr) ((uint8_t*)((size_t)addr ^ (1ULL << 45)))
#define DIFT_MEM_TAG(addr) (*(DIFT_MEM_ADDR(addr)))

int *__teapot_specvariant_array1,__teapot_specvariant_array2[1024];
int __teapot_specvariant_array1_size, __teapot_specvariant_array2_size;
volatile int __teapot_specvariant_global_idx;
volatile int __teapot_specvariant_tmp;
void __teapot_specvariant_setup() {
    __teapot_specvariant_array1_size = 5;
    __teapot_specvariant_array2_size = 1024;
    __teapot_specvariant_global_idx = 10;
    __teapot_specvariant_array1 = malloc(sizeof(int) * __teapot_specvariant_array1_size);
    DIFT_MEM_TAG(&__teapot_specvariant_global_idx) = 0x01; // Attacker Label
}

#define TEAPOT_SPECVARIANT_TYPE1 { \
    if (__teapot_specvariant_global_idx < __teapot_specvariant_array1_size) \
        __teapot_specvariant_tmp &= __teapot_specvariant_array2[__teapot_specvariant_array1[__teapot_specvariant_global_idx] * 512]; \
};



#else
#define TEAPOT_SPECVARIANT_TYPE1

#endif



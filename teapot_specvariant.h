#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef SPECTRE_VARIANT
#define DIFT_MEM_ADDR(addr) ((uint8_t*)((size_t)addr ^ (1ULL << 45)))
#define DIFT_MEM_TAG(addr) (*(DIFT_MEM_ADDR(addr)))

#define DECLARE_GLOBAL_VARIABLES(modifier) \
    modifier int *__teapot_specvariant_array1,__teapot_specvariant_array2[1024]; \
    modifier int __teapot_specvariant_array1_size, __teapot_specvariant_array2_size; \
    modifier volatile int __teapot_specvariant_global_idx; \
    modifier volatile int __teapot_specvariant_tmp;

DECLARE_GLOBAL_VARIABLES(extern)

static inline void __teapot_specvariant_setup() {
    __teapot_specvariant_array1_size = 5;
    __teapot_specvariant_array2_size = 1024;
    __teapot_specvariant_global_idx = 10;
    __teapot_specvariant_array1 = malloc(sizeof(int) * __teapot_specvariant_array1_size);
    if (getenv("SPECTRE_VARIANT_TAINTED")) {
        DIFT_MEM_TAG(&__teapot_specvariant_global_idx) = 0x01; // Attacker Label
    }
}

#define TEAPOT_SPECVARIANT_TYPE1 { \
    if (__teapot_specvariant_global_idx < __teapot_specvariant_array1_size) \
        __teapot_specvariant_tmp &= __teapot_specvariant_array2[__teapot_specvariant_array1[__teapot_specvariant_global_idx] * 512]; \
};

#define TEAPOT_SPECVARIANT_TYPE11 { \
    if (__teapot_specvariant_global_idx < __teapot_specvariant_array1_size) \
        __teapot_specvariant_tmp = memcmp(&__teapot_specvariant_tmp, __teapot_specvariant_array2 + __teapot_specvariant_array1[__teapot_specvariant_global_idx] * 512, 1); \
};

#define TEAPOT_SPECVARIANT_TYPE12 { \
    int __teapot_specvariant_y = 1;  \
    if (__teapot_specvariant_global_idx + __teapot_specvariant_y < __teapot_specvariant_array1_size) \
        __teapot_specvariant_tmp  &= __teapot_specvariant_array2[__teapot_specvariant_array1[__teapot_specvariant_global_idx + __teapot_specvariant_y] * 512]; \
};

#define TEAPOT_SPECVARIANT_TYPE14 { \
    if (__teapot_specvariant_global_idx < __teapot_specvariant_array1_size) \
        __teapot_specvariant_tmp &= __teapot_specvariant_array2[__teapot_specvariant_array1[__teapot_specvariant_global_idx ^ 255] * 512]; \
};

#else
#define DECLARE_GLOBAL_VARIABLES(modifier)
#define TEAPOT_SPECVARIANT_TYPE1
#define TEAPOT_SPECVARIANT_TYPE11
#define TEAPOT_SPECVARIANT_TYPE12
#define TEAPOT_SPECVARIANT_TYPE14
static inline void __teapot_specvariant_setup() {}
#endif



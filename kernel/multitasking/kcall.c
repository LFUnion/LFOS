#include "kcall.h"

void* kc_call(uint32_t number, void* param) {
    kc_func func = kc_list[number];
    return func(param);
}

void kc_register(uint32_t number, kc_func func) {
    kc_list[number] = func;
}

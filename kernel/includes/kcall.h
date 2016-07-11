#ifndef KCALL_H
#define KCALL_H

#include "stdint.h"

typedef void* (*kc_func)(void*);

kc_func kc_list[100];

void* kc_call(uint32_t number, void* param);
void  kc_register(uint32_t number, kc_func func);

#endif /* KCALL_H */

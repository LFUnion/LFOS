#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

void register_exception_handlers();

struct registers {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, errcode;
    unsigned int eip, eflags, useresp, ss;
};

#endif /* EXCEPTIONHANDLER_H */
#include "includes/vga.h"

// Display head
void kmain(void) {
    kclear();
    klog("Welcome to LFOS!");
    klog("(C) 2015 by LFUnion");
    klog("");
    klog("Compiled");
    klog(__DATE__);
    klog("at");
    klog(__TIME__);
}

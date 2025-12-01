#include <stdio.h>
#include <string.h>
#include "ealloc.h"

int main() {
    init_alloc();

    char *a = alloc(1024);
    char *b = alloc(512);
    char *c = alloc(256);

    if (a && b && c) {
        strcpy(a, "Hello from A");
        strcpy(b, "Hello from B");
        strcpy(c, "Hello from C");

        printf("A: %s\n", a);
        printf("B: %s\n", b);
        printf("C: %s\n", c);
    }

    dealloc(b);
    char *d = alloc(512);
    if (d) {
        strcpy(d, "Hello from D");
        printf("D: %s\n", d);
    }

    cleanup();
    return 0;
}
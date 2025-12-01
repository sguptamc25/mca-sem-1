#ifndef EALLOC_H
#define EALLOC_H

void init_alloc();
void cleanup();
char *alloc(int size);
void dealloc(char *ptr);

#endif
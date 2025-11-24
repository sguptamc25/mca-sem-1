#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include "ealloc.h"

#define PAGE_SIZE 4096
#define MAX_PAGES 4

typedef struct Chunk {
    size_t size;
    int is_free;
    struct Chunk *next;
} Chunk;

typedef struct Page {
    void *addr;
    Chunk *free_list;
} Page;

static Page pages[MAX_PAGES];
static int page_count = 0;

void init_alloc() {
    page_count = 0;
    for (int i = 0; i < MAX_PAGES; i++) {
        pages[i].addr = NULL;
        pages[i].free_list = NULL;
    }
}

void cleanup() {
    init_alloc(); // Reset state; no need to munmap
}

char *alloc(int size) {
    if (size <= 0 || size > PAGE_SIZE || size % 256 != 0) return NULL;

    for (int i = 0; i < page_count; i++) {
        Chunk *curr = pages[i].free_list;
        while (curr) {
            if (curr->is_free && curr->size >= size) {
                if (curr->size >= size + sizeof(Chunk) + 256) {
                    Chunk *new_chunk = (Chunk *)((char *)curr + sizeof(Chunk) + size);
                    new_chunk->size = curr->size - size - sizeof(Chunk);
                    new_chunk->is_free = 1;
                    new_chunk->next = curr->next;
                    curr->next = new_chunk;
                    curr->size = size;
                }
                curr->is_free = 0;
                return (char *)curr + sizeof(Chunk);
            }
            curr = curr->next;
        }
    }

    if (page_count >= MAX_PAGES) return NULL;

    void *addr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) return NULL;

    Chunk *chunk = (Chunk *)addr;
    chunk->size = size;
    chunk->is_free = 0;
    chunk->next = NULL;

    pages[page_count].addr = addr;
    pages[page_count].free_list = chunk;

    if (size + sizeof(Chunk) < PAGE_SIZE) {
        Chunk *free_chunk = (Chunk *)((char *)addr + sizeof(Chunk) + size);
        free_chunk->size = PAGE_SIZE - size - sizeof(Chunk);
        free_chunk->is_free = 1;
        free_chunk->next = NULL;
        chunk->next = free_chunk;
    }

    page_count++;
    return (char *)chunk + sizeof(Chunk);
}

void dealloc(char *ptr) {
    if (!ptr) return;

    Chunk *chunk = (Chunk *)(ptr - sizeof(Chunk));
    chunk->is_free = 1;

    if (chunk->next && chunk->next->is_free) {
        chunk->size += sizeof(Chunk) + chunk->next->size;
        chunk->next = chunk->next->next;
    }
}
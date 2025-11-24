#include "ealloc.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct block {
    size_t size;        // size of block including header
    int free;           // free or not
    struct block *next; // next block in free list
} block_t;

#define BLOCK_SIZE sizeof(block_t)

static void *memory = NULL;
static size_t total_size = 0;
static block_t *free_list = NULL;

void init_alloc(void) {
    total_size = PAGESIZE * 5;  // 5 pages (20 KB) to fit overhead
    memory = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    free_list = (block_t *)memory;
    free_list->size = total_size;
    free_list->free = 1;
    free_list->next = NULL;
}

void cleanup(void) {
    if (memory != NULL) {
        if (munmap(memory, total_size) != 0) {
            perror("munmap failed");
            exit(1);
        }
        memory = NULL;
        free_list = NULL;
        total_size = 0;
    }
}

static void split_block(block_t *block, size_t size) {
    if (block->size >= size + BLOCK_SIZE + MINALLOC) {
        block_t *new_block = (block_t *)((char *)block + size);
        new_block->size = block->size - size;
        new_block->free = 1;
        new_block->next = block->next;

        block->size = size;
        block->free = 0;
        block->next = new_block;
    } else {
        block->free = 0;
    }
}

char *alloc(int requested_size) {
    if (requested_size <= 0 || free_list == NULL)
        return NULL;

    size_t aligned_size = ((requested_size + MINALLOC - 1) / MINALLOC) * MINALLOC;
    size_t total_alloc_size = aligned_size + BLOCK_SIZE;

    block_t *curr = free_list;

    while (curr != NULL) {
        if (curr->free && curr->size >= total_alloc_size) {
            split_block(curr, total_alloc_size);
            printf("Alloc: requested %d, aligned %zu, block at %p size %zu\n",
                   requested_size, aligned_size, (void *)curr, curr->size);
            return (char *)curr + BLOCK_SIZE;
        }
        curr = curr->next;
    }

    printf("Alloc failed: no sufficient block for %d bytes\n", requested_size);
    return NULL;
}

static void merge_blocks() {
    block_t *curr = free_list;

    while (curr != NULL && curr->next != NULL) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void dealloc(char *ptr) {
    if (ptr == NULL)
        return;

    if (ptr < (char *)memory || ptr >= (char *)memory + total_size)
        return;

    block_t *block = (block_t *)(ptr - BLOCK_SIZE);

    if ((char *)block < (char *)memory || (char *)block >= (char *)memory + total_size)
        return;

    block->free = 1;
    merge_blocks();
}


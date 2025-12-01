#include "alloc.h"

typedef struct block {
    size_t size;          // Size of the block including header
    int free;             // 1 if free, 0 if allocated
    struct block *next;   // Next block in list
} block_t;

#define BLOCK_SIZE sizeof(block_t)

static void *memory = NULL;      // pointer to mmap-ed memory
static size_t total_size = 0;    // total size of mmap'ed memory
static block_t *free_list = NULL;

int init_alloc() {
    total_size = PAGESIZE * 4;  // allocate 4 pages (16 KB)
    memory = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED)
        return 1;

    free_list = (block_t *)memory;
    free_list->size = total_size;
    free_list->free = 1;
    free_list->next = NULL;
    return 0;
}

int cleanup() {
    if (memory == NULL)
        return 0;
    if (munmap(memory, total_size) != 0)
        return 1;
    memory = NULL;
    free_list = NULL;
    total_size = 0;
    return 0;
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
            return (char *)curr + BLOCK_SIZE;
        }
        curr = curr->next;
    }

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


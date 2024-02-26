#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FRAME_SIZE 3
#define PAGE_SIZE 10

int page_table[PAGE_SIZE];
int frames[FRAME_SIZE];
int oldest_frame_index = 0;

void initialize() {
    for (int i = 0; i < PAGE_SIZE; i++) {
        page_table[i] = -1;  // Initialize page table with invalid values
    }
    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;      // Initialize frames with invalid values
    }
}

void print_page_table() {
    printf("Page Table:\n");
    for (int i = 0; i < PAGE_SIZE; i++) {
        printf("%d -> %d\n", i, page_table[i]);
    }
}

void print_frames() {
    printf("Frames:\n");
    for (int i = 0; i < FRAME_SIZE; i++) {
        printf("%d -> %d\n", i, frames[i]);
    }
}

bool is_page_in_memory(int page) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

void replace_page(int page) {
    frames[oldest_frame_index] = page;
    oldest_frame_index = (oldest_frame_index + 1) % FRAME_SIZE;
}

void simulate_fifo(int pages[], int num_pages) {
    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        if (!is_page_in_memory(page)) {
            replace_page(page);
            print_frames();
        }
    }
}

int main() {
    int pages[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Reference string
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    initialize();
    simulate_fifo(pages, num_pages);

    return 0;
}

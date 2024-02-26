#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 3
#define NUM_PAGES 10

int frames[NUM_FRAMES];
int pageList[NUM_PAGES];
int pageFaults = 0;

void initializeFrames() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;  // Initialize frames with -1 (indicating empty frame)
    }
}

bool isInFrames(int page) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == page) {
            return true;  // Page is already in frames
        }
    }
    return false;  // Page is not in frames
}

int getLRUIndex(int page, int start) {
    int index = start;
    int min = start;

    for (int i = 0; i < NUM_FRAMES; i++) {
        int j;
        for (j = start - 1; j >= 0; j--) {
            if (frames[i] == pageList[j]) {
                if (j < min) {
                    min = j;
                    index = i;
                }
                break;
            }
        }
        if (j == -1) {
            return i;  // If a page is not found in pageList, it is least recently used
        }
    }

    return index;
}

void displayFrames() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    printf("Enter the reference string length: ");
    for (int i = 0; i < NUM_PAGES; i++) {
        scanf("%d", &pageList[i]);
    }

    initializeFrames();

    printf("\nReference String: ");
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("%d ", pageList[i]);
    }

    printf("\n\nLRU Page Replacement:\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        if (!isInFrames(pageList[i])) {
            int index = getLRUIndex(pageList[i], i);
            frames[index] = pageList[i];
            pageFaults++;
            printf("Page Fault at index %d: ", i);
            displayFrames();
        } else {
            printf("No Page Fault at index %d: ", i);
            displayFrames();
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

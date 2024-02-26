#include<stdio.h>
#include<stdlib.h>

int main() {
    int ReadyQueue[100], i, n, TotalHeadMov = 0, initial;

    // Input the number of elements in the ReadyQueue
    printf("Enter the number of elements in the ReadyQueue: ");
    scanf("%d", &n);

    // Input the elements of the ReadyQueue
    printf("Enter the elements of the ReadyQueue:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &ReadyQueue[i]);
    }

    // Input the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &initial);

    // Calculate total head movement
    for (i = 0; i < n; i++) {
        // Calculate absolute distance between current element and initial head position
        TotalHeadMov = TotalHeadMov + abs(ReadyQueue[i] - initial);
        // Update initial head position to the current element
        initial = ReadyQueue[i];
    }

    // Output the total head movement
    printf("Total Head Movement = %d\n", TotalHeadMov);

    return 0;
}

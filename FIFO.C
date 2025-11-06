#include <stdio.h>
#include <stdlib.h>

int main() {
    int frames, n;
    printf("FIFO Page Replacement\n");
    printf("Enter number of frames: ");
    if(scanf("%d", &frames)!=1) return 0;
    printf("Enter length of reference string: ");
    if(scanf("%d", &n)!=1) return 0;

    int ref[n];
    printf("Enter reference string (space separated):\n");
    for (int i = 0; i < n; ++i) scanf("%d", &ref[i]);

    int *frame = (int*)malloc(frames * sizeof(int));
    for (int i = 0; i < frames; ++i) frame[i] = -1;

    int pointer = 0; // next frame to replace (FIFO)
    int faults = 0;

    printf("\nStep\tPage\tFrames\n");
    for (int i = 0; i < n; ++i) {
        int page = ref[i];
        int found = 0;
        for (int j = 0; j < frames; ++j)
            if (frame[j] == page) { found = 1; break; }

        if (!found) {
            frame[pointer] = page;
            pointer = (pointer + 1) % frames;
            faults++;
        }

        // print step
        printf("%2d\t%4d\t", i+1, page);
        for (int j = 0; j < frames; ++j) {
            if (frame[j] == -1) printf(" - ");
            else printf("%3d ", frame[j]);
        }
        if (found) printf("   (hit)\n"); else printf("   (fault)\n");
    }

    printf("\nTotal page faults = %d\n", faults);
    free(frame);
    return 0;
}

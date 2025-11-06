#include <stdio.h>
#include <stdlib.h>

int main() {
    int frames, n;
    printf("LRU Page Replacement\n");
    printf("Enter number of frames: ");
    if(scanf("%d", &frames)!=1) return 0;
    printf("Enter length of reference string: ");
    if(scanf("%d", &n)!=1) return 0;

    int ref[n];
    printf("Enter reference string (space separated):\n");
    for (int i = 0; i < n; ++i) scanf("%d", &ref[i]);

    int *frame = (int*)malloc(frames * sizeof(int));
    int *time = (int*)malloc(frames * sizeof(int)); // last used time (higher = more recent)
    for (int i = 0; i < frames; ++i) { frame[i] = -1; time[i] = -1; }

    int faults = 0, current_time = 0;

    printf("\nStep\tPage\tFrames\n");
    for (int i = 0; i < n; ++i) {
        int page = ref[i];
        current_time++;
        int found = -1;
        for (int j = 0; j < frames; ++j)
            if (frame[j] == page) { found = j; break; }

        if (found != -1) {
            time[found] = current_time; // update last used
        } else {
            // find empty slot or LRU
            int replace = -1;
            for (int j = 0; j < frames; ++j) {
                if (frame[j] == -1) { replace = j; break; }
            }
            if (replace == -1) {
                // choose the frame with smallest time (least recently used)
                int min_time = time[0];
                replace = 0;
                for (int j = 1; j < frames; ++j) {
                    if (time[j] < min_time) { min_time = time[j]; replace = j; }
                }
            }
            frame[replace] = page;
            time[replace] = current_time;
            faults++;
        }

        // print step
        printf("%2d\t%4d\t", i+1, page);
        for (int j = 0; j < frames; ++j) {
            if (frame[j] == -1) printf(" - ");
            else printf("%3d ", frame[j]);
        }
        if (found != -1) printf("   (hit)\n"); else printf("   (fault)\n");
    }

    printf("\nTotal page faults = %d\n", faults);
    free(frame);
    free(time);
    return 0;
}

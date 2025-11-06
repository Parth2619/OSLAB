#include <stdio.h>
#include <stdlib.h>

int find_opt_replace(int frame[], int frames, int ref[], int n, int index) {
    // For each frame entry, find next use index; if never used again, return that frame immediately.
    int farthest = -1, replace = -1;
    for (int i = 0; i < frames; ++i) {
        int page = frame[i];
        int j;
        for (j = index + 1; j < n; ++j) {
            if (ref[j] == page) break;
        }
        if (j == n) {
            // page not used again -> best candidate
            return i;
        }
        if (j > farthest) {
            farthest = j;
            replace = i;
        }
    }
    return replace;
}

int main() {
    int frames, n;
    printf("Optimal Page Replacement\n");
    printf("Enter number of frames: ");
    if(scanf("%d", &frames)!=1) return 0;
    printf("Enter length of reference string: ");
    if(scanf("%d", &n)!=1) return 0;

    int ref[n];
    printf("Enter reference string (space separated):\n");
    for (int i = 0; i < n; ++i) scanf("%d", &ref[i]);

    int *frame = (int*)malloc(frames * sizeof(int));
    for (int i = 0; i < frames; ++i) frame[i] = -1;

    int faults = 0;

    printf("\nStep\tPage\tFrames\n");
    for (int i = 0; i < n; ++i) {
        int page = ref[i];
        int found = 0;
        for (int j = 0; j < frames; ++j)
            if (frame[j] == page) { found = 1; break; }

        if (!found) {
            int replace = -1;
            // first check for empty frame
            for (int j = 0; j < frames; ++j) if (frame[j] == -1) { replace = j; break; }
            if (replace == -1) {
                replace = find_opt_replace(frame, frames, ref, n, i);
            }
            frame[replace] = page;
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

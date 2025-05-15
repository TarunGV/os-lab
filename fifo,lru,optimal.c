#include <stdio.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

void fifo(int pages[], int n_pages, int n_frames) {
    int frames[MAX_FRAMES], page_faults = 0, index = 0, found;

    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
    }

    printf("\nFIFO Page Replacement:\n");
    printf("Page\tFrames\n");

    for (int i = 0; i < n_pages; i++) {
        found = 0;

        for (int j = 0; j < n_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % n_frames;
            page_faults++;

            printf("%d\t", pages[i]);
            for (int j = 0; j < n_frames; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        } else {
            printf("%d\tNo Page Fault\n", pages[i]);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int predict(int pages[], int frames[], int n_pages, int index, int n_frames) {
    int farthest = index, result = -1;
    for (int i = 0; i < n_frames; i++) {
        int found = 0;
        for (int j = index + 1; j < n_pages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                found = 1;
                break;
            }
        }
        if (!found)
            return i;
    }

    return (result == -1) ? 0 : result;
}

void optimal(int pages[], int n_pages, int n_frames) {
    int frames[MAX_FRAMES], page_faults = 0;

    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement:\n");
    printf("Page\tFrames\n");

    for (int i = 0; i < n_pages; i++) {
        int found = 0;

        for (int j = 0; j < n_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = predict(pages, frames, n_pages, i, n_frames);
            frames[pos] = pages[i];
            page_faults++;

            printf("%d\t", pages[i]);
            for (int j = 0; j < n_frames; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        } else {
            printf("%d\tNo Page Fault\n", pages[i]);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int pages[], int n_pages, int n_frames) {
    int frames[MAX_FRAMES], time[MAX_FRAMES], page_faults = 0, counter = 0;

    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");
    printf("Page\tFrames\n");

    for (int i = 0; i < n_pages; i++) {
        int found = 0;

        for (int j = 0; j < n_frames; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            int empty_found = 0;
            for (int j = 0; j < n_frames; j++) {
                if (frames[j] == -1) {
                    counter++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    page_faults++;
                    empty_found = 1;
                    break;
                }
            }

            if (!empty_found) {
                int pos = findLRU(time, n_frames);
                counter++;
                frames[pos] = pages[i];
                time[pos] = counter;
                page_faults++;
            }

            printf("%d\t", pages[i]);
            for (int j = 0; j < n_frames; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        } else {
            printf("%d\tNo Page Fault\n", pages[i]);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES], n_pages, n_frames;

    printf("Enter the number of pages: ");
    scanf("%d", &n_pages);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &n_frames);

    fifo(pages, n_pages, n_frames);
    optimal(pages, n_pages, n_frames);
    lru(pages, n_pages, n_frames);

    return 0;
}

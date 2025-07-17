#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define THREAD_COUNT 8

int original[] = {3, 5, 2, 9, 1, 4, 7, 8, 10, 6, 7};
int found_sorted = 0;
pthread_mutex_t found_mutex = PTHREAD_MUTEX_INITIALIZER;

int is_sorted(int arr[]) {
    for (int i = 1; i < ARRAY_SIZE; i++) {
        if (arr[i - 1] > arr[i]) return 0;
    }
    return 1;
}

void shuffle(int arr[]) {
    for (int i = ARRAY_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void* bogosort_worker(void* arg) {
    int tries = 0;
    int* copy = malloc(sizeof(int) * ARRAY_SIZE);
    if (!copy) pthread_exit(NULL);

    while (1) {
        pthread_mutex_lock(&found_mutex);
        if (found_sorted) {
            pthread_mutex_unlock(&found_mutex);
            break;
        }
        pthread_mutex_unlock(&found_mutex);

        for (int i = 0; i < ARRAY_SIZE; i++) copy[i] = original[i];
        shuffle(copy);
        tries++;

        if (is_sorted(copy)) {
            pthread_mutex_lock(&found_mutex);
            if (!found_sorted) {
                found_sorted = 1;
                printf("\n🐧 Thread %ld sorted it in %d tries!\n", (long)arg, tries);
                printf("Sorted list: ");
                for (int i = 0; i < ARRAY_SIZE; i++) {
                    printf("%d ", copy[i]);
                }
                printf("\n");
            }
            pthread_mutex_unlock(&found_mutex);
            break;
        }
    }

    free(copy);
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    pthread_t threads[THREAD_COUNT];

    clock_t start_time = clock();  // ⏱️ Start timing

    printf("Starting %d threads to bogo-sort...\n", THREAD_COUNT);

    for (long i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, bogosort_worker, (void*)i);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();  // ⏱️ End timing
    double time_used = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("The threads have finished their work.\n");
    printf("Time taken: %.2f seconds\n", time_used);  // Print the time used

    return 0;
}
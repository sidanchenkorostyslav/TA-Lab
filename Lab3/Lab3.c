#include <stdio.h>

#define N 9

typedef struct {
    long comparisons;
    long swaps;
    long assignments;
    long sink_calls;
} Counters;

void swap(int a[], int i, int j, Counters *c ) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;

    c->swaps++;
    c->assignments += 3;
}

void sink(int a[], int i, int n, Counters *c) {
    c->sink_calls++;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < n) {
            c->comparisons++;

            if (a[left] > a[largest]) {
                largest = left;
            }
        }

        if (right < n) {
            c->comparisons++;

            if (a[right] > a[largest]) {
                largest = right;
            }
        }

        if (largest == i) {
            break;
        }

        swap(a, i, largest, c);
        i = largest;
    }
}

void heapsort(int a[], int n, Counters *c) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        sink(a, i, n, c);
    }

    for (int i = n - 1; i >= 1; --i) {
        swap(a, 0, i, c);
        sink(a, 0, i, c);
    }
}

int main(void) {
    int a[N] = {
        7, 89, 4, 68, 70,
        49, 10, 62, 51
    };

    Counters c = {0, 0, 0, 0};

    heapsort(a, N, &c);

    printf("Відсортований масив: ");

    for (int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }

    printf("\nПорівняння: %ld\n", c.comparisons);
    printf("Обміни: %ld\n", c.swaps);
    printf("Присвоєння: %ld\n", c.assignments);
    printf("Виклики sink: %ld\n", c.sink_calls);

    return 0;
}

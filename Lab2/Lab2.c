#include <stdio.h>

#define N 9

typedef struct {
    long comparisons;
    long assignments;
    long recursive_calls;
} Counters;

void print_array(const int a[], int n) {
    printf("[");
    for (int i = 0; i < n; ++i) {
        printf("%d%s", a[i], (i == n - 1) ? "" : ", ");
    }
    printf("]");
}

void merge(int a[], int temp[], int left, int mid, int right, Counters *c) {
    int i = left, j = mid, k = left;

    while (i < mid && j < right) {
        c->comparisons++;
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
        c->assignments++;
    }

    while (i < mid) {
        temp[k++] = a[i++];
        c->assignments++;
    }
    while (j < right) {
        temp[k++] = a[j++];
        c->assignments++;
    }

    for (i = left; i < right; ++i) {
        a[i] = temp[i];
        c->assignments++;
    }
}

void merge_sort_iterative(int a[], int n, Counters *c) {
    int temp[N];

    for (int width = 1; width < n; width *= 2) {
        for (int left = 0; left < n; left += 2 * width) {
            int mid = (left + width < n) ? left + width : n;
            int right = (left + 2 * width < n) ? left + 2 * width : n;

            if (mid < right) {
                merge(a, temp, left, mid, right, c);
            }
        }
    }
}

void merge_sort_recursive(int a[], int temp[], int left, int right,
                          Counters *c) {
    c->recursive_calls++;

    if (right - left <= 1) {
        return;
    }

    int mid = (left + right) / 2;
    merge_sort_recursive(a, temp, left, mid, c);
    merge_sort_recursive(a, temp, mid, right, c);
    merge(a, temp, left, mid, right, c);
}

void quicksort(int a[], int left, int right, Counters *c) {
    c->recursive_calls++;

    if (left >= right) {
        return;
    }

    int pivot = a[left];
    int i = left - 1;
    int j = right + 1;

    while (1) {
        do {
            ++i;
            c->comparisons++;
        } while (a[i] < pivot);

        do {
            --j;
            c->comparisons++;
        } while (a[j] > pivot);

        c->comparisons++; /* перевірка i >= j */
        if (i >= j) {
            quicksort(a, left, j, c);
            quicksort(a, j + 1, right, c);
            return;
        }

        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        c->assignments += 3;
    }
}

int main(void) {
    const int input[N] = {7, 89, 4, 68, 70, 49, 10, 62, 51};
    int a[N], b[N], c_array[N], temp[N];
    Counters ci = {0, 0, 0};
    Counters cr = {0, 0, 0};
    Counters cq = {0, 0, 0};

    for (int i = 0; i < N; ++i) {
        a[i] = input[i];
        b[i] = input[i];
        c_array[i] = input[i];
    }

    merge_sort_iterative(a, N, &ci);
    merge_sort_recursive(b, temp, 0, N, &cr);
    quicksort(c_array, 0, N - 1, &cq);

    printf("Початковий масив: ");
    print_array(input, N);
    printf("\n\nІтеративне сортування злиттям: ");
    print_array(a, N);
    printf("\nПорівнянь: %ld; присвоювань: %ld\n", ci.comparisons,
           ci.assignments);

    printf("\nРекурсивне сортування злиттям: ");
    print_array(b, N);
    printf("\nПорівнянь: %ld; присвоювань: %ld; рекурсивних викликів: %ld\n",
           cr.comparisons, cr.assignments, cr.recursive_calls);

    printf("\nШвидке сортування Хоара: ");
    print_array(c_array, N);
    printf("\nПорівнянь: %ld; присвоювань: %ld; рекурсивних викликів: %ld\n",
           cq.comparisons, cq.assignments, cq.recursive_calls);

    return 0;
}

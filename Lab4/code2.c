#include <stdio.h>

#define M 13
#define N 7

const char *words[N] = {
    "БІЛЬШЕ", "ДІЛА", "МЕНШЕ", "СЛІВ",
    "ОТАК", "ДОБУДЕШ", "ХЛІБ"
};

int key[N] = {97, 35, 78, 53, 58, 93, 56};
const char *table[M];

int hash_function(int value) {
    return value % M;
}

void build_table(void) {
    for (int i = 0; i < M; ++i)
        table[i] = NULL;

    for (int word = 0; word < N; ++word) {
        int index = hash_function(key[word]);

        while (table[index] != NULL)
            index = (index + 1) % M;

        table[index] = words[word];
    }
}

void print_table(void) {
    for (int i = 0; i < M; ++i) {
        if (table[i] == NULL)
            printf("%02d: (порожньо)\n", i);
        else
            printf("%02d: %s\n", i, table[i]);
    }
}

int main(void) {
    build_table();
    print_table();
    return 0;
}

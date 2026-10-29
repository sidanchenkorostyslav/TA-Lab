#include <stdio.h>
#define M 13
#define N 7

typedef struct Node {
    int word_id;
    struct Node *next;
} Node;

Node nodes[N];
Node *table[M];
const char *words[N] = {"БІЛЬШЕ", "ДІЛА", "МЕНШЕ", "СЛІВ",
                        "ОТАК", "ДОБУДЕШ", "ХЛІБ"};
int keys[N] = {97, 35, 78, 53, 58, 93, 56};

int division_hash(int key) { return key % M; }

void build_open_table(void) {
    for (int i = 0; i < M; ++i) table[i] = NULL;
    for (int i = 0; i < N; ++i) {
        int index = division_hash(keys[i]);
        nodes[i].word_id = i;
        nodes[i].next = NULL;
        if (table[index] == NULL) table[index] = &nodes[i];
        else {
            Node *p = table[index];
            while (p->next != NULL) p = p->next;
            p->next = &nodes[i];
        }
    }
}

void display_open_table(void) {
    for (int i = 0; i < M; ++i) {
        printf("%02d: ", i);
        for (Node *p = table[i]; p != NULL; p = p->next)
            printf("%s ", words[p->word_id]);
        printf("\n");
    }
}

int main(void) {
    build_open_table();
    display_open_table();
    return 0;
}

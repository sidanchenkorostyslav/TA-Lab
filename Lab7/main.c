#include <stdio.h>
#include <stdlib.h>

#define N 9
int data[N] = {86, 36, 14, 50, 64, 21, 2, 83, 82};

typedef struct Node {
    int key;
    char color;
    struct Node *left, *right;
} Node;

Node *new_node(int key, char color) {
    Node *p = malloc(sizeof(Node));
    p->key = key; p->color = color;
    p->left = p->right = NULL;
    return p;
}

/*Бінарне дерево пошуку*/
Node *bst_insert(Node *t, int key) {
    if (!t) return new_node(key, 'B');
    if (key < t->key) t->left = bst_insert(t->left, key);
    else if (key > t->key) t->right = bst_insert(t->right, key);
    return t;
}

Node *minimum(Node *t) {
    while (t && t->left) t = t->left;
    return t;
}

Node *bst_delete(Node *t, int key) {
    if (!t) return NULL;
    if (key < t->key) t->left = bst_delete(t->left, key);
    else if (key > t->key) t->right = bst_delete(t->right, key);
    else {
        if (!t->left) { Node *r = t->right; free(t); return r; }
        if (!t->right) { Node *l = t->left; free(t); return l; }
        Node *s = minimum(t->right);
        t->key = s->key;
        t->right = bst_delete(t->right, s->key);
    }
    return t;
}

void inorder(Node *t)  { if (t) { inorder(t->left); printf("%d ", t->key); inorder(t->right); } }
void preorder(Node *t) { if (t) { printf("%d ", t->key); preorder(t->left); preorder(t->right); } }
void postorder(Node *t){ if (t) { postorder(t->left); postorder(t->right); printf("%d ", t->key); } }

/*Червоно-чорне дерево*/
Node *rotate_left(Node *x) {
    Node *y = x->right; x->right = y->left; y->left = x; return y;
}
Node *rotate_right(Node *x) {
    Node *y = x->left; x->left = y->right; y->right = x; return y;
}
int red(Node *t) { return t && t->color == 'R'; }

Node *rb_insert(Node *t, int key) {
    if (!t) return new_node(key, 'R');
    if (key < t->key) t->left = rb_insert(t->left, key);
    else if (key > t->key) t->right = rb_insert(t->right, key);

    if (red(t->right) && !red(t->left)) t = rotate_left(t);
    if (red(t->left) && red(t->left->left)) t = rotate_right(t);
    if (red(t->left) && red(t->right)) {
        t->color = 'R'; t->left->color = t->right->color = 'B';
    }
    return t;
}

void make_black(Node *t) { if (t) t->color = 'B'; }

void collect(Node *t, int key, int a[], int *n) {
    if (!t) return;
    collect(t->left, key, a, n);
    if (t->key != key) a[(*n)++] = t->key;
    collect(t->right, key, a, n);
}
void free_tree(Node *t) {
    if (!t) return;
    free_tree(t->left); free_tree(t->right); free(t);
}
void rb_delete_simple(Node **root, int key) {
    int a[N], n = 0;
    collect(*root, key, a, &n);
    free_tree(*root); *root = NULL;
    for (int i = 0; i < n; ++i) *root = rb_insert(*root, a[i]);
    make_black(*root);
}

void inorder_rb(Node *t) {
    if (t) { inorder_rb(t->left); printf("%d%c ", t->key, t->color); inorder_rb(t->right); }
}

int main(void) {
    Node *bst = NULL, *rb = NULL;
    for (int i = 0; i < N; ++i) {
        bst = bst_insert(bst, data[i]);
        rb = rb_insert(rb, data[i]);
    }
    make_black(rb);

    printf("BST inorder:   "); inorder(bst); putchar('\n');
    printf("BST preorder:  "); preorder(bst); putchar('\n');
    printf("BST postorder: "); postorder(bst); putchar('\n');
    printf("RB inorder:    "); inorder_rb(rb); putchar('\n');

    printf("\nBST deletions: 83, 36, 86\n");
    for (int i = 0; i < 3; ++i) {
        bst = bst_delete(bst, (int[]){83, 36, 86}[i]);
        inorder(bst); putchar('\n');
    }

    printf("\nRB deletions: 36, 14, 50\n");
    for (int i = 0; i < 3; ++i) {
        rb_delete_simple(&rb, (int[]){36, 14, 50}[i]);
        inorder_rb(rb); putchar('\n');
    }
    return 0;
}

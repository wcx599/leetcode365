// set data structure implemented as a ternary search tree

#include <stdlib.h>
#include <assert.h>

#include "set.h"

#define LT (0)
#define EQ (1)
#define GT (2)

#define NUM_KIDS (3)

struct tst {
    char split;
    struct tst *kids[NUM_KIDS];
};

struct set {
    struct tst *root;
};

Set *setCreate(void)
{
    Set *s = malloc(sizeof(Set));
    s->root = 0;

    return s;
}

static void
tstDestroy(struct tst *root)
{
    if(root) {
        for(int i = LT; i <= GT; i++) {
            tstDestroy(root->kids[i]);
        }
        free(root);
    }
}

void
setDestroy(Set *s)
{
    tstDestroy(s->root);
    free(s);
}

static void
tstInsert(struct tst **root, const char *key)
{
    if(*root == 0) {
        *root = malloc(sizeof(struct tst));
        (*root)->split = key[0];
        for(int i = LT; i <= GT; i++) {
            (*root)->kids[i] = 0;
        }
    }

    if(key[0] < (*root)->split) {
        tstInsert(&(*root)->kids[LT], key);
    } else if(key[0] > (*root)->split) {
        tstInsert(&(*root)->kids[GT], key);
    } else if(key[0] != '\0') {
        tstInsert(&(*root)->kids[EQ], key+1);
    }
}

void
setInsert(Set *s, const char *key)
{
    tstInsert(&s->root, key);
}

static int
tstContains(const struct tst *root, const char *key)
{
    if(root == 0) {
        // nope
        return 0;
    } else if(key[0] < root->split) {
        return tstContains(root->kids[LT], key);
    } else if(key[0] > root->split) {
        return tstContains(root->kids[GT], key);
    } else if(key[0] == '\0') {
        return 1;
    } else {
        return tstContains(root->kids[EQ], key+1);
    }
}

int setContains(const Set *s, const char *key)
{
    return tstContains(s->root, key);
}

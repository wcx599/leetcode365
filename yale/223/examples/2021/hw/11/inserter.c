#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "inserter.h"

#define NUM_KIDS (2)
#define LEFT (0)
#define RIGHT (1)

// We will implement an Inserter using a treap.
//
// The keys will be the strings in the linked list.
// Each tree node will point to a struct element
// with the key.
struct node {
    struct element *element;
    int priority;        // for heap
    struct node *kids[NUM_KIDS];
};

// The actual inserter struct contains
// a pointer to the root and a pointer
// to the list head pointer.
struct inserter {
    struct node *root;
    struct element **head;
};

// The rest of this mostly follows the treap
// implementation from the 2021-04-19 lecture.
Inserter
inserterCreate(struct element **head)
{
    // list must be empty
    assert(*head == 0);

    Inserter ins = malloc(sizeof(struct inserter));
    assert(ins);

    ins->root = 0;
    ins->head = head;

    return ins;
}

// Free the node in the tree
static void
treeDestroy(struct node *root)
{
    if(root) {
        for(int i = LEFT; i <= RIGHT; i++) {
            treeDestroy(root->kids[i]);
        }
        free(root);
    }
}

void
inserterDestroy(Inserter ins)
{
    treeDestroy(ins->root);
    free(ins);
}

// Find predecessor element to given string.
// Returns 0 if none exists.
static struct element *
treeFindPredecessor(struct node *root, const char *s)
{
    if(root == 0) {
        return 0;
    } else if(strcmp(root->element->string, s) >= 0) {
        // predecessor is in left subtree
        return treeFindPredecessor(root->kids[LEFT], s);
    } else {
        // predecessor is either root->element
        // or found in right subtree
        struct element *pred =
            treeFindPredecessor(root->kids[RIGHT], s);
        if(pred) {
            return pred;
        } else {
            return root->element;
        }
    }
}

// Rotate child on side up to root
//
//    x        y
//   A y      x C
//     BC    AB
static void
treeRotate(struct node **tree, int side)
{
    struct node *x = *tree;
    struct node *y = (*tree)->kids[side];
    struct node *b = y->kids[!side];

    // fix up all the pointers
    *tree = y;
    y->kids[!side] = x;
    x->kids[side] = b;
}

// Returns new struct element * if not already in tree,
// 0 otherwise.
static struct element *
treeInsert(struct node **tree, const char *s)
{
    struct element *e;

    if(*tree == 0) {
        // tree is empty
        e = malloc(sizeof(struct element));
        assert(e);
        e->next = 0;
        e->string = strdup(s);

        struct node *n = malloc(sizeof(struct node));
        assert(n);
        n->element = e;
        n->priority = rand();
        n->kids[LEFT] = n->kids[RIGHT] = 0;

        *tree = n;
        return e;
    } else {
        int cmp = strcmp((*tree)->element->string, s);
        if(cmp == 0) {
            return 0;
        } else {
            int side = cmp < 0;
            e = treeInsert(&(*tree)->kids[side], s);
            
            if((*tree)->priority < (*tree)->kids[side]->priority) {
                treeRotate(tree, side);
            }

            return e;
        }
    }
}

void
inserterAdd(Inserter ins, const char *s)
{
    struct element *e = treeInsert(&ins->root, s);

    if(e) {
        struct element *pred = treeFindPredecessor(ins->root, s);
        if(pred) {
            e->next = pred->next;
            pred->next = e;
        } else {
            e->next = *(ins->head);
            *(ins->head) = e;
        }
    }
}

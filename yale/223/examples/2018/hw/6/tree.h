#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>

// Ordered tree data structure.
// A tree consists of a root node with
// zero or more subtrees.
// A tree has a size equal to 1 plus
// the total sizes of the subtrees.
typedef struct tree Tree;

// Print a tree to file.
// A tree is represented as
// '[' subtrees ']'
// where subtrees are expanded recursively.
// Example: [[][[][]]] is a tree
// with two subtrees, the first of which is empty,
// the second of which has two empty subtrees.
void treeWrite(const Tree *t, FILE *);

// Read a tree from file.
// A tree is repr
Tree *treeRead(FILE *);

// free a tree
void treeDestroy(Tree *t);

// Sort a tree by decreasing size.
// This means that each node's children
// are sorted in order of decreasing size.
// Ties are broken arbitrarily.
void treeSort(Tree *t);

#endif

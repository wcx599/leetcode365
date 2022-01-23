#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "wordArray.h"

struct wordArray {
    int n;              // key length
    int *contents;      // data in row-major order
};

// create an array indexed by strings of length n
WordArray 
wordArrayCreate(unsigned int n)
{
    // compute number of elements NUM_KEY_LETTERS**n
    size_t size = 1;

    for(unsigned int i = 0; i < n; i++) {
        size *= NUM_KEY_LETTERS;
    }

    WordArray w = malloc(sizeof(struct wordArray));

    assert(w);

    w->n = n;
    w->contents = calloc(size, sizeof(int));

    assert(w->contents);

    return w;
}

// free all space used by array
void
wordArrayDestroy(WordArray w)
{
    free(w->contents);
    free(w);
}

// return key length for w
int
wordArrayKeyLength(const WordArray w)
{
    return w->n;
}

// Returns a pointer to location in word array
// indexed by string key.
//
// If key is the wrong length or contains
// characters that are not lowercase letters,
// returns 0.
int *
wordArrayRef(WordArray w, const char *key)
{
    size_t index = 0;

    if(strlen(key) != wordArrayKeyLength(w)) {
        // wrong length
        return 0;
    }

    for(int i = 0; i < w->n; i++) {
        if(key[i] < MIN_KEY_LETTER || key[i] > MAX_KEY_LETTER) {
            // bounds check failed!
            return 0;
        } else {
            // shift previous index and add new letter
            index = index * NUM_KEY_LETTERS + (key[i] - MIN_KEY_LETTER);
        }
    }

    return &w->contents[index];
}

// returns malloc'd minimum key for w
// as a null-terminated string
char *
wordArrayMinKey(const WordArray w)
{
    int n = wordArrayKeyLength(w);

    // +1 for null
    char *s = malloc(n+1);
    assert(s);

    for(int i = 0; i < n; i++) {
        s[i] = MIN_KEY_LETTER;
    }

    s[n] = '\0';

    return s;
}

// Increments a null-terminated string in place, returning 1 on overflow
// and 0 otherwise
// 
// Examples:
//
// incKey("aaa") -> "aab"
// incKey("abc") -> "abd"
// incKey("abz") -> "aca"
// incKey("zzz") -> "aaa", returns 1
int
wordArrayIncKey(char *s)
{
    size_t n = strlen(s);

    if(n == 0) {
        // 0 length strings always overflow
        return 1;
    }

    // if we got here, we know there is at
    // least one character
    size_t i = n-1;
    for(;;) {
        // increment position i
        if(s[i] == MAX_KEY_LETTER) {
            s[i] = MIN_KEY_LETTER;
        } else {
            s[i]++;

            // done, no overflow
            return 0;
        }

        // need to move on to next position
        if(i == 0) {
            // there is no next position
            return 1;
        } else {
            i--;
        }
    }
}

// print the contents of a wordArray
void
wordArrayPrint(WordArray w)
{
    char *key = wordArrayMinKey(w); 

    do {
        printf("%s %d\n", key, *wordArrayRef(w, key));
    } while(wordArrayIncKey(key) == 0);

    free(key);
}

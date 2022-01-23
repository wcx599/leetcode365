#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "deck.h"

// decks are queues
// Invariant:
//     d->head point to first element or is 0 if deck is empty.
//     d->tail points to last element if deck is not empty.
struct elt {
    struct elt *next;
    Card card;
};

struct deck {
    struct elt *head; 
    struct elt *tail;
};

// make an empty deck
static Deck *
deckCreateEmpty(void)
{
    Deck *d;

    d = malloc(sizeof(Deck));
    assert(d);

    d->head = d->tail = 0;

    return d;
}
 
void
deckPutCard(Deck *d, Card c)
{
    struct elt *e;

    e = malloc(sizeof(struct elt));
    assert(e);

    e->next = 0;
    e->card = c;

    if(d->head) {
        d->tail->next = e;
    } else {
        d->head = e;
    }

    // new tail is always e
    d->tail = e;
}

Card
deckGetCard(Deck *d)
{
    struct elt *head;
    Card c;

    head = d->head;

    /* blame the called if the deck is empty */
    assert(head);

    /* save card and unlink */
    c = head->card;
    d->head = head->next;

    free(head);

    return c;
}

Deck *
deckCreate(void)
{
    Deck *d;
    Card c;

    d = deckCreateEmpty();

    for(int s = 0; SUITS[s]; s++) {
        c.suit = SUITS[s];
        for(int r = 0; RANKS[r]; r++) {
            c.rank = RANKS[r];
            deckPutCard(d, c);
        }
    }

    return d;
}

int
deckNotEmpty(const Deck *d)
{
    return d->head != 0;
}

void
deckDestroy(Deck *d)
{
    while(deckNotEmpty(d)) {
        deckGetCard(d);
    }

    free(d);
}

void
deckSplit(Deck *d, int n, Deck **d1, Deck **d2)
{
    // *d1 starts as a new empty deck
    *d1 = deckCreateEmpty();

    // *d2 is just going to be d
    *d2 = d;

    for(int i = 0; i < n && deckNotEmpty(d); i++) {
        deckPutCard(*d1, deckGetCard(d));
    }
}

// add d1 onto end of d
// destroys d1
// this is an O(1) operation
static void
deckPutDeck(Deck *d, Deck *d1)
{
    if(deckNotEmpty(d1)) {
        if(d->head) {
            // paste onto tail
            d->tail->next = d1->head;
        } else {
            // copy into head
            d->head = d1->head;
        }
        // new tail is d1->tail in either case
        d->tail = d1->tail;
    }

    free(d1);
}

Deck *
deckShuffle(Deck *d1, Deck *d2)
{
    Deck *d = deckCreateEmpty();

    assert(d1 != d2);

    while(deckNotEmpty(d1) && deckNotEmpty(d2)) {
        deckPutCard(d, deckGetCard(d1));
        deckPutCard(d, deckGetCard(d2));
    }

    // paste nonempty deck onto end of d1
    deckPutDeck(d, d1);
    deckPutDeck(d, d2);

    return d;
}

void
deckPrint(const Deck *d, FILE *f)
{
    for(struct elt *e = d->head; e; e = e->next) {
        putc(e->card.rank, f);
        putc(e->card.suit, f);
        if(e->next) {
            putc(' ', f);
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "orderBook.h"

// implementation will be two heaps,
// one for buy orders, one for sell orders.


struct maxHeap {
    size_t size;   // size of data
    size_t n;      // number of elements
    int *data;
};

#define MAXHEAP_INITIAL_SIZE (32)
#define MAXHEAP_MULTIPLIER (2)

static struct maxHeap *
maxHeapCreate(void)
{
    struct maxHeap *m = malloc(sizeof(struct maxHeap));
    assert(m);

    m->size = MAXHEAP_INITIAL_SIZE;
    m->n = 0;
    m->data = calloc(m->size, sizeof(int));
    assert(m->data);

    return m;
}

static void
maxHeapDestroy(struct maxHeap *m)
{
    free(m->data);
    free(m);
}

static size_t
child(size_t parent, int side)
{
    return 2*parent + 1 + side;
}

static size_t
parent(size_t child)
{
    return (child - 1) / 2;
}

void
swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

static int
maxHeapIsEmpty(struct maxHeap *m)
{
    return m->n == 0;
}

static int
maxHeapMin(struct maxHeap *m)
{
    assert(!maxHeapIsEmpty(m));

    return m->data[0];
}

static void
maxHeapInsert(struct maxHeap *m, int value)
{
    // expand if needed
    if(m->n >= m->size) {
        m->size *= MAXHEAP_MULTIPLIER;
        m->data = realloc(m->data, m->size * sizeof(int));
        assert(m->data);
    }

    size_t floater = m->n++;
    m->data[floater] = value;

    // are we bigger than parent?
    while(floater != 0 && m->data[floater] > m->data[parent(floater)]) {
        swap(&m->data[floater], &m->data[parent(floater)]);
        floater = parent(floater);
    }
}

static void 
maxHeapDeleteMin(struct maxHeap *m)
{
    if(m->n > 0) {
        swap(&m->data[0], &m->data[--(m->n)]);

        size_t floater = 0;

        for(;;) {
            // find he bigger child
            size_t bigger = child(floater, 0);
            if(bigger+1 < m->n && m->data[bigger+1] > m->data[bigger]) {
                bigger = bigger+1;
            }

            // is it bigger than floater?
            if(bigger < m->n && m->data[bigger] > m->data[floater]) {
                // swap and continue
                swap(&m->data[floater], &m->data[bigger]);
                floater = bigger;
            }  else {
                // no, we are done
                return;
            }
        }
    }
}

#define SELL (0)
#define BUY (1)
#define NUM_HEAPS (2)

struct orderBook {
    // We want to find smallest sell order (negative)
    // and largest buy order (positive).
    //
    // In both cases this is a numerical max.
    //
    // So we'll use two max heaps, 
    // put negative orders in orders[0],
    // and put positive orders in orders[1].
    struct maxHeap *orders[NUM_HEAPS];
};

OrderBook
orderBookCreate(void)
{
    OrderBook b = malloc(sizeof(struct orderBook));
    assert(b);

    for(int i = 0; i < NUM_HEAPS; i++) {
        b->orders[i] = maxHeapCreate();
    }

    return b;
}

void
orderBookDestroy(OrderBook b)
{
    for(int i = 0; i < NUM_HEAPS; i++) {
        maxHeapDestroy(b->orders[i]);
    }

    free(b);
}

int
orderBookInsert(OrderBook b, int price)
{
    if(price == 0) {
        // no order
        return 0;
    }

    int kind = price > 0;  // BUY/SELL
    int match;

    // Look for best compatible order of opposite kind
    if(!maxHeapIsEmpty(b->orders[!kind]) && (match = maxHeapMin(b->orders[!kind])) + price > 0) {
        // got a match
        maxHeapDeleteMin(b->orders[!kind]);
        return match;
    } else {
        // no match
        maxHeapInsert(b->orders[kind], price);
        return 0;
    }
}

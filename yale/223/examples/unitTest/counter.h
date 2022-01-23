/*
 * Abstract counter type.
 *
 * You can increment it, decrement it, and test for zero.
 *
 * Increment and decrement operations return 1 if successful,
 * 0 if the operation would cause underflow or overflow.
 */

typedef struct counter Counter;

/* make a new counter starting at 0 */
Counter *counterCreate(void);

/* destroy a counter */
void counterDestroy(Counter *);

/* return 1 if counter is 0, 0 otherwise */
int counterIsZero(const Counter *);

/* increment a counter, returns 1 if successful, 0 if increment would cause overflow */
int counterIncrement(Counter *);

/* decrement a counter, returns 1 if successful, 0 if decrement would cause underflow */
int counterDecrement(Counter *);

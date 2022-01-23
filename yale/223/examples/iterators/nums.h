/*
 * Abstract data type representing the set of numbers from 0 to
 * bound-1 inclusive, where bound is passed in as an argument at creation.
 */
typedef struct nums *Nums;

/* Create a Nums object with given bound. */
Nums nums_create(int bound);

/* Destructor */
void nums_destroy(Nums);

/* Returns 1 if nums contains element, 0 otherwise */
int nums_contains(Nums nums, int element);
/*
 * Returns a freshly-malloc'd array containing all elements of n,
 * followed by a sentinel value of -1.
 */
int *nums_contents(Nums n);

/* Three-part iterator */
int nums_first(Nums n);           /* returns smallest element in n */
int nums_done(Nums n, int val);   /* returns 1 if val is past end */
int nums_next(Nums n, int val);   /* returns next value after val */

/* Call f on every element of n with with extra argument f_data */
void nums_foreach(Nums n, void (*f)(int, void *f_data), void *f_data);

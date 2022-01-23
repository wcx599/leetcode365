/*
 * Abstract data type for integer arrays.
 */

/* save some typing with typedef */
typedef struct intArray IntArray;

/*
 * Return a new intArray of given size with all entries initialized to the same value.
 *
 * Returns NULL on failure.
 */
IntArray *intArrayCreate(size_t n, int defaultValue);

/*
 * free an IntArray
 */
void intArrayDestroy(IntArray *a);

/*
 * Get the number of elements in an IntArray.
 */
size_t intArraySize(const IntArray *a);

/*
 * Get a value from an intArray.
 *
 * If index is outside the range, return the array's default value.
 */
int intArrayGet(const IntArray *a, size_t index);

/*
 * Set a value in an IntArray.
 *
 * Has no effect if index is outside the range.
 */
void intArraySet(IntArray *a, size_t index, int value);

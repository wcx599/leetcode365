// usual opaque struct
typedef struct hash Hash;

// create a hash table for storing up to n elts
Hash *hashCreate(size_t n);

void hashDestroy(Hash *h);

void hashSet(Hash *h, const char *key, int value);

// if key is in h, put value in *value, return 1,
// else return 0
int hashGet(const Hash *h, const char *key, int *value);

// print contents of h
void hashPrint(const Hash *h);

// apply f(key, value, data) to each element of h
void hashTraverse(const Hash *h, void (*f)(const char *key, int value, void *data), 
        void *data);

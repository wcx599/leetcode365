// a bytes object is an array of bytes

// notice: struct bytes not defined in this file!

// make a bytes object of given size
struct bytes *bytesCreate(size_t n);

// destroy
void bytesDestroy(struct bytes *b);

// resize data field to new n
void bytesResize(struct bytes *b, size_t n);

// access data
char *bytesData(struct bytes *b);

// access length
size_t bytesLength(struct bytes *b);

// print bytes as string
void bytesPut(struct bytes *b);

// convert string and convert to bytes
struct bytes *bytesFromString(const char *s);

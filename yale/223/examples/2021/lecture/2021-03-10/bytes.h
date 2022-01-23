// a bytes object is an array of bytes

// notice: struct bytes not defined in this file!
typedef struct bytes *Bytes;

// make a bytes object of given size
Bytes bytesCreate(size_t n);

// destroy
void bytesDestroy(Bytes b);

// resize data field to new n
void bytesResize(Bytes b, size_t n);

// access data
char *bytesData(Bytes b);

// access length
size_t bytesLength(Bytes b);

// print bytes as string
void bytesPut(Bytes b);

// convert string and convert to bytes
Bytes bytesFromString(const char *s);

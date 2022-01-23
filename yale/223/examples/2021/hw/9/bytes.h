// extensible block of bytes
// stored as unsigned chars

typedef struct bytes *Bytes;

// create an empty block
Bytes bytesCreate(void);

// destroy a block
void bytesDestroy(Bytes);

// append an unsigned char
void bytesAppendChar(Bytes, unsigned char);

// append a block
void bytesAppendBytes(Bytes, Bytes);

// get length of block
size_t bytesLen(Bytes);

// get contents of block
unsigned char *bytesData(Bytes);

// write contents to FILE *
void bytesWrite(Bytes, FILE *);

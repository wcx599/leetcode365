// Wrapper for FILE * that supports a wordBufferNextWord
// function that returns the next word
// (contiguous sequence of alpha chars),
// or null if none left.
typedef struct wordBuffer *WordBuffer;

WordBuffer wordBufferCreate(FILE *);
void wordBufferDestroy(WordBuffer);

// Returns next word.
// Pointer points to internal data of the
// WordBuffer, and should *not* be
// freed by the caller.
// However, calling wordBufferNextWord again
// may make any previously returned pointers
// invalid.
const char *wordBufferNextWord(WordBuffer);

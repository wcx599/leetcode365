// hash table for passwords
typedef struct table *Table;

Table tableCreate(void);
void tableDestroy(Table);

// insert string with given hash
void tableInsert(Table, uint64_t hash, const char *string);

// Find string from hash
// returns 0 if not found, otherwise pointer
// to internal string.
// It is safe to use this string until
// you call tableInsert or tableDestroy.
const char *tableLookup(Table, uint64_t hash);

// multiple counter abstraction
typedef struct counters *Counters;

// create an array of counters
// this will grow as needed
Counters countersCreate(void);

// free all space used by counters
void countersDestroy(Counters);

// increment the i-th counter
void countersIncrement(Counters, size_t i);

// return the value of the i-th counter
unsigned long long countersValue(Counters, size_t i);

// return number of counters in object
size_t countersSize(Counters);

// clone a Counters object
Counters countersClone(Counters);

// write a Counters object to FILE *
// returns 1 on success, 0 on failure
// in case of failure, errno will be set
int countersWrite(Counters, FILE *);

// read a Counters object from FILE *
// returns null pointer on failure
// in case of failure, errno will be set
Counters countersRead(FILE *);

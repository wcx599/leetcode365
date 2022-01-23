#include <stdio.h>
#include <stdlib.h>

/* CS223 ULA crash course: valgrind
 * Demonstrate common valgrind errors.
 * Aspnes' notes at http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#valgrind
 * More details at http://valgrind.org/docs/manual/mc-manual.html
 **/

/* FROM THE MANUAL:
 * Memcheck is a memory error detector. It can detect the following
 * problems that are common in C and C++ programs.
 *
 * Accessing memory you shouldn't, e.g. overrunning and underrunning
 * heap blocks, overrunning the top of the stack, and accessing memory
 * after it has been freed.
 *
 * Using undefined values, i.e. values that have not been initialised,
 * or that have been derived from other undefined values.
 *
 * Incorrect freeing of heap memory, such as double-freeing heap
 * blocks, or mismatched use of malloc/new/new[] versus
 * free/delete/delete[]
 *
 * Overlapping src and dst pointers in memcpy and related functions.
 *
 * Passing a fishy (presumably negative) value to the size parameter
 * of a memory allocation function.
 *
 * Memory leaks.
 *
 * Problems like these can be difficult to find by other means, often
 * remaining undetected for long periods, then causing occasional,
 * difficult-to-diagnose crashes.
 **/

/* TO RUN VALGRIND
 * Run your program as normal, but put "valgrind" before it.
 * We also strongly recommend always using --leak-check=full.
 * This is explained in memory leaks.
 *
 * We also recommend using the -g3 flag when compiling. This allows
 * valgrind to identify specific lines.
WITHOUT -G3
==8202==    at 0x40059E: illegal_rdwr (in /home/accts/hkb5/cs223/val_err)
==8202==    by 0x4005D9: main (in /home/accts/hkb5/cs223/val_err)

WITH -G3
==8126==    at 0x40059E: illegal_rdwr (valgrind_errors.c:84) <-- look at line 84 in file valgrind_errors.c
==8126==    by 0x4005D9: main (valgrind_errors.c:101)
 *
 * Valgrind works by kind of tracing where something was called.
 * Read these traces from the top down until you see the first line
 * relevant to you and your code.
 *
 * If you don't recognize an error, copy the description (for example
 * "Conditional jump or move depends on uninitialised value(s)") and
 * put it in a search engine.
 **/


/* TABLE OF CONTENTS
 * 1) Memory leak detection
 * 2) Illegal read / Illegal write errors
 * 3) Use of uninitialised values
 * 4) Illegal frees
 **/

/* 1) Memory leak detection
 * Memory leaks are from allocating memory for your program but never
 * releasing the memory back to the computer. The computer eventually
 * runs out of RAM to utilize and bad things result.
 *
 * Be warned: valgrind will report where the leaked memory originated
 * from. This is not always where you want to destroy it. For example,
 * if you have a create() function and a destroy() function but forget
 * to pass something to destroy(), valgrind will identify the origin
 * of the leaked memory as create().
 **/
void mem_leak() {
	int* i_leak = malloc(5 * sizeof(int));

/* VALGRIND ERROR REPORT
==8655== HEAP SUMMARY:
==8655==     in use at exit: 20 bytes in 1 blocks
==8655==   total heap usage: 1 allocs, 0 frees, 20 bytes allocated
==8655== 
==8655== LEAK SUMMARY:
==8655==    definitely lost: 20 bytes in 1 blocks
==8655==    indirectly lost: 0 bytes in 0 blocks
==8655==      possibly lost: 0 bytes in 0 blocks
==8655==    still reachable: 0 bytes in 0 blocks
==8655==         suppressed: 0 bytes in 0 blocks
==8025== Rerun with --leak-check=full to see details of leaked memory
*/

/* With --leak-check=full, the following lines are added:
==8655== 20 bytes in 1 blocks are definitely lost in loss record 1 of 1
==8655==    at 0x4C2DB6B: malloc (vg_replace_malloc.c:299)
==8655==    by 0x4005C8: mem_leak (valgrind_errors.c:81) <-- PROBLEM
==8655==    by 0x40071D: main (valgrind_errors.c:238)
*/

	// to fix this, free i_leak at some point
	// free(i_leak);
}

/* 2) Illegal read / Illegal write errors
 * Illegal reads and writes are from trying to read or write to
 * memory that you do not have. This is often an indexing problem, but
 * can also be a problem of attempting to read from an already-freed
 * variable. Since your program attempts to read or write this data in
 * order to utilize it in some way, reading out-of-bounds
 * uninitialized memory will cause the program to take incorrect or
 * unexpected actions and eventually segfault.
 **/
void illegal_rdwr () {
	int* array = malloc(5 * sizeof(int));	// array of 5 ints

	array[5] = 5;				// illegal write (attempting to access
								//		beyond array bound)
	if (array[5] == 5) {		// illegal read
		printf("hi\n");
	}

/* VALGRIND ERROR REPORT
==8667== Invalid write of size 4
==8667==    at 0x4005EE: illegal_rdwr (valgrind_errors.c:120) <-- PROBLEM
==8667==    by 0x40071D: main (valgrind_errors.c:241)
==8667==  Address 0x520f054 is 0 bytes after a block of size 20 alloc'd
==8667==    at 0x4C2DB6B: malloc (vg_replace_malloc.c:299)
==8667==    by 0x4005E1: illegal_rdwr (valgrind_errors.c:118)
==8667==    by 0x40071D: main (valgrind_errors.c:241)
==8667== 
==8667== Invalid read of size 4
==8667==    at 0x4005FC: illegal_rdwr (valgrind_errors.c:122) <-- PROBLEM
==8667==    by 0x40071D: main (valgrind_errors.c:241)
==8667==  Address 0x520f054 is 0 bytes after a block of size 20 alloc'd
==8667==    at 0x4C2DB6B: malloc (vg_replace_malloc.c:299)
==8667==    by 0x4005E1: illegal_rdwr (valgrind_errors.c:118)
==8667==    by 0x40071D: main (valgrind_errors.c:241)
==8667== 
hi			<-- PROGRAM OUTPUT
*/

	free(array);
}

/* 3) Use of uninitialised values
 * At some point the program attempts to use a variable that doesn't
 * actually have a value assigned to it. Since it's probably
 * attempting to use the value of the variable, this is bad. The
 * program will sometimes make assumptions in order to continue which
 * results in unexpected behavior.
 **/
void uninit0 () {
	int* array = malloc(5 * sizeof(int));	// array of 5 ints

	if (array[2] > 0) {		// there isn't a value in array[2]
		printf("hi\n");
	}

/* VALGRIND ERROR REPORT
==8686== Conditional jump or move depends on uninitialised value(s)
==8686==    at 0x40063E: uninit0 (valgrind_errors.c:159) <-- PROBLEM
==8686==    by 0x40071D: main (valgrind_errors.c:246)
*/
/* WHAT'S A CONDITIONAL JUMP?
 * An "if" statement is a type of conditional, in which the computer
 * checks to see if a condition is true or false. For and while loops
 * also do this.
 * In this case, the if statement "jumps" to the then or the else part
 * of the code.
 **/

	int x;
	if (x > 0) {
		printf("hello\n");
	}
	int y = 5;		// y is assigned a value, getting rid of the error
	if (y > 0) {
		printf("hello\n");
	}

	free(array);
}
void uninit1 () {
	int* array = malloc(5 * sizeof(int));	// array of 5 ints

	printf("%d\n", array[2]);	// printf apparently uses a lot of
								// conditionals. Use gdb if print
								// statements give you this issue.

	free(array);
}
void uninit2 () {
	// If you free an unmalloc'd pointer, you will get this error
	// as well. This ties into error #4. For example:
	int* array;		// pointer is declared but not assigned
	free(array);	// pointer doesn't point to any memory
}

/* 4) Illegal frees
 * You can only release memory once. Once you've released it, it's
 * gone. Attempting to free that same memory again may cause
 * undefined behavior.
 **/
void illegal_free () {
	int* array = malloc(5 * sizeof(int));	// array of 5 ints
	int* array1 = array;					// array1 points to the same place as array
	free(array1);		// free the memory that array1 points to
	free(array);		// ... array doesn't point anywhere now!
						// there's nothing to free here

/* VALGRIND ERROR REPORT
==8790== Invalid free() / delete / delete[] / realloc()
==8790==    at 0x4C2ED18: free (vg_replace_malloc.c:530)
==8790==    by 0x40070C: illegal_free (valgrind_errors.c:212) <-- PROBLEM
==8790==    by 0x40071D: main (valgrind_errors.c:251)
==8790==  Address 0x520f040 is 0 bytes inside a block of size 20 free'd
==8790==    at 0x4C2ED18: free (vg_replace_malloc.c:530)
==8790==    by 0x400700: illegal_free (valgrind_errors.c:211)
==8790==    by 0x40071D: main (valgrind_errors.c:251)
==8790==  Block was alloc'd at
==8790==    at 0x4C2DB6B: malloc (vg_replace_malloc.c:299)
==8790==    by 0x4006E8: illegal_free (valgrind_errors.c:209)
==8790==    by 0x40071D: main (valgrind_errors.c:251)
*/

	/* You may also get an error that looks like this:
*** Error in `./testDeck': double free or corruption (fasttop): 0x0000000000857400 ***
	* It is the same issue. */
}

int main() {
	/* The compiler, when given warning flags, will catch a few of
	 * these... but many memory errors go unnoticed since the compiler
	 * just wants your code to run in the first place. */

	// 1) Memory leak detection
	// mem_leak();

	// 2) Illegal read / Illegal write errors
	// illegal_rdwr();

	/* 3) Use of uninitialised values */
	// uninit0();
	// uninit1();
	// uninit2();

	/* 4) Illegal frees */
	// illegal_free();
}

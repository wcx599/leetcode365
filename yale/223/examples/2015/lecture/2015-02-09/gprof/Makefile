# here are some variable definitions
CC=gcc
# -pg means use profiling
# --static means use static linking
#  (This helps with profiling shared libraries.)
CFLAGS=-std=c99 -Wall -pedantic -g3 -pg --static

# what value to use for n
N=1000000

profile: countPrimes
	time ./countPrimes $(N)
	gprof ./countPrimes | head -12

profileNoSqrt: countPrimesNoSqrt
	time ./countPrimesNoSqrt $(N)
	gprof ./countPrimesNoSqrt | head -12

clean:
	$(RM) countPrimes countPrimesNoSqrt gmon.out *.o

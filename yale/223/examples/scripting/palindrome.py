#!/usr/bin/python

"""For each line in stdin, print PALINDROME if it is a palindrome, or index of
the first non-matching character otherwise."""

import sys

for line in sys.stdin:
    line = line.rstrip('\n')         # remove trailing newline
    if line == line[::-1]:
        print("PALINDROME")
    else:
        mismatches = [ i for i in range(len(line)) if line[i] != line[-(i+1)] ]
        print(min(mismatches))

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>

#include "table.h"

// Password cracker.
//
// Takes a salt string from argv[1], the name of a file with
// passwords to try from argv[2],
// and an encrypted password file with lines of the form
//
//     username:password
//
// from stdin, and sends to stdout out an decrypted password
// file with lines of the form
//
//     username:decrypted-password
//
// Passwords are decrypted by looking for matching lines in the
// file specified in argv[2]. If a password cannot be decrypted,
// it is passed through unmodified.


// All the hash stuff is copied from encrypt.c
#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

// modified version of FNV1a that updates hash
// based on string s
static void
FNV1a(uint64_t *hash, const char *s)
{
    while(*s) {
        *hash ^= *s++;
        *hash *= FNV_PRIME_64;
    }
}

// precompute result of applying salt
static uint64_t
precomputeSaltHash(const char *salt)
{
    uint64_t hash = FNV_OFFSET_BASIS_64;

    FNV1a(&hash, salt);

    return hash;
}

// hash string with precomputed salt
static uint64_t
passwordHash(uint64_t saltHash, const char *password)
{
    FNV1a(&saltHash, password);

    return saltHash;
}

#define GETLINE_INITIAL_SIZE (16)
#define GETLINE_MULTIPLIER (2)

// fetch characters from f to first newline or EOL
// returns malloc'd buffer that should be freed by caller
// if EOL is first character, returns 0
static char *
getLine(FILE *f)
{
    int c;
    
    // invariant:
    // size > top
    // size = size of buffer
    size_t size = GETLINE_INITIAL_SIZE;
    size_t top = 0;
    char *buffer = calloc(size, sizeof(char));

    assert(buffer);

    for(;;) {
        switch((c = getc(f))) {

            case EOF:
                if(top == 0) {
                    // got nothing
                    free(buffer);
                    return 0;
                }
                // else fall through

            case '\n':
                buffer[top] = '\0';
                return buffer;

            default:
                buffer[top++] = c;
                if(top >= size) {
                    size *= GETLINE_MULTIPLIER;
                    buffer = realloc(buffer, size * sizeof(char));

                    assert(buffer);
                }
        }
    }
}

#define PASSWORD_DELIMITER (':')

int
main(int argc, char **argv)
{

    if(argc != 3) {
        fprintf(stderr, "Usage: %s salt dictionary < encrypted-password-file > decrypted-password-file\n", argv[0]);
        return 1;
    }

    // precompute salt
    uint64_t saltHash = precomputeSaltHash(argv[1]);

    int c;
    char *password; // from input
    const char *found; // from table
    uint64_t hash;

    // generate table of hashed passwords
    Table t = tableCreate();
    assert(t);

    FILE *f = fopen(argv[2], "r");

    if(f == 0) {
        perror(argv[2]);
        return 1;
    }

    while((password = getLine(f)) != 0) {
        tableInsert(t, passwordHash(saltHash, password), password);
        free(password);
    }

    fclose(f);

    // main loop: copy username, then attempt to decrypt password
    while((c = getchar()) != EOF) {
        // copy to stdout
        putchar(c);

        if(c == PASSWORD_DELIMITER) {
            // process password
            if(scanf("%" SCNx64 "\n", &hash) != 1) {
                // bad format
                return 2;
            }

            if((found = tableLookup(t, hash)) != 0) {
                puts(found);
            } else {
                // reprint the hashed password
                printf("%" PRIx64 "\n", hash);
            }
        } 
    }

    tableDestroy(t);

    return 0;
}

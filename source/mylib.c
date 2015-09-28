#include <stdio.h>
#include <stdlib.h>
#include <assert.h> //assert
#include "mylib.h"

void *emalloc(size_t s) {
   void *result = malloc(s);
   if (NULL == result) {
      fprintf(stderr, "Can't allocate memory\n");
      exit(EXIT_FAILURE);
   }
   return result;
}

void *erealloc(void *p, size_t s) {
   void *result = realloc(p, s);
   if (NULL == result) {
      fprintf(stderr, "Can't allocate memory\n");
      exit(EXIT_FAILURE);
   }
   return result;
}

/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 * Source: http://stackoverflow.com/a/822361
 */
int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval = 0;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}


int mod(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}

char *
itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
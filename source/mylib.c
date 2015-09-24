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

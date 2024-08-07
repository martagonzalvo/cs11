/*
 * FILE: memcheck.h
 *
 *       Interface to the memory leak checker.
 *
 */

#ifndef MEMCHECK_H
#define MEMCHECK_H

#include <stdlib.h>

void *checked_malloc_fn(size_t size, char *filename, int lineno);
void *checked_calloc_fn(size_t nmemb, size_t size,
                        char *filename, int lineno);
void  checked_free_fn(void *ptr, char *filename, int lineno);
void  print_memory_leaks(void);

/*
 * Macros which maintain the interface of the standard malloc/calloc/free
 * functions.  Don't include these if this file is being included into
 * memcheck.c, or it will screw up the definitions of the checked functions.
 */

#ifndef MEMCHECK_C

#define malloc(n)    checked_malloc_fn((n), __FILE__, __LINE__)
#define calloc(n, m) checked_calloc_fn((n), (m), __FILE__, __LINE__)
#define free(p)      checked_free_fn((p), __FILE__, __LINE__)

#endif  /* MEMCHECK_C */

#endif  /* MEMCHECK_H */


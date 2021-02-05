
#ifndef  ARRAY_INC
#define  ARRAY_INC

#include <stdlib.h>
#include <assert.h>

typedef struct
{
   int* array;
   int len;
} Array;

Array* Array_new( size_t max_len );

void Array_delete( Array** this );

void Array_set( Array* this, size_t loc, int val );

int Array_get( Array* this, size_t loc );

size_t Array_len( Array* this );

#endif   /* ----- #ifndef ARRAY_INC  ----- */

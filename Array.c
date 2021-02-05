
#include "Array.h"

Array* Array_new( size_t max_len )
{
   Array* a = (Array*) malloc( sizeof( Array ) );
   if( a ){
      a->array = (int*) malloc( max_len * sizeof( int ) );
      a->len = max_len;
   }
   return a;
}

void Array_delete( Array** this )
{
   assert( *this );

   free( (*this)->array );
   free( *this );
   *this = NULL;
}

void Array_set( Array* this, size_t loc, int val )
{
   assert( 0 <= loc && loc < this->len );

   this->array[ loc ] = val;
}

int Array_get( Array* this, size_t loc )
{
   assert( 0 <= loc && loc < this->len );

   return this->array[ loc ];
}

size_t Array_len( Array* this )
{
   return this->len;
}


/**
 * @file Array.c
 *
 * @brief Contiene las definiciones de las funciones para el TAD Array que es una arreglo
 * 
 *
 * Array es un TAD que sirve de contenedor, 
 * tiene como estructura subyacente a un arreglo de enteros
 *
 * @autores Francisco Rodríguez
 * @date 
 * @version 
 */

#include "Array.h"

 /**
 * @brief Crea un nuevo Array
 *
 * @param El tamaño del Array
 *
 * @return Una referencia al Array
 *
 * @post Existe el nuevo Array
 */
Array* Array_new( size_t max_len )
{
   Array* a = (Array*) malloc( sizeof( Array ) );/*! a es el TAD Array creado de forma dinámica*/
   if( a ){
      a->array = (int*) malloc( max_len * sizeof( int ) ); 
      a->len = max_len;
   }
   return a;
}

 /**
 * @brief Devuelve la memoria de un Array
 *
 * @param this Una referencia al Array
 *
 * @pre El Array debe existir.
 * @post El Array apunta a NULL
 */
void Array_delete( Array** this )
{
   assert( *this );

   free( (*this)->array );
   free( *this );
   *this = NULL;
}

/**
 * @brief Inserta un elemento en cierta posición del Array
 *
 * @param this Una referencia al Array de trabajo
 * @param loc La posición
 * @param val El elemento a insertar
 *
 * @pre El Array debe tener suficiente espacio para insertar en dicha posición
 * @post Se inserte el elemento
 */
void Array_set( Array* this, size_t loc, int val )
{
   assert( 0 <= loc && loc < this->len );

   this->array[ loc ] = val;
}

/**
 * @brief Devuelve el elemento del Array de cierta posicion
 *
 * @param this Una referencia al Array de trabajo
 * @param loc La posicion
 *
 * @return El elemento en dicha posición
 *
 * @pre Posición debe estar dentro de los límites del Array
 */
int Array_get( Array* this, size_t loc )
{
   assert( 0 <= loc && loc < this->len );

   return this->array[ loc ];
}

/**
 * @brief Devuelve la cantidad de elementos en Array
 *
 * @param this Una referencia al Array de Trabajo de trabajo
 *
 * @return La cantidad de elementos
 *
 * @pre Array this debe existir.
 */
size_t Array_len( Array* this )
{
   return this->len;
}


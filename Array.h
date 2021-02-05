/**
 * @file Array.h
 *
 * @brief Contiene las declaraciones de las funciones para el TAD Array que es una arreglo
 * 
 *
 * Array es un TAD que sirve de contenedor, 
 * tiene como estructura subyacente a un arreglo de enteros
 *
 * @autores Francisco Rodríguez
 * @date 
 * @version 
 */
#ifndef  ARRAY_INC
#define  ARRAY_INC

#include <stdlib.h>
#include <assert.h>

//! Define un tipo compuesto Array con dos campos
typedef struct
{
   int* array; /*! array es el arreglo usado como ED subyacente*/
   int len; /*! len es la cantidad de elementos en array*/
} Array;

Array* Array_new( size_t max_len );

void Array_delete( Array** this );

void Array_set( Array* this, size_t loc, int val );

int Array_get( Array* this, size_t loc );

size_t Array_len( Array* this );

#endif   /* ----- #ifndef ARRAY_INC  ----- */

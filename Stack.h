#ifndef __PILA_INC__
#define __PILA_INC__

#include <stdlib.h>
// malloc and friends

#include <stdbool.h>
// bool, true y false

#include <stdio.h>
// printf y scanf

#include <assert.h>
// assert

typedef struct
{
	int* stack;      /**!< Contenedor de la pila. Es un arreglo dinámico de enteros. */
	size_t top;      /**!< Apunta al tope de la pila. */
	size_t capacity; /**!< Número máximo de elementos en la pila. */
} Stack;

Stack* Stack_New( size_t _capacity );

void Stack_Delete( Stack* this );

void Stack_Push( Stack* this, int _data );

int Stack_Pop( Stack* this );

int Stack_Peek( Stack* this );

bool Stack_IsEmpty( Stack* this );


bool Stack_IsFull( Stack* this );

 */
size_t Stack_Len( Stack* this );


size_t Stack_Capacity( Stack* this );

void Stack_Reset( Stack* this );

void Stack_Print( Stack* this );

void Stack_Copy( Stack* this, const Stack* rhs );

#endif // __PILA_INC__ 

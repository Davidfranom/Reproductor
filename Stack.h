
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

/**
 * @brief Crea una pila 
 *
 * @param _capacity Número de elementos para la pila
 *
 * @return Una referencia a la pila
 */
Stack* Stack_New( size_t _capacity );

/**
 * @brief Destruye una pila
 *
 * @param this Referencia un objeto Stack
 */
void Stack_Delete( Stack* this );

/**
 * @brief Inserta un elemento en el top de la pila
 *
 * @param this Referencia un objeto Stack
 * @param _data Valor a insertar
 *
 * @pre La pila existe y no está llena
 */
void Stack_Push( Stack* this, int _data );

/**
 * @brief Extrae el elemento en el top de la pila
 *
 * @param this Referencia un objeto Stack
 *
 * @return El elemento en el top de la pila
 *
 * @pre La pila existe y no está vacía
 */
int Stack_Pop( Stack* this );

int Stack_Peek( Stack* this );

/**
 * @brief Indica si una pila está vacía
 *
 * @param this Referencia un objeto Stack
 *
 * @return true si la pila está vacía, false en cualquier otro caso
 *
 * @pre La pila existe
 */
bool Stack_IsEmpty( Stack* this );

/**
 * @brief Indica si la pila está llena
 *
 * @param this Referencia un objeto Stack
 *
 * @return true si la pila está llena, false en cualquier otro caso
 *
 * @pre La pila existe
 */
bool Stack_IsFull( Stack* this );

/**
 * @brief Devuelve el número actual de elementos en la pila
 *
 * @param this Referencia un objeto Stack
 *
 * @return El número de elementos actuales en la pila
 *
 * @pre La pila existe
 */
size_t Stack_Len( Stack* this );

/**
 * @brief Devuelve el número máximo de elementos que la pila puede almacenar
 *
 * @param this Referencia un objeto Stack
 *
 * @return El número máximo de elementos que la pila puede almacenar
 *
 * @pre La pila existe
 */
size_t Stack_Capacity( Stack* this );

void Stack_Reset( Stack* this );

void Stack_Print( Stack* this );

void Stack_Copy( Stack* this, const Stack* rhs );

#endif // __PILA_INC__ 

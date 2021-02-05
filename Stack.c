#include "Stack.h"
/**
 * @brief Crea una pila 
 *
 * @param _capacity Número de elementos para la pila
 *
 * @return Una referencia a la pila
 */
Stack* Stack_New( size_t _capacity )
{
	Stack * s = (Stack*) malloc( sizeof ( Stack ) );
	// crea a un nuevo objeto Stack en el heap

	if( NULL != s ){
		s->stack = (int *) malloc( _capacity * sizeof( int ) );
		// crea a un nuevo arreglo de int's en el heap

		// abortamos la misión si la petición de memoria no pudo ser completada
		if( NULL == s->stack ){ 
			free( s );
			s = NULL; 
		}

		else{
			s->top = 0;
			s->capacity = _capacity;
		}
	}

	return s;
}
/**
 * @brief Destruye una pila
 *
 * @param this Referencia un objeto Stack
 */
void Stack_Delete( Stack* this )
{
	assert( this );

	free( this->stack );
	// devuelve la memoria del arreglo
	
	free( this );
	// devuelve la memoria del objeto
}

bool Stack_IsEmpty( Stack* this )
{
	return (this->top == 0);
}
/**
 * @brief Indica si la pila está llena
 *
 * @param this Referencia un objeto Stack
 *
 * @return true si la pila está llena, false en cualquier otro caso
 *
 * @pre La pila existe
 */
bool Stack_IsFull (Stack* this)
{
	return (this->top >= this->capacity);
}
/**
 * @brief Inserta un elemento en el top de la pila
 *
 * @param this Referencia un objeto Stack
 * @param _data Valor a insertar
 *
 * @pre La pila existe y no está llena
 */

void Stack_Push( Stack* this, int _data )
{
	assert( this->top < this->capacity );
	// si top es igual a capacity, entonces tenemos un problema

	this->stack[ this->top ] = _data;

	++this->top;
}
/**
 * @brief Extrae el elemento en el top de la pila
 *
 * @param this Referencia un objeto Stack
 *
 * @return El elemento en el top de la pila
 *
 * @pre La pila existe y no está vacía
 */
int Stack_Pop( Stack* this )
{
	assert( this->top > 0 );
	// si top es cero, entonces tenemos un problema

	--this->top;

	return this->stack[this->top];
}
/**
*@brief Observa el elemento en el tope de la pila.
*
*@param this Referencia a un objeto Stack. 
*
*@return Stack.
*/
int Stack_Peek( Stack* this )
{
	assert( this->top > 0 );
	// si top es cero, entonces tenemos un problema

	return this->stack[this->top - 1];
}

size_t Stack_Capacity( Stack* this )
{
	return this->capacity;
}
/**
*@brief Indica los elementos actuales en la pila.
* 
*@param this Referencia a un objeto Stack.
* 
*@return El número de elementos actuales en la pila.
*/
size_t Stack_Len( Stack* this )
{
	return this->top;
}
/**
*@brief Vacia a la pila. 
*@param this Referencia a un objeto Stack.
*@return top a 0
*/
void Stack_Reset( Stack* this )
{
   this->top = 0;
}
/**
*@brief Imprime los elementos de la pila.
* 
*@param this Referencia a un objeto Stack.
*/
void Stack_Print( Stack* this )
{
   for( size_t i = 0; i < this->top; ++i ){
      printf( "%d, ", this->stack[ i ] );
   }
   printf( "\n" );
}
/**
*@brief Copia los elementos actuales en la pila y los envia al objeto a ser copiado. 
*
*@param this Referencia a un objeto Stack y rhs Referencia a un objeto Stack.
*/
void Stack_Copy( Stack* this, const Stack* rhs )
{
   assert( rhs->top <= this->capacity );
   // la capacidad del objeto receptor (this) debe ser igual o mayor
   // al número máximo de elementos actualmente en el objeto a ser 
   // copiado (rhs)

   size_t i;
   for( i = 0; i < rhs->top; ++i ){
      this->stack[ i ] = rhs->stack[ i ];
   }
   this->top = i;
}

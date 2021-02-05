/** 1. Se adaptaron el archivo y las funciones para usarse como módulo
 *  2. El algoritmo ahora optimiza sin repetición y a la mayor cantidad de elementos
 *  3. Si no encuentra una solución, encuentra la más próxima de manera recursiva
 *  @author David Ortiz
 *  @date 04/02/2020
 *  @version 1
 */


#include "bt.h"

/**
 * @brief Determina si un candidato es factible para ser agregado a la solucion
 *
 * @param c El candidato
 * @param p El problema o límite
 *
 * @return true se el candidato es factible; false si no lo es
 */
bool es_factible (int c, int p, int acum)
{
   return (c+acum) <= p;
}

/**
 * @brief Determina si acumulado es la solución del problema
 *
 * @param p el problema
 * @param acum el acumulado y posible solución
 *
 * @return true si el acumulado coincide con la solución; false, si no
 */
bool es_solucion (int p, int acum)
{
   return (acum == p);
}

/**
 * @brief Realiza las combinaciones con los distintos candidatos de forma
 * recursiva hasta que encuentra una solución o termina con ellos.
 *
 * @param candidatos una referencia al contenedor de candidatos (Array)
 * @param solucion una referencia al contenedor de la solución (Stack)
 * @param posicion una referencia al contenedor de posiciones de los candidatos(Stack)
 * @param p El problema
 * @param acum Una referencia al acumulado
 * @param best Una referencia al contenedor de mejor solución(Stack)
 * @param b_posicion Una referencia al contenedor de posiciones de la mejor solucion(Stack)
 * @param opt un inicializador
 *
 */
void bt( Array* candidatos, Stack* solucion,Stack* posicion, int p, int* acum, Stack* best,Stack* b_posicion,size_t opt )
{
	for(size_t x=opt;x<(Array_len(candidatos));++x){
		opt=x+1;
		if (es_factible(Array_get(candidatos,x),p,*acum)){
			Stack_Push(solucion,Array_get(candidatos,x));
			Stack_Push(posicion,x);
			*acum+=Array_get(candidatos,x);
			if(es_solucion(p,*acum)){
				if(Stack_Len(solucion)>Stack_Len(best)){
					Stack_Copy(best,solucion);
					Stack_Copy(b_posicion,posicion);
				}
				*acum-=Stack_Pop(solucion);
				Stack_Pop(posicion);
			} else{
				bt(candidatos,solucion,posicion,p,acum,best,b_posicion,opt);
			}
		} else{
		}
	}
	if(Stack_IsEmpty(solucion)==false){
		*acum-=Stack_Pop(solucion);
		Stack_Pop(posicion);
	}
}

/**
 * @brief Función de activación. Inicializa los contenedores, define el problema y los candidatos
 *
 * @param candidatos Una referencia al contenedor de candidatos
 * @param solucion Una referencia al contenedor de la solución
 * @param posicion Una referencia al contenedor de las posiciones de los candidatos.
 * @param p El problema o límite
 *
 * @return la cantidad de elementos en la solución
 */
int cambio( Array* candidatos, Stack* solucion,Stack* posicion, int p )
{
	Stack* best=Stack_New(Stack_Capacity(solucion)); /*! Es la direccion de una pila donde se almacenará la mejor solución*/
	Stack* b_posicion=Stack_New(Stack_Capacity(posicion)); /*! Es la direccion de una pila donde se almacenarán las posiciones de los candidatos de la solución*/
 	int acum = 0; /*! Acumulado de la solución*/
 	size_t opt=0; /*! opt inicializa la funcion recursiva y aumenta en cada iteración, de esta manera se evita la repetición de candidatos*/
 	bt( candidatos, solucion,posicion, p, &acum, best,b_posicion,opt);

	Stack_Copy(solucion,best);
	Stack_Copy(posicion,b_posicion);
	return Stack_Len(solucion);

	Stack_Delete( best );
	Stack_Delete(b_posicion);
}


/**
 * @brief Realiza el algoritmo de Backtracking optimizado para insertar la mayor cantidad
 * de elementos para un cierto límite.
 *
 * @param playlist_gral Una referencia a la lista de candidatos
 * @param this Una referencia a la lista donde se almacenará la solución.
 * @param limit El límite de la solución.
 *
 * @pre La lista de candidatos debe existir y contener elementos
 * @post La lista de solución debe estar vacía.
 */
void backtracking(Playlist* playlist_gral,Playlist* this,int limit)
{
   Array* candidatos = Array_new( Playlist_Len(playlist_gral) ); /*! Se crea un contenedor para los candidatos a partir del tamaño de una lista*/

	Playlist_Cursor_front(playlist_gral);
	for(size_t i=0;i<Playlist_Len(playlist_gral);++i){
		Array_set( candidatos, i, Track_GetDuration(Playlist_Get(playlist_gral)) );
		Playlist_Cursor_next(playlist_gral);
	}

	int p = limit; /*! Es el problema*/

   Stack* solucion = Stack_New( p );
   Stack* posicion = Stack_New(p);


   int num_canciones = cambio( candidatos, solucion,posicion, p ); /*! Numero de elementos en la solucion*/

   if( num_canciones > 0 ){

		printf("\nPlaylist %s optimizada\n",Playlist_GetName(this));
      printf( "(%d) canciones: ", num_canciones );
		int tot=0; /*! El acumulado de la solución*/
      while( not Stack_IsEmpty( solucion ) ){
          tot+=Stack_Pop( solucion );
      }
      printf("%d minutos\n",tot);

      while( not Stack_IsEmpty( posicion ) ){
      	//Coloca al cursor en posicion
      	Playlist_Cursor_front(playlist_gral);
      	size_t pos=Stack_Pop( posicion );
        for(size_t i=0;i<pos;++i){
            Playlist_Cursor_next(playlist_gral);
        }

        Playlist_Insert_back( this, Playlist_Get(playlist_gral) );
      }
      Playlist_Traverse(this,Print_TrackTitle);

      printf( "\n" );

   } else{

   		if(p>0){
   			p--;
   			backtracking (playlist_gral,this,p);
   		} else{
   			printf ("No se encontró ninguna solució\n");
   		}
   }

   Array_delete( &candidatos );
   Stack_Delete( solucion );
   solucion = NULL;


}


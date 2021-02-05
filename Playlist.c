#include "Playlist.h"
#include <string.h>

/**
 * @brief  Crea un nuevo nodo e inicializa sus valores
 *
 * @param Track* x  Referencia a objeto Track
 *
 * @return n Dirección de memoria del objeto nodo
 *
 * @pre Debe haber espacio de memoria dinamica disponible
 *
 * @post La asignación de memoria fue exitosa
 */
static Node* newNode( Track* x )
{
	Node* n = (Node*)malloc(sizeof(Node));
	if(n){
		n->datos = *x;
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

/**
 * @brief Crea un nuevo objeto tipo Playlist
 *
 * @param name[] Arreglo de caracteres que se copía al campo name
 *
 * @return lista Dirección de memoria del objeto Playlist
 *
 * @pre Debe haber espacio de memoria dinamica disponible
 *
 * @post La asignación de memoria fue exitosa
 */

Playlist* Playlist_New( char name[] )
{
	Playlist* lista = (Playlist*)malloc(sizeof( Playlist ));
	if( lista ){
		strcpy( lista->name, name );
		lista->cursor = NULL;
		lista->first = NULL;
		lista->last = NULL;
		lista->len = 0;
	} else{
		printf("No se creo la lista");
	}
	return lista;
}


/**
 * @brief Devuelve la memoria pedida por un objeto Playlist
 *
 * @param Playlist** this Doble apuntador al objeto a borrar
 *
 * @pre El objeto Playlist debe existir
 *      No puede ser borrado dos veces
 *
 * @post Se regreso la memoria y no hubo fugas
 *
 */

void Playlist_Delete( Playlist** this )
{
	size_t c = (*this)->len;
	for(size_t i = 0; i < c ; ++i ){
		Node* tmp = (*this)->first->next;
		free( (*this)->first );
		(*this)->first = tmp;
	}
	free(*this);
	*this=NULL;
}


/**
 * @brief Inserta una cancion (Track) en la lista (Playlist)
 *
 * @param lista Una referencia a la playlist (lista) donde se insertara la canción
 * @param cancion  Referencia a la canción que se insertara
 *
 * @pre La playlist ya debe existir (estar creada)
 *      La canción debe existir (estar creada)
 *
 * @post La canción se inserto en la lista sin problemas
 */

void Playlist_Insert( Playlist* this, Track* x )
{
	Node* n = newNode(x);
	if( Playlist_IsEmpty(this) ){
		this->first = this->last = this->cursor = n;
		this->last->next = this->first;
		this->first->prev = this->last;
	} else{
		Node* tmp = this->cursor->next;
		n->next = tmp;
		tmp->prev = n;

		if(this->cursor == this->last){
			this->last = n;
		}
		this->cursor->next = n;
		n->prev = this->cursor;
		this->cursor = n;
	}
	++this->len;
}


/**
 * @brief Inseta una canción en el frente de la lista
 *
 * @param lista Referencia a la lista donde se insertara la canción
 * @param canción Referencia a la canción que se insertara
 *
 * @pre La lista debe existir
 *      La canción debe existir
 *
 * @post La canción se inserto al frente de la lista; donde apunta
 *       first
 */

void Playlist_Insert_front( Playlist* this, Track* x )
{
	Node* n = newNode(x);
	if( Playlist_IsEmpty(this) ){
		this->first = this->last = this->cursor = n;
	} else{
		n->next = this->first;
		this->first->prev = n;
		this->first = n;
	}
	this->last->next = this->first;
	this->first->prev = this->last;

	++this->len;

}


/**
 * @brief Inserta una canción al final de la lista
 *
 * @param lista Referencia a la lista donde se insertara la canción
 * @param canción Referencia a la canción a insertar
 *
 * @pre La lista debe existir
 *      La canción debe existir
 *
 * @post La canción se inserto al final de la lista, donde apunta last
 *
 */

void Playlist_Insert_back( Playlist* this, Track* x )
{
	Node* n = newNode(x);
	if( Playlist_IsEmpty(this) ){
		this->first = this->last = this->cursor = n;
	} else{
		this->last->next = n;
		n->prev = this->last;
		this->last = n;
	}
	this->last->next = this->first;
	this->first->prev = this->last;

	++this->len;

}


/**
 * @brief Elimina el elemento de la lista apuntado por el cursor
 *
 * @param lista Referencia a la lista donde esta la canción
 *                       que sera removida
 *
 * @pre La lista debe existir
 *      La lista debe tener como mínimo un elemento
 *      El cursor debe apuntar a una dirección de memoria valida
 *
 * @post La lista debera tener un nodo menos
 *       El cursor se movera a la derecha, es decir al siguiente nodo
 *
 */

void Playlist_Remove( Playlist* this )
{
	assert( this->len > 0 );

	if( this->len == 1 ){
		free( this->first );
		this->first = this->last = this->cursor = NULL;
		--this->len;
	} else if( this->cursor == this->first ){
		Playlist_Remove_front( this );
		this->cursor = this->first;
	} else if( this->cursor == this->last ){
		Playlist_Remove_back( this );
		this->cursor = this->last;
	} else{
		Node* tmp1 = this->cursor->prev;
		Node* tmp2 = this->cursor->next;
		free( this->cursor );
		tmp1->next = tmp2;
		tmp2->prev = tmp1;
		this->cursor = tmp2;
		--this->len;
	}
}

/**
 * @brief Elimina el elemento que se encuentra en el frente de la lista
 *
 * @param lista Referencia a la lista de donde se removera la canción
 *
 * @pre La lista debe existir
 *      La lista debe tener como mínimo un elemento
 *
 * @post La lista debera tener un nodo menos
 *
 */
void Playlist_Remove_front( Playlist* this )
{
	assert( this->len > 0 );

	if( this->len == 1 ){
		free( this->first );
		this->first = this->last = this->cursor =  NULL;
	} else{
		Node* tmp = this->first->next;
		free( this->first );
		this->first = tmp;
		tmp->prev = this->last;
		this->last->next = tmp;
	}
	--this->len;
}


/**
 * @brief Elimina el elemento que se encuentra al final de la lista
 *
 * @param lista Referencia a la lista de donde se removera la canción
 *
 * @pre La lista debe existir
 *      La lista debe tener como mínimo un elemento
 *
 * @post La lista debera tener un nodo menos
 *
 */
void Playlist_Remove_back( Playlist* this )
{
	assert( this->len > 0 );

	if( this->len == 1 ){
		free( this->last );
		this->first = this->last = this->cursor = NULL;
	}else{
		Node* tmp = this->last->prev;
		free( this->last );
		this->last = tmp;
		tmp->next = this->first;
		this->first->prev = tmp;
	}
	--this->len;
}



/**
 * @brief Devuelve una canción. Otorga la dirección de un objeto canción
          apuntado por el cursor y almacenado en una lista tipo playlist
 *
 * @param lista Referencia a la playlist que contiene la canción
 *
 * @return dirección del objeto canción
 *
 * @pre La lista debe existir
 *      Debe haber por lo menos una canción almacenada en la lista
 *      El cursor debe apuntar a una dirección de memoria valida
 *
 * @post La dirección regresada pertenece a un objeto canción
 *
 */
Track* Playlist_Get( Playlist* this ) // se tiene que modificar
{
	assert( this->cursor );
	return &this->cursor->datos;
}




/**
 * @brief Posiciona al cursor al frente de la lista
 *
 * @param lista Referencia a la playlist donde nos moveremos
 *
 * @pre La Lista debe existir
 *      El cursor debe apuntar a una dirección de memoria valida
 *
 * @post La lista no se modifica, unicamente es recorrida por el cursor
 *       El cursor apunta al frente de la lista
 */
void Playlist_Cursor_front( Playlist* this )
{
    assert( this->cursor );
	this->cursor = this->first;
}


/**
 * @brief Posiciona al cursor al final de la lista
 *
 * @param lista Referencia a la playlist donde nos moveremos
 *
 * @pre La lista debe existir
 *      El cursor debe apuntar a una dirección de memoria valida
 *
 * @post La lista no se modifica, unicamente es recorrida por el cursor
 *       El cursor apunta a la parte trasera de la lista
 */
void Playlist_Cursor_back( Playlist* this )
{
    assert( this->cursor );
	this->cursor = this->last;
}


/**
 * @brief Mueve el cursor al siguiente nodo
 *
 * @param lista Referencia a la playlist donde nos moveremos
 *
 * @pre La lista debe existir
 *      El cursor debe apuntar a una dirección de memoria valida
 *
 * @post El cursor apunta al nodo siguiente al actual
 */
void Playlist_Cursor_next( Playlist* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->next;
}



/**
 * @brief Mueve el cursor al nodo anterior al actual
 *
 * @param lista Referencia a la playlist donde nos moveremos
 *
 * @pre La lista debe existir
 *      El cursor debe apuntar a una dirección de memoria valida
 *
 * @post El cursor apunta al nodo predecesor del nodo actual
 *
 */
void Playlist_Cursor_prev( Playlist* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->prev;
}


/**
 * @brief Indica si la lista esta vacía
 *
 * @param lista Referencia a la lista de la cual se quiere conocer su estado
 *
 * @return true si la lista esta vacia, len = 0, false si
 *         la lista esta tiene mínimo un elemento, len != 0
 *
 * @pre La lista debe existir
 *
 */
bool Playlist_IsEmpty( Playlist* this )
{
	return this->len == 0;
}


/**
 * @brief Da el número de elementos en la lista
 *
 * @param lista Referencia a la lista de la que se quiere conocer su estado
 *
 * @return len que es el número de elementos en la lista
 *
 * @pre La lista debe existir
 */
size_t Playlist_Len( Playlist* this )
{
	return this->len;
}


/**
 * @brief Limpia la lista. Elimina todos los nodos de la lista hasta el momento,
 *        len seria igual a cero y cursor, first y last, apuntan a NULL
 *
 * @param lista Referencia a la lista a limpiar
 *
 * @pre La lista debe existir
 *      len != 0 por lo tanto la lista debe tener al menos un elemento
 *
 * @post La lista no contendra a ningun nodo
 *       los apuntadores first, last y cursor apuntan a NULL
 *
 */
void Playlist_MakeEmpty( Playlist* this )
{
	size_t c=this->len;
	for(size_t i=0; i<c; ++i){
		Playlist_Remove_front(this);
	}
}




/**
 * @brief  Recorre la lista y hace algo en cada uno de sus elementos
 *
 * @param lista Referencia a la lista de trabajo
 * @param fn Esta función hace algo con el campo de datos
 *
 * @pre La lista debe existir
 *      fn debe estar definida y escrita
 *      Los argumentos de fn deben ser del mismo tipo y deben existir
 *
 */
void Playlist_Traverse( Playlist* this, void (*fn)( Track item,size_t c ) ) // se tiene que modificar
{
	if( NULL == this ){ return; }
	size_t cont=0;
	Node* t = this->first;

	size_t c=Playlist_Len(this);
   for(size_t i=0;i<c;++i){
   		cont++;
		fn( t->datos,cont );
		t = t->next;

   }

}


/**
 * @brief Busca un elemento en la lista por su ID y lo elimina
 *
 * @param lista Referencia a lista de trabajo
 * @param id Entero que sirve como identificador unico de cada canción
 *
 * @pre La lista debe existir
 *      La lista debe contener al menos una canción
 *
 */
void Playlist_GralRemove( Playlist* this, size_t id )
{
	if( NULL == this ){ return; }
	Node* t = this->first;

	size_t c=Playlist_Len(this);
   for(size_t i=0;i<c;++i){

		if (t->datos.id==id){
			this->cursor=t;
			Playlist_Remove(this);
		}
		t = t->next;
   }
}


/**
 * @brief Devuelve el ID de una canción apuntada por el cursor
 *
 * @param lista Referencia a la lista de trabajo
 *
 * @return id de una canción
 *
 * @pre La lista debe existir
 *      La lista debe contener canciones, no estar vacía
 *      El cursor debe apuntar a una dirección de memoria valida
 *
 */
size_t Playlist_GetID(Playlist* this){
	assert(this->cursor);
	return this->cursor->datos.id;
}


/**
 * @brief Devuelve el nombre de la lista
 *
 * @param lista Referencia a la lista de trabajo
 *
 * @return el nombre de la playlist
 *
 * @pre La lista debe existir
 *
 */
char* Playlist_GetName(Playlist* this){
	assert(this);
	return (char*)this->name;
}


/**
 * @brief Muestra en pantalla el nombre de la playlist
 *
 * @param lista Copia de la lista de trabajo
 * @param c Numero de la lista
 *
 * @pre La lista debe existir
 *      Debe existir al menos una lista
 *
 */
//Para Traverse
void Print_PlaylistName(Playlist item,size_t c){
	printf("%ld. %s\n",c,item.name);
}


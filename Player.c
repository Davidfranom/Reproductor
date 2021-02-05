/**
 * @file Player.c
 *
 * @brief Contiene las funciones para el TAD Player que es una lista 
 * 
 *
 * Player es un TAD que sirve de lista enlazada, 
 * cuyos nodos contienen como elemento de datos otra lista de distinto tipo.
 *
 * @autores David Ortiz
 * @date 04/02/21
 * @version 1
 */
#include "Player.h"

 /**
 * @brief Crea un nuevo nodo
 *
 * @param Una referencia a la lista de tyrabajo
 *
 * @return Una referencia al nuevo nodo
 *
 * @post El nodo es válido.
 */
static Node_2* newNode_2( Playlist* x )
{
	Node_2* n = (Node_2*)malloc(sizeof(Node_2));
	if(n){
		n->datos = *x; //  Verificar si funciona
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

/**
 * @brief Crea una lista doblemente enlazada
 * 
 * @return Una referencia a la nueva lista
 * @post Una lista existente en el heap
 */
Player* Player_New()
{
	Player* lista = (Player*)malloc(sizeof( Player ));
	if(lista){
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
 * @brief Devuelve la memoria de la lista y todos sus nodos
 *
 * @param lista Una referencia a la dirección de la lista de trabajo
 *
 * @pre La lista this debe existir.
 * @post La lista apunta a NULL
 */
void Player_Delete( Player** this )
{
	size_t c=(*this)->len;
	for(size_t i = 0; i < c ;++i){
		Node_2* tmp = (*this)->first->next;
		free((*this)->first);
		(*this)->first = tmp;
	}
	free(*this);
	*this=NULL;
}

/**
 * @brief Inserta un elemento a la derecha del cursor.
 *
 * @param lista Una referencia a la lista de trabajo
 * @param x El elemento a insertar
 *
 * @return true si el valor se insertÃ³ en la lista; false en caso
 * contrario. Esto podrÃ­a suceder si la memoria se agotÃ³.
 */
void Player_Insert( Player* this, Playlist* x )
{
	Node_2* n= newNode_2(x);
	if( Player_IsEmpty(this) ){
		this->first = this->last = this->cursor = n;
		this->last->next = this->first;
		this->first->prev = this->last;
	} else{
		Node_2* tmp = this->cursor->next;
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
 * @brief Inserta un elemento a la izquierda del first.
 *
 * @param this Una referencia a la lista de trabajo
 * @param x El elemento a insertar
 *
 * @pre La lista this debe existir.
 * @post Len aumenta en 1.
 */
void Player_Insert_front( Player* this, Playlist* x )
{
	Node_2* n= newNode_2(x);
	if(Player_IsEmpty(this)){
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
 * @brief Inserta un elemento a la derecha del last.
 *
 * @param this Una referencia a la lista de trabajo
 * @param x El elemento a insertar
 *
 * @pre La lista this debe existir.
 * @post Len aumenta en 1.
 */
void Player_Insert_back( Player* this, Playlist* x )
{
	Node_2* n = newNode_2(x);
	if(Player_IsEmpty(this)){
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
 * @brief Remueve el elemento apuntado por el cursor
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mueve al elemento a la derecha del nodo borrado.
 * @post Len decrece en 1
 */
void Player_Remove( Player* this )
{
	assert( this->len > 0 );

	if( this->len == 1 ){
		free(this->first);
		this->first = this->last = this->cursor = NULL;
		--this->len;
	} else if(this->cursor == this->first){
		Player_Remove_front(this);
		this->cursor = this->first;
	} else if(this->cursor == this->last ){
		Player_Remove_back(this);
		this->cursor = this->last;
	} else{
		Node_2* tmp1 = this->cursor->prev;
		Node_2* tmp2 = this->cursor->next;
		free(this->cursor);
		tmp1->next=tmp2;
		tmp2->prev=tmp1;
		this->cursor=tmp2;
		--this->len;
	}
}

/**
 * @brief Remueve el elemento al frente de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posiciÃ³n en la que estaba cuando entrÃ³ la
 * funciÃ³n.
 * @post Len decrece en 1
 */
void Player_Remove_front( Player* this )
{
	assert(this->len > 0);

	if( this->len == 1 ){
		free(this->first);
		this->first = this->last = this->cursor =  NULL;
	} else{
		Node_2* tmp=this->first->next;
		free(this->first);
		this->first=tmp;
		tmp->prev=this->last;
		this->last->next=tmp;
	}
	--this->len;
}

/**
 * @brief Remueve el elemento al fondo de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posiciÃ³n en la que estaba cuando entrÃ³ la
 * funciÃ³n.
 */
void Player_Remove_back( Player* this )
{
	assert(this->len > 0);

	if(this->len == 1){
		free(this->last);
		this->first = this->last = this->cursor = NULL;
	}else{
		Node_2* tmp = this->last->prev;
		free(this->last);
		this->last=tmp;
		tmp->next=this->first;
		this->first->prev=tmp;
	}
	--this->len;
}

/**
 * @brief Devuelve una referencia al valor apuntado por el cursor.
 *
 * @param this Una referencia a la lista de trabajo
 *
 * @return El valor apuntado por el cursor
 */
Playlist* Player_Get( Player* this ) 
{
	assert( this->cursor );
	return &this->cursor->datos;
}

/**
 * @brief Manda al cursor al inicio de la lista
 *
 * @param lista Una referencia a la lista de trabajo
 */
void Player_Cursor_front( Player* this )
{
    assert( this->cursor );
	this->cursor = this->first;
}

/**
 * @brief Coloca al cursor en last
 *
 * @param lista Una referencia a la lista de trabajo
 *
 * @pre La lista no debe estar vacía.
 */
void Player_Cursor_back( Player* this )
{
    assert( this->cursor );
	this->cursor = this->last;
}

/**
 * @brief Coloca al cursor en su elemento a la derecha
 *
 * @param lista Una referencia a la lista de trabajo
 *
 * @pre La lista no debe estar vacía
 */
void Player_Cursor_next( Player* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->next;
}

/**
 * @brief Coloca al cursor en su elemento a la izquierda
 *
 * @param lista Una referencia a la lista de trabajo
 *
 * @pre La lista no debe estar vacía.
 */
void Player_Cursor_prev( Player* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->prev;
}

/**
 * @brief Indica si la lista está vacía
 *
 * @param lista Una referencia a la lista de trabajo
 *
 * @return true si está vacía; false si no lo está
 *
 * @pre La lista this debe existir.
 */
bool Player_IsEmpty( Player* this )
{
	return this->len == 0;
}

/**
 * @brief Indica la cantidad de elementos en la lista
 *
 * @param lista Una referencia a la lista de trabajo
 *
 * @return Cantidad de elementos
 *
 * @pre La lista this debe existir.
 */
size_t Player_Len( Player* this )
{
	return this->len;
}

/**
 * @brief Elimina todos los elementos de la lista sin eliminar la lista.
 *
 * @param this Referencia a una lista.
 */
void Player_MakeEmpty( Player* this )
{
	size_t c=this->len;
	for(size_t i=0; i<c; ++i){
		Player_Remove_front(this);
	}
}

/**
 * @brief Recorre la lista y hace algo en cada uno de sus elementos
 *
 * @param lista Una referencia a la lista de trabajo
 * @param fn Esta funciÃ³n hace algo con el campo de datos 
 */
void Player_Traverse( Player* this, void (*fn)( Playlist item, size_t c ) ) 
{
	if( NULL == this ){ return; }
	size_t cont=0;
	Node_2* t = this->first;

	size_t c=this->len;
   for(size_t i=0;i<c;++i){
   		cont++;
		fn( t->datos,cont );
		t = t->next;

   } 

}

/**
 * @brief Elimina un elemento en copncreto de todas las listas hijas que lo contengan
 *
 * @param this Una referencia a la lista de trabajo
 * @param id La id del elemento a eliminar
 *
 * @pre La lista this debe existir.
 * @post La lista es válida.
 */
void Player_GralRemove( Player* this, size_t id ) 
{
	if( NULL == this ){ return; }
	Node_2* t = this->first;
	
	size_t c=this->len;
   for(size_t i=0;i<c;++i){
   		
		Playlist_GralRemove(&t->datos,id);
		t = t->next;
   } 
}


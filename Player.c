#include "Player.h"


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

void Player_Delete( Player** this )
{
	for(size_t i = 0; i < (*this)->len ;++i){
		Node_2* tmp = (*this)->first->next;
		free((*this)->first);
		(*this)->first = tmp;
	}
	free(*this);
	*this=NULL;
}

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


Playlist* Player_Get( Player* this ) // se tiene que modificar
{
	assert( this->cursor );
	return &this->cursor->datos;
}


void Player_Cursor_front( Player* this )
{
    assert( this->cursor );
	this->cursor = this->first;
}

void Player_Cursor_back( Player* this )
{
    assert( this->cursor );
	this->cursor = this->last;
}

void Player_Cursor_next( Player* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->next;
}

void Player_Cursor_prev( Player* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->prev;
}

bool Player_IsEmpty( Player* this )
{
	return this->len == 0;
}

size_t Player_Len( Player* this )
{
	return this->len;
}

void Player_MakeEmpty( Player* this )
{
	for(size_t i=0; i<this->len; ++i){
		Player_Remove_front(this);
	}
}


void Player_Traverse( Player* this, void (*fn)( Playlist item, size_t c ) ) // se tiene que modificar
{
	if( NULL == this ){ return; }
	size_t cont=0;
	Node_2* t = this->first;


   for(size_t i=0;i<Player_Len(this);++i){
   		cont++;
		fn( t->datos,cont );
		t = t->next;

   } 

}

void Player_GralRemove( Player* this, size_t id ) 
{
	if( NULL == this ){ return; }
	Node_2* t = this->first;

   for(size_t i=0;i<Player_Len(this);++i){
   		
		Playlist_GralRemove(&t->datos,id);
		t = t->next;
   } 
}


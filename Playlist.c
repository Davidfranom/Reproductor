#include "Playlist.h"
#include<string.h>


static Node* newNode( Track* x )
{
	Node* n = (Node*)malloc(sizeof(Node));
	if(n){
		n->datos = *x; //  Verificar si funciona
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

Playlist* Playlist_New(char name[])
{
	Playlist* lista = (Playlist*)malloc(sizeof( Playlist ));
	if(lista){
		strcpy(lista->name,name);
		lista->cursor = NULL;
		lista->first = NULL;
		lista->last = NULL;
		lista->len = 0;
	} else{
		printf("No se creo la lista");
	}
	return lista;
}

void Playlist_Delete( Playlist** this )
{
	size_t c=(*this)->len;
	for(size_t i = 0; i < c ;++i){
		Node* tmp = (*this)->first->next;
		free((*this)->first);
		(*this)->first = tmp;
	}
	free(*this);
	*this=NULL;
}

void Playlist_Insert( Playlist* this, Track* x )
{
	Node* n= newNode(x);
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

void Playlist_Insert_front( Playlist* this, Track* x )
{
	Node* n= newNode(x);
	if(Playlist_IsEmpty(this)){
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

void Playlist_Insert_back( Playlist* this, Track* x )
{
	Node* n = newNode(x);
	if(Playlist_IsEmpty(this)){
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

void Playlist_Remove( Playlist* this )
{
	assert( this->len > 0 );

	if( this->len == 1 ){
		free(this->first);
		this->first = this->last = this->cursor = NULL;
		--this->len;
	} else if(this->cursor == this->first){
		Playlist_Remove_front(this);
		this->cursor = this->first;
	} else if(this->cursor == this->last ){
		Playlist_Remove_back(this);
		this->cursor = this->last;
	} else{
		Node* tmp1 = this->cursor->prev;
		Node* tmp2 = this->cursor->next;
		free(this->cursor);
		tmp1->next=tmp2;
		tmp2->prev=tmp1;
		this->cursor=tmp2;
		--this->len;
	}
}

void Playlist_Remove_front( Playlist* this )
{
	assert(this->len > 0);

	if( this->len == 1 ){
		free(this->first);
		this->first = this->last = this->cursor =  NULL;
	} else{
		Node* tmp=this->first->next;
		free(this->first);
		this->first=tmp;
		tmp->prev=this->last;
		this->last->next=tmp;
	}
	--this->len;
}

void Playlist_Remove_back( Playlist* this )
{
	assert(this->len > 0);

	if(this->len == 1){
		free(this->last);
		this->first = this->last = this->cursor = NULL;
	}else{
		Node* tmp = this->last->prev;
		free(this->last);
		this->last=tmp;
		tmp->next=this->first;
		this->first->prev=tmp;
	}
	--this->len;
}


Track* Playlist_Get( Playlist* this ) // se tiene que modificar
{
	assert( this->cursor );
	return &this->cursor->datos;
}


void Playlist_Cursor_front( Playlist* this )
{
    assert( this->cursor );
	this->cursor = this->first;
}

void Playlist_Cursor_back( Playlist* this )
{
    assert( this->cursor );
	this->cursor = this->last;
}

void Playlist_Cursor_next( Playlist* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->next;
}

void Playlist_Cursor_prev( Playlist* this )
{
	assert(this->cursor);
	this->cursor=this->cursor->prev;
}

bool Playlist_IsEmpty( Playlist* this )
{
	return this->len == 0;
}

size_t Playlist_Len( Playlist* this )
{
	return this->len;
}

void Playlist_MakeEmpty( Playlist* this )
{
	size_t c=this->len;
	for(size_t i=0; i<c; ++i){
		Playlist_Remove_front(this);
	}
}


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

size_t Playlist_GetID(Playlist* this){
	assert(this->cursor);
	return this->cursor->datos.id;
}

char* Playlist_GetName(Playlist* this){
	assert(this);
	return (char*)this->name;
}

//Para Traverse
void Print_PlaylistName(Playlist item,size_t c){
	printf("%ld. %s\n",c,item.name);
}


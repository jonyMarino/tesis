/*
 * list.c
 * 
 * Copyright (c) 2011, old_fashioned. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 */


#include "ooc.h"
#include "exception.h"

/* This is a class implementation file
 */

#include "list.h"
#include "implement/list.h"

/** @class List
 *  @brief List class - a standard ooc container.
 * 	@see list.h
 */

/** @file list.h
 * @brief List class - doubly linked list, a standard ooc container.
 * List is a container class, that can hold pointers to any kind of data.
 * Every item stored in the list must work perfectly with the supplied list item destroyer!
 * In practice this means, that you can only store items in the list that has the same deletion method.
 * @note	List implementation is thread safe, in the manner, that adding items to, or deleting from the List
 * 			will not mesh up the List. But the ListIterators may become invalid if multiple threads modify the
 * 			same List object. As a consecvence the @c _foreach_ and @c _find_ methods may behave unexpectedly
 * 			if an other thread is modifying the List! Make your own locking if needed!
 *          The same applies to the ooc_duplicate() method for List (uses list_foreach() internally)!
 */ 

/* Allocating the class description table and the vtable
 */

AllocateClass( List, Base );


/** @class ListNode
 *  @brief ListNode class - brief description.
 * The ListNode objects form the chain of the List. It has two pointers: one for the previous and one 
 * for the next ListNode in the List.
 * You can create a more effective List, if your items are subclasses of ListNode class, and you create
 * the List with list_new_of_nodes(). In this case your data are stored whithin the node, thus less @c malloc()
 * is called, and less space is used.
 * Unlike "noded" Lists, normal Lists hold only a pointer in the ListNode to the data you put in the List, that 
 * needs an additional memory allocation for the ListNode.
 * 	@see listnode.h
 */

AllocateClass( ListNode, Base );

static
void
ListNode_initialize( Class this )
{
}

#ifndef OOC_NO_FINALIZE
static
void
ListNode_finalize( Class this )
{
}
#endif

static
void
ListNode_constructor( ListNode self, const void * params )
{
}

static
void
ListNode_destructor( ListNode self, ListNodeVtable vtab )
{
}

static
int
ListNode_copy( ListNode self, const ListNode from )
{
	/* This ListNode is not a member of any List! */
	/* Both chain pointers has been zeroed by ooc. */
	return OOC_COPY_DONE;
}

/* ListNode for general list items
 */
 
#ifndef OOC_NO_DYNAMIC_MEM

DeclareClass( _ListNodeVoidp, ListNode );

Virtuals( _ListNodeVoidp, ListNode )
EndOfVirtuals;

ClassMembers( _ListNodeVoidp, ListNode )

	void *		item;
	
EndOfClassMembers;

#define get_item_ptr(x) (((_ListNodeVoidp)x)->item)

AllocateClass( _ListNodeVoidp, ListNode  );

static
void
_ListNodeVoidp_initialize( Class this )
{
}

#ifndef OOC_NO_FINALIZE

static
void
_ListNodeVoidp_finalize( Class this )
{
}

#endif

static
void
_ListNodeVoidp_constructor( _ListNodeVoidp self, const void * params )
{
	/* Since ListNode does not require any construction, we can neglect
	 * chaining the constructor here.
	 */
}

static
void
_ListNodeVoidp_destructor( _ListNodeVoidp self, _ListNodeVoidpVtable vtab )
{
	/* We do not destroy the item, because we do not know
	 * the proper destroyer for the item here!
	 * Only List knows it, so List manages the item as well!
	 */
}

static
int
_ListNodeVoidp_copy( _ListNodeVoidp self, const _ListNodeVoidp from )
{
	return OOC_NO_COPY;
}

#endif /* OOC_NO_DYNAMIC_MEM */

/************************************************
 * List class preparation
 */

static
void
List_initialize( Class this )
{
#ifndef OOC_NO_DYNAMIC_MEM
	ooc_init_class( _ListNodeVoidp );
#endif
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
List_finalize( Class this )
{
}
#endif

/* Constructor
 */

static
void
List_constructor( List self, const void * _params )
{
	struct ListConstructorParams * params = (struct ListConstructorParams *) _params;
	
	assert( ooc_isInitialized( List ) );
	
	chain_constructor( List, self, NULL );
	
	self->destroy 		= params->destroyer;
	self->type			= params->type;
	self->list_of_nodes	= params->list_of_nodes;
	
	ooc_mutex_init( self->modify );
}

/* Destructor
 */

static
void
List_destructor( List self, ListVtable vtab )
{
	ListIterator p, next, nomore;
	
	ooc_lock( self->modify );
	
	next = self->first;
	nomore = self->first;
	
	self->first = self->last = NULL;
	
	while( next ) {
		p = next;
		next = next->next != nomore ? next->next : NULL ;
		
		#ifndef OOC_NO_DYNAMIC_MEM
			if( self->list_of_nodes )
			{
				if( self->destroy )
					self->destroy( p );
			}
			else
			{
				if( self->destroy )
					self->destroy( get_item_ptr(p) );
				ooc_delete( (Object) p );
			}
		#else
			if( self->destroy )
				self->destroy( p );
		#endif
	}
	ooc_mutex_release( self->modify );
}

/* Copy constuctor
 */

#ifndef OOC_NO_DYNAMIC_MEM
static
void
list_copy_Object_to( Object item, List target )
{
	list_append( target, ooc_duplicate( item ) );
}
#endif

static
int
List_copy( List self, const List from )
{
	struct ListConstructorParams params;

	params.destroyer	= from->destroy;
	params.type			= from->type;
	params.list_of_nodes= from->list_of_nodes;

	List_constructor( self, (void*) & params );

#ifndef OOC_NO_DYNAMIC_MEM
	if( from->type == NULL)		/* Untyped List can not be copied, since we do not know the */
		return OOC_NO_COPY;		/* copy constructor of the items */

	list_foreach( from, (list_item_executor) list_copy_Object_to, self );

	return OOC_COPY_DONE;
#else
	return OOC_NO_COPY;
#endif
}

/*	=====================================================
	List chain / unchain helpers
 */

/* typedef struct ListNodeObject * ListNode; */

static
ListNode
create_new_node( List self, void * new_item )
{
	ListNode tmp;
	
#ifndef OOC_NO_DYNAMIC_MEM

	if( self->list_of_nodes ) {
		tmp = (ListNode) new_item;
		if( tmp->next != NULL || tmp->previous != NULL )
			ooc_throw( exception_new( err_already_in_use ) );
		}
	else {
		ooc_manage( new_item, self->destroy );
		tmp = (ListNode) ooc_new( _ListNodeVoidp, NULL );
		get_item_ptr(tmp) = (void * ) ooc_pass( new_item );
		}
#else
	assert( self->list_of_nodes );
	tmp = ooc_cast( new_item, ListNode );
	if( tmp->next != NULL || tmp->previous != NULL )
		ooc_throw( exception_new( err_already_in_use ) );
#endif

	return tmp;	
}

static
ListIterator
chain_first_node( List self, ListIterator new_node ) /* List must be locked */
{
	new_node->previous = new_node->next = new_node;
	
	self->first = self->last = new_node;

	return new_node;
}

static
ListIterator
chain_before( List self, ListIterator location, ListIterator new_node ) /* List must be locked */
{
	new_node->previous 	= location->previous;
	new_node->next		= location;
	
	location->previous->next = new_node;
	location->previous	= new_node;
	
	if( location == self->first )
		self->first = new_node;
	
	return new_node;	
}

static
ListIterator
chain_after( List self, ListIterator location, ListIterator new_node ) /* List must be locked */
{
	new_node->previous 	= location;
	new_node->next		= location->next;
	
	location->next->previous = new_node;
	location->next 		= new_node;
	
	if( location == self->last )
		self->last = new_node;
	
	return new_node;
}

static
ListIterator
unchain( List self, ListIterator location ) /* List must be locked */
{
	location->previous->next = location->next;
	
	location->next->previous = location->previous;
		
	if( location == self->first && location == self->last )
		self->first = self->last = NULL;
	else {
		if( location == self->first )
			self->first = location->next;
			
		if( location == self->last )
			self->last = location->previous;
		}
				
	location->previous = location->next = NULL;
	
	return location;
}

/*	=====================================================
	Class member functions
 */

#ifndef OOC_NO_DYNAMIC_MEM

List
list_new( list_item_destroyer destroyer )
{
	struct ListConstructorParams p;
	
	p.destroyer 	= destroyer;
	p.list_of_nodes = FALSE;
	p.type 			= NULL;
	
	return ooc_new( List, & p );
}

List
_list_new_type( Class type, int manage )
{
	struct ListConstructorParams p;

	if( ! _ooc_isClassOf( type, & BaseClass ) )
		ooc_throw( exception_new( err_bad_cast ) );
		
	p.destroyer = manage ? (list_item_destroyer) ooc_delete : NULL ;
	p.type		= type;
	p.list_of_nodes = FALSE;
	
	return (List) ooc_new( List, & p );
}

List
_list_new_of_nodes( Class node, int manage )
{
	struct ListConstructorParams p;
	
	if( ! _ooc_isClassOf( node, & ListNodeClass ) )
		ooc_throw( exception_new( err_bad_cast ) );
		
	p.destroyer = manage ? (list_item_destroyer) ooc_delete : NULL ;
	p.type		= node;
	p.list_of_nodes = TRUE;
	
	return (List) ooc_new( List, & p );
}

#endif /* OOC_NO_DYNAMIC_MEM */

void
_list_use_of_nodes( void * location, Class node, int manage )
{
	struct ListConstructorParams p;
	
	if( ! _ooc_isClassOf( node, & ListNodeClass ) )
		ooc_throw( exception_new( err_bad_cast ) );
		
	p.destroyer = manage ? (list_item_destroyer) ooc_release : NULL ;
	p.type		= node;
	p.list_of_nodes = TRUE;

	ooc_use( location, List, (void *) & p );
}


ListIterator
list_append( List self, void * new_item )
{
	ListIterator	iterator; 
	ListNode		new_node;

	ooc_manage( new_item, self->destroy );
	 
	assert( ooc_isInstanceOf( self, List ) );

	if( self->type )
		ooc_check_cast( new_item, self->type );
		
	new_node = create_new_node( self, ooc_pass( new_item ) );
		
	ooc_lock( self->modify );

	if( self->last == NULL )
		iterator = chain_first_node( self, new_node );
	else
		iterator = chain_after( self, self->last, new_node );

	ooc_unlock( self->modify );

	return iterator;
}

ListIterator
list_prepend( List self, void * new_item )
{
	ListIterator iterator; 
	ListNode		new_node;

	ooc_manage( new_item, self->destroy );

	assert( ooc_isInstanceOf( self, List ) );
	 
	if( self->type )
		ooc_check_cast( new_item, self->type );
		
	new_node = create_new_node( self, ooc_pass( new_item ) );
		
	ooc_lock( self->modify );

	if( self->first == NULL )
		iterator = chain_first_node( self, new_node );
	else
		iterator = chain_before( self, self->first, new_node );	

	ooc_unlock( self->modify );

	return iterator;
}

ListIterator
list_insert_before( List self, ListIterator location, void * new_item )
{
	ListIterator iterator = NULL; 
	ListNode		new_node;

	ooc_manage( new_item, self->destroy );
	 
	assert( ooc_isInstanceOf( self, List ) );

	if( self->type )
		ooc_check_cast( new_item, self->type );
		
	new_node = create_new_node( self, ooc_pass( new_item ) );
	{
		ooc_manage_object( new_node );
		
		ooc_lock( self->modify );
	
		if( self->first == NULL )
			iterator = chain_first_node( self, ooc_pass( new_node ) );
		else 
			if( ooc_isInstanceOf( location, ListNode ) )
				iterator = chain_before( self, location, ooc_pass( new_node ) );
	
		ooc_unlock( self->modify );
	
		if( iterator == NULL )
			ooc_throw( exception_new( err_wrong_position ) );
	}

	return iterator;
}

ListIterator
list_insert_after( List self, ListIterator location, void * new_item )
{
	ListIterator iterator = NULL; 
	ListNode		new_node;

	ooc_manage( new_item, self->destroy );

	assert( ooc_isInstanceOf( self, List ) );
	
	if( self->type )
		ooc_check_cast( new_item, self->type );
		
	new_node = create_new_node( self, ooc_pass( new_item ) );
	{
		ooc_manage_object( new_node );
		
		ooc_lock( self->modify );
	
		if( self->first == NULL )
			iterator = chain_first_node( self, ooc_pass( new_node ) );
		else
			if( ooc_isInstanceOf( location, ListNode ) )
				iterator = chain_after( self, location, ooc_pass( new_node ) );
	
		ooc_unlock( self->modify );
	
		if( iterator == NULL )
			ooc_throw( exception_new( err_wrong_position ) );
	}

	return iterator;
}

STIN
void *
list_unbind_item( List self, ListNode removed_node )
{
	void *			item;

	#ifndef OOC_NO_DYNAMIC_MEM
		if( self->list_of_nodes || removed_node == NULL )
			item = removed_node;
		else {
			item = get_item_ptr( removed_node );
			ooc_delete( (Object) removed_node );
			}
	#else
		item = removed_node;
	#endif

	return item;
}

void *
list_remove_item( List self, ListIterator location )
{
	ListNode	removed_node;

	assert( ooc_isInstanceOf( self, List ) );
	
	if( !ooc_isInstanceOf( location, ListNode ) )
		ooc_throw( exception_new( err_wrong_position ) );

	ooc_lock( self->modify );

	removed_node = unchain( self, location );
	
	ooc_unlock( self->modify );

	return list_unbind_item( self, removed_node );
}

void *
list_remove_first_item( List self )
{
	ListNode	removed_node = NULL;

	assert( ooc_isInstanceOf( self, List ) );
	
	ooc_lock( self->modify );

	if( self->first )
		removed_node = unchain( self, self->first );
	
	ooc_unlock( self->modify );

	return list_unbind_item( self, removed_node );
}

void *
list_remove_last_item( List self )
{
	ListNode		removed_node = NULL;

	assert( ooc_isInstanceOf( self, List ) );
	
	ooc_lock( self->modify );

	if( self->last )
		removed_node = unchain( self, self->last );
	
	ooc_unlock( self->modify );

	return list_unbind_item( self, removed_node );
}

void
list_delete_item( List self, ListIterator location )
{
	void *	item;

	assert( ooc_isInstanceOf( self, List ) );
	
	item = list_remove_item( self, location );

	if( self->destroy )
		self->destroy( item );	
}


ListIterator
list_first( List self)
{
	assert( ooc_isInstanceOf( self, List ) );
	
	return( self->first );
}

ListIterator
list_last( List self )
{
	assert( ooc_isInstanceOf( self, List ) );
	
	return( self->last );
}	

void *
list_get_item( ListIterator node )
{
	if( ! ooc_isInstanceOf( node, ListNode ) )
		ooc_throw( exception_new( err_wrong_position ) );
	
#ifndef OOC_NO_DYNAMIC_MEM
	if( node->Base._vtab->_class == & _ListNodeVoidpClass )
		return get_item_ptr(node);
	else
#endif
		return node;
}

ListIterator
list_next( List self, ListIterator node )
{
	assert( ooc_isInstanceOf( self, List ) );
	
	if( ! ooc_isInstanceOf( node, ListNode ) )
		ooc_throw( exception_new( err_wrong_position ) );
		
	return node != self->last ? node->next : NULL ;
}

ListIterator
list_previous( List self, ListIterator node )
{
	assert( ooc_isInstanceOf( self, List ) );

	if( ! ooc_isInstanceOf( node, ListNode ) )
		ooc_throw( exception_new( err_wrong_position ) );
		
	return node != self->first ? node->previous : NULL ;
}

void
list_swap( List self, ListIterator node1, ListIterator node2 )
{
	assert( ooc_isInstanceOf( self, List ) );

	if( ! ooc_isInstanceOf( node1, ListNode ) || ! ooc_isInstanceOf( node2, ListNode ) )
		ooc_throw( exception_new( err_wrong_position ) );
	
	if( node1 == node2 )
		return;
		
	ooc_lock( self->modify );

#ifndef OOC_NO_DYNAMIC_MEM	
	if( self->list_of_nodes )
#endif
	{ /* http://ptspts.blogspot.com/2010/01/how-to-swap-two-nodes-in-doubly-linked.html */
		ListIterator tmp;
	
		tmp = node1->next;
		node1->next = node2->next;
		node2->next = tmp;
		node1->next->previous = node1;
		node2->next->previous = node2;

		tmp = node1->previous;
		node1->previous = node2->previous;
		node2->previous = tmp;
		node1->previous->next = node1;
		node2->previous->next = node2;
		
		if( self->first == node1 )
			self->first = node2;
		else if ( self->first == node2 )
			self->first = node1;
	
		if( self->last == node1 )
			self->last = node2;
		else if ( self->last == node2 )
			self->last = node1;
	}
#ifndef OOC_NO_DYNAMIC_MEM	
	else
	{
		void * tmp;
		tmp = ((_ListNodeVoidp) node1 )->item;
		((_ListNodeVoidp) node1 )->item = ((_ListNodeVoidp) node2 )->item;
		((_ListNodeVoidp) node2 )->item = tmp;
	}
#endif

	ooc_unlock( self->modify );
}

void
list_foreach( List self, list_item_executor func, void * param )
{
	ListIterator p;
	
	assert( ooc_isInstanceOf( self, List ) );

	for( p = self->first; p; p = ( p != self->last ) ? p->next : NULL ) 
		func( list_get_item( p ), param ); 
}

ListIterator
list_foreach_until_true( List self, ListIterator from, list_item_checker func, void * param )
{
	ListIterator p;
	
	assert( ooc_isInstanceOf( self, List ) );
	
	for( p = from ? from : self->first; p; p = ( p != self->last ) ? p->next : NULL )
		if( func( list_get_item( p ), param ) )
			break;
			 
	return p;
}

void
list_foreach_delete_if( List self, list_item_checker func, void * param )
{
	ListIterator act, next;
	
	assert( ooc_isInstanceOf( self, List ) );

	next = list_first( self );
	
	while ( ( act = next ) ) {

		next = list_next( self, act );

		if( func( list_get_item( act ), param ) )
			list_delete_item( self, act );
		}
}


ListIterator
list_find_item( List self, ListIterator from, list_item_checker fn_match, void * param )
{
	ListIterator p;
	
	assert( ooc_isInstanceOf( self, List ) );

	for( p = from ? from : self->first; p; p = ( p != self->last ) ? p->next : NULL )
		if( fn_match( list_get_item( p ), param ) )
			break;
			
	return p;
}

ListIterator
list_find_item_reverse(  List self, ListIterator from, list_item_checker fn_match, void * param )
{
	ListIterator p;
	
	assert( ooc_isInstanceOf( self, List ) );

	for( p = from ? from : self->last; p; p = ( p != self->first ) ? p->previous : NULL )
		if( fn_match( list_get_item( p ), param ) )
			break;
			
	return p;
}

Class
list_get_type( List self )
{
	assert( ooc_isInstanceOf( self, List ) );

	return self->type;
}

int
list_get_managed( List self )
{
	assert( ooc_isInstanceOf( self, List ) );

	return self->destroy != NULL;
}

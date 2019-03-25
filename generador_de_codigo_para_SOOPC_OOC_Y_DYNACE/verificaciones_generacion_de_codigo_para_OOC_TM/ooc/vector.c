/*
 * vector.c
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

#include "vector.h"
#include "implement/vector.h"

/** @class Vector
 *  @brief Vector class - a standard ooc container.
 * 	@see vector.h
 */

/** @file vector.h
 * @brief Vector class - a standard ooc container.
 * Vector is a container class, that can hold pointers to any kind of data.
 * Every item stored in the list must work perfectly with the supplied list item destroyer!
 * In practice this means, that you can only store items in the vector that has the same 
 * deletion method.
 * There are two types of Vector: typed and non-typed vector. Typed Vector can hold items
 * of a given type or its subtype only, while non-typed Vector can hold any type of data,
 * that conforms to the supplied object destructor. 
 * When creating a Vector, a given amount of space, the chunk size (n*sizeof(void*)) is allocated.
 * If the Vector grows above this size, the Vector automatically reallocates the store, increasing
 * by the chunk size.
 * @note	Vector implementation is thread safe, in the manner, that adding to or deleting items from the Vector
 * 			will not mesh up the Vector. But the VectorIndices may become invalid if multiple threads modify the
 * 			same Vector object. As a consecvence the @c _foreach_ and @c _find_ methods may behave unexpectedly
 * 			if an other thread is modifying the Vector! Make your own locking if needed! 
 *          The same applies to the ooc_duplicate() method for Vector (uses vector_foreach() internally)!
 */

#include <string.h>

/* Allocating the class description table and the vtable
 */

AllocateClass( Vector, Base );

 
/************************************************
 * List class preparation
 */

static
void
Vector_initialize( Class this )
{
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE

static
void
Vector_finalize( Class this )
{
}

#endif

/* Constructor
 */

static
void
Vector_constructor( Vector self, const void * params )
{
	struct VectorConstructorParams const * p = params;
	
	assert( ooc_isInitialized( Vector ) );
	
	chain_constructor( Vector, self, params );
	
	ooc_mutex_init( self->modify );
	
	self->allocated = p->size;
	self->destroy = p->destroy;
	self->type = p->type;
	
	#ifndef OOC_NO_DYNAMIC_MEM

	self->allocation_chunks	= p->size;
	
	self->items = ooc_malloc( self->allocated * sizeof(VectorItem) );

	#else

	self->items = p->store;

	#endif
}

/* Destructor
 */

static
void
Vector_destructor( Vector self, VectorVtable vtab )
{
	VectorIndex i;
	
	ooc_lock( self->modify );
	
	if( self->destroy )
		for( i = 0; i < self->number_of_items; i++ )
			self->destroy( self->items[ i ] );
		
	#ifndef OOC_NO_DYNAMIC_MEM

	ooc_free_and_null( (void **) & self->items );

	#else

	self->items = NULL;

	#endif
	
	ooc_mutex_release( self->modify );
}

/* Copy constuctor
 */

static
int
Vector_copy( Vector self, const Vector from )
{
#ifndef OOC_NO_DYNAMIC_MEM

	VectorIndex i;

	ooc_mutex_init( self->modify );

	if( from->type == NULL )		/* Untyped Vector can not be copied, since we do not know the */
		return OOC_NO_COPY;			/* copy constructor of the items */

	self->type				= from->type;
	self->destroy			= from->destroy;
	self->allocation_chunks	= from->allocation_chunks;

	self->allocated			= from->allocated;
	self->items 			= ooc_malloc( self->allocated * sizeof(VectorItem) );

	for( i=0; i < from->number_of_items; i++ ) {
		self->items[i] = ooc_duplicate( (Object) from->items[i] );
		++self->number_of_items;
		}

	return OOC_COPY_DONE;

#else
	return OOC_NO_COPY;
#endif
}

/*	=====================================================
	Class member functions
 */

#ifndef OOC_NO_DYNAMIC_MEM

Vector
vector_new( VectorIndex size, vector_item_destroyer destroy )
{
	struct VectorConstructorParams p;
	
	p.size = size;
	p.destroy = destroy;
	p.type = NULL;
	
	return (Vector) ooc_new( Vector, & p );
}

Vector
_vector_new_type( VectorIndex size, Class type, int manage )
{
	struct VectorConstructorParams p;
	
	if( ! _ooc_isClassOf( type, & BaseClass ) )
		ooc_throw( exception_new( err_bad_cast ) );
	
	p.size = size;
	p.type = type;
	if( manage )
		p.destroy = (vector_item_destroyer) ooc_delete;
	else
		p.destroy = NULL;
	
	return (Vector) ooc_new( Vector, & p );
}

Vector
vector_new_from_table( void * table, size_t record_size, VectorIndex num_of_records )
{
	Vector vector;
	char * tp;
	VectorIndex counter;
	struct VectorConstructorParams p;
	
	p.size = num_of_records;
	p.destroy = NULL;
	p.type = NULL;
	
	vector = (Vector) ooc_new( Vector, & p );
	
	for( tp = table, counter = 0; counter < num_of_records; counter++, tp += record_size )
		vector->items[ counter ] = tp;
	
	vector->number_of_items = num_of_records;
		
	return vector;
}

#else /* OOC_NO_DYNAMIC_MEM defined */

void
vector_use_with_store( Vector vector, VectorIndex size, vector_item_destroyer destroy, VectorItem store[] )
{
	struct VectorConstructorParams p;
	
	p.size = size;
	p.destroy = destroy;
	p.type = NULL;
	p.store = store;
	
	ooc_use( vector, Vector, (void*) & p );
}

void
_vector_use_type_with_store( Vector vector, VectorIndex size, Class type, int manage, VectorItem store[] )
{
	struct VectorConstructorParams p;
	
	if( ! _ooc_isClassOf( type, & BaseClass ) )
		ooc_throw( exception_new( err_bad_cast ) );
	
	p.size = size;
	p.type = type;
	if( manage )
		p.destroy = (vector_item_destroyer) ooc_release;
	else
		p.destroy = NULL;
	
	p.store = store;
	
	ooc_use( vector, Vector, (void*) & p );
}

#endif /* OOC_NO_DYNAMIC_MEM */

static
void
vector_realloc_if_needed( Vector self )
{
	if( self->number_of_items == self->allocated ) {
		
		#ifndef OOC_NO_DYNAMIC_MEM

		self->allocated += self->allocation_chunks;
		self->items = ooc_realloc( self->items, self->allocated * sizeof(VectorItem) );

		#else

		ooc_throw( exception_new( err_out_of_memory ) );

		#endif
		}
}

VectorIndex
vector_push_back( Vector self, void * data )
{
	ooc_manage( data, self->destroy );
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->type )
		ooc_check_cast( data, self->type );
	
	ooc_lock( self->modify );
	
	vector_realloc_if_needed( self );
	
	self->items[ self->number_of_items ++ ] = ooc_pass( data );
	
	ooc_unlock( self->modify );
	
	return self->number_of_items - 1;
}

VectorIndex
vector_insert( Vector self, VectorIndex position, void * data )
{
	ooc_manage( data, self->destroy );
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->type )
		ooc_check_cast( data, self->type );
	
	if( self->number_of_items < position )
		ooc_throw( exception_new( err_wrong_position ) );	
	
	ooc_lock( self->modify );
	
	vector_realloc_if_needed( self );
	
	if( position != self->number_of_items )
		memmove((GEN_PTR) & ( self->items[ position + 1 ] ), 					/* destination */
				(GEN_PTR) & ( self->items[ position ] ),						/* source */
				( self->number_of_items - position ) * sizeof( VectorItem ) );	/* len */
	
	self->items[ position ] = ooc_pass( data );
	
	self->number_of_items ++;
	
	ooc_unlock( self->modify );
	
	return position;
}

void
vector_delete_item( Vector self, VectorIndex position )
{
	VectorItem tmp;
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->number_of_items <= position )
		ooc_throw( exception_new( err_wrong_position ) );	
	
	ooc_lock( self->modify );
	
	tmp = self->items[ position ];
	
	if( position != self->number_of_items-1 )
		memmove((GEN_PTR) & ( self->items[ position ] ), 								/* destination */
				(GEN_PTR) & ( self->items[ position + 1 ] ),							/* source */
				( self->number_of_items - (position + 1) ) * sizeof( VectorItem ) );	/* len */
	
	self->number_of_items --;
	
	ooc_unlock( self->modify );
	
	if( self->destroy )
		self->destroy( tmp );
}

VectorIndex
vector_items( Vector self )
{
	assert( ooc_isInstanceOf( self, Vector ) );
	
	return self->number_of_items;
}

void *
vector_get_item( Vector self, VectorIndex index )
{
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->number_of_items <= index )
		ooc_throw( exception_new( err_wrong_position ) );
		
	return self->items [ index ];
}

void
vector_set_item( Vector self, VectorIndex index, void * data )
{
	void * tmp;
	
	ooc_manage( data, self->destroy );
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->type )
		ooc_check_cast( data, self->type );
	
	if( self->number_of_items <= index )
		ooc_throw( exception_new( err_wrong_position ) );
		
	ooc_lock( self->modify );
	
	tmp = self->items [ index ];
	
	self->items [ index ]	=	ooc_pass( data );
	
	ooc_unlock( self->modify );
	
	if( self->destroy )
		self->destroy( tmp );
}

void
vector_swap( Vector self, VectorIndex p1, VectorIndex p2 )
{
	VectorItem tmp;
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->number_of_items <= p1 || self->number_of_items <= p2 )
		ooc_throw( exception_new( err_wrong_position ) );
		
	ooc_lock( self->modify );
	
	tmp 				= self->items[ p1 ];
	self->items[ p1 ] 	= self->items[ p2 ];
	self->items[ p2 ]	= tmp;

	ooc_unlock( self->modify );	
}

void
vector_foreach( Vector self, vector_item_executor execute, void * param )
{
	VectorIndex index;
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	for( index = 0; index < self->number_of_items; index++ )
		execute( self->items[ index ], param );
}

VectorIndex
vector_foreach_until_true( Vector self, vector_item_checker match, void * param )
{
	VectorIndex index;
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	for( index = 0; index < self->number_of_items; index++ )
		if( match( self->items[ index ], param ) )
			break;
	
	return index;
}

VectorIndex
vector_find_item( Vector self, VectorIndex from, vector_item_checker match, void * param )
{
	VectorIndex index;
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->number_of_items <= from )
		ooc_throw( exception_new( err_wrong_position ) );

	for( index = from; index < self->number_of_items; index++ )
		if( match( self->items[ index ], param ) )
			break;
	
	return index;
}

VectorIndex
vector_find_item_reverse( Vector self, VectorIndex from, vector_item_checker match, void * param )
{
	VectorIndex index;
	
	assert( ooc_isInstanceOf( self, Vector ) );
	
	if( self->number_of_items <= from )
		ooc_throw( exception_new( err_wrong_position ) );

	for( index = from + 1; index != 0; index-- )
		if( match( self->items[ index - 1 ], param ) )
			break;
	
	return index != 0 ? index - 1 : self->number_of_items;
}

Class
vector_get_type( Vector self )
{
	assert( ooc_isInstanceOf( self, Vector ) );

	return self->type;
}

int
vector_get_managed( Vector self )
{
	assert( ooc_isInstanceOf( self, Vector ) );

	return self->destroy != NULL ? OOC_MANAGE : !OOC_MANAGE;
}

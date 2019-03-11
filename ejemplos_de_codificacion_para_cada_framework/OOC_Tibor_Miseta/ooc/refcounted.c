/*
 * refcounted.c
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

/* This is a class implementation file for the RefCounted class
 */

#include "refcounted.h"
#include "implement/refcounted.h"

/** @class RefCounted
 *  @brief RefCounted class - a reference counted Object.
 * 	@see refcounted.h
 */

/** @file refcounted.h
 * @brief RefCounted class - a reference counted Object.
 * RefCounted serves as a base class for reference counted Objects.
 * @note The initial value for the counter is one.
 * @warning RefCounted overrides the delete operator: do not override the delete operator
 * for inherited classes!
 * @warning Current implementation of RefCounted is not thread safe.
 */ 

/* Allocating the class description table and the vtable
 */

AllocateClass( RefCounted, Base );

/* The overridden destroy operator
 */
 
static
int
RefCounted_destroy_check( RefCounted self )
{
	int to_be_destroyed = FALSE;
	
	ooc_lock( self->access );
	if( self->counter != 0 )
		--self->counter;
	to_be_destroyed = ( self->counter == 0 );
	ooc_unlock( self->access );
	
	return to_be_destroyed;
}


/* Class initializing
 */

static
void
RefCounted_initialize( Class this )
{
	/* Overriding the destroy_check operator */
	assert( this->c.vtable->_destroy_check == NULL );

	this->c.vtable->_destroy_check = (int (*)(Object)) RefCounted_destroy_check;
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
RefCounted_finalize( Class this )
{
}
#endif

/* Constructor
 */

static
void
RefCounted_constructor( RefCounted self, const void * params )
{
	assert( ooc_isInitialized( RefCounted ) );
	
	chain_constructor( RefCounted, self, NULL );
	
    self->counter = 1;
    ooc_mutex_init( self->access );
}

/* Destructor
 */

static
void
RefCounted_destructor( RefCounted self, RefCountedVtable vtab )
{
   ooc_mutex_release( self->access );
}

/* Copy constuctor
 */

static
int
RefCounted_copy( RefCounted self, const RefCounted from )
{
    self->counter = 1;  				/* The new object has a new counter as well */
    ooc_mutex_init( self->access );
    
    return OOC_COPY_DONE;
}

/*	=====================================================
	Class member functions
 */

RefCounted
refcnt_addref( RefCounted self )
{
	assert( ooc_isInstanceOf( self, RefCounted ) );
	
	ooc_lock( self->access );
	self->counter ++;
	ooc_unlock( self->access );
	
	return self;
}

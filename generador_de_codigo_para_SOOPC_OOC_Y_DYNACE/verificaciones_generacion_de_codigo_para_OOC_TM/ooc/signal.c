/*
 * signal.c
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
#include "list.h"
#include "implement/list.h"

#include "signal.h"

/** @class Signal
 *  @brief Signal class - an ooc signal / slot mechanism.
 * 	@see signal.h
 */

/** @file signal.h 
 *  @brief Signal class - an ooc signal / slot mechanism.
 * A signal / slot mechanism implemented for the ooc object manager.
  */ 

/* This is a class implementation file
 */
 
DeclareClass( SignalItem, ListNode );

/* Virtual function definitions
 */

Virtuals( SignalItem, ListNode )

EndOfVirtuals;

/* Class members
 */
 
ClassMembers( SignalItem, ListNode )

	void *			source;
	void *			target;
	SignalHandler	handler;
	
EndOfClassMembers;


/* Allocating the class description table and the vtable
 */

AllocateClass( SignalItem, ListNode );

/* Class virtual function prototypes
 */

/* Class initializing
 */

static
void
SignalItem_initialize( Class this )
{
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE
static
void
SignalItem_finalize( Class this )
{
}
#endif


/* Constructor
 */

static
void
SignalItem_constructor( SignalItem self, const void * params )
{
	assert( ooc_isInitialized( SignalItem ) );
	
	chain_constructor( SignalItem, self, NULL );

}

/* Destructor
 */

static
void
SignalItem_destructor( SignalItem self, SignalItemVtable vtab )
{
}

/* Copy constuctor
 */

static
int
SignalItem_copy( SignalItem self, const SignalItem from )
{
	return OOC_COPY_DEFAULT;
}

static
int
signalitem_compare( SignalItem self, const SignalItem other )
{
	return	( 	( self->source == other->source )
			&&	( self->target == other->target )
			&&	( self->handler == other->handler ) );
}

/* Signal Queue
 */

DeclareClass( SignalQueued, ListNode );

ClassMembers( SignalQueued, ListNode )

	Signal			emitted_signal;
	void *			parameter;				/* managed by SignalQueued! */
	void_fn_voidp	param_destroyer;
	
	int				invalid;				/* Signal in the queue became invalid, should not be emitted. */

#ifndef OOC_NO_THREADS
	ooc_Mutex		processing;
#endif
	
EndOfClassMembers;

Virtuals( SignalQueued, ListNode )
EndOfVirtuals;

AllocateClass( SignalQueued, ListNode );

static	void	SignalQueued_initialize( Class this ) {}
#ifndef OOC_NO_FINALIZE
static	void	SignalQueued_finalize( Class this ) {}
#endif

static
void
SignalQueued_constructor( SignalQueued self, const void * params )
{
	ooc_mutex_init( self->processing );
}

static
void
SignalQueued_destructor( SignalQueued self, SignalQueuedVtable vtab )
{
	if( self->param_destroyer && self->parameter )
		self->param_destroyer( ooc_ptr_read_and_null( & self->parameter ) );
		
	ooc_mutex_release( self->processing );
}

static	int		SignalQueued_copy( SignalQueued self, const SignalQueued from ) { return OOC_NO_COPY; }

static	List		signal_queue	= 	NULL; 	/* List of SignalQueued pointers */

#ifndef OOC_NO_THREADS
static	ooc_Mutex	signal_queue_critical_section;
#endif

/* Signal register
 */
 
static 	List 	signal_register =	NULL; 	/* List of Signal * pointers */

/* Signal class
 */
 
ClassMembers( Signal, List )

	Object		owner;

EndOfClassMembers;

AllocateClass( Signal, List );

/* Class initializing
 */

static
void
Signal_initialize( Class this )
{
	ooc_init_class( List );
	ooc_init_class( SignalItem );
	ooc_init_class( SignalQueued );
	
	signal_queue 	= list_new_of_nodes( SignalQueued, TRUE );
	signal_register = list_new( ( list_item_destroyer ) ooc_delete_and_null );
	
	ooc_mutex_init( signal_queue_critical_section );
}

/* Class finalizing
 */

#ifndef OOC_NO_FINALIZE

static
void
Signal_finalize( Class this )
{
	ooc_delete_and_null( (Object *) & signal_queue );
	ooc_delete_and_null( (Object *) & signal_register );
	
	ooc_mutex_release( signal_queue_critical_section );
	
}

#endif

/* Constructor
 */

static
void
Signal_constructor( Signal self, const void * params )
{
	struct ListConstructorParams p;
	
	assert( ooc_isInitialized( Signal ) );
	
	self->owner = (Object) params;
	
	p.destroyer = (list_item_destroyer) ooc_delete;
	p.type		= & SignalItemClass;
	p.list_of_nodes = TRUE;
	
	chain_constructor( Signal, self, & p );  /* Parent is a List of SignalItems */
}

/* Destructor
 */

static
void
Signal_destructor( Signal self, SignalVtable vtab )
{
}

/* Copy constuctor
 */

static
int
Signal_copy( Signal self, const Signal from )
{
	return OOC_COPY_DEFAULT;
}

/**	Emits a signal asynchronuosly. 
 * Asynchronuos signal emittion means, that the signal_emit() function returns immadiately, and the signal is buffered in the signal queue.
 * Signal is executed when the main eventloop reaches the signal emittion section.
 * @param signal 			The signal that must be emitted.
 * @param parameter 		The parameter to be passed to the connected signal handler. The signaling system takes over the ownership of this 
 * 							memory block or Object if param_destroy_fn != NULL, so you must not destroy it!
 * @param param_destroy_fn	The destroy function for freeing up the memory occupied by the parameter. The signalimg system automatically destroys
 * 							the parameter when all connected signal handler has been executed.
 * 							For constant parameters you should pass NULL (no demolition is required at the end).
 * @see signal_emit_sync()
 */

void
signal_emit( Signal signal, void * parameter, ooc_destroyer param_destroy_fn )
{
	if( signal ) {
		SignalQueued sq;
		
		ooc_manage( parameter, param_destroy_fn ); 

		assert( ooc_isInstanceOf( signal, Signal ) );
		
		sq = ooc_new( SignalQueued, NULL );
		
		sq->emitted_signal 	= signal;
		sq->parameter	  	= ooc_pass( parameter );
		sq->param_destroyer	= param_destroy_fn;
		
		list_append( signal_queue, sq );
		}
	else if( param_destroy_fn && parameter )
		param_destroy_fn( parameter );
}

static
int
signal_queue_process_item( SignalQueued sq )
{
	try {
		ooc_lock( sq->processing );
			
		if( ! sq->invalid )
			signal_emit_sync( sq->emitted_signal, sq->parameter, NULL );
		}
	finally {
		sq->invalid = TRUE; /* Signal has been already fired, no other threads can do it again. */
		ooc_unlock( sq->processing );
		}
	end_try;
	
	return TRUE; /* delete this item from the queue */
}

/**	Processes all asynchronously emitted signals.
 * Must be called from the eventloop. Processes all buffered async signals.
 * @warning	The async signals emitted by the called handlers will be executed as well before return.
 * @note	The signals are processed in a single thread.
 * @warning This is a blocking operation! Only one thread is used for emitting the signals. If an other thread 
 * 			attempts to call signal_process_signals() parallely then that thread will be blocked.
 * @note	If you want to process the signals in threads, use signal_process_next() instead. 
 */
  
void
signal_process_signals( void )
{
	assert( ooc_isInstanceOf( signal_queue, List ) );

	try {
		ooc_lock( signal_queue_critical_section );
	
		list_foreach_delete_if( signal_queue, (list_item_checker) signal_queue_process_item, NULL );
		}
	finally {
		ooc_unlock( signal_queue_critical_section );
		}
	end_try;
	
}

/**	Processes the next asynchronously emitted signals.
 * Must be called from the eventloop. Processes the next buffered async signal in the signal queue.
 * Only one emitted signal is processed.
 * @return	TRUE is signal was processed, FALSE if there was no signal in the queue.
 * @note	This opeartion is thread safe, can be called parallely.
 * @see		signal_process_signals() 
 */
  
int
signal_process_next( void )
{
	SignalQueued volatile sq = NULL;
		
	assert( ooc_isInstanceOf( signal_queue, List ) );

	try {
		sq = list_remove_first_item( signal_queue );
	
		if( sq && !sq->invalid )
			signal_emit_sync( sq->emitted_signal, sq->parameter, NULL );
		
		}
	finally {
		ooc_delete( (Object) sq );
		}
	end_try;
	
	return ( sq != NULL );
}

static
int
signal_register_comparator( Signal * self, Signal * other )
{
	return ( self == other );	
}

static
void
signal_register_signal( Signal * signal_p )
{
	assert( signal_p );
	assert( ooc_isInstanceOf( * signal_p, Signal ) );
	assert( ooc_isInstanceOf( signal_register, List ) );
	
	if( ! list_find_item( signal_register, NULL, (list_item_checker) signal_register_comparator, signal_p ) )
		list_append( signal_register, signal_p );
}

static
int
signalitem_is_targeting( SignalItem self, Object target )
{
	assert( ooc_isInstanceOf( self, SignalItem ) );
	
	return ( self->target == target );
}

static
void
signal_register_disconnect_target( Signal * signal_p, Object target )
{
	assert( signal_p );
	assert( ooc_isInstanceOf( * signal_p, Signal ) );
	
	list_foreach_delete_if( (List) * signal_p, (list_item_checker) signalitem_is_targeting, target );
}

static
int
signal_is_hold_by( Signal * signal_p, Object holder )
{
	assert( signal_p );
	assert( ooc_isInstanceOf( * signal_p, Signal ) );
	
	return ( (* signal_p)->owner == holder );
}

static
void
signal_queued_invalidate_if_hold_by( SignalQueued sq, Object holder )
{
	ooc_lock( sq->processing );
	
	if( signal_is_hold_by( & sq->emitted_signal, holder ) )
		sq->invalid = TRUE;
		
	ooc_unlock( sq->processing );
}

/** Object destroy notifier for the signaling system.
 * Every Object that can be signal source or a signal target, must call this notifier in their destructor.
 * This notifier disconnects all signals that are related to the Object under destruction.
 * @param	object	The Object that is being deleted.
 */
 
void
signal_destroy_notify( Object object )
{
	assert( ooc_isInstanceOf( signal_register, List ) );
	assert( ooc_isInstanceOf( signal_queue, List ) );
	
	/* invalidate all signals in the queue that are held by this object */
	list_foreach( signal_queue, (list_item_executor) signal_queued_invalidate_if_hold_by, object );
	
	/* disconnects all signals, that targets this object */
	list_foreach( signal_register, (list_item_executor) signal_register_disconnect_target, object );
	
	/* delete all signals from signal_register, that are held by this object */
	list_foreach_delete_if( signal_register, (list_item_checker) signal_is_hold_by, object );
}



/*	=====================================================
	Class member functions
 */
 
 /**
  * @typedef typedef void ( * SignalHandler )( void * target, void * source, void * param )
  * @brief	Signal handler prototype.
  * 		The signal handler is a function that has three parameters.
  * 		In Object oriented manner it is a member function of the target object.
  * @param	target		The Object that has been assigned to the handler.
  * @param 	source		The source Object that has activated the signal.
  * @param	param		The parameter the has been passed at the time of signal emittion.
  * @see signal_connect(), signal_emit(), signal_emit_sync()
  * @warning	The signal handler can throw an exception, but this exception will not be propagated! The signal emittion routines will return
  * 		as if everything went normal. 
  */

/** Connects a signal to a signal handler.
 * The connected signal handler will be executed when the signal is emitted.
 * @param	source		The source Object of the signal (the Object that holds the Signal as a member).
 * @param	getter		The getter function, that returns address of the Signal of the source Object.
 * @param	target		The target Object (the object that is passed as the first parameter of the signal handler).
 * @param	handler		The signal handler.
 * @see	signal_disconnect()
 * @note	Multiple handlers can be connected to a signal, they are called in the order of connections in the case of signal emittion.
 * @note	For user's convenience there is no new operator for Signals!
 * 			No need to create new signals, just connect them. Never call ooc_new( Signal, NULL )!;
 */
 
void
signal_connect( void * source, SignalPGetter getter, void * target, SignalHandler handler )
{
	Signal * signal_p;
	SignalItem	si;
	
	assert( getter != NULL );
	
	signal_p = getter( source );
	
	if( * signal_p == NULL )
		* signal_p = ooc_new( Signal, source );
	
	assert( ooc_isInstanceOf( *signal_p, Signal ) );
	
	if( (*signal_p)->owner != source )
		ooc_throw( exception_new( err_bad_connect ) );
	
	si = ooc_new( SignalItem, NULL );
	
	si->source	= source;
	si->target	= target;
	si->handler	= handler;
	
	list_append( (List) *signal_p, si );
	
	signal_register_signal( signal_p );
}

/** Disconnects a signal handler from a signal.
 * The connected signal handler will be disconnected.
 * @param	source		The source Object of the signal.
 * @param	getter		The getter function, that returns address of the Signal of the source Object.
 * @param	target		The target Object.
 * @param	handler		The signal handler.
 * @see	signal_connect()
 * @note	If the same signal handler was connected multiple times to the same source and target
 * 			objects (meaningless but possible) only the first one will be disconnected!
 * @warning	Already buffered async emitted signals will be executed even if they have been disconnected!
 */
 
void
signal_disconnect( void * source, SignalPGetter getter, void * target, SignalHandler handler )
{
	struct SignalItemObject si;
	ListIterator found;
	Signal * signal_p;
	
	assert( getter != NULL );

	signal_p = getter( source );
	
	if( *signal_p ) {
		
		assert( ooc_isInstanceOf( *signal_p, Signal ) );
		
		ooc_use( & si, SignalItem, NULL );
		
		si.source	= source;
		si.target	= target;
		si.handler	= handler;
		
		found = list_find_item( (List) *signal_p, NULL, (list_item_checker) signalitem_compare, & si );
		
		if( found )
			list_delete_item( (List) *signal_p, found );
		}
}


static
void
signalitem_emit_sync( SignalItem self, void * param )
{
	assert( ooc_isInstanceOf( self, SignalItem ) );
	
	try
		self->handler( self->target, self->source, param );
	catch_any;
	end_try;
}

/**	Emits a signal synchronously. 
 * Synchronous signal emittion means, that the signal handlers are called immediately, and the signal_emit_sync() function returns only,
 * when all connected signal handlers has been executed.
 * @param signal 			The signal that must be emitted.
 * @param parameter 		The parameter to be passed to the connected signal handler. The signaling system takes over the ownership of this 
 * 							memory block or Object if param_destroy_fn != NULL, so you must not destroy it!
 * @param param_destroy_fn	The destroy function for freeing up the memory occupied by the parameter. The signalimg system automatically destroys
 * 							the parameter when all connected signal handler has been executed.
 * 							For constant parameters you should pass NULL (no demolition is required at the end).
 * 							If you would like to take care of the lifecycle of the parameter object instaed of the signaling system
 * 							then you can pass NULL as well.
 * @see signal_emit()
 */

void
signal_emit_sync( Signal signal, void * parameter, ooc_destroyer param_destroy_fn )
{
	if( signal ) {
		
		assert( ooc_isInstanceOf( signal, Signal ) );
		
		list_foreach( (List) signal, (list_item_executor) signalitem_emit_sync, parameter );
		}
	
	if( param_destroy_fn && parameter )
		param_destroy_fn( parameter );
}

/** @file signal.h 
@details
The use of the Signal class is optimized for the user's convenience, therefore it is a bit different from other ooc classes.
There are some rules that must be considered using Signals.
The signaling system must be initilaized at the start and released at the end of your application.
@code
int main( int argc, char argv[] )
{
	ooc_init_class( Signal );

	...  Your staff here 

	ooc_finalize_all();
	return 0;
}
@endcode

@todo		Desrcibing the use of the signaling system

@note	Signal implementation is thread safe. Any thread can emit a signal at any time.
		However the initialization of the Signal class must be done before any fork in the program.

@see	signal_process_signals() for blocking behavior!

 */ 

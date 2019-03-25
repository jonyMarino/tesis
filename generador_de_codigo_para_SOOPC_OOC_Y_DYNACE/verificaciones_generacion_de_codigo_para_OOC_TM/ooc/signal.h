/*
 * signal.h
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


#ifndef SIGNAL_H_
#define SIGNAL_H_

#include "list.h"

DeclareClass( Signal, List );

Virtuals( Signal, List )

EndOfVirtuals;

typedef void ( * SignalHandler )( void * target, void * source, void * param );
typedef Signal * (* SignalPGetter) ( void * source );


void		signal_connect( void * source, SignalPGetter getter, void * target, SignalHandler handler );

void 		signal_disconnect( void * source, SignalPGetter getter, void * target, SignalHandler handler );

void		signal_emit( Signal, void * parameter, ooc_destroyer param_destroy_fn );
void		signal_emit_sync( Signal, void * parameter, ooc_destroyer param_destroy_fn );

void		signal_destroy_notify( Object object );

void		signal_process_signals( void );
int			signal_process_next( void );

#endif /*SIGNAL_H_*/

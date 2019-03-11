/*
 * refcounted.h
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


#ifndef REFCOUNTED_H_
#define REFCOUNTED_H_

#include "ooc.h"

DeclareClass( RefCounted, Base );

/*   Class methods
 */

/** Increments the reference counter.
 * @param	object	The Object to be counted.
 * @return	The object.
 * @note	To decrement the reference counter, simply ooc_delete() the object.
 * ooc_delete() decrements the counter, and does not delete it until zero.
 * The last ooc_delete will destroy the object.
 * @see refcnt_inc()
 */
  
RefCounted refcnt_addref( RefCounted object );

/** Increments the reference counter.
 * This is a macro version, which is more convenient since there is no need
 * for manual type casting.
 * @param	object	The Object to be counted.
 * @return	The object.
 * @see refcnt_addref()
 * @warning	Pass a pure Object pointer only! This macro has a side effect otherwise!
 * (e.g. passing a function as a parameter that returns the object is called twice!) 
 */
 
#define refcnt_inc( object ) ( refcnt_addref( (RefCounted) object ), object )

Virtuals( RefCounted, Base )

	/* No virtuals */

EndOfVirtuals;

#endif /*REFCOUNTED_H_*/

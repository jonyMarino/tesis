/*
 * implement/vector.h
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

#ifndef IMPL_VECTOR_H_
#define IMPL_VECTOR_H_

#ifndef VECTOR_H_
#error Do #include "vector.h" right before #include "implement/vector.h"
#endif

/*   Protected class members
 */
 
typedef void * VectorItem;
 
ClassMembers( Vector, Base )

	VectorIndex		allocated;
	VectorItem *	items;
	VectorIndex		number_of_items;
	
	Class					type;
	vector_item_destroyer	destroy;
	
#ifndef OOC_NO_DYNAMIC_MEM
	VectorIndex		allocation_chunks;
#endif

#ifndef OOC_NO_THREADS
	ooc_Mutex		modify;
#endif

EndOfClassMembers;

/* Protected virtuals
 */

Virtuals( Vector, Base )
EndOfVirtuals;

/* Constructor parameters
 */

struct
VectorConstructorParams
{
	VectorIndex				size;
	vector_item_destroyer	destroy;
	Class					type;
	#ifdef OOC_NO_DYNAMIC_MEM
	VectorItem *			store;
	#endif
};



#endif /*IMPL_VECTOR_H_*/


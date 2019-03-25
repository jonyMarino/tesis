/*
 * implement/list.h
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

#ifndef IMPL_LIST_H_
#define IMPL_LIST_H_

#ifndef LIST_H_
#error Do #include "list.h" right before #include "implement/list.h"
#endif

/*   Private class members
 */
 
ClassMembers( List, Base )

    ListIterator		first;
    ListIterator		last;
    
    int					list_of_nodes;
    Class				type;
    list_item_destroyer	destroy;
    
#ifndef OOC_NO_THREADS
	ooc_Mutex			modify;
#endif

EndOfClassMembers;

ClassMembers( ListNode, Base )

	ListNode		next;
	ListNode		previous;

EndOfClassMembers;

struct
ListConstructorParams
{
	list_item_destroyer		destroyer;
	Class					type;
	int						list_of_nodes;
};


#endif /*IMPL_LIST_H_*/


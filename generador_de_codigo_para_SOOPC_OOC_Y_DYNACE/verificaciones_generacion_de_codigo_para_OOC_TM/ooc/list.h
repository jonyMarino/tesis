/*
 * list.h
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

#ifndef LIST_H_
#define LIST_H_

#include "ooc.h"

/** List class declaration
*/

DeclareClass( List, Base );
 
Virtuals( List, Base )
EndOfVirtuals;

DeclareClass( ListNode, Base );

Virtuals( ListNode, Base )
EndOfVirtuals;


/** List iterator.
 * This iterator can be used as an identifier of a list node in the list.
 * @note This is not idenctical to the item stored in the list!
 * @see list_next(), list_previous()
 */
 
typedef ListNode ListIterator;

/** Destroy function prototype for the list items.
 * This function must clean up the item that was stored in the list and must free all 
 * resources (memory) that was allocated by this item.
 * @param	item	The item that shuold be destroyed.
 * @note	Usually ooc_delete() or ooc_free() is used as list_item_destroyer. 
 * @see list_new()
 */
 
typedef void ( * list_item_destroyer ) ( void * item );

/** Execution function prototype for the list items.
 * This function is called by the list_for_each() method.
 * @param	item	The item.
 * @param	param	The parameter passed to the list_for_each() function. 
 * @see list_foreach()
 */
 
typedef void (*	list_item_executor) ( void * item, void * param );

/** Boolean function prototype for the list items.
 * This function is called by some of the list_for_each...() method.
 * @param	item	The item.
 * @param	param	The parameter passed to the list_for_each() function.
 * @return	Must return @c TRUE or @c FALSE.
 * @see list_foreach_until_true(), list_foreach_delete_if(), list_find_item(), list_find_item_reverse()
 */
 
typedef int (*	list_item_checker) ( void * item, void * param );


/* List member functions
 */
 
#ifndef OOC_NO_DYNAMIC_MEM

/** Creates a new List.
 * Creates an empty List.
 * @param	destroyer	The destroy function for the list items. It is usually ooc_free(), ooc_delete()
 * 						or ooc_delete_and_null() depending on the type of the items stored in the List.
 * 						For static List items (that do not need the release of the occupied memory) 
 * 						you can pass @c NULL as well.
 * @return	The List.
 */

List            list_new( list_item_destroyer destroyer );

/** @def list_new_type( pClass, manage )
 *  @brief	Convenient macro for creating typed List.
 *  @param	 pClass		The type of the List. It is guaranteed, that the list holds this type of Objects only.
 * 						Trying to put different Object into the List will cause throwing an @c Exception with 
 * 						@c err_bad_cast error code.
 * @param	manage		@c TRUE if the List must manage the Objects put in the List, @c FALSE if not.
 * @return	The List.
 * @see 	_list_new_type()
 */
 
#define			list_new_type( pClass, manage ) _list_new_type( & pClass ## Class, manage )

/** Creates a new List of a given type.
 * Creates an empty typed List.
 * @param	type		The type of the List. It is guaranteed, that the list holds this type of Objects only.
 * 						Trying to put different Object into the List will cause throwing an @c Exception with 
 * 						@c err_bad_cast error code.
 * @param	manage		@c TRUE if the List must manage the Objects put in the List, @c FALSE if not.
 * @return	The List.
 * @see 	list_new_type()
 */

List            _list_new_type( Class type, int manage );

/** @def list_new_of_nodes( pNode, manage )
 *  @brief	Convenient macro for creating a List of a given type of ListNodes.
 *  @param	 pNode		The type of the ListNodes. It is guaranteed, that the list holds this type of Objects only.
 * 						Trying to put different Object into the List will cause throwing an @c Exception with 
 * 						@c err_bad_cast error code.
 * 						pNode must be a sublass of ListNode.
 * @param	manage		@c TRUE if the List must manage the Objects put in the List, @c FALSE if not.
 * @return	The List.
 * @see 	_list_new_of_nodes()
 * @note	The List created with this method is more powerful, than a normal typed list, because the chaining information
 * is held by the stored object itself.
 */
 
#define			list_new_of_nodes( pNode, manage ) _list_new_of_nodes( & pNode ## Class, manage )

/** Creates a new List of a given type of ListNodes.
 * Creates an empty List of listNodes.
 * @param	node		The type of the ListNodes. It is guaranteed, that the list holds this type of Objects only.
 * 						Trying to put different Object into the List will cause throwing an @c Exception with 
 * 						@c err_bad_cast error code.
 * 						node must be a sublass of ListNode.
 * @param	manage		@c TRUE if the List must manage the Objects put in the List, @c FALSE if not.
 * @return	The List.
 * @see 	list_new_of_nodes()
 */

List            _list_new_of_nodes( Class node, int manage );

#endif /* OOC_NO_DYNAMIC_MEM */

/** @def list_use_of_nodes( location, pNode, manage )
 *  @brief	Convenient macro for creating a List of a given type of ListNodes at a preallocated location.
 *  @param	 location	The location where the preallocated List must be created.
 *						The location must be large enough to hold a ListObject.
 *  @param	 pNode		The type of the ListNodes. It is guaranteed, that the list holds this type of Objects only.
 * 						Trying to put different Object into the List will cause throwing an @c Exception with 
 * 						@c err_bad_cast error code.
 * 						pNode must be a sublass of ListNode.
 * @param	manage		OOC_MANAGE if the List must manage the Objects put in the List, !OOC_MANAGE if not.
 * @see 	_list_use_of_nodes()
 * @note	The List created with this method is more powerful, than a normal typed list, because the chaining information
 * is held by the stored object itself.
 */
 
#define			list_use_of_nodes( location, pNode, manage ) _list_use_of_nodes( location, & pNode ## Class, manage )

/** Creates a new List of a given type of ListNodes at location.
 * Creates an empty List of listNodes at a preallocated location.
 * @param	location	The location where the preallocated List must be created.
 *						The location must be large enough to hold a ListObject.
 * @param	node		The type of the ListNodes. It is guaranteed, that the list holds this type of Objects only.
 * 						Trying to put different Object into the List will cause throwing an @c Exception with 
 * 						@c err_bad_cast error code.
 * 						node must be a sublass of ListNode.
 * @param	manage		OOC_MANAGE if the List must manage the Objects put in the List, !OOC_MANAGE if not.
 * @see 	list_use_of_nodes()
 */

void            _list_use_of_nodes( void * location, Class node, int manage );

/** Appends an item to the end of the list.
 * @param	list	The list
 * @param	item	The item to be appended. The list takes over the ownership of the item
 * 					if you have created the list with a list item destroyer.
 * @return	The position of the inserted item in the list.
 */
 
ListIterator    list_append( List list, void * item );

/** Prepends an item at the beginning of the list.
 * @param	list	The list
 * @param	item	The item to be prepended. The list takes over the ownership of the item
 * 					if you have created the list with a list item destroyer.
 * @return	The position of the inserted item in the list.
 */
 
ListIterator    list_prepend( List list, void * item );

/** Inserts an item before the given position of the list.
 * @param	list	The list
 * @param	position The positon 
 * @param	item	The item to be inserted. The list takes over the ownership of the item
 * 					if you have created the list with a list item destroyer.
 * @return	The position of the inserted item in the list.
 */
 
ListIterator    list_insert_before( List list, ListIterator position, void * item );

/** Inserts an item after the given position of the list.
 * @param	list	The list
 * @param	position The positon 
 * @param	item	The item to be inserted. The list takes over the ownership of the item
 * 					if you have created the list with a list item destroyer.
 * @return	The position of the inserted item in the list.
 */
 
ListIterator    list_insert_after( List list, ListIterator position, void * item );

/** Removes an item from the list.
 * @param	list		The list
 * @param	position	The position of the item to be removed.
 * @return	The item that was removed from the list.
 * @note	This method does not delete the item! You are responsible to destroy the item when it is no longer needed!
 */
 
void *			list_remove_item( List list, ListIterator position );

/** Removes the first item from the list.
 * @param	list		The list
 * @return	The item that was removed from the list, NULL if the list was empty.
 * @note	This method does not delete the item! You are responsible to destroy the item when it is no longer needed!
 */
 
void *			list_remove_first_item( List list );

/** Removes the last item from the list.
 * @param	list		The list
 * @return	The item that was removed from the list, NULL if the list was empty.
 * @note	This method does not delete the item! You are responsible to destroy the item when it is no longer needed!
 */
 
void *			list_remove_last_item( List list );

/** Deletes an item in the list.
 * This method removes and destroys the positioned item in the list.
 * @param	list		The list
 * @param	position	The position of the item to be removed.
 * @return	The item that was removed from the list.
 * @note	If you passed @c NULL as item destroyer for list_new(), then actually no deletion occurs.  
 */
 
void			list_delete_item( List list, ListIterator position );

/** Gets the iterator for the first item in the list
 * @param	list	The list
 * @return	The iterator for the first item in the list, or @c NULL if the list is empty.
 */

ListIterator    list_first( List list );

/** Gets the iterator for the last item in the list
 * @param	list	The list
 * @return	The iterator for the last item in the list, or @c NULL if the list is empty.
 */

ListIterator    list_last( List list );

/** Gets an item in the list.
 * @param	listiterator	The position of the item in the list. It must be a valid list iterator,
 * 							passing @c NULL will throw @c err_wrong_position exception.
 * @return	The item
 * @note	This method does not change the ownership of the item.
 * 			It just returns a pointer to the item, you must not delete or free it!
 */

void *          list_get_item( ListIterator listiterator );

/** Gets the iterator of the next item in the list.
 * @param	list			The list
 * @param	listiterator	The position of the current item in the list. It must be a valid list iterator,
 * 							passing @c NULL will throw @c err_wrong_position exception.
 * @return	The ListIterator of the next item in the list, or @c NULL if there are no more items.
 * @note	For "noded" Lists (those that was made by list_new_of_nodes()) this function just returns
 * 			the listiterator itself. Noded Lists consider the ListNodes as items.
 */

ListIterator    list_next( List list, ListIterator listiterator );

/** Gets the iterator of the previous item in the list.
 * @param	list			The list
 * @param	listiterator	The position of the current item in the list. It must be a valid list iterator,
 * 							passing @c NULL will throw @c err_wrong_position exception.
 * @return	The ListIterator of the previous item in the list, or @c NULL if there are no more items.
 */

ListIterator    list_previous( List list, ListIterator listiterator );

/** Changes two items' position in the list.
 * @param	list			The list.
 * @param	listiterator1	The list iterator of the first item
 * @param	listiterator2	The list iterator of the second item
 * @note	Both parameters must be a valid list iterator,
 * 			passing @c NULL will throw @c err_wrong_position exception.
 */
 
void			list_swap( List list, ListIterator listiterator1, ListIterator listiterator2 );

/** Executes a method for each items in the list.
 * @param	list	The list.
 * @param	method	The method to be executed for each items.
 * @param	param	The parameter to be passed for the executed method.
 */
 
void            list_foreach( List list, list_item_executor method, void * param );

/** Executes a method for each items in the list until it returns @c TRUE.
 * @param	list	The list.
 * @param	from	The position of the first item to be checked, or @c NULL if must start from the first item in the list.
 * @param	method	The method to be executed for each items.
 * @param	param	The parameter to be passed for the executed method.
 * @return	The ListIterator of the first item that matches the condition, or &c NULL if there was no match.
 */
 
ListIterator    list_foreach_until_true( List list, ListIterator from, list_item_checker method, void * param );

/** Deletes each items in the list that match the criteria.
 * @param	list	The list.
 * @param	criteria	The method that is used to decide which items to delete. 
 * 					The item is deleted if the method returns @c TRUE for it. 
 * @param	param	The parameter to be passed for the executed method.
 */
 
void			list_foreach_delete_if( List list, list_item_checker criteria, void * param );

/** Finds the first matching item in the list.
 * This is a forward search (in the direction from the first item to the last item.)
 * @param	list		The list.
 * @param	position	The position from where to start the search. It must be a valid list iterator,
 * 						otherwise will throw @c err_wrong_position exception.
 * 						Passing @c NULL will start from the beginning of the List.
 * @param	criteria	The method that is used to decide which items find. 
 * @param	param		The parameter to be passed for the executed method.
 * @return	The ListIterator of the first matching item in the list, or @c NULL if there was no match.
 * @note	This is a simple linear search, may take long for large lists.
 */
 
ListIterator	list_find_item( List list, ListIterator position,  list_item_checker criteria, void * param );

/** Finds the first matching item in the list in reverse order.
 * This is a backward search (in the direction from the last item to the first item.)
 * @param	list		The list.
 * @param	position	The position from where to start the search. It must be a valid list iterator,
 * 						otherwise will throw @c err_wrong_position exception.
 * 						Passing @c NULL will start from the end of the List.
 * @param	criteria	The method that is used to decide which items find. 
 * @param	param		The parameter to be passed for the executed method.
 * @return	The ListIterator of the first matching item in the list, or @c NULL if there was no match.
 * @note	This is a simple linear search, may take long for large lists.
 */
 
ListIterator	list_find_item_reverse( List list, ListIterator position,  list_item_checker criteria, void * param);

/** Get the type of the list.
 * Returns the type of the list in case of a typed list.
 * @param	list		The list.
 * @return	The Class pointer in case of a typed list, otherwise NULL;
 * @see 	list_new_type(), list_new_of_nodes().
 */

Class			list_get_type( List list );

/** Check if the list is managed.
 * Check is the items in the list are managed by the list.
 * @param	list		The list.
 * @return	OOC_MANAGE if managed list, !OOC_MANAGE if not.
 * @see		list_new(), list_new_type(), list_new_of_nodes().
 */

int 			list_get_managed( List list );

#endif /* LIST_H_ */

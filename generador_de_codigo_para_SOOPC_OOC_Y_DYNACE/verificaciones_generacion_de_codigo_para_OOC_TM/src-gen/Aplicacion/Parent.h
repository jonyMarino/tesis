/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Parent.h
 * Code Management Tool File Version: 
 * SDD Component: Parent
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Parent.h
 * \brief Parent
 */

#ifndef PARENT_H
#define PARENT_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"
#include <ooc/ooc.h>
#include "Aplicacion/Countable.h"
#include "Aplicacion/Serializable.h"

/**********************************************************************************
 * Aplicacion/Parent.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Parent
 * \brief This is the first class in this class hierarchy
 */

DeclareClass( Parent, Base );




Parent parent_new( const char * name );



/* Virtual function definitions
 */


Virtuals( Parent, Base );


	void (*vPrint)(Parent self);

	Interface( Countable );
	Interface( Serializable );

EndOfVirtuals;







#endif

/**********************************************************************************
 * File Path: Aplicacion/parent.h
 **********************************************************************************/





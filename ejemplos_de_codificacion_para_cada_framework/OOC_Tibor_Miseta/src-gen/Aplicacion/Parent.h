/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/Parent.h
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: Parent
 * Language: C
 * Author: marino
 * Last Change: $Id$
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
#include "Aplicacion/MyInterface.h"
#include "Aplicacion/MyMixin.h"

/**********************************************************************************
 * Aplicacion/Parent.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Parent
 * \brief This is the first class in this class hierarchy
 */

DeclareClass( Parent, Base );




Parent parent_new( void );



/* Virtual function definitions
 */


Virtuals( Parent, Base );


	void (*method)(Parent self);
	void (*serialize)(Parent self, char * out);

	Interface( MyInterface );
	Interface( MyMixin );

EndOfVirtuals;







#endif

/**********************************************************************************
 * File Path: Aplicacion/parent.h
 **********************************************************************************/





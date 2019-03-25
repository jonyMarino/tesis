/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Child.h
 * Code Management Tool File Version: 
 * SDD Component: Child
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Child.h
 * \brief Child
 */

#ifndef CHILD_H
#define CHILD_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"
#include "Aplicacion/Parent.h"

/**********************************************************************************
 * Aplicacion/Child.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Child
 */

DeclareClass( Child, Parent );




Child child_new( const char * name );



/* Virtual function definitions
 */


Virtuals( Child, Parent );


	char * (*getNameFollowedByClassName)(Child self);


EndOfVirtuals;







#endif

/**********************************************************************************
 * File Path: Aplicacion/child.h
 **********************************************************************************/





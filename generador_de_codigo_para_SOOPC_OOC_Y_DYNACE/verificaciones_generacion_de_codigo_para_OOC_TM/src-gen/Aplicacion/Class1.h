/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/Class1.h
 * Code Management Tool File Version: 
 * SDD Component: Class1
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/Class1.h
 * \brief Class1
 */

#ifndef CLASS1_H
#define CLASS1_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"
#include <ooc/ooc.h>

/**********************************************************************************
 * Aplicacion/Class1.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package Class1
 */

DeclareClass( Class1, Base );




Class1 class1_new( void );



/* Virtual function definitions
 */


Virtuals( Class1, Base );


	void (*Class1)(Class1 self);


EndOfVirtuals;







#endif

/**********************************************************************************
 * File Path: Aplicacion/class1.h
 **********************************************************************************/





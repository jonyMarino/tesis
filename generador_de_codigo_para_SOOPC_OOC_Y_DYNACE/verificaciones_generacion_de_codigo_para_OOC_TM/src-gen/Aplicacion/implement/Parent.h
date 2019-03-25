/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: Aplicacion/implement/Parent.h
 * Code Management Tool File Version: 
 * SDD Component: Parent
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file Aplicacion/implement/Parent.h
 * \brief Parent
 */

/**********************************************************************************
 * Aplicacion/implement/Parent.h
 **********************************************************************************/
/*## package Aplicacion */


#ifndef IMPLEMENT_PARENT_H
#define IMPLEMENT_PARENT_H

#ifndef PARENT_H
#error Do #include "parent.h" right before doing #include "implement/parent.h"
#endif



#include "Aplicacion/implement/Countable.h"

/*! 
 * \package Parent
 * \brief This is the first class in this class hierarchy
 */

ClassMembers( Parent , Base )
	const char * name;
	unsigned int classHash;
	MixinData(Countable);
EndOfClassMembers;



#endif


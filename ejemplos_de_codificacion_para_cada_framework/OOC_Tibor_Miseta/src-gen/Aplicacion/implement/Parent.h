/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/implement/Parent.h
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: Parent
 * Language: C
 * Author: marino
 * Last Change: $Id$
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



#include "Aplicacion/implement/MyMixin.h"

/*! 
 * \package Parent
 * \brief This is the first class in this class hierarchy
 */

ClassMembers( Parent , Base )
	int instanceVariable;
	unsigned int classVariable;
	MixinData(MyMixin);
EndOfClassMembers;



#endif


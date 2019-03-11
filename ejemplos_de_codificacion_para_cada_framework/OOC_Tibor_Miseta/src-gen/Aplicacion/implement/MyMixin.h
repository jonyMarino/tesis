/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/implement/MyMixin.h
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: MyMixin
 * Language: C
 * Author: marino
 * Last Change: $Id$
 **********************************************************************************/

/*!
 * \file Aplicacion/implement/MyMixin.h
 * \brief MyMixin
 */

/**********************************************************************************
 * Aplicacion/implement/MyMixin.h
 **********************************************************************************/
/*## package Aplicacion */


#ifndef IMPLEMENT_MYMIXIN_H
#define IMPLEMENT_MYMIXIN_H

#ifndef MYMIXIN_H
#error Do #include "mymixin.h" right before doing #include "implement/mymixin.h"
#endif

/*! 
 * \package MyMixin
 */

MixinMembers( MyMixin )
	unsigned int instanceNum;
EndOfMixinMembers;

#endif


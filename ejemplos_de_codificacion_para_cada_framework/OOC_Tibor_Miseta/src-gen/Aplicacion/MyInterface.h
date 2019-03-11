/**********************************************************************************
 * Copyright: 2019 All rights reserved.
 * Project: RootElement
 * File: Aplicacion/MyInterface.h
 * Code Management Tool File Version: 1.0.0
 * Date: $Date$
 * SDD Component: MyInterface
 * Language: C
 * Author: marino
 * Last Change: $Id$
 **********************************************************************************/

/*!
 * \file Aplicacion/MyInterface.h
 * \brief MyInterface
 */

#ifndef MYINTERFACE_H
#define MYINTERFACE_H

/* Dependency with parent package */
#include "Aplicacion/Aplicacion.h"

/**********************************************************************************
 * Aplicacion/myinterface.h
 **********************************************************************************/

/*## package Aplicacion */

/*! 
 * \package MyInterface
 */

#include <ooc/ooc.h>


DeclareInterface( MyInterface  )

	void (*myInterfaceMethod)(Object self);

EndOfInterface;


#endif

/**********************************************************************************
 * File Path: Aplicacion/MyInterface.h
 **********************************************************************************/

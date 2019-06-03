/*
 * test_gen_parent.c
 *
 *  Created on: 17 de may. de 2018
 *      Author: marino
 */


/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/

//-- unity: unit test framework
#include "unity.h"

#include <stdlib.h>

//-- module being tested
#include "Aplicacion/Child.h"

#include "Aplicacion/Parent.h"
#include "Aplicacion/implement/Parent.h"

#include "Aplicacion/Countable.h"
#include "Aplicacion/Serializable.h"
#include "ooc.h"
#include "exception.h"




/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
Child aChild;
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/


/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
	aChild = child_new("Junior");
}

void tearDown(void)
{
	ooc_delete((Object)aChild);
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/


void test_child_vtable(void)
{

	TEST_ASSERT_NOT_NULL(ChildParentVirtual(aChild)->vPrint);
	TEST_ASSERT_NOT_NULL(ChildVirtual(aChild)->getNameFollowedByClassName );
}


void test_child_redefinicion(void)
{
    Parent aParent = parent_new("Papa");
	TEST_ASSERT_NOT_EQUAL(ChildVirtual(aChild)->Parent.Serializable.serialize, ParentVirtual(aParent)->Serializable.serialize);
    ooc_delete((Object)aParent);
}




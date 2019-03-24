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
#include "Aplicacion/Parent.h"

//-- module being tested
#include "Aplicacion/Child.h"



/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
Child  * aChild;
Parent * childAsParent;
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/


/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
	aChild = malloc(sizeof(Child));
	Child_ctor(aChild,"Junior");
	childAsParent = (Parent *) aChild;
}

void tearDown(void)
{
	free(aChild);
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/

void test_child_ctor(void)
{

    TEST_ASSERT_EQUAL_STRING("Junior",childAsParent->name);
    TEST_ASSERT_NOT_NULL(childAsParent->vptr);
}

void test_child_vtable(void)
{

    TEST_ASSERT_EQUAL(childAsParent->vptr->vPrint,Child_vPrint_);
    TEST_ASSERT_EQUAL(((ChildVtbl*) childAsParent->vptr )->getNameFollowedByClassName,Child_getNameFollowedByClassName_);
}

void test_child_selector(void)
{
	char * nameFollowedByClassName = Child_getNameFollowedByClassName(aChild);
	TEST_ASSERT_EQUAL_STRING("JuniorChild",nameFollowedByClassName);
	free(nameFollowedByClassName);

}


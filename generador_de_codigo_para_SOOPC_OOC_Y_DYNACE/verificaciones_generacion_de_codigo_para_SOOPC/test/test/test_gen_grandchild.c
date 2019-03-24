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
#include "Aplicacion/Child.h"

//-- module being tested
#include "Aplicacion/GrandChild.h"



/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
GrandChild  * aGrandChild;
Child * grandchildAsChild;
Parent * grandchildAsParent;
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/


/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
	aGrandChild = malloc(sizeof(GrandChild));
	GrandChild_ctor(aGrandChild,"Mike");
	grandchildAsParent = (Parent *) aGrandChild;
	grandchildAsChild = (Child *) aGrandChild;
}

void tearDown(void)
{
	free(aGrandChild);
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/

void test_grandchild_ctor(void)
{

    TEST_ASSERT_EQUAL_STRING("Mike",grandchildAsParent->name);
    TEST_ASSERT_NOT_NULL(grandchildAsParent->vptr);
}

void test_grandchild_vtable(void)
{

    TEST_ASSERT_EQUAL(grandchildAsParent->vptr->vPrint,Child_vPrint_);
    TEST_ASSERT_EQUAL(((ChildVtbl*) grandchildAsParent->vptr )->getNameFollowedByClassName,GrandChild_getNameFollowedByClassName_);
}

void test_grandchild_selector(void)
{
	char * nameFollowedByClassName = Child_getNameFollowedByClassName(grandchildAsChild);
	TEST_ASSERT_EQUAL_STRING("MikeGrandChild",nameFollowedByClassName);
	free(nameFollowedByClassName);

}

void test_grandchild_metodo_no_virtual(void)
{
	GrandChild_foo(aGrandChild);
	TEST_ASSERT_NULL(NULL);
}


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

//-- module being tested
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


/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/


/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
}

void tearDown(void)
{
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/

void test_parent_ctor(void)
{

	Parent aParent = parent_new("George");
    TEST_ASSERT_NOT_NULL(ParentVirtual(aParent)->vPrint);
    TEST_ASSERT_NOT_NULL( ooc_get_interface( aParent , Countable ) );
    TEST_ASSERT_NOT_NULL( ooc_get_interface( aParent , Serializable ) );

    ooc_delete((Object)aParent);
}

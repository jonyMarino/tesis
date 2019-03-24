#include "build/temp/_test_gen_parent.c"
#include "Aplicacion/Parent.h"
#include "unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}











void test_parent_ctor(void)

{

 Parent aParent;

    Parent_ctor(&aParent,"George");

    UnityAssertEqualString((const char*)(("George")), (const char*)((aParent.name)), (

   ((void *)0)

   ), (UNITY_UINT)(58));

    if ((((aParent.vptr)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(59))));};

}



void test_parent_vtable(void)

{

 Parent aParent;

    Parent_ctor(&aParent,"George");

    UnityAssertEqualString((const char*)(("George")), (const char*)((aParent.name)), (

   ((void *)0)

   ), (UNITY_UINT)(66));

    UnityAssertEqualNumber((UNITY_INT)((aParent.vptr->vPrint)), (UNITY_INT)((Parent_vPrint_)), (

   ((void *)0)

   ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);

}

#include "build/temp/_test_gen_child.c"
#include "Aplicacion/Child.h"
#include "Aplicacion/Parent.h"
#include "unity.h"






Child * aChild;

Parent * childAsParent;

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











void test_child_ctor(void)

{



    UnityAssertEqualString((const char*)(("Junior")), (const char*)((childAsParent->name)), (

   ((void *)0)

   ), (UNITY_UINT)(65));

    if ((((childAsParent->vptr)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(66))));};

}



void test_child_vtable(void)

{



    UnityAssertEqualNumber((UNITY_INT)((childAsParent->vptr->vPrint)), (UNITY_INT)((Child_vPrint_)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((((ChildVtbl*) childAsParent->vptr )->getNameFollowedByClassName)), (UNITY_INT)((Child_getNameFollowedByClassName_)), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);

}



void test_child_selector(void)

{

 char * nameFollowedByClassName = Child_getNameFollowedByClassName(aChild);

 UnityAssertEqualString((const char*)(("JuniorChild")), (const char*)((nameFollowedByClassName)), (

((void *)0)

), (UNITY_UINT)(79));

 free(nameFollowedByClassName);



}

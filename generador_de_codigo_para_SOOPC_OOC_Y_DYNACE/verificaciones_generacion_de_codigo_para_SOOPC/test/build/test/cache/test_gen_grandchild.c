#include "build/temp/_test_gen_grandchild.c"
#include "Aplicacion/GrandChild.h"
#include "Aplicacion/Child.h"
#include "Aplicacion/Parent.h"
#include "unity.h"






GrandChild * aGrandChild;

Child * grandchildAsChild;

Parent * grandchildAsParent;

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











void test_grandchild_ctor(void)

{



    UnityAssertEqualString((const char*)(("Mike")), (const char*)((grandchildAsParent->name)), (

   ((void *)0)

   ), (UNITY_UINT)(68));

    if ((((grandchildAsParent->vptr)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(69))));};

}



void test_grandchild_vtable(void)

{



    UnityAssertEqualNumber((UNITY_INT)((grandchildAsParent->vptr->vPrint)), (UNITY_INT)((Child_vPrint_)), (

   ((void *)0)

   ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((((ChildVtbl*) grandchildAsParent->vptr )->getNameFollowedByClassName)), (UNITY_INT)((GrandChild_getNameFollowedByClassName_)), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);

}



void test_grandchild_selector(void)

{

 char * nameFollowedByClassName = Child_getNameFollowedByClassName(grandchildAsChild);

 UnityAssertEqualString((const char*)(("MikeGrandChild")), (const char*)((nameFollowedByClassName)), (

((void *)0)

), (UNITY_UINT)(82));

 free(nameFollowedByClassName);



}



void test_grandchild_metodo_no_virtual(void)

{

 GrandChild_foo(aGrandChild);

 if ((((

((void *)0)

)) == 

((void *)0)

)) {} else {UnityFail( (((" Expected NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(90))));};

}

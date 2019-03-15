/*
 * MyInterface1.h
 *
 *  Created on: 3 de feb. de 2019
 *      Author: marino
 */

#ifndef MY_INTERFACE1_H_
#define MY_INTERFACE1_H_

#include <glib-object.h>

typedef struct _MyInterface1      MyInterface1;
typedef struct _MyInterface1Iface MyInterface1Iface;

typedef struct _MyInterface1Iface {
    GTypeInterface parent;
    void (*method1)(MyInterface1 *instance);
} MyInterface1Iface;

#define TYPE_MYINTERFACE1           (my_interface1_get_type())
#define MYINTERFACE1(obj)           (G_TYPE_CHECK_INSTANCE_CAST    ((obj), TYPE_MYINTERFACE1, MyInterface1Iface))
#define IS_MYINTERFACE1(obj)        (G_TYPE_CHECK_INSTANCE_TYPE    ((obj), TYPE_MYINTERFACE1))
#define MYINTERFACE1_GET_IFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), TYPE_MYINTERFACE1, MyInterface1Iface))

GType    my_interface1_get_type                 (void);
void     my_interface1_method1                 (MyInterface1 *self);


#endif /* MY_INTERFACE1_H_ */

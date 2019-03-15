#ifndef __CHILD_H__
#define __CHILD_H__

#include <glib-object.h>

typedef struct _ChildClass ChildClass;
typedef struct _Child      Child;

struct _ChildClass {
    GObjectClass parent;
    void (*method) (Child *self);
    void (*signal1Process) (Child *self);
};

struct _Child {
    GObject  parent;
    gint     publicAttr;
};

#define TYPE_CHILD           (child_get_type             ())
#define CHILD(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CHILD, Child))
#define CHILD_CLASS(cls)     (G_TYPE_CHECK_CLASS_CAST    ((cls), TYPE_CHILD, ChildClass))
#define IS_CHILD(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CHILD))
#define IS_CHILD_CLASS(cls)  (G_TYPE_CHECK_CLASS_TYPE    ((cls), TYPE_CHILD))
#define CHILD_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), TYPE_CHILD, ChildClass))

GType  child_get_type  (void);
void   child_method     (Child *self);

#endif

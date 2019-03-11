/* Template for a TYPE private definition
   - replace parent by the type name
   - replace object by the inherited type name
   - add more parent attributes in the parent_attribute definition
   - remove this comment

   Special cases:
   - public attributes:
     . put this content in the parent.h file
   - final type:
     . put this content in the parent.c file
   - root type:
     . remove everything related to object
     . the first attribute should be struct interface *_;
 */
#ifndef PARENT_PH
#define PARENT_PH

#include "parent.h"
#include "object_p.h"

struct parent_attribute {
  struct object_attribute object;
  /* más atributos aquí  */
};

#endif /* PARENT_PH */

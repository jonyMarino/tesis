#include "parent.h"
#include "child.h"


int main (void){

	parent * parent1 = parent_new( );
	parent1 -> attribute2 = 10;
	parent * parent2 = parent_copy( parent1 );
	parent2 -> method ( parent2 );
	parent_free ( parent1 );
	parent_free ( parent2 );


	parent * child1 = (parent*)child_new( );
	child1 -> attribute2 = 10;
	child1 -> method ( child1 );
	child_free((child*)child1);
	return 1;
}

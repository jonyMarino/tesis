#include "Child.h"

int main (int argc, char * argv [])
{	void * child = new( Child() );
												
	printf("%d\n", myMethod(child));

        return 0;
}

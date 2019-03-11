/*
 * main.c
 *
 *  Created on: 11 de oct. de 2018
 *      Author: jonathan
 */


#include "clases/Parent.h"
#include "clases/Child.h"
#include <stdio.h>
int main(void)
{
	t_Parent *const per = Parent.new("Brown");
	sendMsg(per, print);
	delete(per);


	t_Child *const child = Child.new("George");
	sendMsg( super (child, Parent), print);
	delete(child);
	printf("hola mundo!\r\n");
}

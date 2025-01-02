//TODO add function to free context struct on exit

/*
	gcc -Wall -Wextra -Werror main_andrei.c
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("argc [%d], argv addr [%p]\n", argc, argv);
}

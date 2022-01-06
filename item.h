#include <stdio.h>
#include <stdlib.h>

#ifndef ITEM_H
#define ITEM_H

/*
 * Macro definitions related to Item
 */

 /* Macro definition for the maximum length of name */
#define MAX_NAME_LENGTH 30


/* Macro definition for the maximum length of category */
#define MAX_CATEGORY_LENGTH 20


/* Macro definition for the maximum value of x-coordinate */
#define MAX_X_COORDINATE 32


/* Macro definition for the maximum value of y-coordinate */
#define MAX_Y_COORDINATE 32




/*
 * Type definition of Structure Item
 */

struct part{
		char name[MAX_NAME_LENGTH + 1];
		char category[MAX_CATEGORY_LENGTH + 1];
		int x;
		int y;
} item[100];



#endif
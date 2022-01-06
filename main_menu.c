#include <stdio.h>
#include "readline.h"
#include "item.h"
#include "database.h"

/***********************************************************
 * main : Prompts the user to enter an operation code,     *
 *        then calles a function to perform the requested  *
 *        action. Repeats until the user enters the        *
 *        command 'q'. Prints an error message if the user *
 *        enters an illegal code.                          *
 ***********************************************************/
int main(void)
{
    printf("Operation code list:\n\ni: insert item\np: print all item\nl: load item\ns: save item\nf: find items by name\nc: find items by category\nn: find nearest neighbor\nr: find items by range\nj: find by faculty\nq: quit\n\n");
    char code;
    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')  /* skips to end of line */
            ;
        switch (code) {
        case 'i': insert_item();
            break;
        case 'p': print_all_item();
            break;
        case 'l': load_item();
            break;
        case 's': save_item();
            break;
        case 'f': find_items_by_name();
            break;
        case 'c': find_items_by_category();
            break;
        case 'n': find_nearest_neighbor();
            break;
        case 'r': find_items_by_range();
            break;
        case 'j': find_by_faculty();
            break;
        case 'q': return 0;
        default:  printf("Illegal code\n");
        }
        printf("\n");
    }
}
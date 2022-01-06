#ifndef DATABASE_H
#define DATABASE_H

#define RESULT_PAGE "result.html"

/* this header file depends on item.h */
#include "item.h"

/*
 * Macro defitions related to database
 */

 /* Macro definition for the maximum size of database */
#define MAX_ITEM_SIZE 100 

/* Macro definition for the maximum length of file path (loading/saving) */
#define MAX_FILE_PATH_LENGTH 30


/*
 * Function prototypes related to database
 */

 /* function prototype for insertion of a new data item */
void insert_item(void);

 /* function prototype for printing all data items */
void print_all_item(void);


 /* function prototype for loading items from a file */
void load_item(void);

 /* function prototype for saving items into a file */
void save_item(void);

 /* function prototype for finding items based on name */
void find_items_by_name(void);


 /* function prototype for finding items based on category */
void find_items_by_category(void);
void print_page_sample(int *size);

 /* function prototype for finding items based on range */
void find_items_by_range(void);

 /* function prototype for nearest neighbor items */
void find_nearest_neighbor(void);

/* function prototype for faculty */
void find_by_faculty(void);


#endif
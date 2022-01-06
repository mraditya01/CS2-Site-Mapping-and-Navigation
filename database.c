    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <ctype.h>
    #include "database.h"
    #include "readline.h"

    int num_parts = 1;  /* the number of parts currently stored */
    char name[1000]; /* Array for character inputted when searching */
    char result[100]; /* Array for the number of n-th structure that match the search input */


    /***********************************************************
     * insert : Prompts the user for infromation about a new   *
     *          part and then inserts the part into the        *
     *          database. Prints and error message and returns *
     *          prematurely if the part already exists or the  *
     *          database is full                               *
     ***********************************************************/
    void insert_item(void)
    {
        /* scan the inputted character and store it inside the struct item[num_parts].name
        while also skips leading white-space characters */
        printf("Enter Location name: "); 
        read_line(item[num_parts].name, MAX_NAME_LENGTH);
        /* scan the inputted character and store it inside the struct item[num_parts].category
        while also skips leading white-space characters */
        printf("Enter Location Category: ");
        read_line(item[num_parts].category, MAX_CATEGORY_LENGTH);
        /* scan the inputted integer and store it inside the struct item[num_parts].x*/
        printf("Enter X-coordinate: ");
        scanf("%d", &item[num_parts].x);
        /* Maximum coordinate is 31 if it exceed 31 enter another coordinate*/
        if (item[num_parts].x >= MAX_X_COORDINATE) 
        {
            printf("Max 31, Enter another X-coordinate: ");
            scanf("%d", &item[num_parts].x);
        }
        /* scan the inputted integer and store it inside the struct item[num_parts].y */
        printf("Enter Y-coordinate: ");
        scanf("%d", &item[num_parts].y);
        /* Maximum coordinate is 31 if it exceed 31 enter another coordinate*/
        if (item[num_parts].y >= MAX_Y_COORDINATE) 
        {
            printf("Max 31, Enter another Y-coordinate: ");
            scanf("%d", &item[num_parts].y);
        }
        /* add num_parts by 1 so when another location is inserted it is going to be stored in another n-th + 1 struct element*/
        num_parts++;  
    }

    /***********************************************************
     * load :  load a file from CSV, loading the file by part  *
     *         name, part category, and coordinate. Parts      *
     *         are loaded from CSV format in order which       *
     *         they were loaded into the database.             *
     ***********************************************************/
    void load_item(void)
    {
        FILE* fp;
        char filename[255];
        int i;

        printf("Enter name of input file: ");
        read_line(filename, 255);

        if ((fp = fopen(filename, "r")) == NULL) /*open the file*/
        {
            fprintf(stderr, "Error: file %s cannot be read\n", filename); /*if file not found*/
            return;
        }
        char line[MAX_FILE_PATH_LENGTH][1000]; /*2D array to save character inside CSV*/
        i = 0;
        while ((fgets(line[i], 1000, fp) != NULL) && (i < MAX_FILE_PATH_LENGTH)) { /*using fgets put the character inside CSV to line*/
            sscanf(line[i], "%[^,],%[^,],%d,%d\n", &item[num_parts].name, &item[num_parts].category, &item[num_parts].x, &item[num_parts].y);
            i++; /*to scan the next line in char array line[]*/
            num_parts++; /*so the saved data will not overwrite itself*/
        }
        fclose(fp);
        return;
    }
    /***********************************************************
     * save :  Save a file in the database, saving the file    *
     *         by part number, part name, and quantity on      *
     *         hand. Parts are saved in CSV format in          *
     *         order which they were entered into the          *
     *         database.                                       *
     ***********************************************************/
    void save_item(void)
    {
        FILE* fp;
        char filename[255];
        int i;

        printf("Enter name of output file: ");
        read_line(filename, 255);

        if ((fp = fopen(filename, "w")) == NULL)
        {
            fprintf(stderr, "Error, cannot save file %s\n", filename);
            return;
        }
        for (i = 1; i < num_parts; i++)
        fprintf(fp, "%s,%s,%d,%d\n", item[i].name, item[i].category, item[i].x, item[i].y);
        fclose(fp);
        return;
    }

    /*****************************************************************
     * Find by name : Prompts the user to enter a name, then match   *
     *                the inputted string to the structure. If the   *
     *                inputted string match with the struc, print the*
     *                n-th structure, then make an html file of the  *
     *                matching string                                *
     *****************************************************************/

    void find_items_by_name(void)
    {
        int n = 0;
        int find_part_name(char name[])
        {
            int i = 0;
            for (i = i; i < num_parts; i++)
                if (strcmp(item[i].name, name) == 0) {
                    if (i != 0) {
                        result[n] = i;
                        n++;
                    }
                }
            return 0;
        }
        printf("Enter name: ");
        read_line(name, MAX_NAME_LENGTH);
        int a;
        for (a = find_part_name(name); a < n; a++)
            printf("%s, %s, %d, %d\n", item[result[a]].name, item[result[a]].category, item[result[a]].x, item[result[a]].y);
        print_page_sample(&n);
        printf("Search result is written to the file %s.\n", RESULT_PAGE);
    }


    /*********************************************************************
     * Find by category : Prompts the user to enter a category, then     *
     *                    match the inputted string to the structure. If *
     *                    the string match, print the n-th structure     *
     *                    then make an html file of the matching string  *
     ********************************************************************/

    void find_items_by_category(void)
    {
        int n = 0;
        int find_part_category(char name[])
        {
            int i = 0;
            for (i = i; i < num_parts; i++)
                if (strcmp(item[i].category, name) == 0) {
                    if (i != 0) {
                        result[n] = i;
                        n++;
                    }
                }
            return 0;
        }
        printf("Enter category: ");
        read_line(name, MAX_NAME_LENGTH);
        int a;
        for (a = find_part_category(name); a < n; a++)
            printf("%s, %s, %d, %d\n", item[result[a]].name, item[result[a]].category, item[result[a]].x, item[result[a]].y);
        print_page_sample(&n);
        printf("Search result is written to the file %s.\n", RESULT_PAGE);
    }

    /****************************************************************************
     * Find by nearest range: Prompts the user to enter a coordinate and        *
     *                        threshold, then by using Pythagorean theorem, find *
     *                        the item with distance less than or equal to the  *
     *                        threshold. Then the item will be printed and put   *
     *                        into HTML                                         *
     ****************************************************************************/
    void find_items_by_range(void)
    {
        int n = 0;
        int c,d,b,z;
        printf("Input your current X-coordinates:");
        scanf("%d", &d);
        printf("Input your current Y-coordinates:");
        scanf("%d", &b);
        printf("Input distance threshold:");
        scanf("%d", &z);
        int find_part_range(int f, int e, int g)
        {
            int i=1;
            float j;
            for (i = i; i < num_parts; i++) {
                if ((sqrt((item[i].x - f) * (item[i].x - f) + (item[i].y - e) * (item[i].y - e)))*40 <= g) {
                        result[n] = i;
                        n++;
                    }
                }
            if (n < 1) {
                printf("Nothing found within threshold\n");
            }
            return 0;
        }
        find_part_range(d,b,z);
        int a;
        for (a = 0; a < n; a++) {
                printf("%s, %s, %d, %d\n", item[result[a]].name, item[result[a]].category, item[result[a]].x, item[result[a]].y);
        }
                print_page_sample(&n);
                printf("Search result is written to the file %s.\n", RESULT_PAGE);
    }

    /****************************************************************************
     * Find by nearest neighbor : Prompts the user to enter a coordinate, then  *
     *                            by using Pythagorean theorem, find the minimum*
     *                            distance possible to each item in database    *
     *                            the item with minimum distance will be printed*
     *                            and put into HTML                             *
     ****************************************************************************/
    void find_nearest_neighbor(void)
    {
        int n = 0;
        int c, d, b;
        printf("Input your current X-coordinates:");
        scanf("%d", &d);
        printf("Input your current Y-coordinates:");
        scanf("%d", &b);
        int find_part_neighbor(int f, int e)
        {
            int i;
            float j;
            float min = sqrt((item[0].x - f) * (item[0].x - f) + (item[0].y - e) * (item[0].y - e));
            for (i = 0; i < num_parts; i++) {
                if (sqrt((item[i].x - f) * (item[i].x - f) + (item[i].y - e) * (item[i].y - e)) <= min) {
                    if (i != 0) {
                        min = sqrt((item[i].x - f) * (item[i].x - f) + (item[i].y - e) * (item[i].y - e));
                        result[n] = i;
                    }
                }
            }
            j = min * 40;
            printf("Distance to nearest location: %.2f meter\n", j);
            return 0;
        }
        find_part_neighbor(d, b);
        c = n + 1;
        printf("%s, %s, %d, %d\n", item[result[n]].name, item[result[n]].category, item[result[n]].x, item[result[n]].y);
        print_page_sample(&c);
        printf("Search result is written to the file %s.\n", RESULT_PAGE);
    }

    /********************************************************************************
     * Find by Faculty : Prompts the user the Faculty they're located in then by    *
     *                   using the location of the faculty, all the item within     *
     *                   the range of faculty will be printed and put into HTML     *
     *                   Faculty location and coordinates are based on              *
                         https://en.nagoya-u.ac.jp/upload_images/map20190702_en.jpg *
     ********************************************************************************/

    void find_by_faculty(void)
    {
        int n = 0;
        int b, c, d, e;
        int k;
        printf("List of Faculty:\n");
        printf("1. Humanities and Social Science\n2. Natural Science\n3. Engineering Science\n4. Agricultural Science\n5. Inter-Departmental Education and Research Center\n");
        printf("Enter The Faculty you are located in (by using number above):");
        scanf("%d", &k);
        int find_part_faculty(int f, int g, int h, int j)
        {
            int i;
            for (i = 0; i < num_parts; i++) {
                if (item[i].x >= f && item[i].x <= g && item[i].y >= h && item[i].y <= j) {
                    result[n] = i;
                    n++;
                }
            }
            int a;
            for (a = 0; a < n; a++) {
                printf("%s, %s, %d, %d\n", item[result[a]].name, item[result[a]].category, item[result[a]].x, item[result[a]].y);
            }
            print_page_sample(&n);
            printf("Search result is written to the file %s.\n", RESULT_PAGE);
            return 0;
        }
        if (k == 1) {
            find_part_faculty(0, 12, 12, 19);
        }
        if (k == 2) {
            find_part_faculty(14, 21, 3, 12);
        }
        if (k == 3) {
            find_part_faculty(6, 14, 5, 11);
        }
        if (k == 4) {
            find_part_faculty(23, 27, 8, 12);
        }
        if (k == 5) {
            find_part_faculty(23, 31, 14, 26);
        }
    }

    /***********************************************************
     * print : Prints a list of all parts in the database,     *
     *         showing the name, category, and coordinate      *
     *         Parts are printed in the order in which they    *
     *         were entered into the database.                 *
     ***********************************************************/
    void print_all_item(void)
    {
        int i;

        printf("|       Name         |     Category      | Coordinate |\n");
        printf("|--------------------|-------------------|------------|\n");
        for (i = 1; i < num_parts; i++)
            printf("|%-20s|%-19s|(%4d,%4d) |\n", item[i].name, item[i].category, item[i].x, item[i].y);
        printf("|--------------------|-------------------|------------|\n");
    }
